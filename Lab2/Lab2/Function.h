// 8. Создать абстрактный базовый класс Function (функция) с виртуальными методами вычисления
// значения функции y = f(x) в заданной точке "x" и вывода результата на экран.
// Определить производные классы Ellipse Hyperbola c собственными функциями вычисления "y" в
// зависимости от входного параметра x.
// Уравнение эллипса: x^2/a^2 + y^2/b^2 = 1, гиперболы: x^2/a^2 - y^2/b^2 = 1.

// Эллипс: y = b * sqrt(1-x^2/a^2)
// Гипербола: y = b * sqrt(x^2/a^2 - 1)

#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <utility>
using std::string;
using std::cout;
using std::runtime_error;
using std::cin;
using std::unique_ptr;
using std::vector;
using std::make_unique;
using std::move;

void test(const string& ID) { cout << "\033[92m" "\nТест: " "\033[97m" << ID << '\n'; } // номер теста
void shift() { cout << "\n"; } // перенос

// класс Функция
class Function
{
	virtual double calculate(double x) const = 0; // вычисление значения функции
public:
	virtual void print_calculation(double x) const noexcept = 0; // вывод вычисленного результата
	virtual void input() = 0; // ввод
	virtual void print_function() const = 0; // вывод
	virtual ~Function() {} // виртуальный деструктор
};

// класс Эллипс
class Ellipse : public Function
{
    // параметры эллипса
    double a;
    double b;
	virtual double calculate(double x) const override
	{
		double value;
		try
		{
			value = 1 - pow(x, 2) / pow(a, 2);
			if (value < 0) throw runtime_error("Под корнем отрицательное значение!\n");
			return b * sqrt(value);
		}
		catch (const runtime_error& error) { cout << "\nОшибка: " << error.what() << '\n'; return 1; }
	}
public:
	// конструкторы
	Ellipse() : a(1), b(1) {}
	Ellipse(const Ellipse& t) = default;
	Ellipse(Ellipse&& t) noexcept = default;
	// операторы
	Ellipse& operator=(const Ellipse&) noexcept = default;
	Ellipse& operator=(Ellipse&&) noexcept = default;
	// методы
	virtual void print_calculation(double x) const noexcept override
	{
		cout << "Эллипс y(" << x << ") = " << this->calculate(x) << '\n';
	}
	virtual void input() override
	{
		cout << "Эллипс: ";
		try
		{
			cout << "Введите параметр 'a': ";
			cin >> a;
			cout << "Введите параметр 'b': ";
			cin >> b;
			if (a == 0 || b == 0)
			{
				a = 1;
				b = 1;
				throw runtime_error("На ноль делить нелья! Параметры возвращены к значениям по умолчанию\n\n");
			}
		}
		catch (const runtime_error& error) { cout << "\nОшибка: " << error.what(); }
	}
	virtual void print_function() const noexcept override
	{
		cout << "Эллипс: (x^2/" << pow(a, 2) << ") + (y^2/" << pow(b, 2) << ") = 1\n";
	}
	virtual ~Ellipse() { cout << "Вызван деструктор Ellipse\n"; }
};

// класс Гипербола
class Hyperbola : public Function
{
    // параметры гиперболы
    double a;
    double b;
	virtual double calculate(double x) const override // вычисление значения функции
	{
		double value;
		try
		{
			value = pow(x, 2) / pow(a, 2) - 1;
			if (value < 0) throw runtime_error("Под корнем отрицательное значение");
			return b * sqrt(value);
		}
		catch (const runtime_error& error) { cout << "\nОшибка: " << error.what() << '\n'; return 1; }
		
	}
public:
	// конструкторы
	Hyperbola(): a(1), b(1) {}
	Hyperbola(const Hyperbola& t) = default;
	Hyperbola(Hyperbola&& t) noexcept = default;
	// операторы
	Hyperbola& operator=(const Hyperbola&) noexcept = default;
	Hyperbola& operator=(Hyperbola&&) noexcept = default;
	// методы
	virtual void print_calculation(double x) const noexcept override
	{
		cout << "Гипербола y(" << x << ") = " << this->calculate(x) << '\n';
	}
	virtual void input() override
	{
		cout << "Гипербола: ";
		try
		{
			cout << "Введите параметр 'a': ";
			cin >> a;
			cout << "Введите параметр 'b': ";
			cin >> b;
			if (a == 0 || b == 0)
			{
				a = 1;
				b = 1;
				throw runtime_error("На ноль делить нелья! Параметры возвращены к значениям по умолчанию\n\n");
			}
		}
		catch (const runtime_error& error) { cout << "\nОшибка: " << error.what(); }
	}
	virtual void print_function() const noexcept override
	{
		cout << "Гипербола: (x^2/" << pow(a, 2) << ") - (y^2/" << pow(b,2) << ") = 1\n";
	}
	virtual ~Hyperbola() { cout << "Вызван деструктор Hyperbola\n"; }
};

// функция, получающая параметр базового класса по ссылке
void print_function_virtual(const Function& func) { func.print_function(); }

// векторные функции
using Functions = vector<unique_ptr<Function>>;
void vector_print_func(const Functions& functions)
{
	for (const auto& cur_func : functions)
		cur_func->print_function();
}
void vector_print_calc(const Functions& functions, double x)
{
	for (const auto& cur_func : functions)
		cur_func->print_calculation(x);
}
void vector_input(const Functions& functions)
{
	for (auto& cur_func : functions)
		cur_func->input();
}