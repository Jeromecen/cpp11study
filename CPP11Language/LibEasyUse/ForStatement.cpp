//
//  ForStatement.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/6.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "ForStatement.hpp"

void PrintFor()
{
    cout<< "PrintFor Test:" << endl;
    int arr[5] = {1,2,3,4,5};
    for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        cout<< arr[i] << "";
    }
   cout << endl<< "2 line : " << endl;
    for(int e : arr)
    {
      cout<< e << "";
    }
    
    cout << endl<< "3 line : " << endl;
    vector<int> vecInt = {6,7,8,9};
//    vector<int>::iterator it = vecInt.begin();
    for(vector<int>::iterator it = vecInt.begin(); it != vecInt.end(); ++it)
    {
        cout << *it << "";
    }
    cout << endl<< "4 line : " << endl;
    for(auto it = vecInt.begin(); it != vecInt.end(); ++it)
    {
        cout << *it << "";
    }
    cout << endl<< "5 line : " << endl;
    // 自动范围和迭代递增的for语法
    for(auto &e: vecInt)
    {
        cout << e << ""; // e是元素对象，非迭代器对象，故不用*e输出
    }

    cout << endl<< "6 line : " << endl;
    vector<ForData> mydata;
    for(int i = 0; i < 5; i++)
    {
        ForData data;
        data.id = i;
        char str[10];
        sprintf(str, "_id%d", i);
        string temp = str;
        data.name = "test" + temp;
        mydata.push_back(data);
    }
    for(auto e: mydata)
    {
        cout << e.name << "  "; // e是元素对象，非迭代器对象，故不用*e输出
    }
    cout<< endl;
}
