#include <iostream>
#include <memory>
#include <string>

class Value;
class Data;
using namespace std;

// Висячая ссылка
int & GetDanglingRef()
{
	int a = 42;
	return a;
}

unique_ptr<int> GetSmartPtr()
{
	return make_unique<int>(42);
}

void ProcessUniquePtr(unique_ptr<int> ptr)
{
	std::cout << *ptr << std::endl;
}

void ProcessSharedPtr(shared_ptr<int> ptr)
{
	std::cout << *ptr << std::endl;
}

class Data : public std::enable_shared_from_this<Data>
{
public:
	Data()
	{
		cout << "Data constructed" << endl;
	}

	~Data()
	{
		cout << "Data destructed" << endl;
	}
	
	void Init();
	void Process();
	auto & GetInfo() const { return _info; }

private:
	shared_ptr<Value>	_value;
	string				_info = "Data Info";
};

class Value
{
public:
	Value()
	{
		cout << "Value constructed" << endl;
	}

	~Value()
	{
		cout << "Value destructed" << endl;
	}
	
	void Init(shared_ptr<Data> data, int value)
	{
		_weadData = data;
		_number = value;
	}
	void Process()
	{
		auto data = _weadData.lock();
		if (data)
		{
			std::cout << data->GetInfo() << ": " << _number << std::endl;
		}
	}

private:
	weak_ptr<Data>		_weadData;
	int					_number = 0;
};

void Data::Init()
{
	_value = make_shared<Value>();
	_value->Init(shared_from_this(), 42);
}

void Data::Process()
{
	_value->Process();
}

int main()
{
	// int returnedValue = GetDanglingRef();
	// Может вернуть 42... А может не 42.
	// std::cout << returnedValue << std::endl;

	// {
	// 	auto uniquePtr = GetSmartPtr();
	// 	ProcessUniquePtr(std::move(uniquePtr));
	//
	// 	shared_ptr<int> sharedPtr = GetSmartPtr();
	// 	weak_ptr<int> weakPtr = sharedPtr;
	// 	
	// 	shared_ptr<int> anotherSharedPtr = sharedPtr;
	// 	shared_ptr<int> anotherSharedPtr2 = sharedPtr;
	// 	ProcessSharedPtr(sharedPtr);
	// 	
	// 	anotherSharedPtr2.reset();
	// 	anotherSharedPtr.reset();
	// 	sharedPtr.reset();
	//
	// 	auto lockedWeakPtr = weakPtr.lock();
	// 	if (lockedWeakPtr)
	// 	{
	// 		ProcessSharedPtr(lockedWeakPtr);
	// 	}
	// }

	auto data = make_shared<Data>();
	data->Init();
	data->Process();

	return 0;
}
