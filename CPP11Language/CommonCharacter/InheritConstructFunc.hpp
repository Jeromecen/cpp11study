//
//  InheritConstructFunc.hpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef InheritConstructFunc_hpp
#define InheritConstructFunc_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
/* 默认构造函数，构造函数，拷贝构造函数，赋值函数，析构函数基本认识：
1.编写这些函数的目的是提供自己对资源和数据的拷贝复制。
2.只有一个拷贝构造函数，赋值函数，析构函数；构造可以有多个版本，如果提供了构造函数那么默认构造函数编译器将不提供(其它3个函数也一样)。
3.调用和参数：默认构造函数和子类实现了父类相同参数的构造函数，构造先调用父类然后子类构造，析构时相反；
 拷贝构造函数是在对象被创建时调用的（因左边初始化会调用一次默认构造函数），而赋值函数只能被已经存在了的对象调用，子类拷贝和赋值函数没有"透传"父类所以不会调用父类的拷贝和赋值函数，
 拷贝和赋值时候注意非引用参数和函数返回值会发生默认构造和赋值,临时变量的拷贝构造也会被编译器优化掉。
 其实拷贝构造函数和赋值函数都应该少用，而是用好构造函数（using不用透传)和析构函数(虚析构)，对象用指针传递，组合类用initWithOther()实现就可以了。
4.子类构造函数需要在初始化列表中显式声明，调用父类的构造函数。cpp11增加了重用父类构造函数的语法和成员就地初始化，避免了大量书写“透传"父类构造函数。
5.析构函数都声明为虚析构函数，删除指向子类的父类指针，时候子类析构函数和父类析构函数才能都被调用，否则只是调用父类的析构函数。
 */
class Base
{
public:
    Base()
    {
        cout<<"Base()" << endl;
    }
    
    Base(int i)
    {
        cout<<"Base call" << endl;
    }
    
    void f(double i){
        cout<<"Base:"<<i<<endl;
    }
    void print()
    {
        cout<<"Base print call"<<endl;
    }
    
    virtual ~Base()
    {
        cout<<"~Base() call"<<endl;
    }
    
};

class Drived: public Base
{
public:
    using Base::Base;
//    Drived()
//    {
//         cout<<"Drived()" << endl;
//    }
    
    Drived(int i)
    {
        cout<<"Drived call" << endl;
    }
    
    using Base::f;// 1）同名的函数，参数类型不同，那么需要using BaseClass::func；派生类才能使用。
    void f(int i){
        cout<<"Drived:"<<i<<endl;
    }
    
    void Print()
    {
        cout<<"Drived Print call:"<<endl;
        f(10.01f);
        f(100);
        print();
        Base *pDrive = new Drived();
        delete pDrive;
        pDrive = NULL;
    }
    virtual ~Drived()
    {
        cout<<"~Drived() call"<<endl;
    }
};

class A2
{
public:
    A2()
    {
        
    }
    
    A2(int i)
    {
        cout<<"A(int i)"<<endl;
    }
};

class A
{
public:
    A()
    {
        count++;
         cout<<"A() count:"<< count << endl;
    }
    
    A(int i)
    {
        cout<<"A(int i)"<<endl;
    }
    int count = 0;
//private:
    A(double d,int i)
    {
         cout<<"A(double d,int i)"<<endl;
    }
    
    A(float f,int i,const char* str, char c = 'a')
    {
       cout<<"A(float f,int i,const char* c)"<< ", c:" << c <<endl;
       count = 300;
    }

    
//    A(const A &a)
//    {
//        cout<<"A (const A &a) call"<<endl;
//    }
    //...等等系列的构造函数版本号
};

class B: public A, A2
{
public:
    using A::A; // 2）会类似默认构造赋值析构函数一样，如果有调用会把父类的多种非私有构造函数继承下来（不会提供默认无参构造了)，默认参数会产生多个版本但效果都是一个，没有调用则不会继承(节省内存)。
    using A2::A2; // 3）A和A2都有(int i)类型构造函数，B(int i)声明可以覆盖重名问题,避免重命名冲突。
    B(int i):A(i) // 4）原来的手动"透传"构造函数还是支持的，如果本地初始化不能满足要求就可以这样做。
    {
        cout<<"B(int i)"<<endl;
    }
    
    B()
    {
        cout<<"B() count:"<< count << endl;
    }
    // 拷贝构造函数，如果没有默认无参的构造函数，还不允许拷贝
    B(const B &b)
    {
        count++;
        cout<<"B(const B &b) call, this count:"<< count << ", b.count:" << b.count << endl;
    }
    
    B& operator =(const B &b){
        // 释放前面的
        // 只是构造函数调用，这里没有拷贝也没有赋值
        B *other = new B();
        cout <<"B& operator = call" <<endl;
        return *other;
    }
    
    int d{0}; // 5）非基类的成员不能初始化，需要用本地初始化，否则需要原来的“透传"方式。
    void Print()
    {
        cout<<"B Print call"<<endl;
        cout<<"same name contructor start"<<endl;
        B b(1);
        cout<<"same name contructor end"<<endl;
        B b1(1.0f, 1);
        B b2(1.0f, 1, "jessecen", 'j');
        B b3(1.0f, 1, "jessecen2");// 6）默认参数还是可以被继承的，还是调用了父类A(float f,int i,const char* str, char c = 'a')函数，count == 300
        cout<< "拷贝构造函数 call:"<<endl;
//        B *b4 = NULL;
//        *b4 = b3;// 7）这里会调用赋值函数，因为b4虽然为NULL但是也是有值的，所以对象指针最好直接赋值地址，避免拷贝或赋值产生。
        B b4 = b3; // 8）b4会先调用父类默认构造函数，然后整个表达式会调用拷贝函数，输出：A() B(const B &b)。
        cout<< "赋值函数 call:"<<endl;
        b2 = b3; //9）赋值函数调用，输出：A() B() B& operator = call
        cout<<"B Print call end."<<endl;
//        B b5 = b4;

    }
};

class HasPtrMem
{
public:
    HasPtrMem():m(new int(0))
    {
        cout<< "HasPtrMem construct, cCount:" << cCount << endl;
    }
    
    HasPtrMem(const HasPtrMem &b):m(new int(*b.m))
    {
        cout<< "HasPtrMem copy construct, cpCount:" << cpCount << endl;
    }
    
    ~HasPtrMem()
    {
        cout<< "HasPtrMem destruct, dCount:" << dCount << endl;
    }
    int *m;
    static int cCount;
    static int cpCount;
    static int dCount;
};

HasPtrMem GetTempHasPtrMem();

#endif /* InheritConstructFunc_hpp */
