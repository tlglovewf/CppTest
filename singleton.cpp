////
////  singleton.cpp
////
////
////  Created by TuLigen on 16/3/16.
////
////
//
//#include "iostream"
//#include "assert.h"
//template <typename T>
//class Singleton {
//private:
//    Singleton(const Singleton<T> &);
//    
//    Singleton& operator=(const Singleton<T> &);
//    
//protected:
//    static T* msSingleton;
//public:
//    Singleton(void)
//    {
//    }
//    ~Singleton(void)
//    {  }
//    static T& getSingleton( void )
//    {  static T t;return t;  }
//
//};
//namespace oa {
//    
//    class Test : public Singleton<Test>
//    {
//    public:
//        void display(void)const
//        {
//            std::cout << "test" << std::endl;
//        }
//    };
//}
//template<> oa::Test* Singleton<oa::Test>::msSingleton = 0;
//int main(void)
//{
//    oa::Test::getSingleton().display();
//}
