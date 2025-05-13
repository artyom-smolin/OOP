// Требуется создать целевой шаблонный класс А с помощью серверного класса В.
//Показать инстанцирование шаблона для типов int, double и std::string.
//		Целевой шаблонный класс		Реализация с применением
//8.	Set(множество)				Vect

#include <iostream>
#include <stdexcept>
#include <algorithm>
using std::cout;
using std::cin;
using std::runtime_error;
using std::string;
using std::out_of_range;
using std::ostream;
using std::move;
using std::swap;
using std::copy;

void test(string ID) { cout << "\033[92m" "Тест: " "\033[97m" << ID << '\n'; } // номер теста
void shift() { cout << "\n\n"; } // перенос

// серверный класс Вектор
template<typename T>
class Vect 
{
	// размер, ёмкость и массив данных
	size_t size;
	size_t capacity;
	T* data;
public:
	// ctor's и dctor
	Vect() : data(nullptr), size(0), capacity(0) {}
	explicit Vect(size_t count) : size(count), capacity(count) {
		data = new T[count];
		for (size_t i = 0; i < size; ++i)
			data[i] = T();
	}
	~Vect() { delete[]data; data = nullptr; }
	// функции vector
	void push_back(const T& value)
	{
		if (size == capacity)
		{
			capacity = (capacity == 0) ? 1 : 2 * capacity;
			T* new_data = new T[capacity];
			copy(data, data + size, new_data);
			swap(data, new_data); // обмен адресами
			delete[]new_data;
		}
		data[size++] = value;
	}
	void pop_back()
	{
		try
		{
			if (empty())
				throw runtime_error("\nУдаление последнего элемента в пустом векторе!\n");
			data[size - 1].~T();
			size--;
		}
		catch (const runtime_error& error) { cout << error.what(); }
	}
	void clear()
	{
		for (size_t i = 0; i < size; ++i)
			data[i].~T();
		size = 0;
	}
	void erase(size_t pos)
	{
		try
		{
			if (pos >= size || pos < 0)
				throw out_of_range("\nВыход за диапазон при удалении!\n");
			for (size_t i = pos; i < size - 1; ++i)
			{
				data[i] = move(data[i + 1]); // смещение
			}
			data[size - 1].~T();
			--size;
		}
		catch (const out_of_range& error) { cout << error.what(); }
	}
	void reserve(size_t new_capacity)
	{
		if (new_capacity > capacity)
		{
			capacity = new_capacity;
			T* new_data = new T[capacity];
			copy(data, data + size, new_data);
			swap(data, new_data); // обмен адресами
			delete[]new_data;
		}
	}
	void resize(size_t new_size)
	{
		if (new_size > size)
		{
			reserve(new_size);
			for (size_t i = size; i < new_size; ++i)
				data[i] = T(); // добавление новых элементов
		}
		else if (new_size < size)
		{
			for (size_t i = new_size; i < size; ++i)
				data[i].~T(); // удаление лишних элементов
		}
		size = new_size;
	}
	T& operator[](size_t pos)
	{
		return data[pos];
	}
	const T& operator[](size_t pos) const
	{
		return data[pos];
	}
	const T& back() const
	{
		try
		{
			if (empty())
				throw runtime_error("\nОбращение к последнему элементу пустого вектора! Возвращено значение по умолчанию: ");
			return data[size - 1];
		}
		catch (const runtime_error& error) { cout << error.what(); return T(); }
	}
	T& at(size_t pos)
	{
		try
		{
			if (pos < 0 || pos >= size)
				throw out_of_range("\nВыход за диапазон при вызове at()! Возвращено значение по умолчанию: ");
			return data[pos];
		}
		catch (const out_of_range& error) { cout << error.what(); return T(); }
	}
	const T& at(size_t pos) const
	{
		try
		{
			if (pos < 0 || pos >= size)
				throw out_of_range("\nВыход за диапазон при вызове at()! Возвращено значение по умолчанию: ");
			return data[pos];
		}
		catch (const out_of_range& error) { cout << error.what(); return T(); }
	}
	const size_t& get_size() const noexcept
	{
		return size;
	}
	const size_t& get_capacity() const noexcept
	{
		return capacity;
	}
	constexpr bool empty() const noexcept
	{
		return size == 0;
	}
	// дополнительно
	void sort() noexcept
	{
		std::sort(data, data + size);
	}
};

// целевой класс Множество
template<typename T>
class Set
{
	Vect<T> elements;
public:
	// ctor и dctor
	Set() = default;
	~Set() = default;
	// функции set
	const size_t& size() const noexcept
	{
		return elements.get_size();
	}
	bool contains(const T& value) const noexcept
	{
		size_t left = 0;
		size_t right = size();
		size_t mid;
		while (left < right)
		{
			mid = left + (right - left) / 2;
			if (elements[mid] == value)
				return true;
			else if (elements[mid] < value)
				left = mid + 1;
			else
				right = mid;
		}
		return false;
	}
	void insert(const T& value) noexcept
	{
		if (!contains(value))
		{
			elements.push_back(value);
			elements.sort();
		}
	}
	constexpr bool empty() const noexcept
	{
		return elements.get_size() == 0;
	}
	void clear() noexcept
	{
		elements.clear();
	}
	void erase(size_t pos) noexcept
	{
		elements.erase(pos);
	}
	int find(const T& value) const noexcept
	{
		size_t left = 0;
		size_t right = size() - 1;
		size_t mid;
		while (left < right)
		{
			mid = left + (right - left) / 2;
			if (elements[mid] == value)
				return mid;
			else if (elements[mid] < value)
				left = mid + 1;
			else
				right = mid;
		}
		return -1;
	}
	size_t lower_bound(const T& value) // >= value
	{
		size_t left = 0;
		size_t right = size() - 1;
		size_t mid;
		while (left < right)
		{
			mid = left + (right - left) / 2;
			if (elements[mid] < value)
				left = mid + 1;
			else
				right = mid;
		}
		return left;
	}

	size_t upper_bound(const T& value) // > value
	{
		size_t left = 0;
		size_t right = size() - 1;
		size_t mid;
		while (left < right)
		{
			mid = left + (right - left) / 2;
			if (elements[mid] <= value)
				left = mid + 1;
			else
				right = mid;
		}
		return left;
	}
	// дополнительно
	friend ostream& operator<<(ostream& output, const Set<T>& set)
	{
		output << "Множество: ";
		for (size_t i = 0; i < set.elements.get_size(); ++i)
		{
			if (i != set.elements.get_size() - 1)
				output << set.elements[i] << " ";
			else
				output << set.elements[i];
		}
		return output;
	}
};