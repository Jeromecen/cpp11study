//
//  useinlineNameSpace.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef useinlineNameSpace_hpp
#define useinlineNameSpace_hpp

#include <stdio.h>
#include "inlineNameSpace.hpp"
#include <map>
using namespace std;
namespace sandy{
    using namespace sam;
//  如果不是inline namespace b，那么这里不能重载也就是特例化PrintFunc
    template <typename T>
    void PrintFunc(T t)
    {
        cout << "PrintFunc in sandy t:" << t<< endl;
    }
    
    // 其实用匿名函数也可以实现上述效果
    template <typename T>
    void PrintTest(T t)
    {
        cout << "PrintTest in sandy " << endl;
    }
    
    struct SandyA{
        SandyA(int i)
        {
            a = i;
            cout<< "Call SandyA(int i)" << endl;
        }
        int a;
        
        void ADLFunc( SandyA *a){
            cout<< "Sandy A in ADLFunc a:" << a->a<< endl;
        }
    };
    
    namespace ns_adl
    {
        struct A{};
        void ADLFunc( A a);  //ADLFunc 定义在namespace ns_adl中
    }
    
    template<typename T>
    using MapString = map<T, string>;
    
//    template<typename C>
//    typedef map<C, char*> MapString2; // a typedef cannot be a template
//    extern void ADLFunc( SandyA *a); //ADLFunc 定义在namespace ns_adl中
}


#endif /* useinlineNameSpace_hpp */
