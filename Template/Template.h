//
//  Template.hpp
//  XCodeCppTest
//
//  Created by TuLigen on 16/8/23.
//  Copyright © 2016年 TuLigen. All rights reserved.
//

#ifndef Template_hpp
#define Template_hpp


class Node
{
public:
    virtual void show(void)const = 0;
};


template <typename T>
class BaseNode : public Node
{
protected:
    void display(void)const;
public:
    virtual void show(void)const = 0;
};


#endif /* Template_hpp */
