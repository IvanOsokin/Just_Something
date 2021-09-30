#include <algorithm>
#include <list>
#include "MyString.h"

void PrintList(std::list<MyString>& stringList);
bool AscendingComp (const MyString& str1, const MyString& str2);
bool DescendingComp(const MyString& str1, const MyString& str2);

int main(int argc, char* argv[])
{
    MyString object1;
    MyString object2(object1);
    object2 = "1. Return";

    MyString object3 = "2. Second string";
    MyString object4 = object3;
    object4.RemoveBegin(7);

    MyString object5 = object4;
    object5.AddBegin("fourth");
    object4.Remove(2);
    object5.Remove(6, 10);

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
    PrintList(sortedList);

    std::cout << "**********************LIST SORTED IN ASCENDING ORDER**********************" << std::endl << std::endl;
    sortedList.sort(AscendingComp);
    PrintList(sortedList);

    std::cout << "**********************LIST SORTED IN DESCENDING ORDER**********************" << std::endl << std::endl;
    std::list<MyString> reversedList;
    std::copy(sortedList.begin(), sortedList.end(), std::back_inserter(reversedList));
    reversedList.sort(DescendingComp);
    PrintList(reversedList);

    std::cin.get();

    return 0;
}

void PrintList(std::list<MyString>& list)
{
    for (auto i = list.begin(); i != list.end(); ++i)
    {
        if (i->Length())
        {
            std::cout << *i;
        }
    }
}

bool AscendingComp(const MyString& str1, const MyString& str2)
{
   for (std::size_t i = 0; str1[i] != '\0' && str2[i] != '\0'; ++i)
   {
       if (str1.IsEmpty() ||
          (tolower(str1[i]) > tolower(str2[i])) ||
          (str2[i + 1] == '\0' && str2[i + 1] != '\0'))
       {
           return false;
       }
       else if (str2.IsEmpty() ||
               (tolower(str1[i]) < tolower(str2[i])) ||
               (str2[i + 1] != '\0' && str2[i + 1] == '\0'))
       {
           return true;
       }
   }
   return false;
}
bool DescendingComp(const MyString& str1, const MyString& str2)
{
    for (std::size_t i = 0; str1[i] != '\0' && str2[i] != '\0'; ++i)
    {
        if (str1.IsEmpty() ||
            (tolower(str1[i]) > tolower(str2[i])) ||
            (str2[i + 1] == '\0' && str2[i + 1] != '\0'))
        {
            return true;
        }
        else if (str2.IsEmpty() ||
            (tolower(str1[i]) < tolower(str2[i])) ||
            (str2[i + 1] != '\0' && str2[i + 1] == '\0'))
        {
            return false;
        }
    }
    return false;
}
