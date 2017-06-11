//
//  StringTest.hpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//
// CPP 11字符串操作见: http://blog.poxiao.me/p/unicode-character-encoding-conversion-in-cpp11/
// 注意使用的编码集的单个字字节数，大小端存放，BOM前缀。

#ifndef StringTest_hpp
#define StringTest_hpp
#include <string>
#include <iostream>
#include <iomanip>
#include <type_traits>
#define NDEBUG
#include <codecvt>
using namespace std;
//#include <stdio.h>

class StringTest
{
public:
    void BaseTypeTest();
    void PrintStrCode();
    void Display();
// 默认string是UTF-8类型(全面字符)，这样默认类型非ascii，就可以类似c#(默认utf-16)一样统一处理字符串了
// utf16 ucs4编码想用io流输出需要转换为utf8或用boost.local库输出。
//    C++11标准库在<codecvt>头文件中定义了3个Unicode编码转换的Facet
//    std::codecvt_utf8	封装了UTF-8与UCS2及UTF-8与UCS4的编码转换
//    std::codecvt_utf16	封装了UTF-16与UCS2及UTF-16与UCS4的编码转换
//    std::codecvt_utf8_utf16	封装了UTF-8与UTF-16的编码转换
//    编码	BOM
//    UTF-8	0xEF 0xBB 0xBF
//    UTF-16 BE	0xFE 0xFF
//    UTF-16 LE	0xFF 0xFE
//    UTF-32 BE	0x00 0x00 0xFE 0xFF
//    UTF-32 LE	0xFF 0xFE 0x00 0x00
    void PrintStr();
    void FreedomUseUtf8Str();
};

template<typename tStringType, typename tTraits = typename tStringType::traits_type>
void print_code_unit_sequence(tStringType str)
{
//    typedef typename tTraits::char_type char_type;
    using char_type = typename tTraits::char_type; // 模板类型别名char_type
    using int_type = typename tTraits::int_type;
    static_assert(is_same<char_type, char>::value || is_same<char_type, char16_t>::value || is_same<char_type, char32_t>::value, "error");
    using unsigned_char_type = typename std::make_unsigned<char_type>::type;
    using unsigned_int_type = typename std::make_unsigned<int_type>::type;
    int w = is_same<char, char_type>::value ? 2 : (std::is_same<char16_t, char_type>::value ? 4 : 8);
    for(auto c : str) {
        auto value = static_cast<unsigned_int_type>(static_cast<unsigned_char_type>(c));
        cout << "0x" << hex << uppercase << setw(w) << setfill('0') << value << ' ';
    }
}
#endif /* StringTest_hpp */
