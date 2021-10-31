#include <iostream>
#include <vector>

class Animal
{
public:
	virtual void MakeSound() const { std::cout << "There is no sound" << std::endl; }
	virtual void Print() const { std::cout << "This is not what you'd like to see" << std::endl; }

	virtual ~Animal() = default;

protected:
	Animal(int value)
		: _value(value)
	{}

	int GetValue() const { return _value; }

private:
	int _value;
};

class Cat : public Animal
{
public:
	Cat(int value)
		: Animal(value)
	{}

	~Cat() {};

	void MakeSound() const override { std::cout << "\"Meow\"" << std::endl; }
	void Print() const override { std::cout << "Cat's value is " << GetValue() << ". The cat says "; }
};

class Pig : public Animal
{
public:
	Pig(int value)
		: Animal(value)
	{}

	~Pig() {};

	void MakeSound() const override { std::cout << "\"Oink\"" << std::endl; };
	void Print() const override { std::cout << "Pig's value is " << GetValue() << ". The pig says "; }
};

class Fox : public Animal
{
public:
	Fox(int value)
		: Animal(value)
	{}

	~Fox() override {};

	void MakeSound() const override { std::cout << "\"Yipping\"" << std::endl; };
	void Print() const override { std::cout << "Fox's value is " << GetValue() << ". The fox says "; }
};

int main()
{
	Cat cat(1);
	Animal& rCat = cat;
	rCat.Print();
	rCat.MakeSound();

	Pig pig(2);
	Animal* pPig = &pig;
	pPig->Print();
	pPig->MakeSound();

	Fox fox(3);
	Animal& rFox = fox;
	rFox.Print();
	rFox.MakeSound();

	std::cout << std::endl << "////////////////Array of pointers to animals////////////////" << std::endl;

	Animal* arr[] = { &cat, &pig, &fox };

	//for (int i = 0; i < 3; ++i)
	//{
	//	arr[i]->Print();
	//	arr[i]->MakeSound();
	//}
	for (const auto* it : arr)
	{
		it->Print();
		it->MakeSound();
	}

	std::cout << std::endl << "////////////////Vector of pointers to animals////////////////" << std::endl;

	std::vector<Animal*> aniVec;
	aniVec.emplace_back(&cat);
	aniVec.emplace_back(&fox);
	aniVec.emplace_back(&pig);

	//std::cout << std::endl << "////////////////Vector of pointers to animals////////////////" << std::endl;
	//for (size_t i = 0; i < aniVec.size(); i++)
	//{
	//	aniVec[i]->MakeSound();
	//}

	//std::cout << std::endl << "////////////////Vector of pointers to animals////////////////" << std::endl;
	//for (auto it = aniVec.begin(); it != aniVec.end(); ++it)
	//{
	//	(*it)->MakeSound();
	//}

	for (const auto* it : aniVec)
	{
		it->Print();
		it->MakeSound();
	}

	std::cout << std::endl << "////////////////Array of animals////////////////" << std::endl;

	Animal arr2[] = { Cat(11), Pig(22), Fox(33) };

	for (const auto& it2 : arr2)
	{
		it2.Print();
		it2.MakeSound();
	}

	return 0;
}