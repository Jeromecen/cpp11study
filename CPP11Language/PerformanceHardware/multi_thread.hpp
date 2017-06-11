//
//  multi_thread.hpp
//  CPP11Language
//
//  Created by Sam on 2017/6/8.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#ifndef multi_thread_hpp
#define multi_thread_hpp

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cassert>
using namespace std;

// phtread风格
#include <pthread.h>
static long long gTotal = 0;
static pthread_mutex_t gM = PTHREAD_MUTEX_INITIALIZER; // 不添加static修饰会报错
void* run(void*);
void PrintThreadTest();

// c++11风格
#include <thread>
#include <atomic>
using namespace std;
//static atomic_llong gTotal2{0};
static atomic<long long> gTotal2{0};
struct MyatomicType
{
    long long sum;
};
//_Atomic<MyatomicType> gMyData{0}; // _Atomic还没有实现
void func(int);
void PrintCpp11Thread();

// cpp 11 atomic_flag原子类型实现自旋锁
static atomic_flag gFlagLock = ATOMIC_FLAG_INIT;
void Lock(atomic_flag *paf);
void UnLock(atomic_flag *paf);
void FlagFunc1(int threadid);
void FlagFunc2(int threadid);
void PrintAtomicFlag();

// cpp 11 原子类型对多cpu执行代码的内存模型调优
static atomic<string*> pAtomicStr;
static atomic<int> atomicData;
void Producter(int);
void Consumer(int);
void PrintAtomicMemory();
#endif /* multi_thread_hpp */
