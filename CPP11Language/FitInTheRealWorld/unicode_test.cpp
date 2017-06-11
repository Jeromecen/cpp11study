//
//  unicode_test.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/11.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "unicode_test.hpp"
using namespace fitrealworld;

void PrintUnicodeTest()
{
    cout << "PrintUnicodeTest():" << endl;
    char16_t ni= u'好';
    char16_t ni2 = u'\u597D'; // 等价于u‘好’, 也可以用UTF-16的unicode码位来赋值。
    char utf8[] = u8"\u4F60\u597D\u554A";
    char16_t utf16same[] = u"\u4F60\u597D\u554A";

    char16_t utf16[] = u"hello";
    char32_t utf32[] = U"hello equals \u4F60\u597D\u554A"; // utf-32还是utf-8的unicode编码都一样,只是字节长度有区别。
    cout << ni << endl;
    cout << ni2 << endl;
    cout << utf8 << endl;
    cout << utf16 << endl;
    cout << utf32 << endl;
    
    cout << "字面编码相同，存储大小不同测试：" << endl;
    cout << "utf8:" << sizeof(utf8) << endl; // 10
    cout << "utf16same:" << sizeof(utf16same) << endl; // 8
    cout << utf8[1] << endl; // 输出了第一个字的第三个字节，utf8是变长的，不方便进行增删和查找，没有对应的string，但是存储时候节省存储空间，内存操作时候需转换为u16string或u32string。
    cout << utf16same[1] << endl; // 正确输出，定长的，第二个字的首地址，定长的u16string, u32string，方便增删和查找，因此一般在内存中，存储时候可转换为utf8。
    string myname = "岑家园";
    int len = (int)myname.find("家"); // 其实增删查找用utf8的string也是可以的。
    cout << "myname:" << myname << ", len:" << len << endl;
    
    locale lc("en_US.UTF-8");// en_US.UTF-8, zh_CN.GB2312
    cout << "locale unicode codecvt test:" << endl;
    bool can_cvt = has_facet<codecvt<char, char, mbstate_t>>(lc);
    if(!can_cvt)
    {
        cout << "not support utf8->utf8 facet" << endl;
    }
    else
    {
        cout << "support utf8->utf8 facet" << endl;
    }
    
    can_cvt = has_facet<codecvt<char16_t, char, mbstate_t>>(lc);
    if(!can_cvt)
    {
        cout << "not support utf8->utf16 facet" << endl;
    }
    else
    {
        cout << "support utf8->utf16 facet" << endl;
    }
    
    can_cvt = has_facet<codecvt<char32_t, char, mbstate_t>>(lc);
    if(!can_cvt)
    {
        cout << "not support utf8->utf32 facet" << endl;
    }
    else
    {
        cout << "support utf8->utf32 facet" << endl;
    }
    
    can_cvt = has_facet<codecvt<wchar_t, char, mbstate_t>>(lc);
    if(!can_cvt)
    {
        cout << "not support wchar_t->utf8 facet" << endl;
    }
    else
    {
        cout << "support wchar_t->utf8 facet" << endl;
    }
    
    cout<<"-----String Test Start------"<<endl;
    StringTest testObj;
    testObj.BaseTypeTest();
    testObj.PrintStrCode();
    testObj.PrintStr();
    testObj.FreedomUseUtf8Str();
    cout<<"-----String Test End------"<<endl;
    
    StreamUnicodeTest();

    // 字符串字面量，使用R"()"语义即可。
    cout << R"(hello cpp11 \n world is/n end!!!)"<<endl;
}

void StreamUnicodeTest()
{
    cout<<"StreamUnicodeTest:"<<endl;
    ofstream("text.txt") << u8"z\u00df\u6c34\U0001d10b";
    wifstream fin("text.txt");
    // 设置该locale的facet，输出设备将调用codecvt<wchar_t,char,mbstate_t>将utf8转换为utf32
    fin.imbue(locale("en_US.UTF-8"));
    
    cout << "the utf8 file contains the following wide characters:\n";
    for(wchar_t c; fin >> c;)
    {
        cout << "U+" << hex << setw(4) << setfill('0') << c << endl;
    }
}
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
    
    // string to u16string
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
    u16string str16reconvert = myCvt.from_bytes(strPri);
    
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



