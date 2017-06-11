//
//  main.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/5.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
// “易学易用” 总结：主要是是类型推导规则引入，for自动范围和迭代引入。
// 一、基础符号编译器增强：1.>>避免模板或类型转换中需添加额外的空格。2.for(auto &e: containerObj){}自动范围和迭代语句,数组和STL容器都支持（stl中e是元素类型），自定义容器需重载。
// 二、新增了类型推导规则：1.auto编译期类型多用于函数或表达式内部的变量，不能用于函数参数，类成员，数组和模板实例化中（虽然提供值)，可以用于初始化列表和new对象中。会去掉volatile和const修饰符。
//                    2.decltype是最灵活的编译期类型，根据表达式而不是只推导类型，可以用在所有表达式类型确定的地方（函数返回值是不确定的)，可以带走volatile和const修饰符。左值判断技巧。
//                    auto可以减少代码量，decltype可以更灵活的获得表达式运算后的类型，他们都有类型自适应性(值修改后类型不用变),可以多用于库相关代码的编写。业务逻辑用确定类型会清晰些。
// 三、追踪返回类型，auto和decltype的结合，auto Sum(T1 &t1, T2 &t2) -> decltype(t1+t2) { return t1+t2}能确定运算后变化的类型，增强函数和函数指针泛型能力。
//类型格式化输出：http://blog.csdn.net/yockie/article/details/9104899
#include <iostream>
using namespace std;
#include "typeid_decltype_test.hpp"
#include "TraceTemplateReturnType.hpp"
#include "ForStatement.hpp"

#define MAX1(a,b) ((a) > (b)) ? (a):(b)
#define MAX2(a,b) ({\
auto _a = (a);\
auto _b = (b);\
_a > _b ? _a:_b;})

//void foo(auto i = 10)
//{
//
//}
/*
int main(int argc, const char * argv[]) {
    //1.右移符号的改进, cpp98中右移符号优先于模板符号和静态转换符号，若出现>>符号，则在>>之间添加一个空格才能编译通过。
    // cpp11中编译器做了智能处理，进行尖括号配对，>>之间不需要空格即可编译通过。但是对于真正需要有移的情况，那么添加()括号优先级即可。
    //Y<X<1>> yObj; //cpp98编译失败，cpp11编译成功
    // Y<X<1> > yObj; //cpp98编译成功，cpp11编译成功
    //vector<int> v = static_cast<vector<int>>(v0); //cpp98编译失败，cpp11编译成功
    
    // 2.auto编译时期类型推导关键字，在C/C++中之前是作为具有自动存储期的局部变量也就是局部的栈变量（非全局，静态，常量),因为默认是该存储类型，因此没人使用。
    //    因此cpp11中对该关键字赋予了全新的含义，不再是存储类型指示符(static,extern,thread_local等),而是新的类型指示符(int,float等)来指示编译器，auto声明变量
    //    的类型必须由编译器在编译时期推导而得，关于类型自动推导，有些动态语言是在运行时推导得到。
    // auto优势：1）简化长类型如stl iterator类型代码书写。2）类型自适应，如果值的类型因为修改了（程序员重构或平台变化了),类型可以自适应，不需要再修改。3）宏中使用auto，相比原来的替换性能更高。
    // auto缺点：阅读变量类型时候要先看值，值不直观的还要调试下；还是存在溢出因为只是替换，不能像其他动态语言一样自动提升位数防止溢出。
    // auto使用注意：1)auto变量只是替换所以赋值不允许的还是不允许(比如auto指针指向一个右值临时变量); 2) auto变量会去掉值的volatile和const修饰符，auto 引用却可以保留。3)同时声明多个变量，类型必须一样.
    // auto也可以使用在类型{}初始化列表，和new堆对象的类型上。
    
    // auto不能修饰的类型规则：
    //    1）auto作为函数形参类型，无法编译。若要泛型参数，还是要使用模板。
    //    2）auto作为类型的非静态成员变量，无法编译。虽然有初始值，但是编译器阻止对类型内部非静态auto成员的推导。
    //    3）auto类型数组，无法编译。auto数组虽然有初值，但是依然被禁止。
    //    4）auto模板参数(实例化时),无法编译。模板实例化虽然有初值但是也被禁止推导。
    //    5）cpp 98和c风格的， auto int i = 10;声明在cpp 11中是会编译报错的。
    // 因此auto一般在函数或模板函数内使用。cpp11的auto没有动态语言的类型推导职能，auto只是cpp11类型推导一部分，另一部分在decltype中。
    // 追踪返回类型的函数声明，lambda中都有auto关键字的应用。
    auto i = 10;
    //  auto z; // 无法通过编译，auto声明只是占位符，在编译期，编译器通过值推导会把auto类型替换为真实类型，故auto类型变量必须初始化。
    cout<< i << endl;
    unsigned int biggest_int = 4294967295;
    auto autoint = biggest_int + 1;
    cout << "autoint:" << autoint << endl;
    auto bigA = MAX1(1*2*3*4, 5+7+10);
    auto bigB = MAX2(1*2*3*4, 5+7+10); // 宏中使用auto，相比原来的替换性能更高
    cout << "auto MAX1:" << bigA << endl;
    cout << "auto MAX2:" << bigB << endl;
    
    // 3.typeid and decltype，decltype是类型推导上最灵活的在编译期推导，函数参数、类成员、数组、模板参数中都可用，且const volatile符号都是支持的。
    // 可以用declype拓展泛型的编写（可以在参数，类成员和模板参数中），且也具有类型自适应性（因为根据表达式或现有值推导的）。根据表达式推导的类型，注意先声明后赋值，用is_lvalue_reference技巧。
    //  RRTI, typeid获取运行时对象的类型和hash_code信息(也可以获取auto运行时类型信息)。
    //  RTTI的typeid因为运行时有开销，所以很多编辑器都让用户选择性的关闭RTTI，而且很多时候运行时才确定出类型对于程序员来说已经晚了，程序员更多是要在编译期确定出类型，需要使用这些类型而不是识别出来。
    //  因此CPP98的RTTI无法满足要求。
    // decltype类型推导的引入,decltype以一个表达式或变量为输入返回该value的类型作为变量的类型，和auto一样也是在编译期决定的。
    // decltype是随着泛型的模板编程引入的（因为非泛型的类型很容易看出)，可以编译期就得到变量的类型。
    // decltype可以应用在局部函数内部，也可以在函数参数中，可以作为类型的非静态成员变量，可以用在数组上，模板实例化上都可以使用。是和auto不同角度的推导，编译器对decltype的支持比auto更广泛。
    // decltype内部是一个表达式或者一个函数的调用表达式(若只有函数名则不支持), 虽是函数调用表达式但还是没有调用函数的。
    // 推导函数返回类型的result_of<func()>::type t;也是用了delctype的，func必须是一个函数指针，也不会产生函数调用。
    using size_t = decltype(sizeof(0));
    using ptrdiff_t = decltype( (int*)0 - (int*)0);
    using nullptr_t = decltype(nullptr);
//    decltype(e)来获取类型时，具体的类型，编译器将依序判断一下四个规则：
//    1)如果e是一个没有带括号的：标记符表达式(没有修饰的变量名)或者类成员访问表达式。 那么decltype(e)就是e所命名的实体的类型。此外如果e是一个被重载的函数，则会导致编译时错误。
//    int arr[4]; arr是一个标记符表达式，arr[3]，arr[3] + 0都不是标记符。
//    int i;i是标记符，（i)不是标记符。
//    2)若不满足1）第一句，那么假设e的类型是T, 如果e是一个将亡值，那么decltype(e)为T&&.
//    3)若不满足1）第一句，那么假设e的类型是T, 如果e是一个左值，则decltype(e)为T&.
//    4)若不满足1）第一句，那么假设e的类型是T，则decltype(e)为T.
//    技巧：主要是区分左值类型，先定义decltype变量，那么先声明这个变量，再在其它语句里对其初始化。这样，由于左值引用总是需要初始化的，编译器会报错提示。
//    另外，cpp11中添加的模板类 is_lvalue_reference<decltype(xx)>::value，可以帮助程序员进行一些推导结果的识别。
    // 使用时候一般用在模板中就行了，具体见代码：
    PrintTypeInfo();
    // decltype不会去掉类型的volatile和const修饰符，但是类型内成员有无volatile和const修饰符不受外部类型的影响。可以用is_const,is_volatile判断。
    struct decl_cv
    {
        decl_cv()
        {
            value = 0;
        }
        int value;
    };
    const decl_cv cv1;
    volatile decl_cv cv2;
    cout << "decl_cv: " << is_const<decltype(cv1)>::value << endl;
    cout << "decl_cv: " << is_volatile<decltype(cv2)>::value << endl;
    cout << "decl_cv: " << is_const<decltype(cv1.value)>::value << endl;
    cout << "decl_cv: " << is_volatile<decltype(cv2.value)>::value << endl;
    // 在decltype或auto中，冗余的&和const,volatile符号会被省略掉；*指针符号并不会别忽略。
    int i1 = 1;
    int &j = i1;
    const int *p = &i1;
    volatile int jj = 100;
    decltype(j) & dj = i1; // 多余的&符号省略掉
//    decltype(p) *dp = &i1; // *不能省略，编译报错
    decltype(p) *dp = &p; // *符号不能算多余的，所以只能用&p赋值
    auto *v3 = p;
    const decltype(p) p2 = &i1; // 多余的const省略
    volatile decltype(jj) kk = 200; // 多余的volatile省略
    
// 3.追踪返回类型，auto和decltype的结合，会真正释放cpp11中泛型编程的能力。
// cpp98中相同类型的都是可以用泛型返回值的，所以cpp11中引入的追踪类型返回值是很大的拓展了泛型类型组合的能力，但是实际中使用并不多的。
// 语法：追踪返回类型语法，将返回类型decltype写在函数参数后面，函数返回类型可用auto修饰，但是需要decltype尾随类型支持。
    //  -> decltype(t1+t2)称为追踪返回类型
//    auto Sum(T1 &t1, T2 &t2) -> decltype(t1+t2) { return t1+t2}
// 普通函数也可以用追踪返回类型语法,但是编写代码比较多，非泛型没有必要。
//    auto NormalAddTest(int a, char c) -> int;
// 追踪返回类型语法，可以简化多重函数指针的写法。
    // 追踪返回类型，可以广泛的用于转发，转发的需求是根据不同输入参数，得到不同目标函数返回类型（一般使用相同类型的有右值引用实现完美转发即可)
//    double foo(int i);
//    int foo(double d);
//    template <typename T>
//    auto Forward(T t) -> decltype(foo(t))
//    {
//        return foo(t);
//    }
// 追踪返回类型可以在函数模板，普通函数，函数指针，函数引用，这些函数可以在模板中全局中也可以在类或结构体内部。
    PrintTraceTypeTest();
    
// 4.For( auto &e : contanerObj){};避免了for语句内遍历需要知道边界和自动的++p遍历，编译器提供了容器边界的判断和递增操作。
//    能够使用自动范围和增长的for语句，需要满足的条件：
//    1）for循环迭代的范围是可确定的。对于数组而言就是[0,n-1]之间的范围是确定的（a[]没有大小类型的参数不支持），对于类（容器类型，非容器内元素）则需要有begin和end函数。
//    2）for循环还要求迭代的对象（容器类型，非容器内元素）实现++，==等操作符。
//    对于普通的数组和STL容器不会有问题，因为已经实现了。自定义的数据放入容器中是没有问题的，而自定义的容器，则要实现上面的操作。
//    自动范围for语句需要注意的地方：
//    auto声明的迭代器对象it，不是iterator对象，而是*it也就是迭代器对象指向的元素。实例代码如下：
    PrintFor();
}
*/
