#include "Function.h"

int main()
{
	setlocale(LC_ALL, "rus");

	{
		test("Эллипс");
		unique_ptr<Ellipse> smart_Ellipse = make_unique<Ellipse>();
		smart_Ellipse->print_function();
		smart_Ellipse->input();
		smart_Ellipse->print_function();
		smart_Ellipse->print_calculation(1);
		shift();
	}
	{
		test("Гипербола");
		unique_ptr<Hyperbola> smart_Hyperbola = make_unique<Hyperbola>();
		smart_Hyperbola->print_function();
		smart_Hyperbola->input();
		smart_Hyperbola->print_function();
		smart_Hyperbola->print_calculation(1);
		shift();
	}
	{
		test("Функция вывода, демонстрирующая виртуальный вызов");
		unique_ptr<Ellipse> smart_Ellipse = make_unique<Ellipse>();
		unique_ptr<Hyperbola> smart_Hyperbola = make_unique<Hyperbola>();
		print_function_virtual(*smart_Ellipse);
		print_function_virtual(*smart_Hyperbola);
		shift();
	}
	{
		test("Вектор функций");
		unique_ptr<Ellipse> smart_Ellipse = make_unique<Ellipse>();
		unique_ptr<Hyperbola> smart_Hyperbola = make_unique<Hyperbola>();
		Functions functions;
		functions.emplace_back(move(smart_Ellipse)); // передаётся владение над объектом в вектор (копирование запрещено = может быть только один объект unique_ptr, который содержит один и тот же адрес)
		functions.emplace_back(move(smart_Hyperbola));
		vector_print_func(functions);
		vector_print_calc(functions, 1);
		vector_input(functions);
		vector_print_func(functions);
		vector_print_calc(functions, 1);
		shift();
	}
	{
		test("Варианты вызова виртуальных функций с помощью указателя на базовый класс");
		unique_ptr<Ellipse> smart_Ellipse = make_unique<Ellipse>();
		unique_ptr<Hyperbola> smart_Hyperbola = make_unique<Hyperbola>();
		unique_ptr<Function> base_ptr; // указатель на базовый класс
		base_ptr = move(smart_Ellipse); // указатель на базовый класс теперь владеет адресом, принадлежавшим smart_Ellipse
		base_ptr->print_function();
		base_ptr->print_calculation(1);
		base_ptr->input();
		base_ptr->print_function();
		base_ptr->print_calculation(1);
		base_ptr = move(smart_Hyperbola); // указатель на базовый класс теперь владеет адресом, принадлежавшим smart_Hyperbola
		base_ptr->print_function();
		base_ptr->print_calculation(1);
		base_ptr->input();
		base_ptr->print_function();
		base_ptr->print_calculation(1);
		shift();
	}

	return 0;
}