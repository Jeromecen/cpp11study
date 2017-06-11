//
//  generate_attribute.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/11.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "generate_attribute.hpp"
[[ noreturn ]] void ThrowAway(){
    cout<< "ThrowAway()" << endl;
    throw "expection";
}

void DoSomeThing1()
{
    cout << "DoSomeThing1()" << endl;
}

void DoSomeThing2()
{
    cout << "DoSomeThing2()" << endl;
}

void PrintInfo()
{
    DoSomeThing1();
//    ThrowAway(); //声明了[[ noreturn ]]，后面代码不再执行
    DoSomeThing2();
}
