//
//  quick_exit.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/8.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef quick_exit_hpp
#define quick_exit_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;
struct QuickExitA
{
    ~QuickExitA()
    {
        cout << "~QuickExitA call" << endl;
    }
};

void CloseDevice();
void PrintQuitExit();
#endif /* quick_exit_hpp */
