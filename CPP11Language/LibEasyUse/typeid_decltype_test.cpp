//
//  typeid_decltype_test.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
#include "typeid_decltype_test.hpp"
void PrintTypeInfo()
{
    // 1.RRTI, typeid获取运行时对象的类型和hash_code信息(也可以获取auto运行时类型信息)。
    White w;
    Black b;
    cout<< "PrintTypeInfo():" << endl;
//    type_info wInfo = typeid(w).type_info;
    cout<< typeid(w).name() << endl;
    cout<< typeid(b).name() << endl;
    
    bool isSame = typeid(w).hash_code() == typeid(b).hash_code();
    if(isSame)
    {
        cout<< "w and b is the same." << endl;
    }
    else
    {
        cout<< "w and b is not the same." << endl;
    }
    
    White c;
    isSame = typeid(w).hash_code() == typeid(c).hash_code();
    if(isSame)
    {
        cout<< "w and c is the same." << endl;
    }
    else
    {
        cout<< "w and c is not the same." << endl;
    }
    
    auto d = c; // 对运行时候的auto类型进行判断。
    cout<< "auto d name:" << typeid(d).name() << endl;
    isSame = typeid(w).hash_code() == typeid(d).hash_code();
    if(isSame)
    {
        cout<< "w and d is the same." << endl;
    }
    else
    {
        cout<< "w and d is not the same." << endl;
    }
//    is_same<char_type, char>::value
//    static_assert( is_same<d, White>::value);
//  RTTI的typeid因为运行时有开销，所以很多编辑器都让用户选择性的关闭RTTI，而且很多时候运行时才确定出类型对于程序员来说已经晚了，程序员更多是要在编译期确定出类型，需要使用这些类型而不是识别出来。
//  因此CPP98的RTTI无法满足要求。
//2. decltype类型推导的引入,decltype以一个表达式或变量为输入返回该value的类型作为变量的类型，和auto一样也是在编译期决定的。
//   decltype是随着泛型的模板编程引入的（因为非泛型的类型很容易看出)，可以编译期就得到变量的类型。
    int num1 = 1;
    decltype(num1) num2;
    cout<< "decltype test:" << endl;
    cout << typeid(num2).name() <<endl;
    
    float num3 = 1.0f;
    double num4 = 2.0f;
    decltype(num3 + num4) num5;
    cout << typeid(num5).name() <<endl;
    
    decltype(w) e;
    cout << typeid(e).name() <<endl;
    
    cout<< "decltype DecltypeTest test:" << endl;
    DecltypeTest decltest;
    decltest.PrintTest();  
    
    int i0=10;
    decltype(i0) a0; // a推导为int
    decltype((i0))b0=i0;// b推导为int&，必须为其初始化，否则编译错误
    
    int i = 4;
    int arr[5] = { 0 };
    int *ptr = arr;
    struct S{ double d; }s ;
    void Overloaded(int);
    void Overloaded(char);// 重载的函数
    int && RvalRef();
    const bool Func(int);
    
    // 规则一：推导为其类型
    decltype (arr) var1; // int 标记符表达式
    decltype (ptr) var2;// int *  标记符表达式
    decltype(s.d) var3;// doubel 成员访问表达式
    //decltype(Overloaded) var4;// 重载函数。编译错误。
    
    //规则二：将亡值。推导为类型的右值引用。
    decltype (RvalRef()) var5 = 1;
    
    //规则三：左值，推导为类型的引用。
    decltype ((i))var6 = i;     //int&
    decltype (true ? i : i) var7 = i; //int&  条件表达式返回左值。
    decltype (++i) var8 = i; //int&  ++i返回i的左值。
    decltype(arr[5]) var9 = i;//int&. []操作返回左值
    decltype(*ptr)var10 = i;//int& *操作返回左值
    decltype("hello")var11 = "hello"; //const char(&)[9]  字符串字面常量为左值，且为const左值。
    
    //规则四：以上都不是，则推导为本类型(主要是常量和函数调用，函数调用不会真正产生调用）
    decltype(1) var12;//const int
    decltype(Func(1)) var13=true;//const bool
    decltype(i++) var14 = i;//int i++返回右值
    
// i++：i是之前的，所以是一个临时的右值。
//    {
//        int tmp；
//        tmp=i;
//        i=i+1；
//        return tmp;
//    }
// ++i：i是后面的，是一个本类型的地址是左值。
//    {
//        i=i+1;
//        return i;
//    }
    cout << "is_lvalue_reference test:" << endl;
    cout << is_lvalue_reference<decltype(arr[5])>::value << endl;
    cout << is_lvalue_reference<decltype(1+2)>::value << endl;
    cout << "i value1:" << i << endl;
    cout << is_lvalue_reference<decltype(++i)>::value << endl;
    cout << is_lvalue_reference<decltype(i++)>::value << endl;
    cout << "i value2:" << i << endl; // i的值也不会增加
}
