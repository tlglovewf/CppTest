//
//  main.cpp
//  
//
//  Created by TuLigen on 16/4/26.
//
//

#include <iostream>
using namespace std;

class Test
{
public:
    void display(int a)
    {
        cout << a << endl;
    }
    int test(int a, int b)
    {
        cout << a + b << endl;
        return a + b;
    }
    int tt()
    {
        return 100;
    }
    char* cc()
    {
        return "hello world.";
    }
private:
    
};
typedef void ( Test::*common)(...);

template<typename T,typename V>
void getValue( common com, V v, T &t)
{
    t = (v.*(T (V::*)(...))com)();
}
template<typename T,typename V>
T Value(common com, V v)
{
    return (v.*(T (V::*)(...))com)();
}

//int main(void)
//{
//    Test t;
//    common func = (common)&Test::display;
//    (t.*func)(5);
//    func = (common)&Test::test;
//    (t.*func)(10,20);
//    
//    func = (common)&Test::tt;
//    int x;
//    getValue(func, t, x);
//    cout << x << endl;
//    return 0;
//}