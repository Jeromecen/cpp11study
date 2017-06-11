//
//  ExplicitDescribe.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "ExplicitDescribe.hpp"
void Display1(Rational1 ra)
{
    cout<<"Display1 call " << endl;
}

void Display2(Rational2 ra)
{
    cout<<"Display2 call " << endl;
}

void PrintExplict()
{
    Rational1 r1_1 = 11; // OK,隐式类型转换
    Rational1 r1_2(12); // OK,显示转换
    
//    Rational2 r2_1 = 21; // 编译错误，不允许隐式类型转换
    Rational2 r2_1 = (Rational2)21; // OK,显式声明转换
    Rational2 r2_2(22); // OK,显式构造目标类型
    Rational2 r2_3(Rational2(23)); // OK,显式声明转换
    
    Display1(1); // OK
//    Display2(2); // 编译错误，不允许隐式类型转换
    Display2(Rational2(2)); // OK,显式声明转换
    
    cout << "类型转换 explicit修饰call: " << endl;
    int a = 0;
    Ptr<int> iPtr(&a);
    if(iPtr)
    {
        cout<< "iPtr is iPtr not null"<< endl;
    }
    else
    {
        cout<< "iPtr is nullptr"<< endl;
    }
    
    Ptr<int> iPtr2(NULL);
    if(iPtr2)
    {
        cout<< "iPtr2 is iPtr not null"<< endl;
    }
    else
    {
        cout<< "iPtr2 is nullptr"<< endl;
    }
    
    Ptr<double> dPtr(NULL);
//    cout << iPtr + dPtr << endl; // 会输出1但是是不希望的行为，且没有语义含义的; 定义了explicit就不能进行这样的隐式转换了。
    
    
}
