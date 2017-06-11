//
//  ClassStructDefineInput.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef ClassStructDefineInput_hpp
#define ClassStructDefineInput_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
/* C++11中，声明字面量操作符的规则如下：
 【】如果字面量是整型数，那么字面量操作符只可接受unsigned long long 或者 const char*为其参数。当unsigned long long 无法容纳该字面量时，编译器自动将该字面量转化为以\0为结束符的字符串，并调用以const char*为参数的版本进行处理。
 【】如果字面量为浮点数，则字面量操作符只可接受long double 或者const char*为参数。其他规则同上。
 【】如果字面量是字符串，则字面量操作符函数值可接受const char* ,size_t为参数。
 【】如果字面量为字符，则字面量操作符函数只可接受一个char为参数。
 【】在字面量操作符函数的声明中，operator""与用户自定义的后缀之间必须有空格。
 【】后缀建议以下划线开始，否则会被编译器警告。
 */

typedef unsigned char uint8;
struct RGBA
{
    uint8 r;
    uint8 g;
    uint8 b;
    uint8 a;
    RGBA( uint8 R, uint8 G, uint8 B, uint8 A = 0): r(R), g(G), b(B),a(A) {}
};

RGBA operator "" _C( const char* col, size_t n);  //长度为n的字符串col
std::ostream & operator << (std::ostream & out, RGBA & col);
void blend( RGBA && col1, RGBA && col2);

struct Watt
{
    unsigned int v;
};

Watt operator "" _w(unsigned long long v);
void PrintDefineClassStruct();
#endif /* ClassStructDefineInput_hpp */
