来自<<深入理解C++11 c++11新特性解析与应用>>

代码见：https://github.com/Jeromecen/cpp11study/tree/master

I、保持语言的稳定性和兼容性” 总结：主要是utf8字符串，虚函数override/final支持。 1、c++11宏和类型(考虑和c99兼容）：STDC_HOSTED、STDC、__VA_ARGS__宏可以替代...、__cplusplus宏用于c和c++混编，非布尔值还可以判断是否支持c++ 11；_Pragma操作符。 long long 64bit类型, static_assert用于编译时警告,表达式必须是常量。string都是utf-8类型的，可以和utf-16，char*等转换。可用sizeof(类::非静态成员)获取成员大小。 2、面向对象语言特性完善：虚函数override/final支持；增加非静态成员变量就地初始化=和{}符号；noexcept函数声明没有异常抛出，如果抛出了则用std::terminate()来终止程序； 3、完善拓展模板语法：friend FriendClass就可以声明友元，模板中也可使用；模板函数也支持了默认参数；显式模板实例化和外部模板声明优化链接；匿名和局部的类/结构体等，都可以作为模板实参。

II、“通用为本，专用为末” 总结：主要是右值引用，移动语义，完美转发的引入。 1、对性能的更加关注，和C高效兼容：引入右值引用类型，函数模板完美转发实现；和C语言的兼容，pod类型的定义；联合体的拓展。 2、面向对象编写要更加高效和简单：移动构造函数，移动语义；继承构造函数和构造函数委派； explict拓展到类型转换函数；类型初始化列表的支持。 3、完善拓展泛型编程语法：inline名字空间允许父空间中对模板重定义；using别名可以用于模板和实例化模板；实例化模板时对SFINAE原则拓展，允许模板参数中存在非实例化的表达式存在。

III、“易学易用” 总结：主要是是类型推导规则引入，for自动范围和迭代引入。 1、基础符号编译器增强：1).>>避免模板或类型转换中需添加额外的空格。2).for(auto &e: containerObj){}自动范围和迭代语句,数组和STL容器都支持（stl中e是元素类型），自定义容器需重载。 2、新增了类型推导规则： 1).auto编译期类型多用于函数或表达式内部的变量，不能用于函数参数，类成员，数组和模板实例化中（虽然提供值)，可以用于初始化列表和new对象中。会去掉volatile和const修饰符。 2).decltype是最灵活的编译期类型，根据表达式而不是只推导类型，可以用在所有表达式类型确定的地方（函数返回值是不确定的)，可以带走volatile和const修饰符。左值判断技巧。 auto可以减少代码量，decltype可以更灵活的获得表达式运算后的类型，他们都有类型自适应性(值修改后类型不用变),可以多用于库相关代码的编写。业务逻辑用确定类型会清晰些。 3、追踪返回类型，auto和decltype的结合，auto Sum(T1 &t1, T2 &t2) -> decltype(t1+t2) { return t1+t2}能确定运算后变化的类型，增强函数和函数指针泛型能力。

IV 、“提高类型安全" 总结： 1、新枚举类型：新增了enum class enumName:type{}作用域限定符和类型。 2、智能指针：unique_ptr用在单模块内使用，shared_ptr和weak_ptr用引用计数在多个模块间共享。记得初始化；判是否有效，*和->使用，需转换为原指针迭代跳转；move或reset后要小心使用。 3、GC: 标记-清除GC实现，现在暂时定义了接口，原因是指针的太灵活(指针任意在内存中跳转)导致隐藏指针，GC会误删，用declare_reachable等标记隐藏指针解决，且delete和回收是兼容的。

V、"提高性能及其操作硬件的能力“ 总结： 1、1)constexpr是编译期常量，constexpr元编程的引入；2)变长参数模板类和函数模板，库编写用简单实例思维解决，非库编写者用tuple和容器的emplace系列函数即可。元编程对库程序员是一种简化，而不是复杂化。 2、并行编程: 1）原子类型：atomic定义基本类型，自定义类型用_Atomic实现(现在还不支持)，原子类型是编译器用了系统底层的总线锁或存储锁加快锁定，其它同时访问线程会被阻塞，atomic_flag自旋无锁同步，memory_order对弱顺序代码执行内存模型调优，是cpp11并行编程中的一大亮点。 2）.多线程库引入：cpp11内置的线程其实是封装了pthread线程，使用更加简单，但是没有pthread底层和控制能力强。 3).TLS变量，对全局静态常量数据和线程生命期绑定，关键字是thread_local。cpp11 errno变量是线程局部的而不是全局的。 3、进程退出：用quick_exit需要退出回调的用at_quick_exit（目前LLVM还没实现)；异常退出还是要terminate实现。

VI 、"为改变思考方式而改变“ 总结： 1、nullptr引入，用单一职责思维，避免NULL存在指针和整型的二义性，nullptr_t类型可以进行赋值到指针和进行比较运算(与指针的)。 2、=default恢复编译器默认的函数，方便书写和保证POD类型；=delete指定删除，方便禁止一些拷贝构造赋值和移动拷贝构造赋值函数，全局和普通函数的某个重载版本也可以禁止。 3、lambda函数编程的引入，注意捕获列表中传值和传引用区别（都是定义初始化仿函数闭包对象，但是&可获得调用时上下文值,&自定义类型性能更高，但要小心使用)。在stl仿函数，泛型编程，复杂函数中作为匿名函数广泛使用。lambda相比仿函数还是有区别的，只能函数内部初始化和使用，自定义仿函数和普通函数可以在不同作用域初始化和使用，所以使用时候区分就好。

VII、融入实际应用" 总结： 1、alignas是设置变量的对齐大小，alignof是获取变量的对齐大小，可以单独对变量对齐进行设置；stl库里面的align函数，aligned_storage和aligned_union模板对内存块进行对齐调整。 2、通用属性，cpp11引入的[[noreturn]]（用在异常，终止，无限循环函数中)和[[carries_dependency]](用在弱内存模型并行编程中）属性声明符号。 3、Unicode字符串，1）cpp11中默认的string 是utf8编码，存储省空间，增删查找也是可以的(utf16更加方便些)，计算文字数需转换到u16string。 2）c++11对于字符转换用基于locale的codecvt，也可以直接用wstring_convert配合codecvt_utf8_utf16等直接进行转换，注意utf16有大小端。 3）输出时候的一些设置，内部会调用设置相关的函数,cpp98添加了wifstream和wofstream类，但是cpp11没有u16ifstream和u32ofstream等，需要转换到更节省的utf8类型。 4）原生字符串字面量，语法R”()”，但是转义字符不能再使用。

VIII、c++11和boost关系，boost的使用：
你可以大致看下C++11比C++03多了什么。那些东西很多都是从boost库里拉过去的。主要是智能指针、线程、hash数据结构。
正则表达式，另外，boost里面还有filesystem我认为比较实用。
尽量使用c++11，在使用boost可以获得比较方便的方案时候，可以采用boost，如:filesystem,date_time（其实用cpp11实现也是可以的）。
下面是使用xcode下使用filesystem的例子：
下载：http://www.boost.org/users/download/
编译：http://blog.csdn.net/blues1021/article/details/45034133
xcode添加第三方库：http://lirui.blog.51cto.com/2336974/1211215
头文件的添加，借鉴默认的lib searchpath,如下：
$(inherited)
$(PROJECT_DIR)/boost_test
$(PROJECT_DIR)/boost_test/boost
测试代码：
http://blog.csdn.net/flyingleo1981/article/details/7951373
http://blog.csdn.net/wishchin/article/details/11900961
代码见：集成项目见github。

拓展阅读：
http://blog.jobbole.com/44015/
http://zh.cppreference.com/w/cpp
http://www.cplusplus.com/reference/
