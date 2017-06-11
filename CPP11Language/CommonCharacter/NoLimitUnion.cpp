//
//  NoLimitUnion.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "NoLimitUnion.hpp"
void PrintUnion()
{
    // 若unum有complex<double> com成员，则通不过编译，因为有非POD的成员，重写了默认构造函数，会导致unum默认构造函数不再提供，其它构造赋值函数也是一样的。
    // 如果有非POD成员，但是联合体提供了自己的构造函数和析构函数，都是可以正常声明对象的。
    unum uObj = {0};// 有非POD成员不能进行{0}初始化，初始化时候是将所占的最大字节全部初始化为0.
    uObj.i = 0;
    
    Singer student(true, 20);
    int id = 10010;
    Singer native(id);
    string name = "岑家园";
    char* str = const_cast<char*>(name.c_str()); // 常量类型转换为非常量类型
    Singer foreigner(str);
}
