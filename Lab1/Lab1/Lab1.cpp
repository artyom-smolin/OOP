#include "Time.h"

int main()
{
	setlocale(LC_ALL, "rus");
	
	{
		test("Конструктор по умолчанию && toString()");
		Time A;
		cout << "A: " << A.toString();
		shift();
	}
	{
		test("Конструктор с параметрами");
		Time A(10, 3, 61);
		cout << "A: " << A.toString();
		shift();
	}
	{
		test("Конструктор копирования && оператор копирующего присваивания");
		Time A(10, 3, 34);
		Time B(A); // вызов конструктора копирования
		Time C;
		C = B; // вызов оператора копирующего присваивания
		cout << "Время A: " << A.toString();
		cout << "\nВремя B: " << B.toString();
		cout << "\nВремя C: " << C.toString();
		shift();
	}
	{
		test("Ввод с клавиатуры Read()");
		Time A;
		A.Read();
		cout << "A: " << A.toString();
		shift();
	}
	{
		test("Конструктор перемещения && оператор перемещающего присваивания");
		Time A(10, 3, 34);
		cout << "A: " << A.toString();
		Time B(move(A)); // вызов конструктора перемещения
		cout << "\n\nA modified: " << A.toString();
		Time C;
		cout << "\nB: " << B.toString();
		C = move(B); // вызов оператора перемещающего присваивания
		cout << "\n\nB modified: " << B.toString();
		cout << "\nC: " << C.toString();
		shift();
	}
	{
		test("Присвоение && получение отдельных частей");
		Time A(10, 3, 34);
		cout << "A: " << A.GetHour() << ":" << A.GetMinute() << ":" << A.GetSecond() << '\n';
		A.SetHour(20);
		A.SetMinute(45);
		A.SetSecond(15);
		cout << "A modified: " << A.toString();
		shift();
	}
	{
		test("Функции инициализации Init()");
		Time A;
		A.Init(10, 3, 34); // числами
		cout << "A: " << A.toString();

		Time B;
		B.Init("11,22,33"); // строкой
		cout << "\nB: " << B.toString();

		Time C;
		C.Init(B); // временем
		cout << "\nC: " << C.toString();
		shift();
	}
	{
		test("Увеличение && уменьшение времени на заданное количество секунд");
		Time A(0, 0, 4);
		cout << "A: " << A.toString();
		A.increaseBySeconds(3); // увеличение на 3 секунды
		cout << "\nA modified: " << A.toString();

		Time B(12, 0, 0);
		cout << "\nB: " << B.toString();
		B.decreaseBySeconds(1); // уменьшение на 1 секунду
		cout << "\nB modified: " << B.toString();
		shift();
	}
	{
		test("Операторы сравнения");
		Time A(10, 30, 40);
		Time B(9, 45, 20);
		cout << "A: " << A.toString();
		cout << "\nB: " << B.toString();
		cout << "\nA == B: " << (A == B ? "правда" : "ложь");
		cout << "\nA != B: " << (A != B ? "правда" : "ложь");
		cout << "\nA < B: " << (A < B ? "правда" : "ложь");
		cout << "\nA > B: " << (A > B ? "правда" : "ложь");
		cout << "\nA <= B: " << (A <= B ? "правда" : "ложь");
		cout << "\nA >= B: " << (A >= B ? "правда" : "ложь");
		shift();
	}
	{
		test("Сложение временных интервалов");
		Time A(10, 30, 40);
		Time B(0, 45, 35);
		Time C = A + B;
		cout << "A: " << A.toString();
		cout << "\nB: " << B.toString();
		cout << "\nСумма: " << C.toString();
		shift();
	}
	{
		test("Увеличение && уменьшение времени на заданное количество секунд (через операторы)");
		Time A(0, 0, 1);
		cout << "A: " << A.toString();
		A = A + 1;
		cout << "\nA modified: " << A.toString();
		A = 1 + A;
		cout << "\nA modified: " << A.toString();
		A = A - 1;
		cout << "\nA modified: " << A.toString();
		A = 5 - A;
		cout << "\nA modified: " << A.toString();
		shift();
	}

	return 0;
}