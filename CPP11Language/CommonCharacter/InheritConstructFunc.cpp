//
//  InheritConstructFunc.cpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "InheritConstructFunc.hpp"
int HasPtrMem::cCount = 0;
int HasPtrMem::cpCount = 0;
int HasPtrMem::dCount = 0;
HasPtrMem GetTempHasPtrMem()
{
    return HasPtrMem();
}
