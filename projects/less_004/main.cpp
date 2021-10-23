#include <iostream>
#include <string>

class Parent
{
public:
	Parent(std::string motherName = "")
		: _motherName(motherName)
	{
		std::cout << "Parent was constructed" << std::endl;
	}
	~Parent()
	{
		std::cout << "Parent was destructed" << std::endl;
	}

	void Alarm()
	{
		std::cout << "Your mother is about to come back." << std::endl;
	}
	void DisplayMotherName()
	{
		std::cout << "My mother's name is " << _motherName << std::endl;
	}

private:
	std::string _motherName;
};

//class Parent
//{
//public:
//	Parent(int id = 0)
//		: m_id(id)
//	{}
//
//	int getId() const { return m_id; }
//
//private:
//	int m_id;
//};

class Child : public Parent
{
public:
	Child(std::string motherName = "", std::string childName = "")
		: Parent(motherName)
		, _childName(childName)
	{
		std::cout << "Child was constructed" << std::endl;
	}
	~Child()
	{
		std::cout << "Child had not been born" << std::endl;
	}

	void DisplayName()
	{
		std::cout << "My name is " << _childName << std::endl;
	}

private:
	std::string _childName;
};

//class Child : public Parent
//{
//public:
//	Child(double value = 0.0, int id = 0)
//		: Parent(id) // вызывается конструктор Parent(int) со значением id!
//		, m_value(value)
//	{}
//
//	double getValue() const { return m_value; }
//
//private:
//	double m_value;
//};

int main()
{
	Parent parentInstance("Sara");
	parentInstance.Alarm();
	parentInstance.DisplayMotherName();
	
	
	Child childInstance("Beth", "Bobby");
	childInstance.Alarm();
	childInstance.DisplayMotherName();
	childInstance.DisplayName();

	//Child child(1.5, 7); // вызывается конструктор Child(double, int)
	//std::cout << "ID: " << child.getId() << '\n';
	//std::cout << "Value: " << child.getValue() << '\n';

	return 0;
}
