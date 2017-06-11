//
//  ClassStructDefaultMethod.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/9.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "ClassStructDefaultMethod.hpp"

void TestClassPOD()
{
    PODClass podObj;
    cout << "TestPOD test:" << endl;
    cout << "is pod:" << is_pod<PODClass>::value << endl;
}
