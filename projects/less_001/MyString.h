#pragma once

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
	char operator [] (std::size_t index) const;

	void  Swap(MyString& other);

	int   Length() const;
	bool  IsEmpty() const;
	void  Clean();
	void  Remove	   (const std::size_t index);
	void  Remove	   (const std::size_t iBegin, const std::size_t iEnd);
	void  RemoveEnd    (const std::size_t range);
	void  RemoveBegin  (const std::size_t range);
	void  AddEnd	   (const char* subStr);
	void  AddEnd	   (const MyString& other);
	void  AddBegin	   (const char* subStr);
	void  AddBegin	   (const MyString& other);

private:
	char*	_str = nullptr;
	size_t	_len = 0;
};