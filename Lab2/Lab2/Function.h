// 8. ������� ����������� ������� ����� Function (�������) � ������������ �������� ����������
// �������� ������� y = f(x) � �������� ����� "x" � ������ ���������� �� �����.
// ���������� ����������� ������ Ellipse Hyperbola c ������������ ��������� ���������� "y" �
// ����������� �� �������� ��������� x.
// ��������� �������: x^2/a^2 + y^2/b^2 = 1, ���������: x^2/a^2 - y^2/b^2 = 1.

// ������: y = b * sqrt(1-x^2/a^2)
// ���������: y = b * sqrt(x^2/a^2 - 1)

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

void test(const string& ID) { cout << "\033[92m" "\n����: " "\033[97m" << ID << '\n'; } // ����� �����
void shift() { cout << "\n"; } // �������

// ����� �������
class Function
{
	virtual double calculate(double x) const = 0; // ���������� �������� �������
public:
	virtual void print_calculation(double x) const noexcept = 0; // ����� ������������ ����������
	virtual void input() = 0; // ����
	virtual void print_function() const = 0; // �����
	virtual ~Function() {} // ����������� ����������
};

// ����� ������
class Ellipse : public Function
{
    // ��������� �������
    double a;
    double b;
	virtual double calculate(double x) const override
	{
		double value;
		try
		{
			value = 1 - pow(x, 2) / pow(a, 2);
			if (value < 0) throw runtime_error("��� ������ ������������� ��������!\n");
			return b * sqrt(value);
		}
		catch (const runtime_error& error) { cout << "\n������: " << error.what() << '\n'; return 1; }
	}
public:
	// ������������
	Ellipse() : a(1), b(1) {}
	Ellipse(const Ellipse& t) = default;
	Ellipse(Ellipse&& t) noexcept = default;
	// ���������
	Ellipse& operator=(const Ellipse&) noexcept = default;
	Ellipse& operator=(Ellipse&&) noexcept = default;
	// ������
	virtual void print_calculation(double x) const noexcept override
	{
		cout << "������ y(" << x << ") = " << this->calculate(x) << '\n';
	}
	virtual void input() override
	{
		cout << "������: ";
		try
		{
			cout << "������� �������� 'a': ";
			cin >> a;
			cout << "������� �������� 'b': ";
			cin >> b;
			if (a == 0 || b == 0)
			{
				a = 1;
				b = 1;
				throw runtime_error("�� ���� ������ �����! ��������� ���������� � ��������� �� ���������\n\n");
			}
		}
		catch (const runtime_error& error) { cout << "\n������: " << error.what(); }
	}
	virtual void print_function() const noexcept override
	{
		cout << "������: (x^2/" << pow(a, 2) << ") + (y^2/" << pow(b, 2) << ") = 1\n";
	}
	virtual ~Ellipse() { cout << "������ ���������� Ellipse\n"; }
};

// ����� ���������
class Hyperbola : public Function
{
    // ��������� ���������
    double a;
    double b;
	virtual double calculate(double x) const override // ���������� �������� �������
	{
		double value;
		try
		{
			value = pow(x, 2) / pow(a, 2) - 1;
			if (value < 0) throw runtime_error("��� ������ ������������� ��������");
			return b * sqrt(value);
		}
		catch (const runtime_error& error) { cout << "\n������: " << error.what() << '\n'; return 1; }
		
	}
public:
	// ������������
	Hyperbola(): a(1), b(1) {}
	Hyperbola(const Hyperbola& t) = default;
	Hyperbola(Hyperbola&& t) noexcept = default;
	// ���������
	Hyperbola& operator=(const Hyperbola&) noexcept = default;
	Hyperbola& operator=(Hyperbola&&) noexcept = default;
	// ������
	virtual void print_calculation(double x) const noexcept override
	{
		cout << "��������� y(" << x << ") = " << this->calculate(x) << '\n';
	}
	virtual void input() override
	{
		cout << "���������: ";
		try
		{
			cout << "������� �������� 'a': ";
			cin >> a;
			cout << "������� �������� 'b': ";
			cin >> b;
			if (a == 0 || b == 0)
			{
				a = 1;
				b = 1;
				throw runtime_error("�� ���� ������ �����! ��������� ���������� � ��������� �� ���������\n\n");
			}
		}
		catch (const runtime_error& error) { cout << "\n������: " << error.what(); }
	}
	virtual void print_function() const noexcept override
	{
		cout << "���������: (x^2/" << pow(a, 2) << ") - (y^2/" << pow(b,2) << ") = 1\n";
	}
	virtual ~Hyperbola() { cout << "������ ���������� Hyperbola\n"; }
};

// �������, ���������� �������� �������� ������ �� ������
void print_function_virtual(const Function& func) { func.print_function(); }

// ��������� �������
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