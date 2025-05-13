// 8. Создать класс для работы с временем в формате «час, минута, секунда».
// Время описывается тремя полями типа unsigned int,
// класс должен включать не менне трех функций инициализации: числами, строкой вида «час, минута, секунда», временем.
// Обязательными являются : увеличение и уменьшение времени на заданное количество секунд, 
// присвоение и получение отдельных частей, сложение временных интервалов, сравнение.

#include <iostream>
#include <sstream>
#include <utility>
#include <stdexcept>
using std::cout;
using std::cin;
using std::string;
using std::stringstream; // работа со строками как с потоками данных
using std::exchange; // перемещение значений
using std::runtime_error; // класс исключений, которые возникают во время выполнения программы 
using std::move;

void test(string ID) { cout << "\033[92m" "Тест: " "\033[97m" << ID << '\n'; } // номер теста
void shift() { cout << "\n\n"; } // перенос

// класс Время
class Time
{
	// поля
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	// контроль диапазонов
	void time_control()
	{
		if (second >= 60)
		{
			minute += second / 60;
			second %= 60;
		}
		if (minute >= 60)
		{
			hour += minute / 60;
			minute %= 60;
		}
	}
public:
	// конструкторы
	Time() : hour(0), minute(0), second(0) {} // по умолчанию
	explicit Time(unsigned int h, unsigned int m, unsigned int s) : hour(h), minute(m), second(s) { time_control(); } // с параметрами
	Time(const Time& t) : hour(t.hour), minute(t.minute), second(t.second) {} // копирования
	Time(Time&& t) noexcept : hour(exchange(t.hour, 0)), minute(exchange(t.minute, 0)), second(exchange(t.second, 0)) {} // перемещения
	~Time() = default; // деструктор по умолчанию

	// операторы
	Time& operator=(const Time&) noexcept; // копирующего присваивания
	Time& operator=(Time&&) noexcept; // перемещающего присваивания
	Time operator+(const Time&) const noexcept; // сложения
	Time operator+(unsigned int) noexcept; // сложения с числом
	Time operator-(unsigned int) noexcept; // вычитания с числом
	friend Time operator+(unsigned int, const Time&) noexcept; // сложения с числом (с заменой мест)
	friend Time operator-(unsigned int, const Time&) noexcept; // вычитания с числом (с заменой мест)
	
	// сравнения
	bool operator==(const Time&) const noexcept;
	bool operator!=(const Time&) const noexcept;
	bool operator<(const Time&) const noexcept;
	bool operator>(const Time&) const noexcept;
	bool operator<=(const Time&) const noexcept;
	bool operator>=(const Time&) const noexcept;

	// изменение числа секунд
	void increaseBySeconds(unsigned int); // увеличение 
	void decreaseBySeconds(unsigned int) noexcept; // уменьшение

	// преобразование в строку
	string toString() const noexcept;
	// ввод с клавиатуры
	void Read() noexcept;
	// методы инициализации
	void Init(int, int, int) noexcept; // числами
	void Init(const string&) noexcept; // строкой
	void Init(const Time&) noexcept;	// временем

	// присвоение отдельных частей
	void SetHour(unsigned int h) { hour = h; }
	void SetMinute(unsigned int m) { minute = m; }
	void SetSecond(unsigned int s) { second = s; }
	// получение отдельных частей
	const unsigned int& GetHour() const noexcept { return hour; }
	const unsigned int& GetMinute() const noexcept { return minute; }
	const unsigned int& GetSecond() const noexcept { return second; }
};

// преобразование в строку
string Time::toString() const noexcept
{
	stringstream ss;
	ss << hour << ":" << minute << ":" << second;
	return ss.str();
}
// ввод с клавиатуры
void Time::Read() noexcept
{
	cout << "Введите время в формате (час минута секунда): ";
	cin >> hour >> minute >> second;
	time_control();
}
// методы Init()
void Time::Init(int h, int m, int s) noexcept // числами 
{
	if (h < 0 || m < 0 || s < 0) abort();
	hour = h;
	minute = m;
	second = s;
	this->time_control();
}
void Time::Init(const string& timeString) noexcept // строкой
{
	char del;
	stringstream ss(timeString);
	ss >> hour >> del >> minute >> del >> second;
	this->time_control();
}
void Time::Init(const Time& t) noexcept // временем
{
	hour = t.hour;
	minute = t.minute;
	second = t.second;
}
// операторы
Time& Time::operator=(const Time& t) noexcept // копирующего присваивания
{
	if (this != &t)
	{
		hour = t.hour;
		minute = t.minute;
		second = t.second;
	}
	return *this;
}
Time& Time::operator=(Time&& t) noexcept // перемещающего присваивания
{
	if (this != &t)
	{
		hour = exchange(t.hour, 0);
		minute = exchange(t.minute, 0);
		second = exchange(t.second, 0);
	}
	return *this;
}
Time Time::operator+(const Time& t) const noexcept // сложения
{
	Time result;
	result.hour = hour + t.hour;
	result.minute = minute + t.minute;
	result.second = second + t.second;
	result.time_control();
	return result;
}
Time Time::operator+(unsigned int s) noexcept // сложения с числом (секунд)
{
	Time result;
	this->increaseBySeconds(s);
	result = *this;
	result.time_control();
	return result;
}
Time Time::operator-(unsigned int s) noexcept // вычитания с числом
{
	Time result;
	this->decreaseBySeconds(s);
	result = *this;
	result.time_control();
	return result;
}
Time operator+(unsigned int s, const Time& t) noexcept // сложения с числом (с заменой мест)
{
	Time result;
	result = t;
	result.increaseBySeconds(s);
	result.time_control();
	return result;
}
Time operator-(unsigned int s, const Time& t) noexcept // вычитания с числом (с заменой мест)
{
	Time result;
	result = t;

	try
	{
		unsigned int totalSeconds = result.GetHour()* 3600 + result.GetMinute() * 60 + result.GetSecond(); // общее количество секунд
		if (totalSeconds > s)
		{
			// создание исключения
			throw runtime_error("Нельзя вычесть больше секунд, чем есть в исходном времени.");
		}

		s -= totalSeconds;

		// обновление времени
		result.SetHour(s / 3600);
		s %= 3600; // оставшиеся секунды после часов
		result.SetMinute(s / 60);
		result.SetSecond(s % 60);
	}
	catch (const runtime_error& error)
	{
		// вывод ошибки
		cout << " Ошибка: " << error.what();
	}

	result.time_control();
	return result;
}
// сравнения
bool Time::operator==(const Time& t) const noexcept
{
	return hour == t.hour && minute == t.minute && second == t.second;
}
bool Time::operator!=(const Time & t) const noexcept
{
	return !(*this == t);
}
bool Time::operator<(const Time& t) const noexcept
{
	return hour < t.hour || (hour == t.hour && (minute < t.minute || (minute == t.minute && second < t.second)));
}
bool Time::operator>(const Time& t) const noexcept
{
	return hour > t.hour || (hour == t.hour && (minute > t.minute || (minute == t.minute && second > t.second)));
}
bool Time::operator<=(const Time& t) const noexcept
{
	return !(*this > t);
}
bool Time::operator>=(const Time& t) const noexcept
{
	return !(*this < t);
}
// изменение числа секунд
void Time::increaseBySeconds(unsigned int s) // увеличение
{
	second += s;
	this->time_control();
}
void Time::decreaseBySeconds(unsigned int s) noexcept // уменьшение
{
	try
	{
		unsigned int totalSeconds = hour * 3600 + minute * 60 + second; // общее количество секунд
		if (s > totalSeconds)
		{
			// создание исключения
			throw runtime_error("Нельзя вычесть больше секунд, чем есть в исходном времени.");
		}

		totalSeconds -= s;

		// обновление времени
		hour = totalSeconds / 3600;
		totalSeconds %= 3600; // оставшиеся секунды после часов
		minute = totalSeconds / 60; 
		second = totalSeconds % 60; 
	}
	catch (const runtime_error& error)
	{
		// вывод ошибки
		cout << " Ошибка: " << error.what();
	}
}