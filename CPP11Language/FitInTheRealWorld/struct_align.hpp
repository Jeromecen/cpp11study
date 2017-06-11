//
//  struct_align.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/10.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef struct_align_hpp
#define struct_align_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

struct alignas(alignof(double) * 4) ColorVector{ // 没有alignas(32)，alignof大小是8
    double r;
    double g;
    double b;
    double a;
};

template <typename T>
class FixedCapacityArray
{
public:
    void PushBack(T t){};
//    alignas(1) char  data;
    alignas(T) char  data[1024] = {0}; // alignas(T)要在前面定义，aligna根据类型来定义数据成员的对齐大小。
};

struct A {  // non-POD type
    int avg;
    A (int a, int b) : avg((a+b)/2) {}
};
typedef std::aligned_storage<sizeof(A),alignof(A)>::type A_pod;

union U {
    int i;
    char c;
    double d;
    U(const char* str) : c(str[0]) {}
};       // non-POD

typedef std::aligned_union<sizeof(U),int,char,double>::type U_pod;

void PrintAlign();
void StlAlignTest();
#endif /* struct_align_hpp */
