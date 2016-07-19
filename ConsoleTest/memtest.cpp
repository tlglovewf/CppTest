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
#include "dlmamlloc.h"
#define ABORT_ON_ASSERT_FAILURE 0
#include "nedmalloc.c"

#include <time.h>
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

int main(int argc, const char * argv[]) {

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
        int *x = (int*)nedalloc::nedmalloc(sizeof(int));
        nedalloc::nedfree(x);
    }
    time_t t4 = clock();
    cout << "nedmalloc: " << (t4 - t3) / CLOCKS_PER_SEC << endl;
    return 0;
}
