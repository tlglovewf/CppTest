//
//  gpcTest.cpp
//  
//
//  Created by TuLigen on 16/2/23.
//
//

#include <stdio.h>
#include "iostream"
#include <set>
#include <list>
#include <map>
#include <string>
using namespace std;
#define SIZELEN 1e5
bool judge(double r1, double r2)
{
    int t1 = r1 * SIZELEN;
    int t2 = r2 * SIZELEN;
    return t1 == t2;
}
class Test
{
public:
    void display(void)
    {
        ++x;
    }
    void display(void)const
    {
    }
private:
    int x;
};

#define TEST(t) #t

//int main(void)
//{
//    string str = "a\\b\\c\\d";
//    string::size_type len = str.find_last_of('\\');
//    printf("%d\n",len);
//    char *pos = strrchr(str.c_str(), '\\');
//    len = pos - str.c_str();
//    return 0;
//}