//
//  RvaluePerfectDispatch.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/3.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "RvaluePerfectDispatch.hpp"
void RunCode(double &&m){
    cout << "Call RunCode m:" << m << endl;
} // 这里用右值引用类型参数，实现一个版本即可
void RunHome(double && h){
    cout << "Call RunHome h:" << h << endl;
    
}

void PrintForwardDispatch()
{
    PerfectForward(1.5, RunCode);
    PerfectForward(8, RunHome);
}
