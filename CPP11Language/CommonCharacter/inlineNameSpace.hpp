//
//  inlineNameSpace.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef inlineNameSpace_hpp
#define inlineNameSpace_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
namespace sam
{
    namespace a
    {
        struct KnifeA{
            KnifeA()
            {
                cout << "Knife in a" << endl;
            }
        };
    }
    
    inline namespace b
    {
        struct KnifeB{
            KnifeB()
            {
                cout << "Knife in inline namespace b " << endl;
            }
        };
        template <typename T>
        void PrintFunc(T t)
        {
            cout << "PrintFunc in inline namespace b " << endl;
        }
    }
    
    namespace{
        struct Knife2{
            
        };
        template <typename T>
        void PrintTest(T t)
        {
            cout << "PrintTest in inline namespace b " << endl;
        }
    }
    
//    Knife a; // 不能使用
    namespace other
    {
//        Knife a; // 不能使用
        Knife2 b;
    }
    
    using namespace a; // 开放命名空间给外部用，避免外部知道太多子命名空间
}
#endif /* inlineNameSpace_hpp */
