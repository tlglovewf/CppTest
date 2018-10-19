//
//  main.cpp
//  ThreadTest
//
//  Created by TuLigen on 2018/7/9.
//  Copyright © 2018年 TuLigen. All rights reserved.
//

#include <iostream>
//#include <memory>
#include <thread>
#include <vector>
#include <queue>
#include <future>
#include <functional>
#include <stdexcept>

using namespace std;
class ThreadPool
{
public:
    ThreadPool(int size);
    ~ThreadPool();
    template<typename F,class ... Args>
    auto enqueue(F &&f, Args &&... args)->std::future<typename std::result_of<F(Args...)>::type>;
    
private:
    
    std::vector< std::thread > workers;
    std::queue< std::function<void()> > tasks;
    
    std::mutex queue_mutex;
    std::condition_variable condition;
    
    bool stop;
};

ThreadPool::ThreadPool(int size) : stop(false)
{
    for(size_t i = 0;i<size;++i)
        // 添加线程到工作线程组
        workers.emplace_back(   // 与push_back类型，但性能更好(与此类似的还有emplace/emlace_front)
                             [this]
                             {   // 线程内不断的从任务队列取任务执行
                                 for(;;)
                                 {
                                     std::function<void()> task;
                                     
                                     {
                                         // 拿锁(独占所有权式)
                                         std::unique_lock<std::mutex> lock(this->queue_mutex);
                                         // 等待条件成立
                                         this->condition.wait(lock,
                                                              [this]{ return this->stop || !this->tasks.empty(); });
                                         // 执行条件变量等待的时候，已经拿到了锁(即lock已经拿到锁，没有阻塞)
                                         // 这里将会unlock释放锁，其他线程可以继续拿锁，但此处任然阻塞，等待条件成立
                                         // 一旦收到其他线程notify_*唤醒，则再次lock，然后进行条件判断
                                         // 当[return this->stop || !this->tasks.empty()]的结果为false将阻塞
                                         // 条件为true时候解除阻塞。此时lock依然为锁住状态
                                         
                                         
                                         // 如果线程池停止或者任务队列为空，结束返回
                                         if(this->stop && this->tasks.empty()){
                                             return;
                                         }
                                         // 取得任务队首任务(注意此处的std::move)
                                         task = std::move(this->tasks.front());
                                         // 从队列移除
                                         this->tasks.pop();
                                     }
                                     // 执行任务
                                     task();
                                 }
                             }
                             );
}

template<class F, class ... Args>
auto ThreadPool::enqueue(F &&f, Args &&... args )->std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    // 将任务函数和其参数绑定，构建一个packaged_task
    auto task = std::make_shared< std::packaged_task<return_type()> >(
                                                                      std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                                                                      );
    // 获取任务的future
    std::future<return_type> res = task->get_future();
    {
        // 独占拿锁
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        // 不允许入队到已经停止的线程池
        if(stop){
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        // 将任务添加到任务队列
        tasks.emplace([task](){ (*task)(); });
    }
    // 发送通知，唤醒某一个工作线程取执行任务
    condition.notify_one();
    return res;
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }

    condition.notify_all();

    for(std::thread &work : workers)
    {
        work.join();
    }
}

#if 0
int main()
{
    ThreadPool pool(4);
    std::vector< std::future<int> >  results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
                             pool.enqueue([i] {
            std::cout << "hello " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "world " << i << std::endl;
            return i*i;
        })
                             );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    return 0;
}
#else

void F(int n1, int n2,int n3, int n4, int n5)
{
    cout << n1 << " " << n2 << " " << n3 << " " << n4 << " " << n5 << endl;
}


class A
{
public:
    A(){}
    ~A(){}
    void test(int x)
    {
        cout << this << " " << x << endl;
    }
public:
    int _x;
};

int main()
{
    int n = 7;
    auto f1 = std::bind(F, std::placeholders::_1, std::placeholders::_2 ,43, std::cref(n), n);

    f1(3,2,1);

    A a;
    cout << &a << endl;
    std::function<void(int)> f2 = std::bind( &A::test,&a, std::placeholders::_1);
    f2(3);
    return 0;
}



#endif


