//
//  MoveContructFunc.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/3.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef MoveContructFunc_hpp
#define MoveContructFunc_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
/*
一、移动构造/移动赋值函数，右值引用(本身为右值或move/forward/static_cast<T&&>转换才是右值引用)
右值引用参数构建的构造或赋值才会触发(窃为己用,之前对象会被析构调动，其实移动构造和移动赋值函数都类似构建了一个新对象，后面会有一个对应新对象的析构函数调用)。
1.移动构造函数和移动赋值函数：
移动构造就是避免通过临时对象获取对象，会产生多次构造和析构问题，如果有大堆内存(几mb以上)，会造成很大的性能问题。
其实这个问题，早就可以用在临时变量中返回堆指针来解决，但是用堆指针需要程序员编写较多代码且需要管理内存的生命周期。
用移动构造函数，返回的是对象，不需要太多的指针代码，且不需要知道声明周期，是一个比较直观便捷的做法。缺点是要重写学习。
// &&h是右值引用，也就是临时变量的引用声明。构造赋值这里不产生新堆而是指针赋值。
HasPtrMem(HasPtrMem &&h):m(h.m) {
    h.d = nullptr; // 一定要赋值为空，避免临时变量超过生命期(调用栈返回)调用析构产生m为野指针.
    cout << “move construct call”<<endl;
}
拷贝构造函数的省略。
智能指针的拷贝。
链表拼接。
容器内资源的置换。
都会有对临时或非临时指针资源的拷贝，拷贝会导致新堆内存的申请，旧堆内存的释放，很多地方其实是可以通过移动解决的，因此引入通用的移动语义，对于提升标准库的性能也是很有作用的。其实也是可以通过指针来解决的，移动构造只是简化。
移动构造的调用：cpp11中对右值引用拷贝就会检查使用移动构造函数，右值引用也可以用在原来常量左值引用的地方。
也存在移动赋值函数，对于已经存在的对象进行赋值，如果是右值引用则会调用移动赋值。移动构造和移动赋值都类似拷贝构造和赋值函数，编译器会默认提供一个，如果重载了就不会再提供（拷贝和赋值，移动和赋值会绑定，实现了一个就不生成两个）。

2.左值引用和常量左值引用，右值引用特性：
左值：c语言是表达式左边的值，c++和c一样但是增加了定义：可标识的类型/函数/对象名,可以取地址的就是左值。
右值：c语言是表达式右边的值，c++和c一样但是增加了定义：没有标识号，不能取地址的，将亡的.
例如：
a = 3;a是左值，3是右值
a = b + c, a是左值，b+c是右值
非引用返回的函数的临时变量值是右值，因为取不到它的名称和地址，也是将亡的。
a = 1+3, 1+3产生的临时变量值也是右值。
类型转换函数的返回值也是右值。
Lambda表达式也是右值。
在内存堆栈中无论是常量，表达式运算，函数参数压栈和返回值，赋值右边的，不能取到名字和地址的，将要消亡的就是右值。
右值没有名称只能通过引用的方式找到它的存在，Cpp11新增了右值引用相关的表达式，这样表达式通常是将要被移动的对象（移为它用），比如：返回右值引用T&&的函数返回值，std:move的返回值，转换为T&&类型的转换函数的返回值。
Cpp 98/03中的引用类型，是具名的左值引用，cpp11引入的右值引用是对不具名的临时变量的引用，引用都只是别名，没有绑定对象所需的内存。

3.Cpp 11引入的右值引用,和左右值的绑定规则：
T &&a = ReturnRvalue(); // a就是函数返回的没有名称的右值的引用，是一个没有名字对象的别名。
该语句执行情况：ReturnRvalue在没有右值引用下会直接释放(析构)掉函数返回的右值，这里用了右值引用将不会释放，直到a超过生命期。相比T a = ReturnRvalue();会少一次右值析构和a拷贝构造的开销。（当然用指针也可以解决，只是没有那么方便和直观且要管理生命周期)。
右值引用不小心会指向一个左值：
T&& foo = T(); //右值引用
auto&& bar = foo; // 不是右值引用，而是左值
实际上，T&&有两种含义，一种就是常见的右值引用；另一种是即可以是右值引用，也可以是左值引用

右值和左值绑定规则：
Cpp11引入的右值引用是不能绑定要任何左值的，右值常量可以引用常量右值为了语义完整引入，用于移动和转发语义。
Cpp98引入的非常量左值引用是不能帮到到任何右值的。
Cpp98引入的常量左值引用(是个万能引用)是可以帮到到右值的(常量和非常量都可以赋值给它)，缺点是不能修改引用的对象，用于拷贝语义。所以原来使用(const AClass &a)的地方可以用(AClass &&a)来代替，且可以修改引用到的对象，但是一般对于临时值不会修改。除非使用移动语义，移动语义如下：

4.移动语义move，判断引用类型:
void AcceptRvalueRef(Copyable &&s)
{
    // move在<utility>中定义,将一个左值变成一个右值(原来是右值没变化)，这样对象赋值就会调用移动构造函数， 如果没有则会调用拷贝构造。
    // 如果左边是Copyable &&news，则news是原来对象的别名,也不会调用任何构造函数。
    // 移动构造函数声明为：Copyable(Copyable &&o){ 指针赋值，指针置空;}，
    Copyable news = std::move(s);
}
一个引用类型判断，用标准库在<type_traits>头文件中提供了三个模板函数：
is_rvalue_reference, is_lvalue_reference, is_reference判断。
如：cout<< is_rvalue_reference<string &&>::value;配合decltype可以对变量的类型进行判断。

5.模板库中移动构造函数的应用，判断类型移动：
标准库的头文件<type_traits>里，我们可以通过一些辅助类的判断一个类型是否可以移动(是否有移动构造函数，移动赋值函数)，用is_move_constructible, is_trivially_move_constructible, is_nothrow_move_constructible使用方法是：
cout<< is_move_constructible<TypeClass>::value;
使用移动，可以实现高效的置换函数，对于泛型编程来说是很有意义的，如:
template<class T>
void swap(T &a, T &b)
{
    T tmp( move(a) );
    a = move(b);
    b = move(tmp);
}

6.编写移动构造函数：
写移动构造函数时候（右值引用不能用常量右值)，临时变量赋值给指针，临时变量赋空，拷贝构造也要写下；调用时候记得写move()将左值指针或句柄转换为右值才正确(非左值的不用move比如函数返回值)，转换为右值后变量的指针不能再使用。
移动构造函数可以声明为noexcept，这样移动抛出异常马上终止程序。std::move_if_noexcept代替std::move可以实现移动构造有noexcept修饰时候才用，否则用拷贝构造函数。
编译器一般对于临时返回变量，有RVO/NRVO(return value optimization, name return value optimization),一般都会开启，从而返回值的任何拷贝和移动都没有了，但是有些编译器无法完成的，用移动语义就可以解决，一般对于库编写者用得多。
 7.右值引用，移动构造函数实例
 其实移动构造函数也是构造了一次对象(右值引用的对象会被析构掉)，后面会有对应的析构函数：
 noexcept修饰的移动/赋值构造函数实例：
 move_if_noexcept是有noexcept版本的移动构造函数和移动赋值函数才会被调用，否则会调用拷贝构造函数，用于避免移动构造函数产生异常后抛出。
*/
class HugeMem{
public:
    HugeMem(int size): sz(size > 0 ? size : 1) {
        c = new int[sz];
    }
    ~HugeMem() { delete [] c; }
    HugeMem(HugeMem && hm): sz(hm.sz), c(hm.c) {
        hm.c = nullptr; // 赋值为空，后面会对hm临时变量调用析构函数,后面不能再用hm.c
    }
    int * c;
    int sz;
};
class Moveable{
public:
    Moveable():i(new int(3)), h(1024) {}
    ~Moveable() { delete i; }
    Moveable(Moveable && m):
    i(m.i), h(move(m.h)) { // 强制转为右值，以调用移动构造函数
        m.i = nullptr; // 赋值为空，接着m临时变量会被调用析构函数，后面不能再使用m.i
    }
    int* i;
    HugeMem h;
};

Moveable GetTemp();

struct Maythrow {
    Maythrow() {}
    Maythrow(const Maythrow&) {
        std::cout << "Maythorow copy constructor." << endl;
    }
    Maythrow(Maythrow&&) {
        std::cout << "Maythorow move constructor." << endl;
    }
};
struct Nothrow {
    Nothrow() {}
    
    Nothrow(const Nothrow&) {
        std::cout << "Nothorow copy constructor." << endl;
    }
    Nothrow(Nothrow&&) noexcept {
        std::cout << "Nothorow move constructor." << endl;
    }
    
};

void PrintMoveNoexcept();


#endif /* MoveContructFunc_hpp */
