//
//  ListInit.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef ListInit_hpp
#define ListInit_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <initializer_list>
#include <deque>
using namespace std;
void PrintInitList();

enum Gender{
    Boy,
    Girl,
};

class Person
{
public:
    Person(initializer_list<pair<string, int>> l) // 标准是建议使用一个左值类型，如果使用右值引用&&l也是可以的
    {
        initializer_list<pair<string, int>>::iterator it = l.begin();
        for(; it != l.end(); ++it)
        {
            data.push_back(*it);
        }
    }
    void Print()
    {
        for(auto it = data.begin(); it != data.end(); ++it)
        {
            cout<< "name:" << it->first << ", seq:" << it->second << endl;
        }
    }
    void AddFunc(initializer_list<pair<string, int>> &&l) // 这里也可以为l
    {
        auto it = l.begin();
        for(; it != l.end(); ++it)
        {
            data.push_back(*it);
        }
    }
    
    const vector<int> GetList()
    {
        return {100, 101};
    }
    
    deque<float> GetQueue()
    {
        return {1.01f, 1.02f};
    }
    template <typename T>
    void Print(T t) const
    {
        for(auto it = t.begin(); it != t.end(); ++it)
        {
            cout << *it << " " << endl;
        }
    }
private:
    vector<pair<string, int>> data;
};
#endif /* ListInit_hpp */
