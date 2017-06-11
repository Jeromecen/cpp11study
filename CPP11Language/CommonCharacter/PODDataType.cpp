//
//  PODDataType.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/4.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "PODDataType.hpp"
void PrintPlainType()
{
    std::cout << std::is_trivial<CA>::value << std::endl;  // 有不平凡的构造函数
    std::cout << std::is_trivial<CB>::value << std::endl;  // 有不平凡的拷贝构造函数
    std::cout << std::is_trivial<CC>::value << std::endl;  // 有不平凡的拷贝赋值运算符
    std::cout << std::is_trivial<CD>::value << std::endl;  // 有不平凡的拷贝赋值运算符
    std::cout << std::is_trivial<CE>::value << std::endl;  // 有不平凡的移动赋值运算符
    std::cout << std::is_trivial<CF>::value << std::endl;  // 有不平凡的析构函数
    std::cout << std::is_trivial<CG>::value << std::endl;  // 有虚函数
    std::cout << std::is_trivial<CH>::value << std::endl;  // 有虚基类
    
    std::cout << std::is_trivial<CI>::value << std::endl;  // 平凡的类
    
    if (is_pod<PODA>::value)
    {
        std::cout << "before" << std::endl;
        PODA a;
        a.x = 8;
        a.y = 10.5;
        std::cout << a.x << std::endl;
        std::cout << a.y << std::endl;
        
        size_t size = sizeof(PODA);
        char *p = new char[size];
        memcpy(p, &a, size); // POD类型可以直接对类型进行拷贝
        PODA *pA = (PODA*)p;
        
        std::cout << "after" << std::endl;
        std::cout << pA->x << std::endl;
        std::cout << pA->y << std::endl;
        
        delete p;
    }
}
