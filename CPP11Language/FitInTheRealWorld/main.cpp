//
//  main.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/10.
//  Copyright © 2017年 Sam Cen. All rights reserved.
// “融入实际应用" 总结：
//一、alignas是设置变量的对齐大小，alignof是获取变量的对齐大小，可以单独对变量对齐进行设置；stl库里面的align函数，aligned_storage和aligned_union模板对内存块进行对齐调整。
//二、通用属性，cpp11引入的[[noreturn]]（用在异常，终止，无限循环函数中)和[[carries_dependency]](用在弱内存模型并行编程中）属性声明符号。
//三、Unicode字符串，1）cpp11中默认的string 是utf8编码，存储省空间，增删查找也是可以的(utf16更加方便些)，计算文字数需转换到u16string。
//                2）c++11对于字符转换用基于locale的codecvt，也可以直接用wstring_convert配合codecvt_utf8_utf16等直接进行转换，注意utf16有大小端。
//                3）输出时候的一些设置，内部会调用设置相关的函数,cpp98添加了wifstream和wofstream类，但是cpp11没有u16ifstream和u32ofstream等，需要转换到更节省的utf8类型。
//               4）原生字符串字面量，语法R”()”，但是转义字符不能再使用。

#include "struct_align.hpp"
#include "generate_attribute.hpp"
#include "unicode_test.hpp"

int main(int argc, const char * argv[]) {
//1.alignas是设置变量的对齐大小，alignof是获取变量的对齐大小，可以单独对变量对齐进行设置，原来的__attribute__((__aligned__(8)))和#pragma pack是整个app的数据对齐大小。
// stl库里面的align函数，aligned_storage和aligned_union模板对内存块进行对齐调整。
// 结构体数据的对齐与处理器的高速缓存器大小对齐，有利于提供缓存和读取性能。虽然系统设计者常在应用程序二进制接口中(ABI)详细规定在特定平台上数据长度和数据对齐方式的相关信息，
// 但是在不同平台上基本（内置)类型定义上不同长度可能不同，有不同的平台对齐要求，编译出来的自定义数据还是会有不同的对齐表现。
// Cpp11中用alignas(32)指定自定义数据对齐方式，例如：
// struct alignas(32) ColorVector{
//        double r;
//        double g;
//        double b;
//        double a;
// }
// alignas(32),alignas(double)都是可以的，值必须是2的次方，替代GNU的__attribute__((__aligned__(8))),或#pragma pack(8)。alignof和sizeof一样也是获得和平台相关的值，
// 在c++ 11标准中规定了基本对齐值一般等于平台上long double的字节值，可以用alignof(max_align_t)来查询，用alignas指定的是拓展对齐，拓展对齐超过平台要求的对齐值，按照cpp标准是不规范的，
// 可能会导致编译时或运行时错误。
// alignas可以修饰类型，变量，类的数据成员等，但是位域及用register（要求尽量放到cpu寄存器中)声明的变量不可以使用。
// 固定容量的泛型数组有时可能遇到因为对齐不佳而导致的性能损失（甚至遇到错误), 给库的编写者带来了很大的困扰，而引入alignas能够解决这些移植性的困难，可能也是cpp委员会决定不再”隐藏”变量的对齐方式的原因。
// 变长类型的alignas可以用模板来定义alignas(T)。
// 可以用stl库里面的align函数，aligned_storage和aligned_union模板对内存块进行对齐调整，见示例：
    PrintAlign();
    
//  2.通用属性，cpp11引入的[[noreturn]]（用在异常，终止，无限循环函数中)和[[carries_dependency]](用在弱内存模型并行编程中）属性声明符号。
//    GNU编译器的g++可以声明为：
//    __atrribute__ ((attribute-list)) 为函数，变量和类型设定一些额外信息，以便编译器可以进行错误检查和性能优化。
//    extern int area(int n) __attribute__((const)); // 只是依赖于输入，不会改变函数外的数据，编译器对area(3)的值只会计算一次，大大提高了性能。
//    int main(){
//        int i;
//        int areas = 0;
//        for(I = 0; i < 10; I++)
//        {
//            areas += area(3) * I;
//        }
//    }
//    __atrribute__ ((attribute-list)) 的list关键字还有format, noreturn, const和aligned等。
//    windows平台上有另一个关键字__declspec (extend-decl-modifier),微软平台的程序员可以通过：
//    __declspec(align(32)) struct struct32{ // __declspec(align(32))根alignas(32)效果是一样的
//        int I;
//        double d;
//    };
//    __declspec (extend-decl-modifier)还定义了其它的关键字noreturn, oninline, align, dllimport, dllexport等。
//    cpp11也面临着关键字过多的问题，cpp11语言制定者决定增加通用属性这个特性，直观的来看，更加简洁。
//    cpp11的通用属性：
//    [[ attribute-list ]] 这样设计是为了不消除语言添加或者重载关键字的能力，又不会占用用户空间的关键字的名字空间。
//    cpp11的通用属性可以作用于类型，变量，名称，代码块等。
//    Cpp11仅通过了两个通用属性，包括[[noreturn]]和[[carries_dependency]]两种。
//    1）[[noreturn]]标识不会返回的函数，不会返回是该函数被调用后，后续代码不会再被执行，而调用void函数后是后面代码继续执行。
//    [[noreturn]]主要用在终止程序的函数，有无限循环语句的函数，有异常抛出的函数等，帮助编译器免除为调用者保存特定寄存器等代码优化工作，死代码消除，和产生更好的警告信息。
//    [[noreturn]] void abort(void) noexcept;
//    [[noreturn]] void throwaway(){
//        throw “expection”;
//    }
//    2）[[carries_dependency]]是在弱代码内存模型顺序并行情况下进行编译器优化。
//    对于并行编程的原子操作控制类型，例如memory_order_consume需要保证对当前原子类型数据的读取操作先于之后所有对该原子类型的操作。
//    那么对于函数块内，调用了其它函数func2，则编译器为了安全起见，会在调用func2之前插入一条内存栅栏，如果调用函数内没有该原子类型的操作，那么会影响性能。使用[[carries_dependency]]修饰func2的参数或返回类型，
//    那么编译器不会再为func2插入内存栅栏，有利于提高性能。
//    在代码执行内存模型为强顺序的平台不需要[[carries_dependency]]修饰，在弱内存模型平台上，很关心并行程序执行性能时，才会考虑使用[[carries_dependency]]。
    PrintInfo();
    
// 3.Unicode字符串知识，存储增删查找使用和转换：
//    1)字符串编码基础知识，cpp11中默认的string 是utf8编码，存储省空间，增删查找也是可以的(utf16更加方便些)，计算文字数需转换到u16string：
//    Cpp98引入了wchar_t类型，cpp11标准对于whar_t宽度非语言标准由编译器决定的显得太过容忍了，win上是16位宽，linux上是32位，这样程序员写的wchar_t代码通常不可移植。cpp11引入了两种新的内置数据类型，用来编码不同长度的unicode数据：
//    char16_t: 用于存储UTF-16的unicode数据，单个字符2字节16bit。
//    char32_t：用于存储UTF-32的unicode数据，单个字符4字节32bit。
//    Cpp11还是使用char类型的数组来保存UTF-8编码的Unicode数据，单个字符是变长的英文是1个字节8bit，汉字是3个字节表示24bit。
//    这些类型的长度规定和编码方式，在每个编译器或系统中都要求一样。
//    Cpp11还定义了常量字符串前缀：u8表示为UTF-8编码；u为UTF-16编码；U为UTF-32编码，L是声明为wchar_t宽字符串的前缀，没有前缀的是普通的字符串字面量，尽量不要将不同前缀的字符串常量链接，因为不同编译器解析也许不同。
//    char16_t ni= u’好’;
//    char16_t ni2= ‘\u597D’; // 等价于u‘好’, 也可以用UTF-16的unicode码位来赋值。
//    char utf8[] = u8”\u4F60\u597D\u554A”;
//    char16_t utf16[] = u”hello”;
//    char32_t utf32[] = U”hello equals \u4F60\u597D\u554A”;
//    cout << ni << endl;
//    cout << ni2 << endl;
//    cout << utf8 << endl;
//    cout << utf16 << endl;
//    cout << utf32 << endl;
//    要在自己的系统上看到正确的unicode文件，处理内部编码数值和编码集正确，还要输入输出环境，编译器，编辑器等的支持。
//    1）对于代码编辑器，如果是gb2312则输入的”你”会被存储为gb2312的编码数字，如果是ut8编码则存储的是utf8的编码数字。
//    2）编译器也有文件格式设置，如果编译器文件格式和代码文件格式一致，则保持的编码数据是程序员希望的，否则可能出现问题。
//    3）输出，c++的操作符<<保证把数据以字节的方式输出到输出设备，但是输出设备是否能够支持该编码类型的输出，取决于设备驱动的软件层。
//    Linux机器，大多数软件shell,vim,g++编译器都会根据Linux的locale设定而才赢UTF-8编码。而utf16,utf32输出失败，原因就是因为系统并不支持utf16和utf32输出。
//    Linux/Mac上通用utf-8格式，window上用utf-16的unicode设置，当要在不同平台移植时候注意代码编辑器和编译器是否使用了不同的编码方式，并按需调整。
//    
//    2)c++11对于字符转换用基于locale的codecvt，也可以直接用wstring_convert配合codecvt_utf8_utf16等直接进行转换，注意utf16有大小端。
//    类型的转换c11方式可以方便转换。
//    c++11对于字符转换的新方法都要c++ local机制的支持。c++中，通常情况下locale描述的是一些必须知道的区域特征，如程序运行的国家/地区的数字符号日期货币等，例如美国采用英文和utf-8编码这样的locale表示为:
//    en_US.UTF-8;//好像没有该字符集
//    而中国大陆采用简体中文和gb2312编码的local为：
//    zh_CN.GB2312
//    知道了一个地区的locale,需要使用不同地区的特征，则需访问该locale的一个facet,facet可以简单的理解为locale的一些接口，如num_put/num_get等操作来获取地区的数字存取函数，c++中常见的facet除了num_get/num_put, money_get/money_put，还有一种就是codecvt。
//    Coecvt是一个模板类，是一种能够完成从当前locale下多字符编码字符串到多种unicode字符编码转换（也包括unicode之间字符编码转换)的facet。cpp11规定，一共需要实现四种这样的codecvt facet。
//    如下：
//    codecvt<char, char, mbstate_t> // 多字节和char之间的转换
//    codecvt<char16_t, char, mbstate_t>// UTF-16和UTF-8之间的转换
//    codecvt<char32_t, char, mbstate_t>// UTF-32和UTF-8之间的转换
//    codecvt<wchar_t, char, mbstate_t>// 多字节和wchar_t之间的转换
//    现在编译器下一种locale不一定支持上述所有的codecvt facet的转换，可以用has_facet来查询该locale在本机上的支持情况：
//    locale lc("zh_CN.GB2312");
//    cout << "locale unicode codecvt test:" << endl;
//    bool can_cvt = has_facet<codecvt<char, char, mbstate_t>>(lc);
//    if(!can_cvt)
//    {
//        cout << "not support utf8->utf8 facet" << endl;
//    }
//    else
//    {
//        cout << "support utf8->utf8 facet" << endl;
//    }
//    也可以直接用派生自codecvt的函数:codecvt_utf8,codecvt_utf16,codecvt_utf8_utf16等可以用于字符串转换的模板类, 这些模板配合wstring_convert模板，可以进行一些不同的字符串的转换。
//    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> cvt;
//    wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> myCvt;
//    string u8_source_str = u8"汉字"; // utf-8
//    u16string u16_cvt_str = cvt.from_bytes(u8_source_str); // utf-8 to utf-16
//    string u8_cvt_str = cvt.to_bytes(u16_cvt_str); // utf-16 to utf-8
//    string strPri = myCvt.to_bytes(str16Pri);;
//    u16string str16reconvert = myCvt.from_bytes(strPri);
//    
//    //3) 输出时候的一些设置，内部会调用设置相关的函数,cpp98添加了wifstream和wofstream类，但是cpp11没有u16ifstream和u32ofstream等，因为太浪费空间是不必要的：
//    ofstream(“text.txt”) << u8”z\u00df\u6c34\U0001d10b”;
//    wifstream fin(“text.txt”);
//    // 该locale的facet: codecvt<wchar_t,char,mbstate_t>可以将utf8转换为utf32
//    fin.imbute(locale(“en_US.UTF-8”));
//    
//    Cout << “the utf8 file contains the following wide characters:\n”;
//    for(wchar_t c; fin >> c;)
//    {
//        cout”U+” << hex << setw(4) << setfile(‘0’) << c << ‘\n’;
//    }
//    4）原生字符串字面量
//    Cpp11提供了”所见即所得”的原生字符串字面量支持，不再需要\t,\n等控制字符来调整字符串中的格式，方便了学习和代码的编写。
//    语法是：R”()”;
//    R”(originstring)”.
//    UTF-8是u8R,UTF-16是uR, UTF-32是UR。
//    但是使用原生字符串标识后，转义字符就不能再使用了，如果有影响还是使会非原生字符串字面量。
//    链接不同声明的字符串时候可能会得到不是自己想要的结果，所以尽量不要去链接。
    PrintUnicodeTest();
}
