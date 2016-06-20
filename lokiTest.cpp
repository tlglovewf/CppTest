//
//  lokiTest.cpp
//  
//
//  Created by TuLigen on 16/6/14.
//
//
#include "loki/SmallObj.h"
#include "loki/SmartPtr.h"
#include "loki/Factory.h"
#include "loki/singleton.h"
#include "loki/AbstractFactory.h"
#include "loki/visitor.h"
#include <ctime>
#include "iostream"
using namespace std;
class TestOne
{
public:
    TestOne(){}
    ~TestOne(){cout << "destroy testone." << endl;}
    virtual void display(void)const
    {
        cout << "test one." << endl;
    }
};
class TestTwo : public TestOne
{
public:
    TestTwo(){}
    ~TestTwo(){cout << "destroy testtwo." << endl;}
    void display(void)const
    {
        cout << "test two." << endl;
    }
};

class TestOnePtr : public Loki::SmartPtr<TestOne>
{
public:
};

/**
 *  单例
 *  注:使用SingletonHolder的对象必须要有默认构造函数
 */
typedef Loki::SingletonHolder<TestOne> TestSingleton;

class Widget
{
public:
    Widget(int _a):a(_a){}
    virtual void event(void)const
    {
        cout << "base." << endl;
    }
protected:
    int a;
};

class Button : public Widget
{
public:
    Button(int _a):Widget( 10 + _a){}
    void event(void)const
    {
        cout << "button." << a <<  endl;
    }
};

class Edit : public Widget
{
public:
    Edit(int _a):Widget( 20 + _a){}
    void event(void)const
    {
        cout << "edit." << a << endl;
    }
};

template <typename T>
struct Create_T {
    T* operator()(int a)const
    {
        return new T(a);
    }
};
/**
 *  带形参的构造函数的工厂
 */
typedef Loki::Factory<Widget,std::string,Loki::Seq<int> > WidgetFactorys;

/**
 *  抽象类定义
 */
struct IButton
{
    IButton(){}
    virtual ~IButton(){}
    virtual void click(void)const = 0;
};

struct IEdit
{
    IEdit(){}
    virtual ~IEdit(){}
    virtual void edit(void)const = 0;
};

struct IListBox
{
    IListBox(){}
    virtual ~IListBox(){}
    virtual void scroll(void)const = 0;
};

/**
 *  抽象工厂
 *
 *  @param IButton
 *  @param IEdit
 *  @param IListBox
 *
 */
typedef Loki::AbstractFactory<LOKI_TYPELIST_3(IButton, IEdit, IListBox)> IWidgetFactory;

struct CWinBtn : public IButton
{
    void click(void)const{cout << "win btn." << endl;}
};

struct CWinEdit : public IEdit
{
    void edit(void)const { cout << "win edit." << endl;}
};

struct CWinListBox : public IListBox
{
    void scroll(void)const { cout << "win listbox." << endl;}
};

struct CMacBtn : public IButton
{
    void click(void)const{ cout << "mac btn." << endl;}
};

struct CMacEdit : public IEdit
{
    void edit(void)const { cout << "mac edit." << endl;;}
};

struct CMacListBox : public IListBox
{
    void scroll(void)const { cout << "mac listbox." << endl;}
};

//实例化抽象工厂
typedef Loki::ConcreteFactory<IWidgetFactory,Loki::OpNewFactoryUnit,LOKI_TYPELIST_3(CWinBtn, CWinEdit, CWinListBox)> CWinFactory;
    
typedef Loki::ConcreteFactory<IWidgetFactory,Loki::OpNewFactoryUnit,LOKI_TYPELIST_3(CMacBtn, CMacEdit, CMacListBox)> CMacFactory;
    
/**
 *  使用抽象工厂
 *
 */
void UsingWidget(IWidgetFactory *factory)
{
    IButton  *btn = factory->Create<IButton>();
    IEdit    *edt = factory->Create<IEdit>();
    IListBox *box = factory->Create<IListBox>();
    
    btn->click();
    edt->edit();
    box->scroll();
    
    delete btn;
    delete edt;
    delete box;
}

/**
 *  visitor
 *
 */


struct TTextNode : Loki::BaseVisitable<>{
    LOKI_DEFINE_VISITABLE()
    TTextNode(std::string text):m_text(text){}
    std::string m_text;
};

struct TCDataNode : Loki::BaseVisitable<>{
    LOKI_DEFINE_VISITABLE()
    TCDataNode(std::string text):m_cdata(text){}
    std::string m_cdata;
};

struct TElementNode : Loki::BaseVisitable<> {
    LOKI_DEFINE_VISITABLE()
    TElementNode(std::string text):m_name(text){}
    std::string m_name;
    typedef Loki::BaseVisitable<> visitable_t;
    typedef Loki::SmartPtr< visitable_t >  ptr_t;
    std::vector< ptr_t > m_childs;
};

class CPrintVisitor : public Loki::BaseVisitor,public Loki::Visitor<TElementNode>
{
public:
    void Visit(TTextNode &n){ cout << n.m_text << endl;}
    void Visit(TCDataNode &n){ cout << n.m_cdata << endl;}
    void Visit(TElementNode &n)
    {
        cout << '<' << n.m_name.c_str() << '>' << endl;
        for( size_t idx = 0, len = n.m_childs.size(); idx < len; idx++)
        {
            n.m_childs[idx]->Accept(*this);
        }
    }
};



//void* operator new ( std::size_t size)
//{
//    return  MyAlloc::Instance().Allocate(size, false);
//}
//
//void operator delete(void *p, std::size_t size)
//{
//    MyAlloc::Instance().Deallocate(p,size);
//}


class AllocOne : public Loki::SmallObject<>
{
public:
private:
    int num;
};



//int main(void)
//{
//    time_t t = time(NULL);
//    for(int i = 0 ; i < 1e8;++i)
//    {
////        int *c = new int;
////        delete c;
//        AllocOne *one = new AllocOne;
//        delete one;
//    }
//    cout << (time(NULL) - t)  << endl;
//    /**
//     *  SmartPoint
//     *
//     */
//    Loki::SmartPtr<TestOne>  a = new TestTwo;
//    a->display();
//    a = new TestOne;
//    a->display();
//
//    /**
//     *  单例
//     */
//    
//    TestSingleton::Instance().display();
//    
//    /**
//     *  简单工厂
//     */
//    WidgetFactorys wf;
//    wf.Register("Button", Create_T<Button>());
//    wf.Register("Edit", Create_T<Edit>());
//    Widget *widget = wf.CreateObject("Button",5);
//    widget->event();
//    delete widget;
//    
//    /**
//     *  抽象工厂
//     */
//    CWinFactory winfac;
//    UsingWidget(&winfac);
//    CMacFactory macfac;
//    UsingWidget(&macfac);
//    
//    /**
//     *  访问者模式
//     */
//    TElementNode root("root");
//    TElementNode *child1 = new TElementNode("child1");
//    child1->m_childs.push_back(new TTextNode("hello"));
//    TElementNode *child2 = new TElementNode("child2");
//    child2->m_childs.push_back(new TCDataNode("world"));
//    root.m_childs.push_back(child1);
//    root.m_childs.push_back(child2);
//    CPrintVisitor vis;
//    root.Accept(vis);
//    
//    
//    return 0;
//}