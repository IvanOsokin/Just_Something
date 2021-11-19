#include <iostream>
#include <cstring>
#include "MyString.h"

MyString::MyString(const char* initString, size_t length)
{
	if (!(strlen(initString) > length))
	{
		_len = length;
		size_t newLen = _len + 1;
		_str = new char[newLen];
		strncpy(_str, initString, newLen);
	}
}

MyString::MyString(const char* initString)
	: MyString(initString, strlen(initString))
{}

MyString::MyString(const MyString& other)
	: _len(other._len)
{
	if (other._str)
	{
		_str = new char[_len + 1];
		strcpy(_str, other._str);
	}
}

MyString::MyString(MyString&& obj) noexcept
	: _str(obj._str)
	, _len(obj._len)
{
	obj._str = nullptr;
	obj._len = 0;
}

MyString& MyString::operator= (MyString obj)
{
	Swap(obj);
	return *this;
}

MyString::~MyString()
{
	delete[] _str;
}

MyString operator + (const MyString& obj1, const MyString& obj2)
{
	MyString temp;

	if (obj1._str || obj2._str)
	{
		if (!obj1._str && obj2._str)
		{
			temp = obj2._str;
		}
		else if (obj1._str && !obj2._str)
		{
			temp = obj1._str;
		}
		else
		{
			MyString temp2(obj1._str, obj1._len + obj2._len);
			strcat(temp2._str, obj2._str);
			return temp2;
		}
	}
	return temp;
}

std::ostream& operator << (std::ostream& os, const MyString& obj)
{
	if (obj._len == 0)
	{
		os << "***String is empty***" << "\tlength = " << obj._len << std::endl << std::endl;
	}
	else
	{
		os << obj._str << "\tlength = " << obj._len << std::endl << std::endl;
	}

	return os;
}

char MyString::operator [] (std::size_t index) const
{
	if (_str && index <= _len)
	{
		return _str[index];
	}
	else
	{
		return '\0';
	}
}

void MyString::Swap(MyString& other)
{
	std::swap(other._str, _str);
	std::swap(other._len, _len);
}

int MyString::Length() const
{
	return _len;
}

bool MyString::IsEmpty() const
{
	return !_len;
}

void MyString::Clean()
{
	if (_str)
	{
		delete[] _str;
		_str = nullptr;
		_len = 0;
	}
}

void MyString::Remove(const std::size_t index)
{
	if (index >= 0 && index <= _len)
	{
		char* tmpChar = new char[_len];
		char* tC = tmpChar;

		for (char* oldStr = _str; *oldStr != '\0'; ++oldStr)
		{
			if (oldStr == _str + index)
			{
				continue;
			}
			*tmpChar = *oldStr;
			++tmpChar;
		}
		tC[_len - 1] = '\0';

		MyString temp(tC);

		delete[] tC;

		*this = std::move(temp);
	}
}

void MyString::Remove(const std::size_t iBegin, const std::size_t iEnd)
{
	if (iBegin < iEnd && iBegin >= 0 && iEnd <= _len)
	{
		char* tmpChar = new char[_len - (iEnd - iBegin)];
		char* tC = tmpChar;

		for (char* oldStr = _str; *oldStr != '\0'; ++oldStr)
		{
			if (oldStr >= _str + iBegin && oldStr <= _str + iEnd)
			{
				continue;
			}
			*tmpChar = *oldStr;
			++tmpChar;
		}
		*tmpChar = '\0';

		MyString tempClass(tC);

		*this = std::move(tempClass);
	}
}

void MyString::RemoveEnd(const std::size_t range)
{
	if (!(_len < range))
	{
		char* tmpChar = new char[_len - range + 1];
		char* tC = tmpChar;

		for (char* oldStr = _str; oldStr != _str + _len - range; ++oldStr, ++tmpChar)
		{
			*tmpChar = *oldStr;
		}
		*tmpChar = '\0';

		MyString tempClass(tC);

		delete[] tC;

		*this = std::move(tempClass);
	}
}

void MyString::RemoveBegin(const std::size_t range)
{
	if (!(_len < range))
	{
		char* tmpChar = new char[_len - range + 1];
		char* tC = tmpChar;

		for (char* oldStr = _str + range; *oldStr != '\0'; ++oldStr, ++tmpChar)
		{
			*tmpChar = *oldStr;
		}
		*tmpChar = '\0';

		MyString tempClass(tC);

		delete[] tC;

		*this = std::move(tempClass);
	}
}

void MyString::AddEnd(const char* subStr)
{
	if (!_str)
	{
		MyString temp(subStr);
		*this = std::move(temp);
	}
	else if (!subStr)
	{
		MyString temp(_str);
		*this = std::move(temp);
	}
	else
	{
		MyString temp(_str, strlen(subStr) + _len);
		strcat(temp._str, subStr);
		*this = std::move(temp);
	}
}

void MyString::AddEnd(const MyString& other)
{
	if (!_str)
	{
		MyString temp(other._str);
		*this = std::move(temp);
	}
	else if (!other._str)
	{
		MyString temp(_str);
		*this = std::move(temp);
	}
	else
	{
		MyString temp(_str, (other._len + _len));
		strcat(temp._str, other._str);
		*this = std::move(temp);
	}
}

void MyString::AddBegin(const char* subStr)
{
	if (!_str)
	{
		MyString temp(subStr);
		*this = std::move(temp);
	}
	else if (!subStr)
	{
		MyString temp(_str);
		*this = std::move(temp);
	}
	else
	{
		MyString temp(subStr, strlen(subStr) + _len);
		strcat(temp._str, _str);
		*this = std::move(temp);
	}
}

void MyString::AddBegin(const MyString& other)
{
	if (!_str)
	{
		MyString temp(other._str);
		*this = std::move(temp);
	}
	else if (!other._str)
	{
		MyString temp(_str);
		*this = std::move(temp);
	}
	else
	{
		MyString temp(other._str, (_len + other._len));
		strcat(temp._str, _str);
		*this = std::move(temp);
	}
}