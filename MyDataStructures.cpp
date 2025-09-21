//Кратко о проекте: написание своих аналогов структурам данных STL для того, чтобы лучше разобраться как они работают "под капотом"
//На данный момент готов vector, list (без глубокого тестирования)


#include <iostream>
#include <algorithm>
#include "MyDataStructures.h"

int main()
{
    //используйте
    mds::list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    mds::list<int> list2(std::move(list1));
    //list1.clear();
    std::cout << list2[0] << ' ' << list2[1] << ' ' << list2[2] << ' ' << list1.size();
    return 0;
}