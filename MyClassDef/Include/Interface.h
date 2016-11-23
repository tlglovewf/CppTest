//
//  Interface.h
//
//  Created by TuLigen on 16/7/19.
//  Copyright © 2016年 TuLigen. All rights reserved.
//

#ifndef Interface_hpp
#define Interface_hpp
namespace TLG
{
    /// 分配策略基类
    class AllocPolicy
    {
    public:
        AllocPolicy(){}
        virtual ~AllocPolicy(){}
        /**
         *  分配内存
         *
         *  @param sz 大小
         *  @return  地址
         */
        virtual void* allocBytes( size_t sz) = 0;
        /**
         *  释放
         *
         *  @param ptr 内存地址
         */
        virtual void deallocBytes(void *ptr) = 0;
        /**
         *  获取一次分配的最大内存块
         *
         *  @return 大小
         */
        virtual size_t getMaxAllocationSize(void)const = 0;
    };
}

#endif /* Interface_h */
