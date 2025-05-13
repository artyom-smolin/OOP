// 8. ������� ����� ��� ������ � �������� � ������� ����, ������, �������.
// ����� ����������� ����� ������ ���� unsigned int,
// ����� ������ �������� �� ����� ���� ������� �������������: �������, ������� ���� ����, ������, �������, ��������.
// ������������� �������� : ���������� � ���������� ������� �� �������� ���������� ������, 
// ���������� � ��������� ��������� ������, �������� ��������� ����������, ���������.

#include <iostream>
#include <sstream>
#include <utility>
#include <stdexcept>
using std::cout;
using std::cin;
using std::string;
using std::stringstream; // ������ �� �������� ��� � �������� ������
using std::exchange; // ����������� ��������
using std::runtime_error; // ����� ����������, ������� ��������� �� ����� ���������� ��������� 
using std::move;

void test(string ID) { cout << "\033[92m" "����: " "\033[97m" << ID << '\n'; } // ����� �����
void shift() { cout << "\n\n"; } // �������

// ����� �����
class Time
{
	// ����
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	// �������� ����������
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
	// ������������
	Time() : hour(0), minute(0), second(0) {} // �� ���������
	explicit Time(unsigned int h, unsigned int m, unsigned int s) : hour(h), minute(m), second(s) { time_control(); } // � �����������
	Time(const Time& t) : hour(t.hour), minute(t.minute), second(t.second) {} // �����������
	Time(Time&& t) noexcept : hour(exchange(t.hour, 0)), minute(exchange(t.minute, 0)), second(exchange(t.second, 0)) {} // �����������
	~Time() = default; // ���������� �� ���������

	// ���������
	Time& operator=(const Time&) noexcept; // ����������� ������������
	Time& operator=(Time&&) noexcept; // ������������� ������������
	Time operator+(const Time&) const noexcept; // ��������
	Time operator+(unsigned int) noexcept; // �������� � ������
	Time operator-(unsigned int) noexcept; // ��������� � ������
	friend Time operator+(unsigned int, const Time&) noexcept; // �������� � ������ (� ������� ����)
	friend Time operator-(unsigned int, const Time&) noexcept; // ��������� � ������ (� ������� ����)
	
	// ���������
	bool operator==(const Time&) const noexcept;
	bool operator!=(const Time&) const noexcept;
	bool operator<(const Time&) const noexcept;
	bool operator>(const Time&) const noexcept;
	bool operator<=(const Time&) const noexcept;
	bool operator>=(const Time&) const noexcept;

	// ��������� ����� ������
	void increaseBySeconds(unsigned int); // ���������� 
	void decreaseBySeconds(unsigned int) noexcept; // ����������

	// �������������� � ������
	string toString() const noexcept;
	// ���� � ����������
	void Read() noexcept;
	// ������ �������������
	void Init(int, int, int) noexcept; // �������
	void Init(const string&) noexcept; // �������
	void Init(const Time&) noexcept;	// ��������

	// ���������� ��������� ������
	void SetHour(unsigned int h) { hour = h; }
	void SetMinute(unsigned int m) { minute = m; }
	void SetSecond(unsigned int s) { second = s; }
	// ��������� ��������� ������
	const unsigned int& GetHour() const noexcept { return hour; }
	const unsigned int& GetMinute() const noexcept { return minute; }
	const unsigned int& GetSecond() const noexcept { return second; }
};

// �������������� � ������
string Time::toString() const noexcept
{
	stringstream ss;
	ss << hour << ":" << minute << ":" << second;
	return ss.str();
}
// ���� � ����������
void Time::Read() noexcept
{
	cout << "������� ����� � ������� (��� ������ �������): ";
	cin >> hour >> minute >> second;
	time_control();
}
// ������ Init()
void Time::Init(int h, int m, int s) noexcept // ������� 
{
	if (h < 0 || m < 0 || s < 0) abort();
	hour = h;
	minute = m;
	second = s;
	this->time_control();
}
void Time::Init(const string& timeString) noexcept // �������
{
	char del;
	stringstream ss(timeString);
	ss >> hour >> del >> minute >> del >> second;
	this->time_control();
}
void Time::Init(const Time& t) noexcept // ��������
{
	hour = t.hour;
	minute = t.minute;
	second = t.second;
}
// ���������
Time& Time::operator=(const Time& t) noexcept // ����������� ������������
{
	if (this != &t)
	{
		hour = t.hour;
		minute = t.minute;
		second = t.second;
	}
	return *this;
}
Time& Time::operator=(Time&& t) noexcept // ������������� ������������
{
	if (this != &t)
	{
		hour = exchange(t.hour, 0);
		minute = exchange(t.minute, 0);
		second = exchange(t.second, 0);
	}
	return *this;
}
Time Time::operator+(const Time& t) const noexcept // ��������
{
	Time result;
	result.hour = hour + t.hour;
	result.minute = minute + t.minute;
	result.second = second + t.second;
	result.time_control();
	return result;
}
Time Time::operator+(unsigned int s) noexcept // �������� � ������ (������)
{
	Time result;
	this->increaseBySeconds(s);
	result = *this;
	result.time_control();
	return result;
}
Time Time::operator-(unsigned int s) noexcept // ��������� � ������
{
	Time result;
	this->decreaseBySeconds(s);
	result = *this;
	result.time_control();
	return result;
}
Time operator+(unsigned int s, const Time& t) noexcept // �������� � ������ (� ������� ����)
{
	Time result;
	result = t;
	result.increaseBySeconds(s);
	result.time_control();
	return result;
}
Time operator-(unsigned int s, const Time& t) noexcept // ��������� � ������ (� ������� ����)
{
	Time result;
	result = t;

	try
	{
		unsigned int totalSeconds = result.GetHour()* 3600 + result.GetMinute() * 60 + result.GetSecond(); // ����� ���������� ������
		if (totalSeconds > s)
		{
			// �������� ����������
			throw runtime_error("������ ������� ������ ������, ��� ���� � �������� �������.");
		}

		s -= totalSeconds;

		// ���������� �������
		result.SetHour(s / 3600);
		s %= 3600; // ���������� ������� ����� �����
		result.SetMinute(s / 60);
		result.SetSecond(s % 60);
	}
	catch (const runtime_error& error)
	{
		// ����� ������
		cout << " ������: " << error.what();
	}

	result.time_control();
	return result;
}
// ���������
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
// ��������� ����� ������
void Time::increaseBySeconds(unsigned int s) // ����������
{
	second += s;
	this->time_control();
}
void Time::decreaseBySeconds(unsigned int s) noexcept // ����������
{
	try
	{
		unsigned int totalSeconds = hour * 3600 + minute * 60 + second; // ����� ���������� ������
		if (s > totalSeconds)
		{
			// �������� ����������
			throw runtime_error("������ ������� ������ ������, ��� ���� � �������� �������.");
		}

		totalSeconds -= s;

		// ���������� �������
		hour = totalSeconds / 3600;
		totalSeconds %= 3600; // ���������� ������� ����� �����
		minute = totalSeconds / 60; 
		second = totalSeconds % 60; 
	}
	catch (const runtime_error& error)
	{
		// ����� ������
		cout << " ������: " << error.what();
	}
}