//
//  noexceptTest.cpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "noexceptTest.hpp"
#include <iostream>
using namespace std;
void noexceptTest::Throw()
{
    throw 1;
}
void noexceptTest::NoBlockThrow()
{
    Throw();
}
void noexceptTest::BlockThrow() noexcept
{
//    Throw();
}


struct A {
    
    ~A() {
//        throw 1; // 默认类和结构体析构函数是不抛出异常的，如果抛出了那么调用std:ternimate()
    }
};

struct B {
    ~B() noexcept(false) { throw 2; }
};

struct C {
    B b;
};

void funA() {
    A a;
}

void funB()
{
    B b;
}

void funC() {
    C c;
}

void noexceptTest::Display(){
   // 定义函数抛出异常，默认是抛出的有异常可以捕获到，如果定义了不抛出异常的函数抛出了异常则调用std::ternimate()
    try {
        Throw();
    }
    catch(...) {
        cout << "Found throw." << endl;     // Found throw.
    }
    
    try {
        NoBlockThrow();
    }
    catch(...) {
        cout << "Throw is not blocked." << endl;    // Throw is not blocked.
    }
    
    try {
        BlockThrow();   // terminate called after throwing an instance of 'int'
    }
    catch(...) {
        cout << "Found throw 1." << endl;
    }
    
    // cpp 11 delete函数和类和结构析构函数默认是不抛出异常的(抛出则终止程序)，但是如果自定义了抛出异常，那么无论是继承函数关联该类或结构体，都会抛出异常
    try {
        funB();
    }
    catch(...){
        cout << "caught funB." << endl; // caught funB.
    }
    
    try {
        funC();
    }
    catch(...){
        cout << "caught funC." << endl; // caught funC.
    }
    
    try {
        funA(); // terminate called after throwing an instance of 'int'
    }
    catch(...){
        cout << "caught funA." << endl;
    }
}
