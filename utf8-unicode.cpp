//
//  cppTest.cpp
//
//
//  Created by TuLigen on 16/4/15.
//
//

#include <iostream>
#include <time.h>
#include <map>
#include <set>
#include <list>
#include <math.h>
#include <vector>
using namespace std;

typedef unsigned int uint32;
uint32 UTF8StrToUnicode( const char* UTF8String, uint32 UTF8StringLength, unsigned short* OutUnicodeString, uint32 UnicodeStringBufferSize )
{
    uint32 UTF8Index = 0;
    uint32 UniIndex = 0;
    
    while ( UTF8Index < UTF8StringLength )
    {
        unsigned char UTF8Char = UTF8String[UTF8Index];
        
        if ( UnicodeStringBufferSize != 0 && UniIndex >= UnicodeStringBufferSize )
            break;
        
        if ((UTF8Char & 0x80) == 0)
        {
            const uint32 cUTF8CharRequire = 1;
            
            // UTF8字码不足
            if ( UTF8Index + cUTF8CharRequire > UTF8StringLength )
                break;
            
            if ( OutUnicodeString )
            {
                unsigned short& WideChar = OutUnicodeString[UniIndex];
                
                WideChar = UTF8Char;
            }
            
            UTF8Index++;
            
        }
        else if((UTF8Char & 0xE0) == 0xC0)  ///< 110x-xxxx 10xx-xxxx
        {
            const uint32 cUTF8CharRequire = 2;
            
            // UTF8字码不足
            if ( UTF8Index + cUTF8CharRequire > UTF8StringLength )
                break;
            
            if ( OutUnicodeString )
            {
                unsigned short& WideChar = OutUnicodeString[UniIndex];
                WideChar  = (UTF8String[UTF8Index + 0] & 0x3F) << 6;
                WideChar |= (UTF8String[UTF8Index + 1] & 0x3F);
            }
            
            UTF8Index += cUTF8CharRequire;
        }
        else if((UTF8Char & 0xF0) == 0xE0)  ///< 1110-xxxx 10xx-xxxx 10xx-xxxx
        {
            const uint32 cUTF8CharRequire = 3;
            
            // UTF8字码不足
            if ( UTF8Index + cUTF8CharRequire > UTF8StringLength )
                break;
            
            if ( OutUnicodeString )
            {
                unsigned short& WideChar = OutUnicodeString[UniIndex];
                
                WideChar  = (UTF8String[UTF8Index + 0] & 0x1F) << 12;
                WideChar |= (UTF8String[UTF8Index + 1] & 0x3F) << 6;
                WideChar |= (UTF8String[UTF8Index + 2] & 0x3F);
            }
            
            
            UTF8Index += cUTF8CharRequire;
        }
        else if((UTF8Char & 0xF8) == 0xF0)  ///< 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx
        {
            const uint32 cUTF8CharRequire = 4;
            
            // UTF8字码不足
            if ( UTF8Index + cUTF8CharRequire > UTF8StringLength )
                break;
            
            if ( OutUnicodeString )
            {
                unsigned short& WideChar = OutUnicodeString[UniIndex];
                
                WideChar  = (UTF8String[UTF8Index + 0] & 0x0F) << 18;
                WideChar  = (UTF8String[UTF8Index + 1] & 0x3F) << 12;
                WideChar |= (UTF8String[UTF8Index + 2] & 0x3F) << 6;
                WideChar |= (UTF8String[UTF8Index + 3] & 0x3F);
            }
            
            UTF8Index += cUTF8CharRequire;
        }
        else ///< 1111-10xx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx
        {
            const uint32 cUTF8CharRequire = 5;
            
            // UTF8字码不足
            if ( UTF8Index + cUTF8CharRequire > UTF8StringLength )
                break;
            
            if ( OutUnicodeString )
            {
                unsigned short& WideChar = OutUnicodeString[UniIndex];
                
                WideChar  = (UTF8String[UTF8Index + 0] & 0x07) << 24;
                WideChar  = (UTF8String[UTF8Index + 1] & 0x3F) << 18;
                WideChar  = (UTF8String[UTF8Index + 2] & 0x3F) << 12;
                WideChar |= (UTF8String[UTF8Index + 3] & 0x3F) << 6;
                WideChar |= (UTF8String[UTF8Index + 4] & 0x3F);
            }
            
            UTF8Index += cUTF8CharRequire;
        }
        
        
        UniIndex++;
    }
    
    return UniIndex;
}


uint32 UniCharToUTF8(wchar_t UniChar, char *OutUTFString)
{
    
    uint32 UTF8CharLength = 0;
    
    if (UniChar < 0x80)
    {
        if ( OutUTFString )
            OutUTFString[UTF8CharLength++] = (char)UniChar;
        else
            UTF8CharLength++;
    }
    else if(UniChar < 0x800)
    {
        if ( OutUTFString )
        {
            OutUTFString[UTF8CharLength++] = 0xc0 | ( UniChar >> 6 );
            OutUTFString[UTF8CharLength++] = 0x80 | ( UniChar & 0x3f );
        }
        else
        {
            UTF8CharLength += 2;
        }
    }
    else if(UniChar < 0x10000 )
    {
        if ( OutUTFString )
        {
            OutUTFString[UTF8CharLength++] = 0xe0 | ( UniChar >> 12 );
            OutUTFString[UTF8CharLength++] = 0x80 | ( (UniChar >> 6) & 0x3f );
            OutUTFString[UTF8CharLength++] = 0x80 | ( UniChar & 0x3f );
        }
        else
        {
            UTF8CharLength += 3;
        }
    }
    else if( UniChar < 0x200000 )
    {
        if ( OutUTFString )
        {
            OutUTFString[UTF8CharLength++] = 0xf0 | ( (int)UniChar >> 18 );
            OutUTFString[UTF8CharLength++] = 0x80 | ( (UniChar >> 12) & 0x3f );
            OutUTFString[UTF8CharLength++] = 0x80 | ( (UniChar >> 6) & 0x3f );
            OutUTFString[UTF8CharLength++] = 0x80 | ( UniChar & 0x3f );
        }
        else
        {
            UTF8CharLength += 4;
        }
        
    }
    
    return UTF8CharLength;
}
