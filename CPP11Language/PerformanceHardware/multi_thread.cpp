//
//  multi_thread.cpp
//  CPP11Language
//
//  Created by Sam on 2017/6/8.
//  Copyright © 2017年 Sam Cen. All rights reserved.
//

#include "multi_thread.hpp"
void* run(void*)
{
    long long i = 0;
    cout << "call run begin gTotal:" << gTotal << ", i:" << i << endl;
    for(; i < 1000000LL; i++)
    {
        pthread_mutex_lock(&gM);
        gTotal += i;
        pthread_mutex_unlock(&gM);
    }
    cout << "call run end gTotal:" << gTotal << ", i:" << i << endl;
    return nullptr;
}

void PrintThreadTest()
{
    cout << "PrintThreadTest: " << endl;
    pthread_t thread1, thread2;
    if(pthread_create(&thread1, nullptr, run, nullptr))
    {
        throw;
    }
    if(pthread_create(&thread2, nullptr, run, nullptr))
    {
        throw;
    }
    cout << "call thread1:" << endl;
    pthread_join(thread1, nullptr); // 表现上，会阻塞主线程在此，但是内部的thread2，cpp11的thread1和thread2都是有运行的；后面会一起全部返回。
    cout << "call thread2:" << endl;
    pthread_join(thread2, nullptr);
    cout << "total value:" << gTotal << endl;
    
    // cpp 11 thread test, is wrapper POSIX pthread,with atomic, thread pool more powerful
    PrintCpp11Thread();
    
    PrintAtomicFlag();
    
    PrintAtomicMemory();
}

void func(int)
{
    long long i = 0;
    cout << "cpp11 call func begin gTotal:" << gTotal2 << ", i:" << i << endl;
    for(; i < 1000000LL; i++)
    {
        gTotal2 += i;
    }
    cout << "cpp11 call func end gTotal:" << gTotal2 << ", i:" << i << endl;
}


void PrintCpp11Thread()
{
    thread thread1(func, 0), thread2(func, 0);
    cout << "cpp11 call thread1:" << endl;
    thread1.join();
    cout << "cpp11 call thread2:" << endl;
    thread2.join();
    cout << "cpp11 total2 value:" << gTotal2 << endl;
}

void Lock(atomic_flag *paf)
{
    while(paf->test_and_set(std::memory_order_acq_rel)) // test_and_set会将atomic_flag写入true值，返回旧值,如果一直为true则会等待，比锁效率高。
    {
//        cout << "Waiting" << endl;
    }
}

void UnLock(atomic_flag *paf)
{
    paf->clear();// test_and_set会将atomic_flag写入false值
}

void FlagFunc1(int threadid)
{
    while(1)
    {
        Lock(&gFlagLock);
        cout << "Thread working" << endl;
    }
}

void FlagFunc2(int threadid)
{
    while(1)
    {
        usleep(100);
        UnLock(&gFlagLock);
    }
}

void PrintAtomicFlag()
{
    cout << "PrintAtomicFlag:" << endl;
    gFlagLock.test_and_set();// 设置为true值
    //
//    thread thread1(FlagFunc1, 1), thread2(FlagFunc2, 2);
    
//    thread1.join();
//    usleep(100);
//    thread2.join();
}

void Producter(int)
{
    string *pStr = new string("item");
    pAtomicStr.store(pStr, memory_order_release); // 本线程中，所有的之前的原子写操作完成后，才能执行本原子操作；确保在顺序中是最后一个写的。
    atomicData.store(42, memory_order_relaxed); // 没有内存顺序限制，cpu执行代码可以乱序调优
    
}

void Consumer(int)
{
    string *p2 = nullptr;
    while( !(p2 = pAtomicStr.load(memory_order_consume)) ) // 本线程中，所有后续关于本原子类型的操作，必须在本操作完成后进行；确保是第一个消费的。
    {
    }
    assert(*p2 == "item"); // 这里*p2是没有问题的，因为memory_order_consume保证了
    cout << "from consumer str:" << *p2 << endl;
    int value = atomicData.load(memory_order_relaxed);// cpu执行代码可以乱序调优
    cout << "from consumer value:" << value << endl;
}

void PrintAtomicMemory()
{
    cout << "PrintAtomicMemory:" << endl;
    thread thread1(Producter, 0), thread2(Consumer, 0);
    thread1.join();
    thread2.join();
    
}









