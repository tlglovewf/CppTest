//
//  allocTest.cpp
//  
//
//  Created by TuLigen on 16/3/31.
//
//

#include <stdio.h>
#include <string>
#include <map>
#include <assert.h>
#define GLOBAEVARNAME(t)  g##t
#define DECLARE(TYPE,VAR) \
    void Set##VAR(TYPE var){GLOBAEVARNAME(VAR) = var;}\
    TYPE Get##VAR(){return GLOBAEVARNAME(VAR);}
int gx;
DECLARE(int, x)

#define DECALE(T)  

class IParameter
{
public:
    IParameter(){}
    virtual ~IParameter(){}
    /**
     *  值
     */
    virtual const void* value(void)const = 0;
    /**
     *  键
     *
     *  @return 值
     */
    virtual const char* key(void)const = 0;
    /**
     *  设置值
     *
     *  @param value 值
     */
    virtual void set(const void *value) = 0;
    
    /**
     *  拷贝
     *
     *  @return 参数
     */
    virtual IParameter* copy(void) = 0;
};

template<typename T>
class GpuParameter : public IParameter
{
public:
    GpuParameter(const char *key):mKey(key)
    {
        
    }
    const void* value(void)const
    {
        return &mValue;
    }
    const char* key(void)const
    {
        return mKey.c_str();
    }
    void set(const void *value)
    {
        if(NULL != value)
        {
            mValue = *static_cast<const T*>(value);
        }
    }
    IParameter* copy(void)
    {
        IParameter *item = new GpuParameter(*this);
        return item;
    }
private:
    std::string mKey;
    T           mValue;
};
class IParameters
{
public:
    IParameters(){}
    virtual ~IParameters(){}
    
    virtual void setParameter( IParameter &param) = 0;
    
    virtual IParameter* operator[](const char *key) = 0;
};

class GpuParameters : public IParameters
{
public:
    GpuParameters():mParams(GpuParameters::cmpKey)
    {
    }
    ~GpuParameters()
    {
        ParamDicIter it = mParams.begin();
        ParamDicIter ed = mParams.end();
        for(;it != ed;++it)
        {
            assert(NULL != it->second);
            delete it->second;
        }
    }
    
    void setParameter( IParameter &param)
    {
        ParamDicIter it = mParams.find(param.key());
        
        if( mParams.end() == it )
        {
            mParams.insert(std::make_pair(param.key(), param.copy()));
        }
        else
        {
            it->second->set(param.value());
        }
    }
    
    IParameter* operator[](const char *key)
    {
        return mParams[key];
    }
    
    const void* Get(const char *key)
    {
        if( NULL == key)
            return NULL;
        ParamDicIter it = mParams.find(key);
        if( it == mParams.end())
        {
            return NULL;
        }
        else
        {
            assert(NULL != it->second);
            return it->second->value();
        }
    }
    template<typename T>
    void Set(const char *key, void *value)
    {
        if(NULL == key || NULL == value)
            return;
        ParamDicIter it = mParams.find(key);
        if(it == mParams.end())
        {
            IParameter *param = new GpuParameter<T>(key);
            param->set(value);
            mParams.insert(std::make_pair(param->key(), param));
        }
        else
        {
            IParameter *param = it->second;
            assert(NULL != param);
            param->set(value);
        }
    }
    
    static bool cmpKey(const char *lft, const char *rgt)
    {
        if(NULL == lft || NULL == rgt )
            return false;
        int isequal = strcmp(lft, rgt);
        if(0 == isequal)
            return false;
        else
            return 0 < isequal;
    }
private:
    typedef std::map<const char *,IParameter*, bool (*)(const char *,const char *)>    ParamDic;
    typedef ParamDic::iterator ParamDicIter;
    ParamDic mParams;
    
    //禁用拷贝赋值
    GpuParameters(const GpuParameters&);
    GpuParameters& operator=(const GpuParameters&);
};


//int main(void)
//{
//    GpuParameters parameters;
//    int x = 10;
//    parameters.Set<int>("test", &x);
//    x = 11;
//    parameters.Set<int>("test", &x);
//    IParameter *param = new GpuParameter<int>("world");
//    int dd = 100;
//    param->set(&dd);
//    parameters.setParameter(*param);
//    dd = 101;
//    parameters["world"]->set(&dd);
//    delete param;
//    printf("%d", *(int*)parameters.Get("world"));
//    return 0;
//}