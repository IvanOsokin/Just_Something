#include <iostream>
#include <memory>

////////////////////////////////////unique_ptr//////////////////////////////////////////////////////////////////////////

//Измените следующую программу, заменив обычный указатель
//на умный указатель std::unique_ptr, где это необходимо

		//class Fraction
		//{
		//private:
		//	int _numerator = 0;
		//	int _denominator = 1;
		//
		//public:
		//	Fraction(int numerator = 0, int denominator = 1)
		//		: _numerator(numerator)
		//		, _denominator(denominator)
		//	{
		//		std::cout << "Fraction()" << std::endl;
		//	}
		//
		//	//friend std::ostream& operator<< (std::ostream& out, const Fraction& f1)
		//	friend std::ostream& operator<< (std::ostream& out, const std::unique_ptr<Fraction>& ptr)
		//	{
		//		out << ptr->_numerator << "/" << ptr->_denominator << std::endl;			//out << f1._numerator << "/" << f1._denominator;
		//		return out;
		//	}
		//
		//	~Fraction()
		//	{
		//		std::cout << "~Fraction()" << std::endl;
		//	}
		//};
		//
		//void PrintFraction(const std::unique_ptr<Fraction>& ptr)				//void PrintFraction(const Fraction* const ptr)
		//{
		//	if (ptr)
		//	{
		//		std::cout << ptr;												//std::cout << *ptr;
		//	}
		//	else
		//	{
		//		std::cout << "Empty unique_ptr" << std::endl;
		//	}
		//}
		//
		//int main()
		//{
		//	std::unique_ptr<Fraction> ptr = std::make_unique<Fraction>(7, 9);	//Fraction* ptr = new Fraction(7, 9);
		//	PrintFraction(ptr);
		//	//delete ptr;
		//
		//	std::unique_ptr<Fraction> ptr2;
		//	PrintFraction(ptr2);
		//
		//	std::unique_ptr<Fraction> ptr3 = std::make_unique<Fraction>(10, 10);
		//	ptr3 = std::make_unique<Fraction>(2, 1);		//Потеря предыдущего объекта <Fraction>(10, 10) - деструктор не срабатывает
		//	std::cout << ptr3;
		//	PrintFraction(ptr3);
		//
		//	std::unique_ptr<Fraction> ptr4 = std::make_unique<Fraction>(15, 30);
		//	Fraction* manual_pointer = ptr4.release();		//Передача данных из умного указателя обычно (умный освобождается)
		//	PrintFraction(ptr4);							//Дальнейшее освобождения памяти на плечах программиста
		//
		//	auto ptr5 = std::make_unique<Fraction>();
		//	ptr5.reset();									//Удаляет данные в указателе
		//	ptr5 = std::make_unique<Fraction>(333, 111);
		//	PrintFraction(ptr5);
		//
		//	auto ptr6 = std::make_unique<Fraction>(13, 17);
		//	Fraction* manual_pointer2 = ptr6.get();			//Копирует адрес из умного указателя в обычный (теперь 2 владельца)
		//	PrintFraction(ptr6);
		//	manual_pointer2 = nullptr;
		//	return 0;
		//}



////////////////////////////////////shared_ptr//////////////////////////////////////////////////////////////////////////

class Fraction
{
private:
	int _numerator = 0;
	int _denominator = 1;

public:
	Fraction(int numerator = 0, int denominator = 1)
		: _numerator(numerator)
		, _denominator(denominator)
	{
		std::cout << "Fraction()" << std::endl;
	}

	~Fraction()
	{
		std::cout << "~Fraction()" << std::endl;
	}

	friend std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Fraction>& ptr)
	{
		out << ptr->_numerator << "/" << ptr->_denominator;
		out << "\tNumber of shared_ptr: " << ptr.use_count() << std::endl;	//use_count() возвращает количество shared_ptr
		return out;
	}

	void SetValues(int n, int d)
	{
		_numerator = n;
		_denominator = d;
	}
};

void PrintFraction(const std::shared_ptr<Fraction> ptr)
{
	if (ptr)
	{
		std::cout << ptr;
	}
	else
	{
		std::cout << "Empty shared_ptr" << std::endl;
	}
}

void SameAddress(const std::shared_ptr<Fraction>& ptr1, const std::shared_ptr<Fraction>& ptr2)
{
	std::cout << "Objects in shared poinetrs have "											//get возвращает адрес объекта в shared_ptr
		<< ((ptr1.get() == ptr2.get()) ? "the same address" : "different addresses")
		<< std::endl;
}

int main()
{
	std::shared_ptr<Fraction> sPtr1;
	PrintFraction(sPtr1);

	std::shared_ptr<Fraction> sPtr2 = std::make_shared<Fraction>(11, 22);
	PrintFraction(sPtr2);
	auto sPtr3 = sPtr2;
	std::cout << (sPtr2.unique() ? "Shared_ptr is unique" : "Shared_ptr is not unique") << std::endl;	//unique
	sPtr3.reset();																						//true, если shared_ptr -
	std::cout << (sPtr2.unique() ? "Shared_ptr is unique" : "Shared_ptr is not unique") << std::endl;	//единственный владелец данными
	sPtr2.reset();
	PrintFraction(sPtr2);
	PrintFraction(sPtr3);

	auto sPtr4 = std::make_shared<int>(100);
	auto sPtr5 = std::make_shared<int>(333);
	std::cout << "sPtr4 = " << *sPtr4 << ";\tsPtr5 = " << *sPtr5 << std::endl;
	sPtr4.swap(sPtr5);
	std::cout << "sPtr4 = " << *sPtr4 << ";\tsPtr5 = " << *sPtr5 << std::endl;

	auto sPtr6 = std::make_shared<Fraction>(8, 4);
	auto sPtr7 = sPtr6;
	SameAddress(sPtr6, sPtr7);
	auto sPtr8 = std::make_shared<Fraction>(2, 1);
	SameAddress(sPtr6, sPtr8);

	return 0;
}


////////////////////////////////////weak_ptr////////////////////////////////////////////////////////////////////////////