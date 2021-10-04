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
		//	~Fraction()
		//	{
		//		std::cout << "~Fraction()" << std::endl;
		//	}
		//
		//	friend std::ostream& operator<< (std::ostream& out, const std::shared_ptr<Fraction>& ptr)
		//	{
		//		out << ptr->_numerator << "/" << ptr->_denominator;
		//		out << "\tNumber of shared_ptr: " << ptr.use_count() << std::endl;	//use_count() возвращает количество shared_ptr
		//		return out;
		//	}
		//
		//	void SetValues(int n, int d)
		//	{
		//		_numerator = n;
		//		_denominator = d;
		//	}
		//};
		//
		//void PrintFraction(const std::shared_ptr<Fraction> ptr)
		//{
		//	if (ptr)
		//	{
		//		std::cout << ptr;
		//	}
		//	else
		//	{
		//		std::cout << "Empty shared_ptr" << std::endl;
		//	}
		//}
		//
		//template <typename T>
		//void SameAddress(const T& ptr1, const T& ptr2)
		//{
		//	std::cout << "Objects in shared poinetrs have "											//get возвращает адрес объекта в shared_ptr
		//		<< ((ptr1.get() == ptr2.get()) ? "the same address" : "different addresses")
		//		<< std::endl;
		//}
		//
		//int main()
		//{
		//	std::shared_ptr<Fraction> sPtr1;
		//	PrintFraction(sPtr1);
		//
		//	std::shared_ptr<Fraction> sPtr2 = std::make_shared<Fraction>(11, 22);
		//	PrintFraction(sPtr2);
		//	auto sPtr3 = sPtr2;
		//	std::cout << (sPtr2.unique() ? "Shared_ptr is unique" : "Shared_ptr is not unique") << std::endl;	//unique
		//	sPtr3.reset();																						//true, если shared_ptr -
		//	std::cout << (sPtr2.unique() ? "Shared_ptr is unique" : "Shared_ptr is not unique") << std::endl;	//единственный владелец данными
		//	sPtr2.reset();
		//	PrintFraction(sPtr2);
		//	PrintFraction(sPtr3);
		//
		//	auto sPtr4 = std::make_shared<int>(100);
		//	auto sPtr5 = std::make_shared<int>(333);
		//	std::cout << "sPtr4 = " << *sPtr4 << ";\tsPtr5 = " << *sPtr5 << std::endl;
		//	sPtr4.swap(sPtr5);
		//	std::cout << "sPtr4 = " << *sPtr4 << ";\tsPtr5 = " << *sPtr5 << std::endl;
		//
		//	auto sPtr6 = std::make_shared<Fraction>(8, 4);
		//	auto sPtr7 = sPtr6;
		//	SameAddress(sPtr6, sPtr7);
		//	auto sPtr8 = std::make_shared<Fraction>(2, 1);
		//	SameAddress(sPtr6, sPtr8);
		//
		//	auto uPtr1 = std::make_unique<int>(123);
		//	std::cout << *uPtr1 << std::endl;
		//	//auto uPtr2 = uPtr1;
		//	std::shared_ptr<int> sPtr9 = std::move(uPtr1);
		//	auto sPtr10 = sPtr9;
		//	SameAddress(sPtr9, sPtr10);
		//
		//
		//	return 0;
		//}


////////////////////////////////////weak_ptr////////////////////////////////////////////////////////////////////////////

class Item
{
public:
	Item()
	{
		std::cout << "Item acquired\n"; 
	}

	Item(int num)
		: _num(num)
	{ 
		std::cout << "Item acquired\n"; 
	}

	~Item()
	{
		std::cout << "Item destroyed\n"; 
	}

	void SetValue(std::shared_ptr<Item> ptr)
	{
		_ptr = ptr;
	}

	int GetNum() const
	{
		return _num;
	}

private:
	int					_num = 0;
	std::weak_ptr<Item> _ptr;						//std::shared_ptr<Item> _ptr;
};

int main()
{
	{
		auto sPtr1 = std::make_shared<Item>();
		auto sPtr2 = std::make_shared<Item>();
		sPtr1->SetValue(sPtr2);
		sPtr2->SetValue(sPtr1);
	}

	auto sPtr3 = std::make_shared<int>(555);
	std::weak_ptr<int> wPtr1(sPtr3);
	std::cout << "1. wPtr1 " << (wPtr1.expired() ? "is" : "is not") << " expired\n";	// Проверяет, не пустая ли weak_ptr и есть ли shared_ptr
	sPtr3.reset();	// wPtr1.reset();	 в данном случае одно и то же					// на объект, на который указывает weak_ptr
	std::cout << "2. wPtr1 " << (wPtr1.expired() ? "is" : "is not") << " expired\n";	// true - пустая или нет shared_ptr

	auto sPtr4 = std::make_shared<Item>(10);
	auto sPtr5 = std::make_shared<Item>(5);
	auto sPtr6 = sPtr5;
	std::weak_ptr<Item> wPtr2 = sPtr4;
	std::weak_ptr<Item> wPtr3 = sPtr5;
	std::cout << "Number of shared_ptr's through wPtr2: " << wPtr2.use_count() << std::endl;	// Возвращает число shared_ptr к одному объекту
	wPtr2.swap(wPtr3);
	std::cout << "sPtr4 = " << sPtr4->GetNum() << std::endl;
	std::cout << "sPtr5 = " << sPtr5->GetNum() << std::endl;
	std::cout << "wPtr2 = " << wPtr2.lock()->GetNum() << std::endl;		// "weak_ptr".lock() для работы с данными через weak_ptr
	std::cout << "wPtr3 = " << wPtr3.lock()->GetNum() << std::endl;
	std::cout << "Number of shared_ptr's through wPtr2: " << wPtr2.use_count() << std::endl;

	auto sPtr7 = std::make_shared<Item>(777);
	std::shared_ptr<Item> sPtr8;
	std::weak_ptr<Item> wPtr4 = sPtr7;
	sPtr8 = wPtr4.lock();
	std::cout << "sPtr8 = " << sPtr8->GetNum() << std::endl;
	std::cout << "Number of shared_ptr's through wPtr4: " << wPtr4.use_count() << std::endl;

	return 0;
}
