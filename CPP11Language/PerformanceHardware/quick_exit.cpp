//
//  quick_exit.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/8.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "quick_exit.hpp"
void CloseDevice()
{
    cout << "CloseDevice after quick_exit" << endl;
}

void PrintQuitExit()
{
    QuickExitA a;
//    at_quick_exit(CloseDevice);
//    quick_exit();
    atexit(CloseDevice);
    exit(1);
}
