//
//  main.cpp
//  ShpTest
//
//  Created by TuLigen on 2018/7/11.
//  Copyright © 2018年 TuLigen. All rights reserved.
//

#include <iostream>

#include <shapefil.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    SHPHandle shp = SHPOpen("", "rb");
    
    
    
    
    SHPClose(shp);
    return 0;
}
