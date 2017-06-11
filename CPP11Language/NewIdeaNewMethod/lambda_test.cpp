//
//  lambda_test.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/9.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "lambda_test.hpp"
void LambdaTest()
{
    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y) ->int{return x+y;};
    auto totalChild2 = [=]() ->int{return girls + boys;};
    
    auto num = totalChild(girls, boys);
    cout << "LambdaTest()" << endl;
    cout << "num:" << num << endl;
    cout << "num2:" << totalChild2() << endl;
    
    []{};
    int a = 3;
    int b = 4;
    [=] {return a+b;};
    auto func1 = [&](int c) {b = a+c; return b;};
    auto func2 = [=,&b](int c)mutable ->int {return b = b + a +c;}; // 上下文中的b被使用了，捕获列表是lambda最大的特点。捕获列表可以传值，也可以传引用。
    cout << "func1:" << func1(2) << endl; // 输出5
    cout << "func2:" << func2(1) << endl; // 输出9，而不是8
    
    if( a >= 3)
    {
        auto func3 = [=]() ->int{return a + b;}; // 捕获的是函数内的变量，而不是{}内的。
        cout << "func3:" << func3() << endl;
    }
    const int ca = 10;
    static int sa = 20;
    int *pn = new int(30);
    auto func4 = [=,&pn]()->int{return ca +sa + *pn;}; // llvm可以捕获静态，常量，堆的数据
    cout << "func4:" << func4() << endl;
}
