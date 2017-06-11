//
//  struct_align.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/10.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "struct_align.hpp"
void PrintAlign()
{
    cout << "PrintAlign():" << endl;
    cout << "sizeof:" << sizeof(ColorVector) << endl;
    cout << "alignof:" << alignof(ColorVector) << endl;
    cout << "platform define max align value:" << alignof(max_align_t) << endl;
    
    FixedCapacityArray<char> dataCh;
    cout << "FixedCapacityArray<char> char:" << alignof(char) << ", data:" << alignof(dataCh.data) << endl;
    
    FixedCapacityArray<ColorVector> dataColor;
    cout << "FixedCapacityArray<ColorVector> ColorVector:" << alignof(ColorVector) << ", data:" << alignof(dataColor.data) << endl;
    
    StlAlignTest();
}

void StlAlignTest()
{
    cout << "StlAlignTest():" << endl;
   // 1.可以用align模板对内存块，进行对齐调整，调整参数见如下，对于每个调整后的对齐块，需要迭代一个字节进行下一个对齐块的调整；>0地址后调整返回的是对齐块的末地址。
    char buftest[] = "--";
    int sizetest = sizeof(buftest);
    
    char buffer[] = "------------------------?";
    void * pt = buffer;
    std::cout << pt << '\n';
    std::size_t space = sizeof(buffer)-1;// 25字节，\0是结尾字符
//  void* align (size_t alignment, size_t size, void*& ptr, size_t& space);
//  alignmen: Requested alignment, in bytes.
//  size: Size of the element to be aligned, in bytes.
//  ptr: Pointer to contiguous storage of at least space bytes.This argument, passed by reference, is updated by the function.
//  space: Maximum size of the buffer to consider for alignment.This argument, passed by reference, is updated by the function.
//  return value: If the aligned buffer fits into the proposed space, the function returns the updated value of ptr. Otherwise, a null pointer is returned.
    int count = 0;
    while ( std::align(alignof(int),sizeof(char),pt,space) != nullptr) { //调整成功返回调整后块的ptr首地址,否则返回nullptr
        count++;
        cout << "loop count:" << count << endl; //
        cout << "before pt:" << pt << endl;// pt是内存块对齐调整后返回的首地址，0x7fff5fbfed80,0x7fff5fbfed84
        char* temp = static_cast<char*>(pt);
        *temp='*';
        ++temp;
//        temp = temp +4; // 加4会crash
        cout << "before space:" << space << endl; // 25,21
        space-=sizeof(char); // space是空间的大小,注释掉不会迭代，加了一个temp字节，减少一个space字节
//        space-=sizeof(int); // 不能加4
        cout << "after space:" << space << endl; // 24,20
        pt=temp;// 当前返回的首地址+1，,注释掉不会迭代，从调整完毕后的下一个地址开始调整对齐
        cout << "after pt:" << pt << endl; // 0x7fff5fbfed81,0x7fff5fbfed85
    }
//    char curch = static_cast<char>(*pt);
//    std::cout << curch << '\n';
    std::cout << buffer << '\n';
    
    // 2.aligned_storage对齐模板库，用于在支持或不支持align中的编译环境下共享结构体，可以用aligned_storage解决。
//    Obtains a POD type suitable to use as storage for an object of a size of at most Len bytes, aligned as specified by Align.
    // 见：http://www.cplusplus.com/reference/type_traits/aligned_storage/?kw=aligned_storage
    A_pod a,b;
    new (&a) A (10,20);
    b=a;
    std::cout << reinterpret_cast<A&>(b).avg << std::endl;
    
    // 3.aligned_union可用于联合体等，使用了变长参数，要求最严格的一个
//    Obtains a POD type suitable for use as storage for any object whose type is listed in Types, and a size of at least Len.
    // 见：http://www.cplusplus.com/reference/type_traits/aligned_union/?kw=aligned_union
    U_pod ua, ub;              // default-initialized (ok: type is POD)
    new (&ua) U ("hello");   // call U's constructor in place
    ub = ua;                  // assignment (ok: type is POD)
    std::cout << reinterpret_cast<U&>(ub).i << std::endl;
}
