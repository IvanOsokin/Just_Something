#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>

class MyString
{
public:
	MyString() = default;
	MyString(const char* initString, size_t length);
	MyString(const char* initString);
	
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;
	MyString& operator= (MyString other);

	~MyString();

	friend MyString operator + (const MyString& obj1, const MyString& obj2);
	friend std::ostream& operator << (std::ostream& os, const MyString& obj);
	char   operator [] (int index);

	void Swap(MyString& other);

	int   length() const;
	void  clean();
	void  remove	   (const std::size_t index);
	void  remove	   (const std::size_t iBegin, const std::size_t iEnd);
	void  remove_end   (const std::size_t range);
	void  remove_begin (const std::size_t range);
	void  add_end	   (const char* subStr);
	void  add_end	   (const MyString& other);
	void  add_begin	   (const char* subStr);
	void  add_begin	   (const MyString& other);

	friend bool ascendingComp (const MyString& obj1, const MyString& obj2);
	friend bool descendingComp(const MyString& obj1, const MyString& obj2);


private:
	char*	_str = nullptr;
	size_t	_len = 0;
};

#endif MY_STRING_H
