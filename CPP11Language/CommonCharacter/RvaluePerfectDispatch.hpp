//
//  RvaluePerfectDispatch.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/3.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef RvaluePerfectDispatch_hpp
#define RvaluePerfectDispatch_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
/*
右值引用函数模板(引用折叠和推导规则)，forward<T>(t),右值模板函数，实现完美转发(用右值引用作为参数，简化为一个右值引用分发函数)：
因为一个函数调用另一个函数，在函数参数传递过程中，可能发生构造析构，基础类型值栈内存拷贝，该开销其实可以通过引用来解决。
这里的完美转发是指在函数模板中，完全依照模板的参数类型，将参数传递给函数模板中调用的另外一个函数，不产生任何参数拷贝花销(引用类型没有拷贝的开销)。
Cpp11通过引入一条所谓”引用折叠”的新语言规则，并结合新的模板推导规则来完成完美转发，所以完美转发只在模板函数中。
引用折叠原则：
在函数模板T&&t参数类型中，实参真实类型，先判断形参的类型或实参（本身是什么引用类型）有左值引用就是左引用，然后判断形参或实参（本身是什么引用类型）有右值引用就是右值引用：
* A& & 折叠成 A&
* A& && 折叠成 A&
* A&& & 折叠成 A&
* A&& && 折叠成 A&&
第二条是特殊模板参数推导原则：
1.如果fwd传进的是个A类型的左值，那么T被决议为A&。 2.如果fwd传进的是个A类型的右值，那么T被决议为A。
完美转发定义：
完美转发的模板函数，参数类型用T&&t, 目标转发函数也用右值引用。
 例如：
 void foo(X&& x)
 {
 // ...
 }
 
 template<class T>
 void fwd(T&& t) // 这里要声明为右值引用
 {
 foo(std::forward<T>(t)); // 这里要用右值引用转换符转换为右值引用（foo的左值引用,常量引用就不用声明了)，forward<T>(t)等价于move(t),只是区分。
 }
 A x;
 fwd(x); //推导出fwd(A& &&) 折叠后fwd(A&)
 
 A foo();
 fwd(foo());//推导出fwd(A&& &&) 折叠后 fwd(A&&)
 
 Cpp11标准库中有大量完美转发的实现，make_pair, make_unique等，还可以减少一些函数的const和非const版本的重复，无论是从性能还是代码简化上完美转发都非常完美。
*/
template<typename T, typename U>
void PerfectForward(T && t, U & func) // 这里用了类型折叠实现一个版本即可，根据形参和实参真实的t类型，可能是左值引用，也可能是右值引用
{
    func(forward<T>(t));// 这里将传入的类型转换为右值引用类型
}

void RunCode(double &&m);
void RunHome(double && h);
void PrintForwardDispatch();
#endif /* RvaluePerfectDispatch_hpp */
