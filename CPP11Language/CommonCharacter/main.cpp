//
//  main.cpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
// “通用为本，专用为末” 总结：主要是右值引用，移动语义，完美转发的引入。
// 一、对性能的更加关注，和C高效兼容：引入右值引用类型，函数模板完美转发实现；和C语言的兼容，pod类型的定义；联合体的拓展。
// 二、面向对象编写要更加高效和简单：移动构造函数，移动语义；继承构造函数和构造函数委派； explict拓展到类型转换函数；类型初始化列表的支持。
// 三、完善拓展泛型编程语法：inline名字空间允许父空间中对模板重定义；using别名可以用于模板和实例化模板；实例化模板时对SFINAE原则拓展，允许模板参数中存在非实例化的表达式存在。

// 右值引用和移动语义要反复斟酌
#include "InheritConstructFunc.hpp"
#include "MoveContructFunc.hpp"
#include "RvaluePerfectDispatch.hpp"
#include "ExplicitDescribe.hpp"
#include "ListInit.hpp"
#include "PODDataType.hpp"
#include "NoLimitUnion.hpp"
#include "ClassStructDefineInput.hpp"
#include "useinlineNameSpace.hpp"
#include "SFINAETest.hpp"
template<typename T>
struct CAA
{
public:
    T data; // cpp11中struct也可以作为模板类型；struct和class的区别就是成员权限和默认继承区别，都是引用类型；c#中却一个是值类型一个是引用类型。
};

/*
int main(int argc, const char * argv[]) {
    // 1.继承构造函数，在构造函数中用using BaseClass::BaseClass;就可以将父类的多种参数形式的构造函数都继承下来，拷贝赋值析构不会继承下来。避免原来使用的“透传"方式。
    // 如果子类要定义自己的变量初始化可以就地初始化，或用原来透传方式实现。
    Drived drivedObj;
    drivedObj.Print();
    cout << "Test inherit construct func:"<<endl;
    B b;
    b.Print();
    
    cout << "Test construct call detail:"<<endl;
    HasPtrMem mem = GetTempHasPtrMem();
    cout << "Test construct call detail end."<<endl;
    
    // 2.构造函数委派，其实是学习java的，在同一个类中，多个构造函数之间，可以定义一个通用的目标构造函数，然后其它构造函数（委派函数)在构造列表中调用目标构造函数，
    // 语法：可以有多个目标构造函数；其它构造函数称为委派构造函数，可以调用目标构造函数，但不能有初始化列表。
    // 调用了目标构造函数那么不能列表中初始化其它数据成员。还要注意构造函数调用之间循环的问题。
    // 委派函数一般用于模板设计中，可以定义一个模板目标构造函数，其它模板构造函数(委派)就能使用各自特例化的目标构造函数。避免声明不同类型的Init函数。非模板还是用Init解决委派更经典。
    //    例如：
    //    class TDConstructed {
    //        template<class T> TDConstructed(T first, T last) :
    //        l(first, last) {}
    //        list<int> l;
    //
    //    public:
    //        TDConstructed(vector<short> & v):
    //        TDConstructed(v.begin(), v.end()) {}
    
    //        TDConstructed(deque<int> & d):
    //        TDConstructed(d.begin(), d.end()) {}
    
    // 3.移动构造函数，右值引用，移动语义; 在隐形或显性转换为右值引用初始化或赋值给类对象时候(指针不会),会调用该类的移动或赋值构造函数，实现没有资源消耗的析构之前的对象构造出新对象。
    // 移动语义的使用也是为了调用移动或赋值构造函数实现指针资源“窃为己用”。
    cout << "Test MoveContructFunc:"<<endl;
    Moveable a(GetTemp()); // GetTemp()返回值为右值，调用Moveable的移动构造函数。
    cout << hex << "Huge Mem from " << __func__ << " @" << a.h.c << endl;// Huge Mem from main @0x603030
    PrintMoveNoexcept();
    
    // 4.右值引用在函数模板(引用折叠+模板引用推导规则)实现完美转发，函数模板和分发函数都用右值引用即可，分发时候要用forward<T>(t)类型转换(forward现在和move是一样的只是为了后面拓展引入）。
    cout << "Test RvaluePerfectDispatch:"<<endl;
    PrintForwardDispatch();
    
    // 5.explict可以修饰类型转换符，类转换运行符重载声明形式：explict inline operator 类型名() const,需要一个返回值，inline和const是否添加都是可以的。
    // 转换运算符与转换构造函数（即带一个参数的构造函数）是互逆的，如有了构造函数Test(int)，那么最好有一个转换运算符inline operator int() const{}。
    // 对于转换运算符，还有一个需要注意的地方就是，如果A类中有以B为参数的转换函数（构造函数），那B中不能有A的转换运算符，不然就存在转换的二义性,如：
    //    class A{A(B&){…}}; class B{ operator A(){…}};那么以下语句就会有问题：
    //    B b; A(b);//A(b)有就可能是A的构造函数，也可以是B的转换运算符
    PrintExplict();
    
    // 6.初始化列表
    //    初始化列表，标准库中对于vector这样的容器，需要声明对象-循环初始化这样的重复操作，对于使用模板的泛型编程是非常不利的。java/c#中早就支持了列表初始化。
    //    列表初始化语法：int a = 3 + 4; int a = {3+4}, int a(3+4); int a{3+4}.后面两种可以用于对象new 中，如new int{3+4}。
    //    标准容器的初始化列表：vector<int> vec = {1, 2, 3, 4, 5}; // 初始化列表，线性容器初始化都是一样的，具体返回什么数据结构依据的是左值声明类型。
    //    map<int, float> map_data = {{1, 1.1f}, {2, 2.1f}, {3, 3.1f}}; // 初始化map
    //    自定义结构体可以直接初始化，自定义类可以使用initializer_list<T> t构造函数提供初始化列表的支持。函数的参数也可以使用初始化列表，列表初始化如果发生类型不能表示或精度缺失(类型收窄)则会编译报错。
    // 见代码：
    PrintInitList();
    
    // 7.POD类型，cpp 11引入了POD类型的判断,POD有两个方面：1）平凡的 2）内存标准布局的。
    //    一个类型，如果是平凡的且是标准布局的，那么就是一个POD类型(基础类型都是POD的)。POD是plain old data,就是一个和C类型一样的内存类型，可以用C函数操作等特点。
    cout << "Test POD:"<<endl;
    PrintPlainType();
    
    // 8.Cpp11规定任何非引用类型都可以成为联合体的数据成员，这样的联合体称为非受限联合体(unrestricted union)。
    //    联合体可以定义不同的数据类型，这些数据将会共享相同内存空间，可以达到复用内存空间的目的。cpp98中并不是所有的数据类型都能够成为联合体的数据成员。
    //    非POD类型就不能作为联合体成员，也不允许有静态或引用类型的成员。这样虽然保证了和C兼容，但是也为联合体的使用带来了很大限制。cpp11放开了cpp98对联合体的限制。
    //    静态联合成员所有对象都共享，所以一般作为静态常量函数；联合体可以有构造函数析构函数等若有非POD类型那么默认的构造函数就不会再提供，可以重载构造函数用placement new实现。
    //    类的匿名联合体，为类提供了可变成的成员，可以设计出高度内存优化的类。
    PrintUnion();
    
    // 9.用户自定义类型的字面量(类或结构体)，其实是提供了operator "" _x运算符重载。
    // 目的是让用户根据专业领域方便的输入字符串或数字，来构建类或结构体(其实是要自己构造的),字符串和整型都可以作为输入，见：
    PrintDefineClassStruct();
    
    // 10.内联名字空间，c++98中不允许不同的名字空间对模板进行特化。namespace a{ inline namspace b{}}允许外部引入a命名空间的程序特化b中的模板.
    //用匿名命名空间也可以实现在其它命名空间引入父命名空间特化模板，在客户端通过父命名空间限定就可以访问到匿名或内联空间里面的内容，匿名命名空间还可以在父命名空间的其它空间内调用它里面的成员。
    //这样内联命名空间的本意大概是用于库模板作者开放外部特化接口专用，其它形式下用匿名模板即可。但是命名空间一般尽量简单，用一个即可类似std，不必搞那么复杂。
    cout << "Test inline namespace:"<<endl;
    sam::PrintFunc(100);
    sandy::PrintFunc(100);
    sam::PrintTest(100);
    sandy::PrintTest(100);
    sam::KnifeA an;
    //关于编译器的“参数关联名字查找”特性（ADL, Argument_Dependent name Lookup）.这个特性允许编译器在名字空间中找不到函数名字时，可以在参数的名字空间内查找函数名字。实践中一般sn::func规范化。
    //    using namespace sandy;
    sandy::SandyA aobj(10);
    aobj.ADLFunc(&aobj); // 作为类内部成员可以调用
    //    sandy::ns_adl::A atest;
    //    sandy::ns_adl::ADLFunc(atest); // xcode LLVM编译器上不能调用，故也不能调用ADL，一般不建议使用ADL,虽然可以简化代码的编写，但是可读性较差。
    
    // 11.模板别名 用using userType = existType; existType可以是还没实例化的模板类型且可以用userType时候实例化该实例化的类型。typedef existType userType却不能做到。
    // 因此using 是比typedef提供了泛型的别名支持。多使用typedef和using有助于简化代码输入；且using给模板编写提供了更加灵活的类型，有助于模板能力的拓展。
    //    a typedef cannot be a template
    sandy::MapString<int> numberStr;
    numberStr[1] = "samboy";
    sandy::MapString<string> stringStr;
    stringStr["aman"] = "samboy";
    
    // 12.SFINAE原则，模板实例化时候有一个原则：实例化失败并不是错误。这样就会寻找最合适的函数或类模板来实例化，这样同名模板就具有了多个版本的特性。
    // cpp98中对于模板参数中存在表达式的情况不支持，c++11都要求支持，规定"没有出现外部于表达式本身的元素"都不会有SFINAE错误，
    // 表达式有模板实例化或出现隐式构造函数调用则是出现了外部于表达式的，是不支持的。模板参数允许表达式，让decltype和stl模板库能从该支持中获益（其它的应用暂时没有看到）。
    cout<<"SFINAE(substitution failure is not an error) Test: "<<endl;
    SFINAE_Foo<SFINAE_A>(10);
    SFINAE_Foo<int>(10);
    //    SFINAE_Func(1);
    
    return 0;
}
*/
