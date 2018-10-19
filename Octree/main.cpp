//
//  main.cpp
//  Octree
//
//  Created by TuLigen on 2018/7/17.
//  Copyright © 2018年 TuLigen. All rights reserved.
//

#include "mector.h"
#include "iostream"
using namespace std;

unsigned int col1 = 0xAF222222;
unsigned int col2 = 0x5F222222;

class A
{
public:
    
};

class B : public A
{
    
};

class C : public A
{
    
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
//    cout << strlen("\n")  << endl;
    
    
//    double   a = 1230.1234567891234567;
//    double  a = 123456789;
//    float    b = 2 ^ 5;
    
//    cout << b << " " << a << endl;
//    printf("%f",b);
//    cout <<  (int)('\n') << endl;
    
//    unsigned int uu = 0xf0;
//
//    unsigned int xx = (uu ^ 0xff);
//
//    printf("%x -- %x \n",uu, xx);
    

//    Value val1 = mecator(113.8920379, 22.9503711);
//    Value val2 = mecator(113.8920379, 22.9503710);
//
//    Value center = mecator(113.89203798,22.950371);
//
//
//
//    display(val1 - center);
//    display(val2 - center);
    
    
//    Value m = mecator(180, 85.05112877980659);
//
//
//    double d = pow(2,22);
//
//    cout << m.x / d << endl;
//
//    cout << "lon :" << tileX2Lon(437318, 19) << "lat : " << tileY2Lat(213771, 19) << endl;
//
//    display(m);
    
//
//    char *t = "ff,xx";
//
//    char *p = strchr(t, ',');
//
//    cout << p << endl;
    
    double lon =  113.1975221;
    double lat =   30.7503750;
    Value v = mecator(lon, lat);
    cout.precision(15);
    cout << v.x <<  " " << v.y << endl;
//
    Value d;

    d.x = 12601090.524325095;
    
    d.y = 3600372.853397599;
    
//    cout << lon << " " << lat << endl;
//    double lonrad = Deg2Rad(lon);
//    double latrad = Deg2Rad(lat);
//
//    lon = Rad2Deg(lonrad);
//    lat = Rad2Deg(latrad);
//
//    cout << lon << " " << lat << endl;
    
  //12601090.524325095, Y = 3600372.853397599
    
    //113.1982813 30.7503749
   
    lon = lat = 0.0;
    getmecator( d, lon, lat);
 cout << lon << " " << lat << endl;
    v = mecator(lon, lat);
      getmecator( v, lon, lat);
    cout << lon << " " << lat << endl;
  
    getchar();
    
    return 0;
}
