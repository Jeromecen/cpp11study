//
//  main.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/8.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
// "为改变思考方式而改变“ 总结：
// 一、nullptr引入，用单一职责思维，避免NULL存在指针和整型的二义性，nullptr_t类型可以进行赋值到指针和进行比较运算(与指针的)。
// 二、=default恢复编译器默认的函数，方便书写和保证POD类型；=delete指定删除，方便禁止一些拷贝构造赋值和移动拷贝构造赋值函数，全局和普通函数的某个重载版本也可以禁止。
// 三、lambda函数编程的引入，注意捕获列表中传值和传引用区别（都是定义初始化仿函数闭包对象，但是&可获得调用时上下文值,&自定义类型性能更高，但要小心使用)。在stl仿函数，泛型编程，复杂函数中作为匿名函数广泛使用。
// lambda相比仿函数还是有区别的，只能函数内部初始化和使用，自定义仿函数和普通函数可以在不同作用域初始化和使用，所以使用时候区分就好。

#include <cstddef>
#include <iostream>
using namespace std;

#include "ClassStructDefaultMethod.hpp"
#include "lambda_test.hpp"
/*
int main(int argc, const char * argv[]) {
    // 1.nullptr,因为NULL是具有二义性的，是一个整型，当程序员想调用指针版本函数时候可能会调用到整型版本，nullptr没有该问题，更加健壮，nullptr是一个右值空指针常量，负责指针类型，是一个单一职责设计。
    // nullptr_t 类型是typedef decltype(nullptr) nullptr_t，相比void*类型，nullptr_t一般不用来表达任意指针;该类型变量可以赋值给其它指针(赋值到非指针不允许)，不能算术运算, 可以进行比较运算。
    nullptr_t t = nullptr; //
    int *i = new int(10);
    if(t < i)
    {
        cout << "nullptr_t t < i " << endl;
    }
    
    if(nullptr == 0) // llvm编译器中还是允许相等的，后面会去掉。
    {
        cout << "nullptr == 0 " << endl;
    }
    
    if(!nullptr) // llvm编译器中还是允许隐式转换为bool，cpp11已经不允许这样做了（应用if(p != nullptr))，后面会去掉。
    {
        cout << "!nullptr" << endl;
    }
    
    // 2.构造函数等用=default;恢复编译器默认的函数。删除构造函数等用=delete;默认和重载的都删除，相比原来cpp98的用private声明但是友元可以访问更加安全简单。
    // 自定义类型的默认函数有：构造函数/析构函数，拷贝构造函数/拷贝赋值函数，移动构造函数/移动赋值函数.
    // 自定义类型提供全局默认操作符函数：.，*，->/->*、&/&&、new/delete
    // 这些默认函数和默认全局运算符，如果重载了就不会默认提供了。会导致POD的变为非POD的。
    // 恢复编译器提供的默认的函数，cpp11允许用=default来声明。
    // 例如：
    TestClassPOD();
    // =default;和=delete；函数不仅可以用在编译器默认提供的函数中，还可以用在全局函数。=delete；还可以用在普通函数中删除某个版本，=delete不要和explicit修饰符混用会导致混淆。
    
    // 3.cpp11引入了lambda函数，捕获列表是lambda最大的特点，可捕获所在函数{}内的所有可见数据（其实是定义时候构造了一个自定义仿函数，上下文值就确定了，但&的值可得到调用点上下文值，&性能更好但要小心)。
//  返回类型是闭包class仿函数类型，ambda函数也就是函数编程范式（借鉴了lisp,lisp自描述自解释太灵活可读性太差了)。stl和泛型编程中用lambda函数，在可读性，灵活性，性能方面都比仿函数优秀。也可重构改善复杂算法。
//  仿函数和普通函数可在不同作用域范围初始化和使用进行复用；lambda函数被设计为内部函数，不可以在不同作用域中复用，区分使用即可。
    //    lambda函数语法：
    //    [capture](parameters) mutable ->returntype{statement};
    //    1)[]必须的，capture可选的：没有函数名使用[]作为lambda标识开始。内部的capture是捕获上下文的变量以供lambda函数的statement使用。
    //    2)可选的：parameters是函数参数列表和一般函数一样，没有参数()符合可以省略。
    //    3)可选的：mutable 是非常量修饰符(若是非常量函数参数列表不能省略)，默认lambda函数都是const函数。
    //    4)可选的：->returntype是追踪返回类型，不需要返回值（或者编译器可明显推导出类型，如常量）的情况下->符号都可以省略。
    //    5){}必须的，statement可选的：{statement}函数体和普通函数体一样，且除了使用参数，还可以使用[capture]中的capture值。
    // 最简单的lambda函数为：[]{}
    //    使用实例：
    //    Int main()
    //    {
    //        int girls = 3, boys = 4;
    //        auto totalChild = [](int x, int y) ->int{return x+y;};
    //        return totalChild(girls, boys);
    //    }
    // 捕获列表是lambda最大的特点。捕获列表可以传值，也可以传引用。
    //    [var]传值捕获父作用域变量var。父作用域是lambda所在的函数块，即函数{}块。
    //    [&var]传引用。
    //    [=]用值传父作用域所有变量。
    //    [&]用引用传父作用域所有变量。
    //    [this]值传递方式传当前的this指针。
    //    可以组合[=,&a,&b], 但是不能重复传如[=,a,b]，标准规定只能传栈自动变量，但LLVM c++11能传递全局/静态/常量，和堆内存数据。
    LambdaTest();
    //  lambda函数本质：本身是由仿函数实现的，仿函数是一个类，可有数据成员且必须重载()运算符，先构造初始化，调用时候和函数调用一样的形式和效果。实现记录当前上下文状态目的，
    // 所以lambda捕获的作用域上下文参数是可以作为构造函数实参的就可以了。lambda是仿函数的语法糖，书写更加简单一点，其实是引入了内嵌匿名函数，对复杂算法测试和自说明函数内部重用很有作用，
    // 但是非函数内部还是要用仿函数或者普通函数，在stl中都有广泛应用。
    // lambda函数特性分析：
    // 1)传值和传引用区别：lambda函数的捕获传值类型是定义时候的值(仿函数构造)，引用类型是调用时候的地址对应的值(也是定义时候构造，不过引用地址不变不代表值不变)，函数内部使用都一样。
    // 2）返回类型：lambda函数的返回值是一个闭包类型，闭包类型是一个特有的匿名的和非联合的class类型，没有捕获列表的lambda函数可以转换为一个函数指针要求参数一致，函数指针类型不能转换到闭包类型，
    // 3）const类型和闭包含义：可以用auto或decltype来获取类型。闭包含义和const,mutable关键字，mutable修饰是允许修改捕获到的值包括引用，默认是const的即捕获的值不变或引用不变但是引用上的值可以变，闭包的由来也在于此，用上下文变量初始化后上下文的值就不变了，只是作为输入，如果要输出可以用返回值或引用。默认const关键字是对灵活的仿函数容易设计出问题的改进, 尽量独立不污染闭包外的内容。

//   lambda在stl广泛代替仿函数,泛型编程中,复杂函数内部复用(如打印)：使用仿函数时候声明需要传递的类型不需要传for或find_if中容器的值，lambda函数参数值就是容器的值，lambda更加清晰和方便拓展，比stl仿函数优秀。
// 需要改变stl容器的值的话用仿函数需要用transform函数不能用for_each函数了，但是用lambda使用[&]作为输入即可。需要多次用不同仿函数遍历容器的，使用lambda可以遍历一次操作完成，提高了性能。
// lambda函数，在可读性，灵活性，性能方面都比仿函数优秀，也方便重构改善复杂算法逻辑，将函数编程优秀思想引入到了cpp11。
//    Vector<int> nums;
//    Vector<int> largeNums;
//    for_each(nums.begin(), nums.end(), [=](int i){
//        if( i >ubound)
//        { largeNums.push_back(i);
//        });
//        Void oneCond(int val)
//        {
//            // 传统的for
//            for(auto I == nums.begin(); I != nums.end(); I++)
//            {
//                if(*I == val) break;
//            }
//            // 用stl内置的bind2nd仿函数实现
//            find_if(nums.begin(), nums.end(), bind2nd(equal_to<int>(), val));
//            // 用自定义的lambda表达式实现
//            find_if(nums.begin(), nums.end(), [=](int i){
//                return i == val;
//            });
//        }
//        
//        // 当发生改变时候, 明显lambda方式占优势。
//        Void TwoCond(int low, int high)
//        {
//            // 传统的for
//            for(auto I == nums.begin(); I != nums.end(); i++)
//            {
//                if(*I >= low && *I < high) break;
//            }
//            // 用stl内置的bind2nd仿函数实现
//            find_if(nums.begin(), nums.end(), 
//                    compose2(logical_and<bool>(),
//                             bind2nd(less<int>(), high),
//                             bind2nd(greater_equal<int>(), low)));
//            
//            // 用自定义的lambda表达式实现
//            find_if(nums.begin(), nums.end(), [=](int i){
//                return i >= val && i < high;
//            });
//        }
}
*/
