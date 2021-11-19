#include <vector>
#include <algorithm>

void RemoveNumber(int numberToRemove)
{
	// ������� ���������, ����� ���������� ������ ������������� std::remove_if ������ std::remove
	struct Data
	{
		Data() = default;
		Data(int n) : number(n) {}

		int number = 0;
	};
	std::vector<Data> v = {1, 2, 3, 1, 4, 5, 1};

	// �) ����� ��������� ������������ �������� ���������� � ����� ��� ������������, �������� � ��� ����� � std::find_if � �������
	// �) ����� ������ ���� ������ ��� � ����� ����� �������, � �� � ������ ������ :)
	// �) ���� ������ �������, �� ����� ������� � ��� � �����/�������/����������
	auto it = std::remove_if(v.begin(), v.end(), [numberToRemove](const Data & data)
	{
		return data.number == numberToRemove;
	});

	// ������ ��������, ��� std::remove_if �� ������� ��������, � ������ ������ �� ������� � ���������� � �����, �.�. ������������ �������� ������������� ����� 'it' �����������.
	// � ������� ������� ������ �������� ���������.
	v.erase(it, v.end());
}

int main()
{
	RemoveNumber(1);
}