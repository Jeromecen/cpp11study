//
//  va_template_function.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/7.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "va_template_function.hpp"
double sum(int n, ...)//求n个double数据之和
{
    double sum = 0;
    va_list args;//接受输入数据的数据结构，需声明stdarg.h，
    va_start(args, n); //初始化数据
    while (n>0)
    {
        sum += va_arg(args, double); //将args中的数据一一取出，每隔sizeof(double)取一次数，再求和
        --n;
    }
    va_end(args);
    return sum;
}

void Printf(const char *s)
{
    cout << endl << "Printf inner begin:" << endl;
    while (*s)
    {
        if (*s == '%'&&*++s != '%')
        {
            throw runtime_error("invalid formatstring: missing arguments");
        }
        cout << *s++;
    }
}

void PrintDynamicArgLenFunc()
{
    cout << "PrintDynamicArgLenFunc test: " << endl;
    // 缺点是sum函数根本不知道...的类型，也不能输出自定义类型
    double d = sum(3, 1.0f, 2.0f, 3.2f);
    cout << "c99 sum d :" << d << endl;
    
    // cpp11通过引入泛型来解决。
    int mulValue =  Multiply<1,2, 3, 4, 5>::val;
    cout << "cpp 11 mulValue :" << mulValue << endl;
    
    Printf("hello%sspc%sspc%s\n", string("world"), string("for"), string("sam"));
    
    cout << "...T T...t ..." << endl;
    PrintDummy("sam", 101, "sandy", 202);
    cout << endl;
    
    tuple<int, string> tp = make_tuple(30, "samcen");
//    int age0 = tp.get<0>();
    int age;
    string name;
    tie(age, name) = tp;
    cout << "age:" << age << ", name:" << name << endl;
}
