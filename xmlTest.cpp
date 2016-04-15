////
////  xmlTest.cpp
////  
////
////  Created by TuLigen on 16/3/2.
////
////
//
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <assert.h>
#include "tinyxml.h"
#include "tinystr.h"


class FMConfig
{
public:
    
    bool load(const char *fileName);
    
    const char* getItem(const char *key);
    
    void setItem(const char *key, const char *value, const char *discribe = NULL);
    
    void save(const char *fileName = NULL);
    
private:
    std::string m_cfgpath;
    TiXmlDocument m_doc;
};

bool FMConfig::load(const char *fileName)
{
    if( NULL != fileName )
    {
        return m_doc.LoadFile(fileName);
    }
    else
    {
        return false;
    }
}
const char* FMConfig::getItem(const char *key)
{
    if( NULL != key )
    {
        TiXmlNode *node =  m_doc.FirstChild(key);
        TiXmlElement *child = NULL;
        if( NULL != node && (NULL != (child = node->ToElement())))
        {
            return child->GetText();
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

void FMConfig::setItem(const char *key, const char *value, const char *discribe /*=NULL*/)
{
    if( (NULL != key) && (NULL != value) )
    {
        TiXmlElement *node = (TiXmlElement*)m_doc.FirstChild(key);
        TiXmlNode *text = NULL;
        if(NULL != discribe )
        {
            m_doc.InsertEndChild(TiXmlComment(discribe));
        }
        
        if( NULL != node && ( NULL != (text = node->FirstChild())))
        {
            text->SetValue(value);
        }
        else
        {
            m_doc.InsertEndChild(TiXmlElement(key))->InsertEndChild(TiXmlText(value));
        }
    }
}

void FMConfig::save( const char *fileName /*= NULL*/)
{
    //check if the file exist.
    if(NULL == fileName)
    {
        m_doc.SaveFile();
    }
    else
    {
        m_doc.SaveFile(fileName);
    }
}

int foo(int i )
{
    if(0 == i )
    {
        return 0;
    }
    return 2 * foo(i/2) + 1;
}

//int main(void)
//{
//    FMConfig config;
//    if(config.load("/Users/TLG/Desktop/config/fastmap.cfg"))
//    {
//        config.setItem("LanguageCode", "31","语言");
//        config.save();
//    }
//    return 0;
//}