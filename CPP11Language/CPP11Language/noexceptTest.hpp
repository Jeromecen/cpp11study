//
//  noexceptTest.hpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef noexceptTest_hpp
#define noexceptTest_hpp

#include <stdio.h>
class noexceptTest
{
    void Throw();
    void NoBlockThrow();
    void BlockThrow() noexcept;
public:
    void Display();
    
};
#endif /* noexceptTest_hpp */
