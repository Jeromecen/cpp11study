//
//  MoveContructFunc.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/3.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "MoveContructFunc.hpp"

Moveable GetTemp() {
    Moveable tmp = Moveable();
    cout << hex << "Huge Mem from " << __func__<< " @" << tmp.h.c << endl; // Huge Mem from GetTemp @0x603030
    return tmp;
}

void PrintMoveNoexcept()
{
    Maythrow m;
    Nothrow n;
    Maythrow mt = move_if_noexcept(m);// Maythorow copy constructor.
    Nothrow nt(move(n)); // noexcept不影响移动构造函数的调用
    Nothrow nt2 = move_if_noexcept(nt);// Nothorow move constructor.
}
