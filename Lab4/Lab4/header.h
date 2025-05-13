// Первая часть демонстрирует использование контейнерных классов для хранения встроенных типов данных.
// Вторая часть демонстрирует использование контейнерных классов для хранения пользовательских типов данных.
// Третья часть демонстрирует использование алгоритмов STL.

#include <iostream>
#include <fstream>
#include <vector> // часть №1
#include <deque> // часть №2
#include <algorithm> // часть №3
using std::string;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::vector;
using std::deque;
using std::move;
using std::copy;
using std::sort;
using std::find_if;
using std::copy_if;
using std::merge;
using std::any_of;

void test(const string& ID) { cout << "\033[92m" "Тест: " "\033[97m" << ID << '\n'; } // номер теста

// класс Кот
class Cat
{
	string name;
	unsigned age;
public:
	// конструкторы и деструктор
	Cat() : name(""), age(0) {}
	explicit Cat(const string& n, const unsigned& a): name(n), age(a) {}
	Cat(const Cat&) = default;
	Cat(Cat&&) noexcept = default;
	~Cat() = default;
	// функции доступа к закрытым полям
	const string& GetName() const noexcept { return name; }
	const unsigned& GetAge() const noexcept { return age; }
	// операторы
	Cat& operator=(const Cat&) noexcept = default;
	Cat& operator=(Cat&&) noexcept = default;
	friend istream& operator>>(istream& input, Cat& cat)
	{
		string tempName;
		unsigned tempAge;
		input >> tempName >> tempAge;
		cat.name = tempName;
		cat.age = tempAge;
		return input;
	}
	friend ostream& operator<<(ostream& output, const Cat& cat) 
	{
		output << cat.name << " " << cat.age;
		return output;
	}
	bool operator<(const Cat& other) const { return age < other.age; }
};

// функция-предикат 1
bool isName(const Cat& cat, const string& name)
{
	return cat.GetName() == name;
}

// функция-предикат 2
bool isOlderThan(const Cat& cat, const unsigned& age) 
{
	return cat.GetAge() >= age;
}