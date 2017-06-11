//
//  PragmaTest.hpp
//  CPP11Language
//
//  Created by Sam on 2017/5/30.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

//#ifndef PragmaTest_hpp
//#define PragmaTest_hpp
//#pragma once
_Pragma("once");
// 上面三句话是一样的结果都是向编译器传递编译标准以外的信息，_Pragma是和sizeof一样的编译器操作符，在宏中可以展开因此会更加灵活些
#include <stdio.h>

//__cplusplus宏用于c和c++混编,
#ifdef __cplusplus
extern "C"{
#endif
    
#ifdef __cplusplus
}
#endif

#if __cplusplus < 201103L
    #error "Should support c++ 11"
#endif
//#endif /* PragmaTest_hpp */
