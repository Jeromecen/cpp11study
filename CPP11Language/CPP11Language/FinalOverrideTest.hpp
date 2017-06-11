//
//  FinalOverrideTest.hpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef FinalOverrideTest_hpp
#define FinalOverrideTest_hpp

#include <stdio.h>
class Object
{
public:
//    void Print() final;// 只有虚函数才能用final
    virtual void  Print() = 0; // 纯虚函数不能final
    void Sum();
    virtual float Area();
    virtual float Square();
};

class Base: public Object
{
public:
    void Print() final;
    float Area() override; // 原来非override的方式还是可以重载的, 编译器会给一个警告
//    float Squrae() override; // 拼写不正确会有警告
    float Square() override; // 解决了拼写导致不正确重载问题，和阅读需要不断往父类查找virtual声明难于阅读代码的问题
//    void Sum() override;
};

class FinalOverrideTest:public Base
{
public:
//    void Print(); // final的虚函数不能重载了
};
#endif /* FinalOverrideTest_hpp */
