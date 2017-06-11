//
//  PODDataType.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef PODDataType_hpp
#define PODDataType_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
/*一个类型，如果是平凡的且是标准布局的，那么就是一个POD类型。POD是plain old data,就是一个和C类型一样的内存类型，可以用C函数操作等特点。
 POD对象类型的优点；
 1）字节赋值，代码中可以安全的用memset和memcpy对POD类型进行初始化和拷贝。
 2）提供了对C内存布局兼容，C++程序和C函数进行相互操作，因为POD类型的数据在他们间的操作总是安全的。
 3）保证了静态初始化的安全有效。静态初始化很多时候能够提供程序性能，而POD类型的对象初始化很简单(如.bss段，在初始化中直接被赋值0)。
 理解POD对理解C++ 11中其它概念非常重要。
 
 基础类型都是平凡的，一个类或结构体是平凡的定义：
 1）拥有平凡的默认构造函数和析构函数。自己写了编译器不再提供，但=default关键字可以恢复平凡的版本。
 2）拥有平凡的拷贝构造函数和移动构造函数，=default关键字可以恢复平凡的版本。
 3）拥有平凡的拷贝赋值函数和移动赋值函数，=default关键字可以恢复平凡的版本。。
 4）不能包含虚函数以及虚基类。
 标准库提供了std::is_trivial<T>::value判断。
 
 基础类型都是标准布局的，一个类或结构体是标准布局的定义：
 1）所有非静态成员（主要是数据)有相同的访问权限。
 2)在类或结构体继承时，满足以下两种之一：
 （1）派生类中有非静态成员，且只有一个仅包含静态成员的基类。
 (2)  派生类没有非静态成员, 且基类有非静态成员。
 3）类中第一个非静态成员的类型与基类不同（c++标准要求类型相同的对象必须地址不同，如果相同为了保证基类指针和成员同类指针地址不同，会额外偏移一个字节）。
 4）没有虚函数和虚基类。
 5）所有非静态数据成员均符合标准布局类型，其基类也符合标准布局（这是一个递归定义)。
 标准库提供了std::is_standard_layout<T>::value来判断。
 
 标准库中用std::is_pod<T>::value判断一个类型是否是POD类型。
 */
class CA { CA(){} };
class CB { CB(CB&){} };
class CC { CC(CC&&){} };
class CD {
    CD operator=(CD&){
        return *this;
    }
};
class CE {
    CE (CE&&){
    }
};

class CF {
    ~CF(){}
};
class CG {
    virtual void foo() = 0;
};

class CH : CG {};
class CI {};

class PODA
{
public:
    int x;
    double y;
};

void PrintPlainType();


#endif /* PODDataType_hpp */
