//
//  main.cpp
//  CPP11Language
//
//  Created by Sam on 2017/5/30.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
//“保持语言的稳定性和兼容性” 总结：主要是utf8字符串，虚函数override/final支持。
// 一、c++11宏和类型(考虑和c99兼容）：__STDC_HOSTED__、__STDC__、__VA_ARGS__宏可以替代...、__cplusplus宏用于c和c++混编，非布尔值还可以判断是否支持c++ 11；_Pragma操作符。
// long long 64bit类型, static_assert用于编译时警告,表达式必须是常量。string都是utf-8类型的，可以和utf-16，char*等转换。可用sizeof(类::非静态成员)获取成员大小。
// 二、面向对象语言特性完善：虚函数override/final支持；增加非静态成员变量就地初始化=和{}符号；noexcept函数声明没有异常抛出，如果抛出了则用std::terminate()来终止程序；
// 三、完善拓展模板语法：friend FriendClass就可以声明友元，模板中也可使用；模板函数也支持了默认参数；显式模板实例化和外部模板声明优化链接；匿名和局部的类/结构体等，都可以作为模板实参。
#include <stdio.h>
#include <iostream>
#include <cassert>
using namespace std;
#include "StringTest.hpp"
#include "noexceptTest.hpp"

const char* HelloFunc()
{
    return __func__;
}

const char* WorldFunc()
{
    return __func__;
}


class MyFuncClass
{
public:
    MyFuncClass()
    {
        cout<<"file name:"<<__FILE__<<endl;
        cout<<"line :"<<__LINE__<<endl;
        cout<<"MyFuncClass:"<< __func__<<endl;
    }
    void CallMe()
    {
        cout<<"MyFuncClass, CallMe:"<< __func__<<endl;
    }
    void CallFail(string strContent /*= __func__*/) // __func__在函数内部才是合法的，否则不清楚 __func__的值
    {
        //        int n = 10;
        //        MyLog("My Log n:%d", n);
        cout<<"MyFuncClass, CallFail:"<< strContent<<endl; // 输出：空
    }
};

template <typename T> class X {};
template <typename T> void TempFun(T t){};
struct A{} a;
//struct {int i;}b;           // b是匿名类型变量
typedef struct {int i;}B;   // B是匿名类型

#define PR(...) printf(__VA_ARGS__)
/*
 int main(int argc, const char * argv[]) {
 // 1.CPP 11与C99兼容的宏
 cout<<"Standard clib:"<<__STDC_HOSTED__<<endl; // 编译环境是否包含完整的C库
 cout<<"Standard C:"<<__STDC__<<endl; // 编译器是否和C标准一致
 #ifdef __STDC_VERSION__
 cout<<"Standard C version:"<<__STDC_VERSION__<<endl; // 编译器支持C标准的版本，xcode llvm 8.1未定义改值
 #endif
 #ifdef __STDC_ISO_10646__
 cout<<"ISO/IEC:"<<__STDC_ISO_10646__<<endl;//编译器是否符合__STDC_ISO_10646__标准， xcode llvm 8.1未定义改值
 #endif
 
 //2.__func__, __FILE__, __LINE__宏对于轻量级的调试很有用
 cout<<"HelloFunc() call name:"<< HelloFunc() <<", WorldFunc() call name:"<< WorldFunc() << endl;
 MyFuncClass myFuncObj;
 myFuncObj.CallMe();
 myFuncObj.CallFail("CallFail");
 
 //3. __VA_ARGS__宏可以替代...，因...不可以传递，用__VA_ARGS__却可以实现
 PR("Hello:%s", "samcen\n");
 //#define MyLog(...){\
 //fprintf(stderr, "file:%s, line:%d\t",__FILE__, __LINE__);\
 //fprintf(stderr, __VA_ARGS__);\
 //fprintf(stderr, "\n");\
 //}
 
 //4.宽窄字符串的链接，CPP98/03中char转换为wchar_t是未定义的行为，CPP11可以转换；他们之间也可以连接。
 // cpp 11支持更多Unicode字符串的操作
 StringTest strTestObj;
 strTestObj.Display();
 
 // 5.long long类型引入了CPP11其实已经引入了C99很多编译器也支持，但是VC上之前是用__int64
 // cpp 11要求long long在不同编译器上有不同的长度，但是任何编译器上至少有64位， long long和long long int也是等价的。
 // cpp 11没有定义编译器可拓展的整型，例如48位，128位的，但是编译器拓展因为类型提升整型必须符合规则：
 // 1)长度越长等级越高. 2)编译器拓展的整型位数相等下级别低于标准类型 3）位数相同的有符号和无符号类型等级相同，有符号会提升为无符号。
 signed long long bigInt = LLONG_MIN;
 signed long long bigInt2 = LLONG_MAX;
 unsigned long long bigSint = ULLONG_MAX;
 printf("bigInt %lld \n", bigInt);
 printf("bigInt %lld \n", bigInt2);
 printf("bigInt %llu \n", bigSint);
 
 // 6.__cplusplus宏用于c和c++混编，非布尔值还可以判断是否支持c++ 11
 //#ifdef __cplusplus
 //    extern "C"{
 //#endif
 //
 //#ifdef __cplusplus
 //    }
 //#endif
 #if __cplusplus < 201103L
 #error "Should support c++ 11"
 #endif
 
 // 7.assert宏用于运行时，在<cassert>和<assert.h>中定义，用于调试排查逻辑缺陷，发布时在<cassert>前声明NDEBUG宏可以去掉assert判断
 int n = 0;
 assert(n == 0);// 运行时不为true则报错
 // static_assert用于编译时警告,表达式必须是常量,变量可以用sizeof编译时宏求取为常量，这样可以部分解决运行时忽略的运行分支报错提示，不能转换为常量表达式只能用assert了.
 static_assert(sizeof(n) != 0, "n size must not eq 0");
 
 // 8.noexcept没有异常抛出的声明，如果抛出了那么会调用std::terminate()来终止程序，cpp98中的void excpt_func() throw(int, double) { ... }函数抛出异常的声明被废弃了。
 // 代码块中的try{ throw();} catch(exception e){}还是可以使用的，函数异常废弃一个原因是为了安全性如delete函数和类析构函数默认不抛出异常（因为析构大多时候代表结束程序了),
 // 另一个是为了库代码的性能,stl等库代码中为了更加健壮经常需要函数抛出异常的捕获，有些要特别声明不抛出异常，因为异常处理需要帧栈的全部信息记录很影响性能。
 // 从语法上讲，noexcept修饰符有两种形式，一种就是简单地在函数声明后加上noexcept关键字。比如：
 //    void excpt_func() noexcept;
 //    另外一种则可以接受一个常量表达式作为参数，如下所示：
 //    void excpt_func() noexcept (常量表达式);
 //    常量表达式的结果会被转换成一个bool类型的值。该值为true，表示函数不会抛出异常，反之，则有可能抛出异常。这里，不带常量表达式的noexcept相当于声明了noexcept(true)，即不会抛出异常。
 //   cpp11定义了delete函数，类和结构体的析构函数是不抛出异常的，默认类型的函数是可以抛出异常的。通过显式声明noexcept可以更安全且高效的编写程序库和app。
 noexceptTest exceptTest;
 exceptTest.Display();
 
 // 9.可以用=和{}对非静态成员变量就地初始化，类似静态常量就地初始化效果，同时保留列表初始化(后于就地初始化)。
 // cpp 98/03建议用init提供统一的初始化来解决多构造函数初始化问题，cpp 11可以用就地初始化数据成员来达到比init更加高效和便捷的写法。
 // 非常量的静态成员，还是需要在.cpp内部独立的初始化。
 
 // 10.sizeof()在没有定义类实例的时候，也可以用sizeof(类::非静态成员)获取非静态成员变量大小
 // cpp 98/03中没事实例化类时候需要 sizeof(((类*)0)->非静态成员)获取非静态成员大小。
 
 // 11.友元可以无视private等限制，声明friend class FriendClass的改进（友元破坏了封装建议写get/set进行访问，但是友元确实可以减少很多代码量）可以不用class就可以声明为友元，如：
 // friend FriendClass，这是一个小的改进,但是对于模板类则是大的改进，因为模板之间也可以声明为友元了。如果模板的实例化友元不是类而是int等基础类型，则模板的友元声明会被忽略。
 // 功能模板类传入一个拓展类作为友元是一个好的做法(如拓展类是测试用例类).
 
 // 12.面向对象override/final,只有虚函数才支持这两个关键字，final是不能再派生了；override是编译检查正确重载和方便阅读重载关系(不必不断往父类查找virtual关键字)。借鉴了java和c#的做法。
 
 // 13.cpp 98/03中只支持模板类默认参数,cpp11对模板函数也支持了默认参数且不需要默认参数在最右往左，模板类还是不变要求默认参数从右往左
 // 默认的模板形参只有实例化没有提供的时候才会采用，否则模板的类型还是实例化类型决定。
 
 // 14.显式模板实例化和外部模板声明，因为编译器对于一个.c文件每次都会实例化一个模板，连接器又会剔除重复的模板实例（保存一份实例化代码), 因此在泛型应用很多的项目中浪费很多编译和链接时间
 // 可以通过显示实例化和外部声明来解决，显示模板实例化语法来自cpp98，外部模板则来自cpp 11。该特性一般项目不用管就行，但是看到别人代码要理解。
 //    模板实例化和外部声明可以用于模板类和函数模板。
 //    函数模板：
 //    template<typename T> void fun(T){}
 //    显示实例化为：
 //    template void fun<int> (int);
 //    使用时候正常：
 //    func(3);
 //    其它模板中，对需要使用相同的模板，外部模板声明：
 //    extern template void fun<int> (int);
 //    模板显示实例化和外部模板不能对static的文件域函数，但是可以对类的静态函数，非静态函数。外部模板声明需要在其它文件中，或相同文件的模板实例化前面。
 
 // 15.cpp11中匿名和局部的类/结构体/联合体/枚举，都可以作为模板类和函数模板类的实参(不能实例化时候声明)，cpp98/03中却不支持
 // template<typename T> class X{ X(T t){}; }
 // template<typename T> void TempFun(T t){}
 // struct A{} a;
 // struct {in i;}b;  b是匿名类型变量
 // typedef struct {int I;}B;  B是匿名类型
 // void main()
 // {
 // struct C {} c;           C是局部类型
 // class D{
 // public:
 // int n = 10;
 // };
 // X<A> x1;     C++98通过，C++11通过
 // X<B> x2;     C++98错误，C++11通过
 // X<C> x3;     C++98错误，C++11通过
 // TempFun(a);  C++98通过，C++11通过
 // TempFun(b);  C++98错误，C++11通过
 // TempFun(c);  C++98错误，C++11通过
 // D d;
 // TempFun(d);
 // return 0;
 }
*/
