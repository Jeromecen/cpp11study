//
//  main.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/6.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
//“提高类型安全" 总结：一、新枚举类型：新增了enum class enumName:type{}作用域限定符和类型。
//                 智能指针：unique_ptr用在单模块内使用，shared_ptr和weak_ptr用引用计数在多个模块间共享。记得初始化；判是否有效，*和->使用，需转换为原指针迭代跳转；move或reset后要小心使用。
//                 GC: 标记-清除GC实现，现在暂时定义了接口，原因是指针的太灵活(指针任意在内存中跳转)导致隐藏指针，GC会误删，用declare_reachable等标记隐藏指针解决，且delete和回收是兼容的。
//
#include <iostream>
using namespace std;
/*
int main(int argc, const char * argv[]) {
    //1.cpp11 enum class类型被设计为强作用域类型(和struct,union,class,namespace一样)； 避免命名冲突的困扰。其实一个类内有一个枚举类型是可以接受的。
    // 可以指定类型（避免不同编译器产生不同枚举类)，默认类型是int,指定语法是：enum class enumTypeName: unsigned int{};unsigned int可以是任何基础类型（除了wchar_t)。
    // 原来C风格的enum类型还是保留兼容的。新增的特性，考虑到简单和兼容，就是在原来基础上增加一个关键字class。
    // 这里所有的enum类型都是POD类型的。
    enum class Type{ // enum struct语法是一样的，这里都没有访问控制符，没有进行模板声明；使用新的枚举类型尽量提供名字。
        Male,
        Female,
    };
    enum TypeOrigin: char{// 原来的枚举类型可以指定类型，来保证各个编译器中一致类型
        Male,
        Female,
    };
    
    enum class TypeChar: char{
        Male,
        Female,
    };
    cout << "enum class test:" << endl;
    cout << "Male 1:" << Male <<  endl; // 该Male是来自enum TypeOrigin类型的
    cout << "Male 2:" << (int)Type::Male <<endl; // 要输出还是要转换为基础类型实现
    // 2.堆内存管理：智能指针和垃圾回收
    // 总结：智能指针是通过智能指针对象本身是栈类型对象，委托管理了堆内存对象，栈对象超出生命期后会自动调用析构函数。shared_ptr和weak_ptr内部还有一个ptr_manage堆对象，实现统计引用计数。
    // unique_ptr用在单模块内，是限制增强版的auto_ptr，支持数组和返回右值。只有一个初始化，get()判空判断有效性，p++操作转换为原类型进行操作，reset/release或move后不能再使用。
    // shared_ptr和weak_ptr(避免循环引用)用在多个模块间引用计数，支持数组和返回右值。make_shared会深拷贝一个新对象，use_count和lock判断有效性，p++操作转换为原类型进行操作，reset或move后不能再使用。
    
    // 堆内存指针问题：多个模块相互引用，申请，操作，释放 会导致一些经典问题：野指针(删除后没有赋空或者删除后其它模块持有的指针)，空指针(未赋值或已经删除)，移动转换后的指针(各种重赋值操作)。
    // 导致的问题：1.使用及删除过程中的crash（使用空指针，野指针，delete/free野指针/空指针/移动后的指针。
    //           2.内存泄露（指针重赋值没有删除堆资源，隐含的无虚析构函数，容器元素指向的内存，一直持有不复用).
    // 堆内存的管理：一定要简单，接口统一,new/delete要一一对应，各模块之间强绑定或采用引用计数，或者模块1不持有模块2自管理（模块2复用需要申请才向模块1申请)。
    
    // 通过智能指针能够实现普通指针实现不了的功能，可以通过模板类的成员函数get()返回一个用于传递普通指针，实现向下兼容。
    // 智能指针能够自动回收资源，确保程序不存在内存何资源泄露切是异常安全的。通过new操作符需要自定义delete进行资源回收，存在这异常安全的隐患，造成内存泄露/野指针。
    // 在现代 C++ 中，原始指针仅用于范围有限的小代码块、循环或者性能至关重要且不会混淆所有权的 Helper 函数中。
    
    // 因为它本质是存放在栈的模板对象，只是在栈内部包了一层指针。而栈在其生命周期结束时，其中的指针指向的堆内存也自然被释放了。
    // cpp98采用auto_ptr智能指针，只能解决对于new非数组指针封装一层，到生命期后自动调用delete,避免程序员忘记delete。但是拷贝智能指针所有权转移了只有一个指针有所有权无法共享且有空指针问题，delete[]不支持。
    // 所以auto_ptr被cpp11废弃了。cpp11可以有效的解决cpp98存在的问题。
    // cpp11引入unique_ptr, shared_ptr, weak_ptr等智能指针（全面的思考)来自动回收堆内存。标准库还提供了"最小垃圾回收"支持。
    
    // 1）unique_ptr是一个唯一栈指针对象，唯一指向堆内存，不能拷贝赋值给其它unique_ptr（包括变量，函数参数），但是可以move转移给其它对象（移动构造函数, 移动赋值要避免)，自身不再拥有对象。
    // 栈的unique_ptr，拥有堆内存指针下（非空）在reset或超过声明期后会调用unique_ptr析构函数（不需要自动释放避免泄露），会释放堆内存，若是reset之后unique_ptr堆内存指针为空，自身对象还存在。
    // 使用：unique_ptr：构造ptr使用T*, 访问数据用ptr->使用的就是T*指针，获取T&类型用*ptr,获取T*类型用ptr->get()，手动释放用ptr->reset()/release()要小心不能再使用, get()==nullptr判断有效性。
    // 拷贝和赋值被删除了，只能转移。可以处理数组类型的堆内存，只是使用时候需要获取原来类型。
    // unique_ptr(const _Myt&) = delete;
    // _Myt& operator=(const _Myt&) = delete;
    cout<<"智能指针测试:"<<endl;
    unique_ptr<int> pt1(new int(1020)); // cpp11中唯一初始化方式，不能用unique_ptr<int> pt = new int(1020)形式，因为unique_ptr栈类没提供赋值函数。
    //  unique_ptr<int> pt2 = pt1; // 不能拷贝或赋值
    //  pt1.reset(); // 这里reset会释放堆内存
    //  pt1.release(); // release和reset效果一样，会释放堆内存
    cout<< "pt1 value:" << *pt1 <<endl; // 获取构造时候指针T*的值类型也就是T&类型。
    int *getPtr = pt1.get(); // *pt1不能获取int *getPtr指针，需要用unique_ptr的get()函数获取，目的是和非使用智能指针的项目向下兼容。
    //  unique_ptr<int> pt11 = make_unique<int>(getPtr); // make_unique不是cpp11的一部分，他是cpp14中引入的。
    cout<< "getPtr value:" << *getPtr <<endl;
    unique_ptr<int> pt2 = move(pt1); // 转换为右值引用，使用移动构造函数，pt1指向的堆内存指针被赋值为NULL
    pt1.reset();// pt1指向空堆内存，Reset不会产生作用
    if(pt1.get() == nullptr)
    {
        cout<< "pt1.get() is nullptr." <<endl;
    }
    //  cout<< "pt1 value:" << *pt1 <<endl; // 在pt1指向空堆内存操作，会crash。
    cout<< "pt2 value:" << *pt2 <<endl;
    
    // 2)shared_ptr是一个共享栈指针对象，通过引用计数的方式，可以拷贝赋值给其它shared_ptr，可以传递给shared_ptr函数参数。
    // shared_ptr实现是构造函数中才会去关联堆内存指针和一个ptr_manage对象，后面的拷贝构造/赋值函数，都是只是增加堆内存引用计数(但都存在指向堆内存指针和一个ptr_manage结构指针)，
    // 栈的shared_ptr对象超过生命期或主动reset时候，关联的ptr_manage对象的引用计数会减去1（刚初始化时候也是1），当为0则清理堆内存，若主动reset，则该shared_ptr指向的内存是空指针。
    // ptr_manage对象有shared_ref_cnt, weak_ref_cnt,ptr堆内存指针，当shared_ref_cnt等于0时候释放ptr堆内存指针，当shared_ref_cnt和weak_ref_cnt都等于0时候释放ptr_manage对象。
    //    使用：构造ptr使用T*, 访问数据用ptr->使用的就是T*指针，获取T&类型用*ptr,获取T*类型用ptr->get()，有效性判断用ptr.use_count()是否等于零。
    //    手动释放用ptr->reset()/release()要小心引用计数会减去1(自身对象还在，ptr_manage弱引用减去1，指向ptr_manage指针赋空), 返回T*都为空了（move也会导致T*返回为null)。
    //    make_shared会深拷贝一个全新的shared_ptr出来，语法如下：shared_ptr<MySharedData> sp3 = make_shared<MySharedData>(*sp2);
    class MySharedData
    {
    public:
        MySharedData(int i):id(i){};
        int id;
    };
    shared_ptr<MySharedData> sp1(new MySharedData(2020));
    shared_ptr<MySharedData> sp2 = sp1;
    MySharedData* osp = sp2.get();// 返回堆内存对象指针
    cout<< "sp osp * value:" << osp->id << endl; // ->符号其实是直接返回堆内存对象指针
    cout<< "sp 1 use_count:" << sp2.use_count() << endl;
    sp1.reset();
    //    sp1.release(); // 无release
    if(sp1.get() == nullptr)// reset后，ptr_manage对象有shared_ref_cnt减去1，且它能够获取T*的能力没有了。
    {
        cout<< "sp1.get() is nullptr." <<endl;
    }
    cout<< "sp value:" << sp2->id << endl;
    cout<< "sp 2 use_count:" << sp2.use_count() << endl;
    
    shared_ptr<MySharedData> sp3 = make_shared<MySharedData>(*sp2); // 深拷贝了一个全新的出来。
    cout<< "sp3  value:" << sp3->id << endl;
    cout<< "sp 3 use_count:" << sp2.use_count() << endl;
    
    //  3）weak_ptr不会增加shared_ref_cnt将不影响堆内存生命期，但是会增加shared_ptr关联的ptr_manage对象的weak_ref_cnt。
    //  用它的目的是破除循环引用的，它本身没有重载*和->运算符不能直接获取内存。当用weak_ptr访问堆内存时，堆内存可能已被释放，要先lock()获得一个可用的shared_ptr对象。
    //  weak_ptr使用：用shared_ptr或weak_ptr构造或赋值，通过lock()返回一个shared_ptr(成功强引用会加1，失败返回空，一定要判空进行有效性判断），然后访问数据；
    //              reset释放弱引用指针(自身对象还在，ptr_manage弱引用减去1，指向ptr_manage指针赋空)，利于ptr_manage对象的释放，use_cout获取也是强指针引用数。
    //  weak_ptr<MySharedData> wp = pt2; // 不能引用unique_ptr
    weak_ptr<MySharedData> wp(sp2); // 不会增加shared_ptr的use_count;说明use_count是强引用。
    weak_ptr<MySharedData> wp2(wp);
    cout<< "sp 4 use_count:" << sp2.use_count() << endl;
    cout<< "wp count 1 :" << wp.use_count() << endl; // 也是强指针引用数
    sp2.reset();
    //    wp.reset();
    shared_ptr<MySharedData> sp4 = wp.lock();
    if(sp4 == nullptr)// 判空可以避免堆内存释放后，弱智能指针还存在无法获取到强引用的情况。
    {
        cout<< "sp4 == nullptr from wp.lock() is nullptr." <<endl;
    }
    cout<< "sp 5 use_count:" << sp2.use_count() << endl;
    cout<< "wp count 2:" << wp.use_count() << endl;
    
    cout<< "sp3 value:" << sp3->id << ", count:" << sp3.use_count() << endl;
    shared_ptr<MySharedData> sp5 = move(sp3);
    if(sp3.get() == nullptr)
    {
        cout<< "sp3 == nullptr from wp.lock() is nullptr." <<endl;
    }
    cout<< "sp5 value:" << sp5->id << ", count:" << sp5.use_count() << endl;
    
    cout << "arry test:" << endl;
    unique_ptr<int> upArr(new int[100]);
    int *pArr = upArr.get();
    for(int i = 0; i < 100; i++)
    {
        *pArr++ = i;
    }
    pArr = upArr.get();
    for(int i = 0; i < 100; i++)
    {
        cout << *pArr++ << " ";
    }
    cout << endl;
    upArr.release();
    if(upArr.get() == nullptr)
    {
        cout << "arry pointer is null" << endl;
    }
    
    // 3.垃圾回收 最小垃圾回收支持
    //    没有指针再指向的内存空间称为”垃圾“，因为指针也是栈整型，如果所有指向该内存的指针脱离了生命期或者显式赋了它值(如null等)，那么该内存就是垃圾内存。
    //    而将这些垃圾回收起来以便再次利用的机制，称为”垃圾回收GC”.
    //    C/C++一大优势就是对于指针的灵活运用，指针可以在内存区域内区域外灵活的跳转，这样给垃圾回收器分析该内存是否有指针引用带来了麻烦，直接删则指针恢复指向该内存可能不存在了，记录灵活的指针指向和复原又太浪费编译器时间。要解决这种问题通常是使用新接口，引入了安全派生指针概念，对于非安全派生的可以用：
    //    declare_reachable()声明可达的，用undeclare_reachable()声明为不可达的。
    //    如:
    int *p = new int;
    *p = 22500;
    declare_reachable(p); // 编译器知道p类型，传递void*类型即可，通知垃圾回收器该地址可达，该指针指向的地址即使没有指向了，GC也不能删除它。
    //  void declare_no_pointers(<#char *__p#>, <#size_t __n#>); declare_no_pointers声明和declare_reachable意义一样，只不过是p开始连续n字节数的内存。
    p=p+10;
    // 通过函数模板，编译器记录的属性信息，返回实际的类型
    p = undeclare_reachable<int>(p - 10);// 去掉通知可达，GC可管理。
    //    void undeclare_no_pointers(<#char *__p#>, <#size_t __n#>);// 对应declare_no_pointers。
    cout << "Garbage collection" << endl;
    cout << " p value:" << *p << endl;
    
    // 判断编译器是否支持垃圾回收
    pointer_safety safeInfo = get_pointer_safety();
    cout << "pointer_safety test:" << endl;
    switch(safeInfo)
    {
        case pointer_safety::strict:
        {
            cout << "pointer_safety::strict" << endl;// 支持最小垃圾回收和安全派生指针概念。
            break;
        }
        case pointer_safety::relaxed:
        {
            cout << "pointer_safety::relaxed" << endl; // 不支持，这里是：XCODE LLVM C++11输出
            break;
        }
        case pointer_safety::preferred:
        {
            cout << "pointer_safety::preferred" << endl;// 不支持
            break;
        }
    }
    // 如果想要垃圾回收器工作（目前应该是基于标记清除的GC模式)，必须做出必要的假设来保证垃圾回收器能工作。必须限制指针的使用或用
    // declare_reachable/undeclare_reachable/declare_no_pointers/undeclare_no_pointers让一些不安全的指针使用免于垃圾回收器的检查。
    // 但是项目中使用指针的量太大，手动去修改几乎是不可能的。cpp11对指针的垃圾回收支持仅限于系统提供的new运算符分配的内存，而malloc分配的内存则由程序员控制。
    // 现在“最小垃圾回收”LLVM,GCC都不支持(2017.6.6包括cpp14)，但是对于被隐藏指针的堆对象进行declare_reachable/undeclare_reachable/declare_no_pointers/undeclare_no_pointers保护，
    // 且显式的delete并不会和垃圾回收形成冲突。在未来“最小垃圾回收”支持的时候，就会给项目带来益处。
 
}
*/
