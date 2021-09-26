#include <algorithm>
#include <list>
#include "My_String.h"

void printList(std::list<MyString>& stringList);
bool ascendingComp (const MyString& obj1, const MyString& obj2);
bool descendingComp(const MyString& obj1, const MyString& obj2);

int main(int argc, char* argv[])
{
    MyString object1;
    MyString object2(object1);
    object2 = "First string";

    MyString object3 = "Second string";
    MyString object4 = object3;
    object4.remove_begin(7);

    MyString object5 = object4;
    object5.add_begin("fourth");
    object4.remove(2);
    object5.remove(6, 10);

    MyString object6 = "First strimg1";
    MyString object7 = "First string2";
    MyString object8 = "Firsta string3";
    MyString object9 = "JHGjGHjhGK";
    MyString object10 = object6 + object7;

    std::cout << "**********************INITIAL LIST**********************" << std::endl << std::endl;
    std::list<MyString> sortedList;
    sortedList.push_back(std::move(object1));
    sortedList.push_back(std::move(object2));
    sortedList.push_back(std::move(object3));
    sortedList.push_back(std::move(object4));
    sortedList.push_back(std::move(object5));
    sortedList.push_back(std::move(object6));
    sortedList.push_back(std::move(object7));
    sortedList.push_back(std::move(object8));
    sortedList.push_back(std::move(object9));
    sortedList.push_back(std::move(object10));
    printList(sortedList);

    std::cout << "**********************LIST SORTED IN ASCEND ORDER**********************" << std::endl << std::endl;
    sortedList.sort(ascendingComp);
    printList(sortedList);

    std::cout << "**********************LIST SORTED IN DESCEND ORDER**********************" << std::endl << std::endl;
    std::list<MyString> reversedList;
    std::copy(sortedList.begin(), sortedList.end(), std::back_inserter(reversedList));
    reversedList.sort(descendingComp);
    printList(reversedList);

    std::cin.get();

    return 0;
}

void printList(std::list<MyString>& list)
{
    for (auto i = list.begin(); i != list.end(); ++i)
    {
        if (i->length())
        {
            std::cout << *i;
        }
    }
}

bool ascendingComp(const MyString& obj1, const MyString& obj2)
{
    if (obj1._str && obj2._str)
    {
        if (tolower(*(obj1._str)) < tolower(*(obj2._str)) ||
            (obj1._str[1] == '\0' && obj2._str[1] != '\0') ||
            (obj2._len == 0))
        {
            return true;
        }
        else if (tolower(*(obj1._str)) > tolower(*(obj2._str)) ||
            (obj1._str[1] != '\0' && obj2._str[1] == '\0') ||
            (obj1._len == 0))
        {
            return false;
        }
        else
        {
            MyString oc1 = &obj1._str[1];
            MyString oc2 = &obj2._str[1];
            return ascendingComp(oc1, oc2);
        }
    }
    else
    {
        return false;
    }
}

bool descendingComp(const MyString& obj1, const MyString& obj2)
{
    if (obj1._str && obj2._str)
    {
        if (tolower(*(obj1._str)) < tolower(*(obj2._str)) ||
            (obj1._str[1] == '\0' && obj2._str[1] != '\0') ||
            (obj2._len == 0))
        {
            return false;
        }
        else if (tolower(*(obj1._str)) > tolower(*(obj2._str)) ||
            (obj1._str[1] != '\0' && obj2._str[1] == '\0') ||
            (obj1._len == 0))
        {
            return true;
        }
        else
        {
            MyString oc1 = &obj1._str[1];
            MyString oc2 = &obj2._str[1];
            return descendingComp(oc1, oc2);
        }
    }
    else
    {
        return false;
    }
}