//
//  main.cpp
//  XCodeCppTest
//
//  Created by TuLigen on 15/11/30.
//  Copyright (c) 2015年 TuLigen. All rights reserved.
//

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <rapidjson.h>
#include <prettywriter.h>
#include <filereadstream.h>
#include <stringbuffer.h>
#include <document.h>
#include <algorithm>



using namespace std;
using namespace rapidjson;


class TipsDisplay_StyleJsonParse
{
public:
    struct Item
    {
        string icon;
        int  col;
        int  row;
    };
    
    TipsDisplay_StyleJsonParse():mLen(0){}
    inline bool load( const char *str)
    {
        bool bol = !mDoc.Parse(str).HasParseError();
        if( bol )
        {
            mLen = int(mDoc.End() - mDoc.Begin());
        }
        return bol;
    }
    inline int  getCount(void){return mLen;}
    inline void getItem(int index, Item &item)
    {
        if( index < mLen )
        {
            Document::ValueIterator it = mDoc.Begin() + index;
            Document::MemberIterator iit = it->MemberBegin();
            item.icon = iit++->value.GetString();
            item.col  = iit++->value.GetInt();
            item.row  = iit++->value.GetInt();
        }
    }
private:
    Document mDoc;
    int      mLen;
};

typedef unsigned short WCHAR;
static bool cmp(const WCHAR *lhs, const WCHAR *rhs )
{
    const WCHAR *tlhs = lhs;
    const WCHAR *rrhs = rhs;
    while( (0 != *lhs) && (0 != *rhs) && *lhs == *rhs )
    {
        ++lhs;
        ++rhs;
    }
    if( (0 == *lhs) && (0 == *rhs) )
    {
        return false;
    }
    else
    {
        return *tlhs < *rrhs;
    }
}

