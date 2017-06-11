//
//  ClassStructDefaultMethod.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/9.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef ClassStructDefaultMethod_hpp
#define ClassStructDefaultMethod_hpp

#include <stdio.h>
#include <type_traits>
#include <iostream>

using namespace std;

class PODClass
{
public:
//    PODClass() // 会导致非POD的。
//    {
//        
//    }
    PODClass() = default; // 恢复编译器提供的默认函数。是POD的了。
    PODClass(int i):id(i)
    {
        
    }
    int id;
};

void TestClassPOD();
#endif /* ClassStructDefaultMethod_hpp */
