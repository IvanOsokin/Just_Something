#include <vector>
#include <algorithm>

void RemoveNumber(int numberToRemove)
{
	// Добавим структуру, чтобы обосновать пример использования std::remove_if вместо std::remove
	struct Data
	{
		Data() = default;
		Data(int n) : number(n) {}

		int number = 0;
	};
	std::vector<Data> v = {1, 2, 3, 1, 4, 5, 1};

	// а) давай сохранять возвращаемое значение алгоритмов и потом его использовать, касается в том числе и std::find_if и прочего
	// б) давай писать тело лямбды вот с таким видом отсупов, а не в центре экрана :)
	// в) если лямбда сложная, то стоит вынести её код в метод/функцию/переменную
	auto it = std::remove_if(v.begin(), v.end(), [numberToRemove](const Data & data)
	{
		return data.number == numberToRemove;
	});

	// Обрати внимание, что std::remove_if не удаляет элементы, а просто меняет их местами с элементами в конце, т.о. использовать элементы расположенное после 'it' некорректно.
	// И удалять следует именно диапазон элементов.
	v.erase(it, v.end());
}

int main()
{
	RemoveNumber(1);
}