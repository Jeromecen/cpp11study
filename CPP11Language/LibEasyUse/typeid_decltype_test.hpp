//
//  typeid_decltype_test.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef typeid_decltype_test_hpp
#define typeid_decltype_test_hpp

#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;
class White{
};
class Black{
};

class DecltypeTest
{
public:
    int GetHashCode(string &&str)
    {
        cout << "DecltypeTest GetHashCode call" << endl;
        return (int)str.length();
    }
    
//    template <class T>
//    int func(T t)
//    {
//        return 10;
//    }
    void PrintTest()
    {
        map<string, decltype(GetHashCode(""))> strTest; // 没有对函数GetHashCode进行调用，只是根据该函数的声明取得返回类型。
//      map<string, decltype(GetHashCode)> strTest; // 不支持的decltype内部必须是表达式。
        string key = "samdy";
        int code = GetHashCode(move(key)); // 这个时候才调用了一次
        strTest[key] = code;
        
        typedef int (*func)();
        result_of<func()>::type f = 1000; // 函数类型推导，必须是一个函数指针
        cout << f << endl;
    }
private:
    map<string, int> strHashCode;
};
void PrintTypeInfo();
#endif /* typeid_decltype_test_hpp */
