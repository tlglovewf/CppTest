//
//  test.cpp
//  
//
//  Created by TuLigen on 16/4/26.
//
//

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
struct Item
{
    int vec;
};

class One
{
public:
    One():x(1),y(2),z(3){}
    
    void display(void)const
    {
        cout << x << " " << y << " " << z << endl;
    }
protected:
    int x;
    int y;
    int z;
};

class Funcs
{
public:
    typedef void (__cdecl Funcs::*memFunc)(...);
    Funcs()
    {
        init();
    }
    void one(int* a,int *c)
    {
        int *b = a;
        cout << "one" << *b << endl;
    }
    void two(int* a,int *c)
    {
        int *b = a;
        cout << "two" << *b << endl;
    }
    void three(int* a, int *c)
    {
        int *b = a;
        cout << "three" << *b << endl;
    }
    void four(int* a, int *c)
    {
        int *b = a;
        cout << "four" << *b + *c << endl;
    }
    
    void test(One *a)
    {
        a->display();
    }
    void check(One *a)
    {
        a->display();
    }
    void init()
    {
//        funcs[0] = (memFunc)&Funcs::one;
//        funcs[1] = (memFunc)&Funcs::two;
//        funcs[2] = (memFunc)&Funcs::three;
//        funcs[3] = (memFunc)&Funcs::four;
        funcs[0] = (memFunc)&Funcs::test;
        funcs[1] = (memFunc)&Funcs::check;
    }
    void display(void)
    {
        One *one = new One;
        for(int i = 0; i < 2; ++i)
        {
           
            (this->*funcs[i])(one);
        }
    }
protected:
    
    memFunc funcs[4];
};
struct TypeDef
{
    int zIndex;
    int value;
};

#define PRINT(T)   for_each(T.begin(), T.end(), [](int a){\
                cout << a << " ";});\   
                cout << endl;

static bool Comp(int a, int b)
{
    return a > b;
}

//int main(void)
//{
//    vector<int>  test;
//    test.push_back(5);
//    test.push_back(3);
//    test.push_back(4);
//    test.push_back(3);
//    test.push_back(5);
//    test.push_back(10);
//    PRINT(test)
//    sort(test.begin(),test.end(),Comp);
//    PRINT(test)
//    
//    set<int,bool (*)(int,int)> sets(Comp);
//    sets.insert(5);
//    sets.insert(10);
//    sets.insert(3);
//    sets.insert(4);
//    PRINT(sets)
//    
//    
//    return 0;
//}