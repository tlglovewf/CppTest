//
//  2dPolylineTest.cpp
//  
//
//  Created by TuLigen on 16/5/4.
//
//

#include "iostream"
#include <vector>
#include <set>
#include <list>
#include <sstream>
#include <algorithm>
#include <iomanip>
extern "C"{
#include "polygontri/interface.h"
}
using namespace std;

struct Test {
    int x;
};

class find_int
{
public:
    find_int(int value):_value(value){}
    bool operator()(const Test &te)
    {
        return te.x == _value;
    }
private:
    int _value;
};


class find_range
{
public:
    find_range(int value,int deep = 5):_value(value),_deep(deep){}
    
    bool operator()(int x)
    {
        int tmp = 0;
        while(1)
        {
            if(_value == x++ )
                return true;
            if(++tmp > _deep)
            {
                return false;
            }
        }
    }
private:
    int _value;
    int _deep;
};

class OOne
{
public:
    OOne()
    {
        
    }
    ~OOne()
    {
        cout << "tt" << endl;
    }
};

class Do
{
public:
    void display(void)
    {
        OOne one;
        return ;
    }
};

//class Vec2d
//{
//public:
//    Vec2d(double x, double y):X(x),Y(y){}
//    double X;
//    double Y;
//};
//class Idx
//{
//public:
//    int fst;
//    int sec;
//    int tre;
//};
//int main(void)
//{
// 
//    return 0;
//}