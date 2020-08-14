/*************************************************************************
	> File Name: 2.thread_pool.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年08月13日 星期四 16时07分54秒
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;



//封装的Task类
class Task {
public:
    template<typename T, typename ...ARGS>
    Task(T func, ARGS... args) {
        this->func = std::bind(func, forward<ARGS>(args)...);
    }
    void operator()() {
        this->func();
        return ;
    }

private:
    function<void()> func;
};




//线程池类
class ThreadPool {
public:
    ThreadPool(int n = 5) 
    : is_running(false), max_threads_num(n), m_mutex(), m_cond() {    
    }
    void start() {
        if (is_running) return ;
        std:unique_lock<std::mutex> lock(m_mutex);
        is_running = true;
        for (int i = 0; i < this->max_threads_num; i++) {
            threads.push_back(new thread(&ThreadPool::worker, this));//以成员方法作为线程入口
        }
        return ;
    }
    void stop() {
        if (is_running == false) return ;
        std:unique_lock<std::mutex> lock(m_mutex);
        is_running = false;
        m_cond.notify_all();//通知所有线程你们可以结束了
        for (int i = 0; i < this->max_threads_num; i++) {
            threads[i]->join();
            delete threads[i];
        } 
        threads.clear();
        return ;
    }
    
    template<typename Func_T, typename ...ARGS>
    void add_one_task(Func_T f, ARGS... args) {
        __add_one_task(new Task(f, std::forward<ARGS>(args)...));
    }

private:
    void worker();
    Task *get_one_task();
    void __add_one_task(Task *t); 

    bool is_running;
    int max_threads_num;
    vector<thread *> threads;//线程队列
    queue<Task *>  Tasks;//任务队列
    mutex m_mutex;
    condition_variable m_cond;
};


//线程入口
void ThreadPool::worker() {
    while (is_running) {
        Task *t = get_one_task();//取任务,任务队列为空会一直阻塞
        if (t != nullptr) {
            cout << "thread_worker tid : " << std::this_thread::get_id() << std::endl;
            t->operator()();//运行任务
        }
    }
}

Task *ThreadPool::get_one_task() {
    //m_cond.notify;//通知所有等待的线程 条件成熟了
    std::unique_lock<std::mutex> lock(m_mutex);//获得和条件变量绑定的互斥锁
    while (Tasks.empty() && is_running) {
        m_cond.wait(lock);//阻塞，等待条件成熟
    }

    Task *t = nullptr;
    if (!Tasks.empty() && is_running) {
        t = Tasks.front();
        Tasks.pop();
    }
    return t;
}

void ThreadPool::__add_one_task(Task *t) {
    std:unique_lock<std::mutex> lock(m_mutex);
    Tasks.push(t);
    //添加完任务之后要通知
    m_cond.notify_one();

    return ;
}




void thread_func1(int a, int b) {
    cout << a << " + " << b << " = " << a + b << endl;
    return ;
}

void func(int x, int &n) {
    n += 2;
    cout << "func : " << x << " " << n  << endl;
    return;
}

int main() {
    int n = 123;
    cout << "------------------------" << endl;
    ThreadPool tp(2);
    tp.start();
    for (int i = 0; i < 10; i++) {
        tp.add_one_task(func, i, ref(n));
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout << "add task done" << endl;
    tp.stop();
    return 0;
}
