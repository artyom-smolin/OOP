#include "Containers.h"

int main()
{
	setlocale(LC_ALL, "rus");

	{
		test("Set<int>");
		Set<int> set;
		cout << set << '\n';
		cout << "Размер: " << set.size() << '\n';
		cout << "Пуст: " << set.empty() << '\n';
		set.insert(1);
		set.insert(356);
		set.insert(234);
		set.insert(1);
		set.insert(-710);
		cout << set << '\n';
		cout << "Размер: " << set.size() << '\n';
		cout << "Пуст: " << set.empty() << '\n';
		cout << "Содержит 356: " << set.contains(356) << '\n';
		cout << "Содержит 2: " << set.contains(2) << '\n';
		cout << "Индекс первого элемента, который >= 11: " << set.lower_bound(11) << '\n';
		cout << "Индекс первого элемента, который > 0: " << set.upper_bound(0) << '\n';
		set.erase(0); // удаление первого элемента
		cout << set << '\n';
		cout << "Индекс элемента 234: " << set.find(234) << '\n';
		cout << "Индекс элемента 5: " << set.find(5) << '\n'; // вернёт -1
		set.clear();
		cout << set;
		shift();
	}
	{
		test("Set<double>");
		Set<double> set;
		cout << set << '\n';
		cout << "Размер: " << set.size() << '\n';
		cout << "Пуст: " << set.empty() << '\n';
		set.insert(-543.4);
		set.insert(2.1);
		set.insert(64.64);
		set.insert(2.1);
		set.insert(6.42);
		cout << set << '\n';
		cout << "Размер: " << set.size() << '\n';
		cout << "Пуст: " << set.empty() << '\n';
		cout << "Содержит 1.5: " << set.contains(1.5) << '\n';
		cout << "Содержит 64.64: " << set.contains(64.64) << '\n';
		cout << "Индекс первого элемента, который >= 0.5: " << set.lower_bound(0.5) << '\n';
		cout << "Индекс первого элемента, который > 50.4: " << set.upper_bound(50.4) << '\n';
		set.erase(1); // удаление второго элемента
		cout << set << '\n';
		cout << "Индекс элемента -543.4: " << set.find(-543.4) << '\n';
		cout << "Индекс элемента 0.1: " << set.find(0.1) << '\n'; // вернёт -1
		set.clear();
		cout << set;
		shift();
	}
	{
		test("Set<string>");
		Set<string> set;
		cout << set << '\n';
		cout << "Размер: " << set.size() << '\n';
		cout << "Пуст: " << set.empty() << '\n';
		set.insert("a");
		set.insert("bj");
		set.insert("a");
		set.insert("it");
		set.insert("hg");
		cout << set << '\n';
		cout << "Размер: " << set.size() << '\n';
		cout << "Пуст: " << set.empty() << '\n';
		cout << "Содержит abc: " << set.contains("abc") << '\n';
		cout << "Содержит g: " << set.contains("g") << '\n';
		cout << "Индекс первого элемента, который >= a: " << set.lower_bound("a") << '\n';
		cout << "Индекс первого элемента, который > a: " << set.upper_bound("a") << '\n';
		set.erase(0); // удаление первого элемента
		cout << set << '\n';
		cout << "Индекс элемента it: " << set.find("it") << '\n';
		cout << "Индекс элемента bc: " << set.find("bc") << '\n'; // вернёт -1
		set.clear();
		cout << set;
		shift();
	}

	return 0;
}