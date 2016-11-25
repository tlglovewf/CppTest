//
//  test.cpp
//  XCodeCppTest
//
//  Created by TuLigen on 16/8/4.
//  Copyright © 2016年 TuLigen. All rights reserved.
//
#include <iostream>
//#include <experimental/optional>
//#include "Template.h"
#include <algorithm>
#include <sstream>
//#include <list>
#include "stdio.h"
using namespace std;
//class Test
//{
//public:
//    Test() = default;
//    Test(const Test&) = delete;
//};
//
//class Sprite : public BaseNode<Sprite>
//{
//public:
//    virtual void show(void)const
//    {
//        display();
//    }
//protected:
//    void display(void)const
//    {
//        cout << "show sprite." << endl;
//    }
//};
//
//class VItem
//{
//public:
//    VItem(){}
//    virtual ~VItem(){}
//    virtual void setIndex(int index) = 0;
//    virtual int  getIndex(void)const = 0;
//};
//class Item : public VItem
//{
//public:
//    Item():mindex(0){}
//    bool operator<( const Item &it)
//    {
//        return this->mindex < it.mindex;
//    }
//    virtual void setIndex(int index) { mindex = index;}
//    virtual int  getIndex(void)const { return mindex; }
//private:
//    int mindex;
//};
//bool comp(Item *left, Item *right)
//{
//    if(NULL == left ||
//       NULL == right)
//    {
//        return false;
//    }
//    else
//    {
//        return left->getIndex() < right->getIndex();
//    }
//}
int main(void)
{
//    char *cstr = "55,33";
//    char *pos = strchr(cstr, '-');
//    std::string  cc(cstr, pos - cstr);
//    std::stringstream ss(cstr);
//    int x;
//    ss >> x;
//    int y;
//    cout << x << " " << y <<  endl;
//    cout << ++pos << " " << cc.c_str() << endl;
//    
//    const char *test = "ff0000";
//    int x = 0;
//    sscanf(test,"%x",&x);
//    x =  x | 0xff000000;
//    printf("hello world %x.\n",x);
    const char *test = "502ff0000abcaff";
    int index,width,forecolor,backcolor;
//    sscanf(test, "%d%2d%x%x",&index,&width,&forecolor,&backcolor);
//    cout<< index << width << forecolor << backcolor << endl;
    string str(test);
    cout << atoi(str.substr(0,1).c_str()) << endl;
    cout << atoi(str.substr(1,2).c_str()) << endl;
    cout << str.substr(3,6).c_str() << endl;
    cout << str.substr(9,14).c_str()<<endl;
    return 0;
}