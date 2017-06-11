//
//  StringTest.cpp
//  CPP11Language
//
//  Created by Sam on 2017/5/31.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "StringTest.hpp"
void StringTest::BaseTypeTest()
{
    cout<<"BaseTypeTest():"<<endl;
    // utf-8，默认的类型，中文大部分是3个字节，少数是4个字节
    char u8_array[] = u8"Sam的博客";
    string u8_str = u8"Sam的博客";
    // utf-16，中文一般2个字节，需要用格式化输出需转换为utf-8或boost.locale
    char16_t u16_c = u'中';
    char16_t u16_array[] = u"Sam的博客";
    u16string u16_str = u"Sam的博客";
    
    // ucs4
    char32_t u32_c = U'𪚥';
    char32_t u32_array[] = U"Sam的博客";
    u32string u32_str = U"Sam的博客";
    //    locale loc("chs");
    //    wcout.imbue(loc);
    u8_str += " , Sandy Ou";
    cout<< "string:" << u8_str<< ", len:" << u8_str.length() << endl;
    //    locale loc("chs");
    //    wcout.imbue(loc);
}

void StringTest::PrintStrCode()
{
    cout<<"PrintStrCode():"<<endl;
    string u8_str = u8"字"; // utf-8
    u16string u16_str = u"字"; // utf-16
    u32string u32_str = U"字"; // ucs4
    cout << "utf-8: ";
    print_code_unit_sequence(u8_str);
    cout << std::endl;
    
    cout << "utf-16: ";
    print_code_unit_sequence(u16_str);
    cout << std::endl;
    
    cout << "ucs4: ";
    print_code_unit_sequence(u32_str);
    cout << std::endl;
}

void StringTest::PrintStr()
{
    cout<<"PrintStr():"<<endl;
    string u8_source_str = u8"汉字"; // utf-8
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> cvt;
    
    u16string u16_cvt_str = cvt.from_bytes(u8_source_str); // utf-8 to utf-16
    string u8_cvt_str = cvt.to_bytes(u16_cvt_str); // utf-16 to utf-8
    cout << "u8_source_str = ";
    print_code_unit_sequence(u8_source_str);
    cout << endl;
    cout << "u16_cvt_str = ";
    print_code_unit_sequence(u16_cvt_str);
    cout << endl;
    cout << "u8_cvt_str = ";
    print_code_unit_sequence(u8_cvt_str);
    cout << endl;
    
    // u16string to string , output
    cout<<"Out put u16string:"<<endl;
    u16string str16Pri = u"输出我u16string字符串";
    wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> myCvt;
    string strPri = myCvt.to_bytes(str16Pri);
    cout << strPri << endl;
    
    // u16string with bom to string, output；这种情况用C二进制块处理更加合适（通过字符识别去掉头)
    cout<<"Out put u16string without bom:"<<endl;
    u16string u16le_byte_str = u"\xff\xfe\x41\x00"; // utf-16 little endian with BOM
    u16string u16be_byte_str = u"\xfe\xff\x00\x41"; // utf-16 big endian with BOM
    wstring_convert<codecvt_utf8_utf16<char16_t, 0xffff, consume_header>, char16_t> utf16le_cvt; // little endian
    wstring_convert<codecvt_utf8_utf16<char16_t, 0xffff, consume_header>, char16_t> utf16be_cvt; // default big endian
    string str_from_le = cvt.to_bytes(u16le_byte_str); // utf-16 to ucs4
    string str_from_be = cvt.to_bytes(u16be_byte_str); // utf-16 to ucs4
    cout << "str_from_le = ";
    print_code_unit_sequence(str_from_le);
    cout << endl;
    cout << "str_from_be = ";
    print_code_unit_sequence(str_from_be);
    cout << endl;
}

void StringTest::FreedomUseUtf8Str()
{
    cout << "FreedomUseUtf8Str()"<< endl;
    string myName = "SamCen, with chinese name:";
    myName.append("岑家源");
    myName += ", cpp 11 is very cool!￥";
    cout << "name:" << myName << endl;
}
void StringTest::Display()
{
    cout<<"-----String Test Start------"<<endl;
    BaseTypeTest();
    PrintStrCode();
    PrintStr();
    FreedomUseUtf8Str();
    cout<<"-----String Test End------"<<endl;

}
