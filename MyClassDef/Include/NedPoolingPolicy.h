//
//  NedPoolingPolicy.h
//  XCodeCppTest
//
//  Created by TuLigen on 16/7/19.
//  Copyright © 2016年 TuLigen. All rights reserved.
//

#ifndef NedPoolingPolicy_hpp
#define NedPoolingPolicy_hpp
#include "interface.h"
namespace TLG
{
    /// ned pool
    class NedPoolingPolicy  : public AllocPolicy
    {
    public:
        /**
         *  分配内存
         *
         *  @param sz 大小
         *  @return  地址
         */
        virtual void* allocBytes( size_t sz);
        /**
         *  释放
         *
         *  @param ptr 内存地址
         */
        virtual void deallocBytes(void *ptr) ;
        /**
         *  获取一次分配的最大内存块
         *
         *  @return 大小
         */
        virtual size_t getMaxAllocationSize(void)const;
    };
}

#endif /* NedPoolingPolicy_hpp */
