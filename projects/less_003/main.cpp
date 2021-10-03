#include <iostream>
#include <memory>

////////////////////////////////////unique_ptr//////////////////////////////////////////////////////////////////////////

//Измените следующую программу, заменив обычный указатель
//на умный указатель std::unique_ptr, где это необходимо

class Fraction
{
private:
	int m_numerator = 0;
	int m_denominator = 1;

public:
	Fraction(int numerator = 0, int denominator = 1)
		: m_numerator(numerator)
		, m_denominator(denominator)
	{
		std::cout << "Fraction()" << std::endl;
	}

	//friend std::ostream& operator<< (std::ostream& out, const Fraction& f1)
	friend std::ostream& operator<< (std::ostream& out, const std::unique_ptr<Fraction>& ptr)
	{
		out << ptr->m_numerator << "/" << ptr->m_denominator << std::endl;			//out << f1.m_numerator << "/" << f1.m_denominator;
		return out;
	}

	~Fraction()
	{
		std::cout << "~Fraction()" << std::endl;
	}
};

void printFraction(const std::unique_ptr<Fraction>& ptr)				//void printFraction(const Fraction* const ptr)
{
	if (ptr)
	{
		std::cout << ptr;												//std::cout << *ptr;
	}
	else
	{
		std::cout << "Empty unique_ptr" << std::endl;
	}
}

int main()
{
	std::unique_ptr<Fraction> ptr = std::make_unique<Fraction>(7, 9);	//Fraction* ptr = new Fraction(7, 9);
	printFraction(ptr);
	//delete ptr;

	std::unique_ptr<Fraction> ptr2;
	printFraction(ptr2);

	std::unique_ptr<Fraction> ptr3 = std::make_unique<Fraction>(10, 10);
	ptr3 = std::make_unique<Fraction>(2, 1);		//Потеря предыдущего объекта <Fraction>(10, 10) - деструктор не срабатывает
	std::cout << ptr3;
	printFraction(ptr3);

	std::unique_ptr<Fraction> ptr4 = std::make_unique<Fraction>(15, 30);
	Fraction* manual_pointer = ptr4.release();		//Передача данных из умного указателя обычно (умный освобождается)
	printFraction(ptr4);							//Дальнейшее освобождения памяти на плечах программиста

	std::unique_ptr<Fraction> ptr5 = std::make_unique<Fraction>();
	ptr5.reset();									//Удаляет данные в указателе
	ptr5 = std::make_unique<Fraction>(333, 111);
	printFraction(ptr5);

	std::unique_ptr<Fraction> ptr6 = std::make_unique<Fraction>(13, 17);
	Fraction* manual_pointer2 = ptr6.get();			//Копирует адрес из умного указателя в обычный (теперь 2 владельца)
	printFraction(ptr6);
	manual_pointer2 = nullptr;
	return 0;
}



////////////////////////////////////shared_ptr//////////////////////////////////////////////////////////////////////////





////////////////////////////////////weak_ptr////////////////////////////////////////////////////////////////////////////