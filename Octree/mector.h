
//
//  mector.cpp
//  Octree
//
//  Created by TuLigen on 2018/7/31.
//  Copyright © 2018年 TuLigen. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
#define EARTH_RADIUS  6378137
#define PI 3.1415926535897932384626433832795028841971693993751
struct  Value
{
    double x;
    double y;
    
    Value operator-(const Value &val)
    {
        return { this->x - val.x, this->y - val.y};
    }
};

struct  ValueF
{
    float x;
    float y;
};

ValueF returnF(const Value &val)
{
    return {(float)val.x, (float)val.y};
}

Value mecator( double lon , double lat)
{
    lon = lon * PI / 180.0;
    lat = lat * PI / 180.0;
    Value val;
    val.x = lon * EARTH_RADIUS;
    val.y = log(tan( lat * 0.5 + 0.25 * PI )) * EARTH_RADIUS;
    return val;
}

void getmecator(const Value &v, double &lon, double &lat)
{
    lon = v.x / EARTH_RADIUS * 180.0 / PI;
    lat = (2 * ( atan( exp(v.y / EARTH_RADIUS))) - PI * 0.5) * 180.0 / PI;
}

void display(const Value val)
{
    cout <<setiosflags(ios::fixed);
    cout << setprecision(10) << val.x << " " << val.y << endl;
    
    ValueF f = returnF(val);
    
    cout << setprecision(10) << f.x << " " << f.y << endl;
}

double tileX2Lon(int tileX, int zoom)
{
    return tileX / pow(2.0, zoom) * 360.0 - 180.0;
}


double  Deg2Rad( double deg )
{
    return deg * PI / 180.0;
}

double Rad2Deg( double rad )
{
    return rad * 180.0 / PI;
}

/*对特定瓦片序号返回纬度
 tileY：横向的瓦片序号，即y
 zoom：瓦片的zoom级别
 n = 2 ^ zoom
 lat_rad = arctan(sinh(π * (1 - 2 * tileY / n)))
 lat_deg = lat_rad * 180.0 / π
 注意：纬度范围为+- 85.0511度
 */
double tileY2Lat(int tileY, int zoom)
{
    double n = M_PI - 2.0 * M_PI * tileY / pow(2.0, zoom);
    
    return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
    
    //        return 90.0 - tileY / pow(2.0, zoom) * 180.0;
}
