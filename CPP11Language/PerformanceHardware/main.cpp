//
//  main.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/6.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
// 多核多线程的能力，cpp11在硬件和性能上的创新，可引领并行编程的浪潮。
// "提高性能及其操作硬件的能力“ 总结：
//一、1)constexpr是编译期常量，constexpr元编程的引入；2)变长参数模板类和函数模板，库编写用简单实例思维解决，非库编写者用tuple和容器的emplace系列函数即可。元编程对库程序员是一种简化，而不是复杂化。
//二、并行编程；1）原子类型：atomic<T>定义基本类型，自定义类型用_Atomic<T>实现(现在还不支持)，原子类型是编译器用了系统底层的总线锁或存储锁加快锁定，其它同时访问线程会被阻塞，atomic_flag自旋无锁同步，
//   memory_order对弱顺序代码执行内存模型调优，是cpp11并行编程中的一大亮点。
// 2）.多线程库引入：cpp11内置的线程其实是封装了pthread线程，使用更加简单，但是没有pthread底层和控制能力强。
// 3).TLS变量，对全局静态常量数据和线程生命期绑定，关键字是thread_local。cpp11 errno变量是线程局部的而不是全局的。
//三、进程退出：用quick_exit需要退出回调的用at_quick_exit（目前LLVM还没实现)；异常退出还是要terminate实现。
#include "constexprtest.hpp"
#include "va_template_function.hpp"
#include "va_perfect_forward.hpp"
#include "multi_thread.hpp"
#include "quick_exit.hpp"
/*
int main(int argc, const char * argv[]) {
    // 1.引入constexpr是编译期常量，而原来的const是运行期常量, constexpr元编程比模板元编程更优秀(但是目前编译器支持还不完善）。
    // 常量表达式函数，可以取代#define对常量的定义，常量表达式函数必须使用前全部定义好，且函数内部不包含运行期计算的非常量表达式和函数调用，只能是返回一个简单的常量表达式值。
    // constexpr常量表达式，在编译期计算值,编译前如果不使用则不会产生该标识符；const是运行时的编译器都会为其产生值。
    // constexpr 用在自定义类型中，需要编写constexpr构造函数，构造的对象要是constexpr类型的，就可以获取constexpr函数成员了，
    // 非constexpr类型的函数成员不能调用,而数据成员可以调用。
    // constexpr也可以用在函数模板中，实例化时候如果发现不满足常量函数的特性，那么会把constexpr关键字省略作为一个普通函数；满足则是一个constexpr函数。
    // constexpr函数在cpp11中规定至少支持512层的递归。
    //    constexpr支持编译期运算出表达式的值（部分编译器还不支持）基于编译期运算的编程称为元编程。
    
    // 模板元编程是利用模板实例化时候提供条件判断能力，模板递归调用提供了循环的能力，这两点使得它具有图灵完备性(表达任何计算)。
    // 模板实例化参数<t>为输入，模板中的typedef/static const/enum类型作为输出，代码就算是通过实例化输入，返回上述返回类型的值（进行递归循环展开)得到结果的。
    // 模板元编程是模板设计获得的意外能力，编译期数值计算、类型计算、代码计算（如循环展开），其中数值计算实际不太有意义，而类型计算和代码计算可以使得代码更加通用，更加易用，性能更好
    // ；也更难阅读，更难调试，有时也会有代码膨胀问题。但是大量使用泛型编程的地方，例如stl库，boost库，还是使用了模板元编程，所以对于模板元编程还是要有所了解的。
    // 用C语言的宏定义也可以利用编译期，对表达式展开，在编译期获得需要的值。
    // constexpr元编程，也是图灵完备的，输入为常量，通过编译期递归支持用循环计算输出为constexpr的返回值。由于constexpr支持浮点数运算（模板元编程只支持整型)，支持三元表达式，逗号表达式，
    // 所以很多人认为constexpr元编程会比模板元编程更加强大（但目前有些编译器constexpr运算会推迟到运行时）。
    ConstExpr expr;
    expr.Print();
    
    // 2.C风格变长参数函数，cpp11风格变长参数模板类和函数模板(通过模板元编程实现,解开...args包来实例化),库编写用简单实例思维解决，非库编写者多使用std的tuple,和容器的emplace系列函数即可。
    // 变长参数的实现，c风格的变长参数是用va_list,va_start,va_arg(跳转指针获取该类型的值）,va_end实现，支持变长参数的函数只是转发其实根本不知道参数的类型和个数的，也不支持自定义非POD类型。
    //    通过变长函数模板的模板推导，通过编译期构建（其实是用模板元编程支持变长类型和变长函数参数)，能够获取需要的自定义类型模板或函数模板。
    // cpp11引入的tuple类似pair如std::pair<int,double>，pair只是两个类型的组合，tuple可以支持任意多不同类型的元素的集合。如：
    // std::tuple<double, char, std::string> collections;
    // tuple val = make_tuple("jj", 2, 2.0f, "yy");
    // cpp11的变长参数，用变长模板在模板推导时候求取解包的类型，调用手动的递归将私有继承递归解包,递归返回得到所需变长参数类型的类或函数：
    // Template<typename … Elements> class tuple;
    // … 表示该参数是变长的，Elements是模板参数包(pack)，是一种新的模板参数类型。一个模板参数包在模板推导时被认为是模板的单个参数，为了使用模板参数包，总是需要将其解包(unpack),解包通过一个包拓展（pack expansion）的表达式来完成，如下：
    // template<typename…A> class template: private B<A…>{};
    // 模板解包展开时候会用递归的方式实现，如下：
    // Template<typename…Elements> class tuple; // 变长模板声明
    // Template<typename Head, typename…Tail> // 编译器要求取解包的typename Head值，调用递归的解包定义；head是解出来的第一个参数类型，Tail是子包。
    // Class tuple<Head, Tail…> : private tuple<Tail…>{ // 私有继承，进行包的解压。
    //      Head head;
    // };
    // Template<> class tuple<>{}; // 递归解包终止条件，没有了就返回。
    // 例如：tuple<double, int, char, float> t;会在递归返回时候先建造出tuple<float>到tuple<char,float>到tuple<int,char,float>到tuple<double, int, char, float>类型，其它类型都是私有继承父类（其它类型是组成tuple<double, int, char, float>类型的部分)。
    // Multiply类 模板中编译器求取static const值，驱动手动编写递归实现变长乘法实现。
    // Printf函数 编译器模板推导要求取解包的T value值，调用手动定义的递归调用，实现变长的Printf参数。
    // 这样cpp11通过变长函数模板的模板推导，通过编译期构建，获取了每个变长参数的实例，而让类型或函数知道每个传入的参数类型，也可以打印自定义的类型。相比c99风格的变长函数，更加完善和方便拓展。
    // 实例代码：
    PrintDynamicArgLenFunc();
    // cpp11定义了7种可展开参数包的地方：
    //    表达式
    //    初始化列表
    //    基类描述列表
    //    类成员初始化列表
    //    模板参数列表
    //    通用属性列表
    //    Lambada函数的捕捉列表
    // 语言的其它地方则无法展开参数包，对拓展包，解包也与其声明的形式息息相关，声明了Arg为参数包，使用Arg&&…这样的包拓展表达式，解包后等价于Arg1&&,Arg2&&等。
    // 注意拓展表达式的使用，类和函数声明都是一样的：
    // template<typename…A> class T: private B<A>…{}; // 这里会解析成多重继承
    // template<typename…A> class T: private B<A…>{}; // 这里会解析为多参数的B模板类
    // 1)类型的声明用...T
    // 2)函数参数，使用类型用T... t
    // 3)调用参数使用类型，func(t…);
    // 获取函数传入参数的个数用sizeof... 例如：int size = sizeof…(A); // 得到传入参数包的长度，获得了长度后可以不用递归实现循环。
    // 利用变长模板的变长类型和变长函数参数，实现完美转发的例子：
    PrintVaPerfectForward();
    //库中添加了tuple,emplace_back这样的变长模板类和变长模板函数，直接利用即可，如果读者需要传递变长的类型或者函数参数，不妨使用变长模板试试。
    // 使用map的emplace和vector的emplace_back等emplace函数有利于提高性能：
    //  emplace/emplace_back的性能比之前的insert和push_back的性能要提高很多，我们应该尽量用emplace/emplace_back来代替原来的插入元素的接口以提高性能。需要注意的是，我们还不能完全用emplace_back来取代push_back等老接口，因为在某些场景下并不能直接使用emplace来进行就地构造，比如，当结构体中没有提供相应的构造函数时就不能用emplace了，这时就只能用push_back。
    
    /*
     3.c++11多线程支持，原子类型提高互斥性能(原子是总线或缓存锁,其它阻塞)，atomic_flag实现所谓的无锁编程的同步，memory_order可以对代码弱顺序cpu可以调优，且使用更加简单，其实是封装自pthread库。
        单处理器的频率提升遇到了漏电流等各种技术瓶颈。多处理器的硬件架构，需要编程语言向并行化方向发展。cpp11之前c/c++(纯语言)的app一直是由单cpu(同一个时刻只有一个程序计数器指向可执行代码的代码段)运行代码段
     中的指令。c/c++(纯语言)代码构建的app也总是对应的拥有一份OS赋予app进程的堆、栈、可执行代码区、全局静态常量数据区的内存区。
        常见的并行编程模型有：内存共享，多线程，消息传递等。
        多线程模型允许同一时间有多个cpu执行统一进程中的代码部分（同一个cpu不同时间片或不同的cpu各自加载当前需要的可执行的代码区），通过分离的栈空间，和共享的数据区及堆空间，线程可以拥有独立的执行状态以及
     进行快速的数据共享。
        c/c++一直没有在语言层面纳入多核处理器的多线程编程模型。在cpp11之前主要应用POSIX线程(pthread线程库，windows线程库)和OpenMP编译器指令，OpenMP的编译器指令将大部分的线程化工作交给编译器完成，
     识别需要线程化的区域交给程序员，这样使用更加简单，是现行的一种非常有影响力的使用线程程序优化的编程模型。OpenMP只是更加简单，OpenMP并不适合需要复杂的线程间同步和互斥的场合。OpenMp的另一个缺点是
     不能在非共享内存系统(如计算机集群)上使用。在这样的系统上，MPI使用较多。因此POSIX线程库才是正确选择。
        c++11从语言层面引入了对多线程编程的支持。因为从app角度需要同步的总是数据而不是代码，所以cpp11对数据进行了抽象，引入了原子类型，c11中也引入了原子类型，在<cstdatomic>中定义，都是用atomic<T>定义的。
     也可以用atomic<T>进行基本类型定义，自定义类型用_Atomic<T>来实现(现在还不支持)，原子类型只能用构造函数构建，拷贝/移动/赋值构造都是默认删除的，原子类型可以赋值转换为T类型。
     原子类型是同时只有一个cpu可以访问该变量，编译器保证所有的原子类型操作是顺序内存执行的（硬件非顺序n的如powerpc,armv7等会插入一条内存栅栏指令保证顺序执行).
        其实c++11线程库来自于boost线程库，底层是封装了pthread库, 使用c++11线程库可以获得原子类型互斥访问快和内部线程池的优势，但是非cpp11编译器不支持或者存在不完善。使用pthread库才能获得最底层、最灵活、
     跨平台的多线程支持。见：
     https://software.intel.com/en-us/articles/choosing-the-right-threading-framework
        cpp11的atomic_flag可以在底层提供非传统锁的，基于原子操作的加锁功能（实现所谓的无锁同步功能，更大的挖掘并行能力)。
        Cpp11中原子类型的成员函数（原子操作)总是保证了顺序一致性，可以用原子操作对象的.store(写), .load(读) RMW(同时读写)等大多数操作都可以指定memory_order要求(重载操作符默认是顺序的，不用即可不必重载）。
     是采用代码顺序执行，还是可以乱序优化执行（去掉插入的内存栅栏等待，且一个时钟周期内可以执行多条指令)，代码块的内存乱序执行可能会得到不是代码中看到的结果（可能引入多线程中非常难排查的问题)。
     用memory_order_release和memory_order_acquire结合称为release-acquire代码内存顺序，可以得到又好又快的结果（要花很大精力来分析优化), memory_oreder_releae和memory_order_consume可以建立release-onsume内存顺序。其实原子操作特性很多编译器还没有支持。一般采用原子操作默认的顺序执行即可。
     http://blog.csdn.net/qq100440110/article/details/52304389
     http://www.infoq.com/cn/articles/atomic-operation
     */
/*
    PrintThreadTest();
    
//    4.TLS变量，对全局静态常量数据和线程生命期绑定，关键字是thread_local
//    进程空间中的全局/静态/常量区数据是进程生命期的，在多线程中是可以共享的，为了每个线程对保留一份避免读写冲突，cpp11添加thread_local修饰，实现为线程生命期的，例如：
//    Int thread_local errCode;
//    TLS变量可以在程序一开始就分配，也可以在线程开始时候分配，线程内对TLS变量取地址，也是基于本线程的，线程结束TLS变量生命期结束。
    static int thread_local s_testNum = 15;
    cout << "s_testNum:" << s_testNum << endl;
    
// 5.程序高效正常退出，用quick_exit需要退出回调的用at_quick_exit；异常退出还是要terminate实现。
//    terminate是异常退出会调用abort快速结束掉app，堆内存标记为未使用，可能系统会进行coredump以辅助程序员进行问题分析，且若有关联其它app的情况，例如进程共享内存，外接设备对象（显卡，网卡，声卡)会出现问题。
//    exit是正常退出，调用全局数据类的析构函数，调用各种对象的析构函数，调用atexit注册的函数，可以安全的退出app,但是退出速度太慢了(析构回收堆内存)。
//    quick_exit是正常退出，但是不执行析构函数(不回收堆内存)，而仅是调用at_quick_exit中注册的函数，目前cpp11中还不支持。
    PrintQuitExit();

}
*/
