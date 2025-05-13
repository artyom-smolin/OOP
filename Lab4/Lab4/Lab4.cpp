#include "header.h"

int main()
{
	setlocale(LC_ALL, "rus");

	{
		test("Часть 1");

		// Создать объект-контейнер и заполнить его данными.
		vector<int> vector_first{ 0,1,2,3,4,5,6,7,8,9 };

		// Просмотреть контейнер.
		cout << "vector_first: ";
		for (const auto& element : vector_first)
			cout << element << " ";
		cout << '\n';

		// Изменить контейнер, удалив из него одни элементы и заменив другие.
		vector_first.pop_back();
		vector_first.erase(vector_first.begin());
		vector_first.at(4) = 2;
		vector_first[2] = 3463;

		// Просмотреть контейнер, используя для доступа к его элементам итераторы.
		cout << "vector_first: ";
		for (auto it = vector_first.begin(); it != vector_first.end(); ++it)
			cout << *it << " ";
		cout << '\n';

		// Создать второй контейнер этого же класса и заполнить его данными того же типа, что и первый контейнер.
		vector<int> vector_second{ 10,20,30,40,50 };

		// Изменить первый контейнер, удалив из него n элементов после заданного и добавив затем в него все элементы из второго контейнера.
		int n = 2;
		vector_first.erase(vector_first.begin() + 1, vector_first.begin() + 1 + n); // удалится два элемента начиная со второго
		for (auto it = vector_second.begin(); it != vector_second.end(); ++it)
			vector_first.insert(vector_first.begin() + 1, move(*it));
		vector_second.clear();

		// Просмотреть первый и второй контейнеры.
		cout << "vector_second: ";
		for (auto it = vector_second.begin(); it != vector_second.end(); ++it)
			cout << *it << " ";
		cout << '\n';
		cout << "vector_first: ";
		for (const auto& element : vector_first)
			cout << element << " ";
		cout << "\n\n";
	}
	{
		test("Часть 2");

		// Создаем объект-контейнер и заполняем его данными.
		deque<Cat> deque_first;
		ifstream input_file;
		input_file.open("Cats_first.txt");
		if (!input_file.is_open())
		{
			cout << "Не удалось открыть файл для чтения\n";
			return 1;
		}
		Cat cat_first;
		while (input_file >> cat_first)
			deque_first.push_back(cat_first);
		input_file.close();

		// Просматриваем контейнер.
		cout << "deque_first: ";
		for (const auto& cat : deque_first)
			cout << cat << " ";
		cout << '\n';

		// Изменяем контейнер, удаляя из него одни элементы и заменяя другие.
		deque_first.pop_front();
		deque_first.erase(deque_first.begin() + 1); // удаление второго элемента
		deque_first.at(1) = Cat("new_Cat_one", 3);
		deque_first[0] = Cat("new_Cat_two", 6);

		// Просматриваем контейнер.
		cout << "deque_first: ";
		for (const auto& cat : deque_first)
			cout << cat << " ";
		cout << '\n';

		// Создаем второй контейнер этого же класса и заполняем его данными того же типа, что и первый контейнер.
		deque<Cat> deque_second;
		input_file.open("Cats_second.txt");
		if (!input_file.is_open())
		{
			cout << "Не удалось открыть файл для чтения\n";
			return 1;
		}
		Cat cat_second;
		while (input_file >> cat_second)
			deque_second.push_back(cat_second);
		input_file.close();

		// Изменяем первый контейнер, удаляя из него n элементов после заданного и добавляя затем в него все элементы из второго контейнера.
		int n = 1;
		deque_first.erase(deque_first.begin() + 1, deque_first.begin() + 1 + n); // удалится второй элемент
		copy(deque_second.begin(), deque_second.end(), back_inserter(deque_first));

		// Просматриваем первый и второй контейнеры.
		cout << "deque_second: ";
		for (auto it = deque_second.begin(); it != deque_second.end(); ++it)
			cout << *it << " ";
		cout << '\n';
		cout << "deque_first: ";
		for (const auto& cat : deque_first)
			cout << cat << " ";

		// Файлы с обновлённым содержимым
		ofstream output_file_first("Cats_first_updated.txt");
		if (!output_file_first.is_open()) 
		{
			cout << "Не удалось открыть файл для записи\n";
			return 1;
		}
		for (const auto& cat : deque_first)
			output_file_first << cat << '\n';
		output_file_first.close();

		ofstream output_file_second("Cats_second_updated.txt");
		if (!output_file_second.is_open()) 
		{
			cout << "Не удалось открыть файл для записи\n";
			return 1;
		}
		for (const auto& cat : deque_second)
			output_file_second << cat << '\n';
		output_file_second.close();
		cout << "\n\n";
	}
	{
		test("Часть 3");

		// Создать контейнер, содержащий объекты пользовательского типа.
		vector<Cat> vector_first;
		vector_first.push_back(Cat("Marsik", 18));
		vector_first.push_back(Cat("Barsik", 5));
		vector_first.push_back(Cat("Felix", 1));
		vector_first.push_back(Cat("Alex", 3));
		vector_first.push_back(Cat("Simon", 10));

		// Отсортировать его по убыванию элементов.
		auto comp = [](const Cat& a, const Cat& b) { return a.GetAge() > b.GetAge(); };
		sort(vector_first.begin(), vector_first.end(), comp);

		// Просмотреть контейнер.
		cout << "vector_first: ";
		for (const auto& cat : vector_first)
			cout << cat << " ";
		cout << '\n';

		// Используя подходящий алгоритм, найти в контейнере элемент, удовлетворяющий заданному условию.
		auto found_codition = find_if(vector_first.begin(), vector_first.end(), [](const Cat& cat)
			{
				return isName(cat, "Marsik");
			});
		if (found_codition != vector_first.end())
			cout << "Найденный кот: " << *found_codition << '\n';
		else
			cout << "Кот не найден" << '\n';

		// Переместить элементы, удовлетворяющие заданному условию в другой (предварительно пустой) контейнер.
		vector<Cat> vector_second;
		copy_if(vector_first.begin(), vector_first.end(), back_inserter(vector_second), [](const Cat& cat)
			{
				return isOlderThan(cat, 5);
			});

		// Просмотреть второй контейнер.
		cout << "vector_second: ";
		for (const auto& cat : vector_second)
			cout << cat << " ";
		cout << '\n';

		// Отсортировать первый и второй контейнеры по возрастанию элементов.
		sort(vector_first.begin(), vector_first.end());
		sort(vector_second.begin(), vector_second.end());

		// Просмотреть их.
		cout << "vector_first: ";
		for (const auto& cat : vector_first)
			cout << cat << " ";
		cout << '\n';
		cout << "vector_second: ";
		for (const auto& cat : vector_second)
			cout << cat << " ";
		cout << '\n';
		
		// Получить третий контейнер путём слияния первых двух.
		vector<Cat> vector_third(vector_first.size() + vector_second.size());
		merge(vector_first.begin(), vector_first.end(), vector_second.begin(), vector_second.end(), vector_third.begin());

		// Просмотреть третий контейнер
		cout << "vector_third: ";
		for (const auto& cat : vector_third)
			cout << cat << " ";
		cout << '\n';

		// Подсчитать, сколько элементов, удовлетворяющих заданному условию, содержит третий контейнер.
		auto count_condition = count_if(vector_third.begin(), vector_third.end(), [](const Cat& cat)
			{
				return isOlderThan(cat, 5);
			});
		cout << "Число котов, удовлетворяющих условию: " << count_condition << '\n';
		
		// Определить, есть ли в третьем контейнере элемент, удовлетворяющий заданному условию.
		auto check_condition = any_of(vector_third.begin(), vector_third.end(), [](const Cat& cat)
			{
				return isName(cat, "Max");
			});
		if (check_condition)
			cout << "Кот с заданным именем есть.";
		else
			cout << "Кот с заданным именем отсутствует.";
		cout << '\n';
	}

	return 0;
}