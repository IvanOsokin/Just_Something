#include <iostream>
#include <iomanip>
#include <string>

	//class Parent
	//{
	//public:
	//	Parent(std::string motherName = "")
	//		: _motherName(motherName)
	//	{
	//		std::cout << "Parent was constructed" << std::endl;
	//	}
	//	~Parent()
	//	{
	//		std::cout << "Parent was destructed" << std::endl;
	//	}
	//
	//	void Alarm()
	//	{
	//		std::cout << "Your mother is about to come back." << std::endl;
	//	}
	//	void DisplayMotherName()
	//	{
	//		std::cout << "My mother's name is " << _motherName << std::endl;
	//	}
	//
	//private:
	//	std::string _motherName;
	//};
	//
	//class Child : public Parent
	//{
	//public:
	//	Child(std::string motherName = "", std::string childName = "")
	//		: Parent(motherName)
	//		, _childName(childName)
	//	{
	//		std::cout << "Child was constructed" << std::endl;
	//	}
	//	~Child()
	//	{
	//		std::cout << "Child was destructed" << std::endl;
	//	}
	//
	//	void DisplayName()
	//	{
	//		std::cout << "My name is " << _childName << std::endl;
	//	}
	//
	//private:
	//	std::string _childName;
	//};
	//
	//int main()
	//{
	//	Parent parentInstance("Sara");
	//	parentInstance.Alarm();
	//	parentInstance.DisplayMotherName();
	//	
	//	
	//	Child childInstance("Beth", "Bobby");
	//	childInstance.Alarm();
	//	childInstance.DisplayMotherName();
	//	childInstance.DisplayName();
	//
	//	return 0;
	//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Реализуем наш пример с Фруктом, о котором мы говорили на уроке №153.
 * Создайте родительский класс Fruit, который имеет два закрытых члена : name(std::string) и color(std::string).
 * Создайте класс Apple, который наследует свойства Fruit.
 * У Apple должен быть дополнительный закрытый член : fiber(тип double).
 * Создайте класс Banana, который также наследует класс Fruit.
 * Banana не имеет дополнительных членов.
 */

//class Fruit
//{
////private:
//protected:
//	std::string _name;
//	std::string _color;
//
//public:
//	Fruit(std::string name, std::string color)
//		: _name(name)
//		, _color(color)
//	{}
//
//	~Fruit() = default;
//
//	//const std::string& GetName()  const { return _name; }
//	//const std::string& GetColor() const { return _color; }
//};
//
//class Apple : public Fruit
//{
//private:
//	double _fiber;
//
//public:
//	Apple(std::string name, std::string color, double fiber)
//		: Fruit(name, color)
//		, _fiber(fiber)
//	{}
//	~Apple() = default;
//
//	friend std::ostream& operator << (std::ostream& os, const Apple& obj)
//	{
//		//os << "Apple(" << obj.GetName() << ", " << obj.GetColor() << ", " << obj._fiber << ")" << std::endl;
//		os << "Apple(" << obj._name << ", " << obj._color << ", " << obj._fiber << ")" << std::endl;
//		return os;
//	}
//};
//
//class Banana : public Fruit
//{
//public:
//	Banana(std::string name, std::string color)
//		: Fruit(name, color)
//	{}
//
//	~Banana() = default;
//
//	friend std::ostream& operator << (std::ostream& os, const Banana& obj)
//	{
//		//os << "Banana(" << obj.GetName() << ", " << obj.GetColor() << ")" << std::endl;
//		os << "Banana(" << obj._name << ", " << obj._color << ")" << std::endl;
//		return os;
//	}
//};
//
//int main()
//{
//	const Apple a("Red delicious", "red", 7.3);
//	std::cout << a;
//
//	const Banana b("Cavendish", "yellow");
//	std::cout << b;
//
//	return 0;
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//class Parent
//{
//public:
//	Parent(std::string pub, std::string pro, std::string pri)
//		: _pub(pub)
//		, _pro(pro)
//		, _pri(pri)
//	{
//		std::cout << "Parent()\n";
//	}
//	~Parent()
//	{
//		std::cout << "~Parent()\n";
//	}
//
//	void print()
//	{
//		std::cout << "Parent:" << std::endl;
//		std::cout << std::setw(12) << _pub << std::endl;
//		std::cout << std::setw(12) << _pro << std::endl;
//		std::cout << std::setw(12) << _pri << std::endl;
//	}
//
//public:
//	std::string _pub;
//protected:
//	std::string _pro;
//private:
//	std::string _pri;
//};
//
//class Child : private Parent
//{
//public:
//	Child(std::string pub, std::string pro, std::string pri)
//		: Parent(pub, pro, pri)
//	{
//		std::cout << "Child()\n";
//	}
//	~Child()
//	{
//		std::cout << "~Child()\n";
//	}
//
//	void print()
//	{
//		std::cout << "Child:" << std::endl;
//		std::cout << std::setw(12) << _pub << std::endl;
//		std::cout << std::setw(12) << _pro << std::endl;
//		//std::cout << std::setw(12) << _pri << std::endl;
//	}
//};
//
//int main()
//{
//	Child ch("Public", "Protected", "Private");
//	ch.print();
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//a) Создайте классы Apple и Banana, которые наследуют класс Fruit. У класса Fruit есть две переменные-члены: name и color.
//
//Следующий код :
//
//int main()
//{
//	Apple a("red");
//	Banana b;
//
//	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
//	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
//
//	return 0;
//}
//
//Должен выдавать следующий результат :
//My apple is red.
//My banana is yellow.

class Fruit
{
private:
	std::string _name;
	std::string _color;

public:
	Fruit(std::string name, std::string color)
		: _name(name)
		, _color(color)
	{}

	~Fruit() = default;

	std::string getName()  const { return _name; }
	std::string getColor() const { return _color; }
};

class Apple : public Fruit
{
public:
	Apple(std::string color, std::string name = "apple")
		: Fruit(name, color)
	{}
	~Apple() = default;
};

class Banana : public Fruit
{
public:
	Banana(std::string name = "banana", std::string color = "yellow")
		: Fruit(name, color)
	{}

	~Banana() = default;
};

class GrannySmith : public Apple
{
public:
	GrannySmith(std::string name = "Granny Smith apple", std::string color = "green")
		: Apple(color, name)
	{}

	~GrannySmith() = default;
};

int main()
{
	Apple a("red");
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

	return 0;
}

//b) Добавьте новый класс GrannySmith, который наследует класс Apple.
//
//Следующий код :
//
//int main()
//{
//	Apple a("red");
//	Banana b;
//	GrannySmith c;
//
//	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
//	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
//	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
//
//	return 0;
//}
//
//Должен выдавать следующий результат :
//My apple is red.
//My banana is yellow.
//My Granny Smith apple is green.