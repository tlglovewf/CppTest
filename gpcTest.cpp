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
extern "C"{
#include "gpc/gpc.h"
}
using namespace std;

int main(void)
{
    gpc_polygon polgon;
    polgon.num_contours = 1;
    gpc_vertex_list vlist;
    vlist.num_vertices = 4;
    gpc_vertex v[4];
    v[0].x = 0.0;
    v[0].y = 0.0;
    v[1].x = 100.0;
    v[1].y = 0.0;
    v[2].x = 100.0;
    v[2].y = 100.0;
    v[3].x = 0.0;
    v[3].y = 100.0;
    vlist.vertex = v;
    polgon.contour = &vlist;
    polgon.hole = NULL;
    
    gpc_tristrip tri;
    gpc_polygon_to_tristrip(&polgon, &tri);
    
    for(int i = 0;i < tri.num_strips;++i)
    {
        gpc_vertex_list *list = tri.strip;
        if(NULL != list)
        {
            int vlen = list->num_vertices;
            gpc_vertex *pvtx = list->vertex;
            for(int j = 0; j < vlen; ++j)
            {
                cout << pvtx[j].x << " " << pvtx[j].y << endl;
            }
        }
    }

    return 0;
}