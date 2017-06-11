//
//  ListInit.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "ListInit.hpp"

struct PersonStruct
{
    string name;
    int age;
};

void PrintInitList()
{
    int a = 3 + 4;
    int b = {3+4};
    int c(3+4);
    int d{3+4};
    int *p = new int{3+4};
    cout << "a: " << a << ", b: " << b << ", c: " << c << "d: " << d << ", *p:" << *p << endl;
    
    vector<int> vec = {1, 2, 3, 4, 5}; // 初始化列表
    map<int, float> map_data = {{1, 1.1f}, {2, 2.1f}, {3, 3.1f}}; // 初始化map
    cout << "vec value is :" << endl;
    vector<int>::iterator itVec = vec.begin();
    for(; itVec != vec.end(); ++itVec)
    {
        cout << *itVec << " ";
    }
    cout << endl;
    
    cout << "map value is :" << endl;
    map<int, float>::iterator itMap = map_data.begin();
    for(; itMap != map_data.end(); ++itMap)
    {
        cout << itMap->second << " ";
    }
    cout << endl;
    
    
    PersonStruct person = {"Frank", 25};
    cout << person.name << " : " << person.age << endl;
    
    Person perList = {{"jack", 1}, {"sam", 2}, {"jerome", 3}};
    perList.AddFunc({{"sandy", 4}, {"july", 5}});
    perList.Print();
    
    const vector<int> refVec = perList.GetList();
    deque<float> &&refQue = perList.GetQueue();
    cout << endl;
    cout << "refVec value is :" << endl;
    perList.Print(refVec);
    cout << "refQue value is :" << endl;
    perList.Print(refQue);
    cout << endl;
    
    char cA = {127}; // OK
//    char cB = {129}; // error
    char cB2 = 129; // 也是有编译警告的
    cout << "type narrow test:" << cA <<", " << cB2 << endl;
}
