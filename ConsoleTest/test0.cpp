//
//  main.cpp
//  test0
//
//  Created by TuLigen on 17/8/23.
//  Copyright © 2017年 TuLigen. All rights reserved.
//
#include "stdio.h"
#include <iostream>
#include "string.h"
#include <map>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

struct Item
{
    int a;
    int b;
};

typedef Item item[3];


void display( item *i)
{
    cout << i[0]->a << endl;
}

struct T
{
    int a;
    int b;
};

class Te
{
public:
    
protected:
    const int a = 10;
};
int main(int argc, const char * argv[]) {

    
    std::vector<int>   vec;
    
    vec.push_back(10);
    vec.push_back(12);
    vec.push_back(13);
    
    cout << *(vec.data() + 1)<< endl;
    
    
    return 0;
     //srand((int)time(NULL));
    
    string str = "12345678";
    
    string sub = str.substr( 10, 11);
    
    cout << sub.c_str() << endl;
    return 0;
    time_t  t = clock();
    
    cout << t <<endl;
    return 0;
    
    cout << pow(2, 1/3.0) << endl;
    return 0;
    for(int i = 0; i < 100;++i)
    {
       
        
        printf("%f\n",  (rand()%10)/10.0);
    }
    
    return 0;
    
    cout << floor(0.3) << endl;
    return 0;
    vector<int>  temps;
    temps.push_back(0);
    temps.push_back(1);
    temps.push_back(2);
    temps.push_back(3);
    
     cout << temps[2] << endl;
    
    temps.resize(2);
    
    cout << temps.size() << endl;
    
    temps.push_back(4);
    
    cout << temps[2] << endl;
    return 0;
    
    // insert code here...
    /*char ccc[] = {"1-3-l-o-v-e"};
    
    char *t = strtok(ccc , "-");
    
    while(NULL != t)
    {
        cout << t << endl;
        
        t = strtok(NULL, "-");
    }
    */
    /*
    const char *str = "c_5";
    int a, b;
    char c[20];
    sscanf(str, "%d_%d_%s",&a,&b,c);
    
    cout<<a<<b<<c<<endl;
    
    return 0 ;
    
    map<string,int>    temps;
    int size = 0;
    const float time_len = 1000.0;
    time_t  cur1 = time(NULL) ;
    for(int i = 0;i < 1e6;++i)
    {
        char   temp[1024] = {0};
        sprintf(temp, "abcdefghijklmnopqrst %d",10);
        temps.insert(make_pair(temp, 1));
        size += sizeof(char) * strlen(temp) + sizeof(int);
    }
    time_t  cur2 = time(NULL);
    float t = (cur2 - cur1) / time_len;
    cout << t << endl;
    
    map<string, int>::iterator it = temps.find("abcdefghijklmnopqrst10");
    
    time_t cur3 = time(NULL);
    t = (cur3 - cur2) / time_len;
    cout << t << endl;
    temps.insert(make_pair("helloworld templatid1000", 1));
    time_t cur4 = time(NULL);
    t = (cur4 - cur3) / time_len;
    cout << t << endl;
    cout << size / (1024.0 * 1024.0) << endl;
    return 0;
    */
}
