//
//  useinlineNameSpace.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "useinlineNameSpace.hpp"
using namespace sandy::ns_adl;
//void ADLFunc( SandyA *a){
//    cout<< "Sandy A in ADLFunc a:" << a->a<< endl;
//}
 void ADLFunc( A a){}  //ADLFunc 定义在namespace ns_adl中
