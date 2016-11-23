//
//  NedPoolingPolicy.cpp
//  XCodeCppTest
//
//  Created by TuLigen on 16/7/19.
//  Copyright © 2016年 TuLigen. All rights reserved.
//

#include "NedPoolingPolicy.h"
namespace TLG
{
    /**
     *  分配内存
     *
     *  @param sz 大小
     *  @return  地址
     */
    void* NedPoolingImpl::allocBytes( size_t sz)
    {
        return NULL;
    }
    /**
     *  释放
     *
     *  @param ptr 内存地址
     */
    void NedPoolingImpl::deallocBytes(void *ptr)
    {
        
    }
    /**
     *  获取一次分配的最大内存块
     *
     *  @return 大小
     */
    size_t NedPoolingImpl::getMaxAllocationSize(void)
    {
        return std::numeric_limits<size_t>::max();
    }
}
