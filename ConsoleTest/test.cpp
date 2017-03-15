//
//  test.cpp
//  XCodeCppTest
//
//  Created by TuLigen on 16/8/4.
//  Copyright © 2016年 TuLigen. All rights reserved.
//
#include <iostream>
#include <vector>
//#include <experimental/optional>
//#include "Template.h"
#include <algorithm>
#include <sstream>
//#include <list>
#include "stdio.h"
#include <map>
#include <math.h>
#include <cassert>
#include <array>
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
template<typename T>
void output(const T &t)
{
    cout << t << endl;
}
template<typename T ,typename... Args>
void output(const T &a, Args... arg)
{
    cout << a << endl;
    output(arg...);
}
template<typename... T>
std::tuple<T...> getDD(T... aa)
{
    return std::make_tuple(aa...);
}


template<typename TT,std::size_t N>
struct TuplePrinter{
static void print(const TT &value)
{
    TuplePrinter<TT, N - 1>::print(value);
    cout << "," << std::get<N-1>(value);
}
};
template<typename T>
struct TuplePrinter<T,1>{
static void print(const T &t)
{
    cout << std::get<0>(t) ;
}
};
template<typename ... Args>
void PrintTuple(const std::tuple<Args...> &t)
{
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
}
class One
{
    
};
class Two : public One
{
protected:
    int a = 10;
};

template<typename T, typename L>
auto func(T x, L y)->decltype(x + y){return x + y ;}


void  ppt(int num)
{
    cout << "int print(int):" <<endl;
}
template<typename _Ty>
void ppt(_Ty tt, typename _Ty::vlaue_type *pvt_dummy = NULL)
{
    typename _Ty::value_type vt_someval;
    cout << "template" << endl;
}
//template<> void ppt<short>(short st)
//{
//    cout << "short" << endl;
//}

using Clock = std::chrono::steady_clock;

template<typename ...Types>
class Varient
{
public:
    Varient()
    {
        cout << sizeof...(Types) << endl;
    }
private:
};

//int main(void)
//{
//    auto vv = getDD(10,11);
//    cout << "num = " << std::tuple_size<decltype(vv)>::value << endl;
//    output(std::get<0>(vv), std::get<1>(vv));
//    auto cc = std::tie("test","world");//
//    cout << std::get<0>(cc) << endl;
//    
//    auto oo = std::tuple_cat(vv, cc);
//    PrintTuple(oo);
//    cout << endl;
//    
//    
//    cout <<  std::is_same<int, char>::value << endl;
//    cout << std::is_convertible<Two, One>::value << endl;
//    cout << std::is_convertible<Two, One>::value << endl;
//    short num = 10;
//    ppt(num);
//    struct test
//    {
//        char a;
//        char b;
//        test():a('a'),b('b'){}
//    };
//    
//    
//    std::map<int,int> ms;
//    ms.insert(std::make_pair(0, 1));
//    ms.insert(std::make_pair(1, 2));
//    auto a = ms.emplace(2,3);
    
//    cout << alignof(test) << endl;
//    cout <<  func(10,20.3) << endl;
//    std::aligned_storage<sizeof(test),alignof(test)>::type cc;
//    new (&cc) test;
    
    //Clock::time_point;
    //int x = 0010;
    //std::to_string(10);
    //cout << x << endl;
    
    //Varient<int, char, short>();
    
    
    
//    return 0;
//}


#include <stdio.h>
#include <time.h>

class ValueTest
{
public:
    ValueTest(){}
    ValueTest(ValueTest &&t)
    {
        cout << "call move construct." << endl;
    }
};

template<typename T>
void change(T &&t)
{
    
}
template <typename ...Type>
class TestTemplate {
    
public:
    TestTemplate()=default;
    void display(void)const
    {
        cout << sizeof...(Type) << endl;
    }
public:
    
};
template<typename T>
void outerr(T &t)
{
    cout <<  t << endl;
}
template<typename T, typename C>
void puter(T t, C c)
{
    using R = typename std::result_of<T(C)>::type;
    cout << typeid(R).name() << endl;
    
}

int CallbackInt(int a)
{
    return 0 ;
}

char CallbackChar(char ch)
{
    return ch;
}

template<typename T>
void checkType(T t)
{
    
}

template<typename T1, typename T2>
auto sum(T1 t1, T2 t2)->decltype(t1 + t2)
{
    return t1 + t2;
}


struct Person
{
    std::string name;
    int         code;
    int         value;
};

template<typename Ty>
class Range
{
public:
    typedef typename Ty::value_type value_type;
    Range(const Ty &t):_t(t)
    {
        
    }
    
    
    template<typename Fn>
    std::multimap<typename std::result_of<Fn(value_type)>::type, value_type>  groupBy(Fn fn)
    {
        typedef decltype(std::declval<Fn>()(std::declval<value_type>())) key_type;
        std::multimap<key_type, value_type>   maps;
        std::for_each(begin(_t), end(_t), [&maps,&fn](const value_type &item)
                      {
                          maps.insert(std::make_pair(fn(item), item));
                      });
        return maps;
    }
    
private:
    Ty _t;
};

template<typename Type, typename ...Args>
void PrintMap(Type t ,Args ...args)
{
    PrintMap(t);
    PrintMap(args...);
}
template<typename T>
void PrintMap(T t)
{
    for( auto it = begin(t); it != end(t); ++it)
    {
        cout << it->first << " " << it->second.name << " " << it->second.code <<  " " << it->second.value << endl;
    }
}


class TypeLess
{
public:
    TypeLess(){}
    TypeLess(int x)
    {
        cout << "create typeless." << endl;
    }
    
    char getChar()const
    {
        return 'c';
    }
};


template<typename T>
void printT(T t)
{
    cout << t << " ";
}
template<typename T, typename ...Args>
void printT(T t, Args ...args)
{
    printT(t);
    printT(args...);
}
template<typename ...Args>
void clacSize(Args ...args)
{
    cout << "size:" << sizeof...(args) << endl;
}

int main(int argc, const char * argv[])
{
/*std::vector<Person>  pers = {{"aa",10,23},{"bb",13,24},{"aa",10,25},{"bb",13,25}};
        
    Range< std::vector<Person> >  ranges(pers);
    auto a1 = ranges.groupBy([](const Person &person)
    {
        return person.code;
    });
    auto a2 = ranges.groupBy([](const Person &person)
    {f
        return person.name;
    });
    PrintMap(a1,a2);
  */
    std::array<int, 5> a2 = {1,2,3,4,5};
    return 0;
}
