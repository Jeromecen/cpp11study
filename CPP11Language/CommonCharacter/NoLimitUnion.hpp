//
//  NoLimitUnion.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef NoLimitUnion_hpp
#define NoLimitUnion_hpp
#include <stdio.h>
#include <complex>
#include <iostream>
using namespace std;
union unum
{
    int i;
//    complex<double> com; // cpp 98编译不过，cpp 11支持
    static int s_num; // cpp11 也可以用静态成员，但是会导致所有unum类型的对象都有一个同样的s_num,所以一般用于静态函数返回一个常量。
    static int GetSNum(){ return 32;}
public:
//    unum()
//    {
//        new (&com) complex<double>;
//    }
//    ~unum()
//    {
//        com.~complex<double>();
//    }
};
class Student
{
public:
    Student(bool g, int a):gender(g), age(a){}
private:
    bool gender;
    int age;
};
// 匿名联合体，作为类的变长成员，给类的设计节省空间带来了很大的灵活性。
class Singer{
public:
    enum Type{
        NATIVE,
        STUDENT,
        FOREIGN,
    };
    
    Singer(bool g, int a):s(g,a){
        t = STUDENT;
        cout<< "Singer(bool g, int a) a: " <<  dec << a << endl; // cpp11格式化输出用dec
    }
    Singer(int i):id(i)
    {
        t = NATIVE;
        cout<< "Singer(int i) id: " << dec << id << endl; // cpp11格式化输出用dec
    }
    Singer(char * n)
    {
        int len = 0;
        char *pN = n;
        while(*pN != '\0')
        {
            len++;
            pN++;
        }
        int cpyLen = len > 19? 19:len;
        memcpy(name, n, cpyLen);
        name[cpyLen] = '\0';
        cout<< "Singer(char * n) name: " << name << endl;
    }
private:
    enum Type t;
    union{
        int id;
        Student s;
        char name[20];
    };
};
void PrintUnion();
#endif /* NoLimitUnion_hpp */
