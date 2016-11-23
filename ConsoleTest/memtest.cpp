//
//  main.cpp
//  ConsoleTest
//
//  Created by TuLigen on 16/6/17.
//  Copyright (c) 2016年 TuLigen. All rights reserved.
//


#include <fstream>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "mempool/MemoryPool.h"
#include "dlmamlloc.h"
//#define ABORT_ON_ASSERT_FAILURE 0
//#include "nedmalloc.c"

#include <time.h>
#include "MemAllocConfig.h"
using namespace std;
enum eStats
{
    eSuccessful,
    eFail
};


int getFileName(const char *path)
{
    DIR *basedir = NULL;
    basedir = opendir(path);
    if(NULL == basedir)
    {
        cout << "can not open directory:" << path << endl;
        return eFail;
    }
    
    chdir(path);
    struct dirent *entry;
    struct stat    filest;
    cout << " file list :" << endl;
    while((entry = readdir(basedir)) != NULL)
    {
        lstat(entry->d_name,&filest);
        if(S_ISDIR(filest.st_mode))
        {
            if(strcmp(".",entry->d_name) == 0 ||
               strcmp("..",entry->d_name) == 0)
                continue;
            char tmp[255] = {0};
            sprintf(tmp, "%s/%s",path,entry->d_name);
            getFileName(tmp);
        }
        else
        {
            cout <<  entry->d_name << endl;
        }
    }
    return eSuccessful;
}



void  testMalloc(void)
{
    time_t t1 = clock();
    const long exp = 1e8;
    /**
     *  system alloc
     */
    for(int i = 0; i < exp;++i)
    {
        int *x = new int(5);
        delete x;
    }
    time_t t2 = clock();
    cout <<  "crt : " << (t2 - t1) / CLOCKS_PER_SEC << endl;
    /**
     *  dlmalloc
     */
    for(int i = 0; i < exp;++i)
    {
        int *x = (int*)dlmalloc(sizeof(int));
        dlfree(x);
    }
    time_t t3 = clock();
    cout << "dlmalloc: " << (t3 - t2) / CLOCKS_PER_SEC << endl;
    /**
     *  nedmalloc
     */
    for(int i = 0; i < exp;++i)
    {
//        int *x = (int*)nedalloc::nedmalloc(sizeof(int));
//        nedalloc::nedfree(x);
    }
    time_t t4 = clock();
    cout << "nedmalloc: " << (t4 - t3) / CLOCKS_PER_SEC << endl;
}

class TestOne
{
public:
    TestOne(int _x):x(_x){}
    
    void display(void)const
    {
        cout << "print value : " << x << endl;
    }
private:
    int x;
};

typedef MemoryPool<TestOne> TestOneAlloc;


static TestOneAlloc testa;
void testMemPool(void)
{
    time_t t1 = clock();
    const int len  = 1e8;
    for(int i = 0; i < len ; ++i)
    {
        TestOne *x = new TestOne(5);
        delete x;
    }
    time_t t2 = clock();
    cout << "alloc time : " << (t2 - t1) / CLOCKS_PER_SEC << endl;
    for(int i = 0; i < len; ++i)
    {
        TestOne *x = testa.newElement(5);
        testa.deleteElement(x);
    }
    time_t t3 = clock();
    cout << "alloc time : " << (t3 - t2) / CLOCKS_PER_SEC << endl;
}

//.........test ned pool


class TestPool : public TLG::BaseAllocatedObject
{
public:
    TestPool(int _x):x(_x){}
private:
    int x;
};


void testNedPool()
{
    time_t t1 = clock();
    const int len  = 1e8;
    for(int i = 0; i < len ; ++i)
    {
        TestOne *x = new TestOne(5);
        delete x;
    }
    time_t t2 = clock();
    cout << "alloc time : " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl;
    for(int i = 0; i < len; ++i)
    {
//        TestPool *x = new TestPool(5);
//        delete x;
        TestOne *x = (TestOne*)dlmalloc(sizeof(TestOne));
        dlfree(x);
    }
    time_t t3 = clock();
    cout << "alloc time : " << (float)(t3 - t2) / CLOCKS_PER_SEC << endl;
}

//int main(int argc, const char * argv[])
//{
//    
////    testNedPool();
//
//    unsigned long  x = 1e32;
//    printf("%lu\n",x);
//    return 0;
//}
