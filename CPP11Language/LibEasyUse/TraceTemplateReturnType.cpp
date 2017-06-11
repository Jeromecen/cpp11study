//
//  TraceTemplateReturnType.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "TraceTemplateReturnType.hpp"

auto NormalAddTest(int a, char c) -> int
{
    return a + static_cast<int>(c);
}

double foo(int i)
{
    return double(i) + 1.1f;
}
int foo(double d)
{
    return (int)d;
}

void PrintTraceTypeTest()
{
    int a = 10;
    int b = 20;

    float c = 10.2f;
    float d = 10.4f;
    
    int s1 = Sum(a, c);
    float s2 = Sum(b, d);
    cout << "PrintTraceTypeTest:" << endl;
    cout << "s1:" << s1 << endl;
    cout << "s2:" << s2 << endl;
    
    float s3 = SumSameType(c, d);
    cout << "s3:" << s3 << endl;
    
    float mc = 10.2f;
    float md = 10.4f;
    float ms = Multi(mc, md);
    cout << "ms:" << ms << endl;
    
    int utf8value = NormalAddTest(1, 'a');
    cout << "utf8value:" << utf8value << endl;

    // 使用追踪返回类型，实现根据不同参数返回不同类型的函数转发效果
    cout << "Forward 1 :" << Forward(1.2f) << endl;
    cout << "Forward 2 :" << Forward(2) << endl;
}
