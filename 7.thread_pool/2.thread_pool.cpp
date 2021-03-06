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
#include <mutex>
#include <condition_variable>
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

void thread_func1(int a, int b) {
    cout << a << " + " << b << " = " << a + b << endl;
    return ;
}



//线程池类
class ThreadPool {
public:
    ThreadPool(int n = 5) 
    : is_running(false), max_threads_num(n) {    
    }
    void start() {
        if (is_running) return ;
        is_running = true;
        for (int i = 0; i < this->max_threads_num; i++) {
            threads.push_back(new thread(&ThreadPool::worker, this));//以成员方法作为线程入口
        }
        return ;
    }
    void worker() {
        while (is_running) {
            //取任务
            //执行任务
            //释放任务
            Task *t = this->getOneTask();
            if (t == nullptr) break;
            (*t)();
            delete t;
            return ;
        }
    }
    void stop() {
        if (is_running == false) return ;
        do {
            unique_lock<mutex> lock(m_mutex);
            is_running = false;
            m_cond.notify_all();//通知所有线程你们可以歇菜了
        } while(0);
        for (int i = 0; i < this->max_threads_num; i++) {
            threads[i]->join();
            delete threads[i];
        } 
        threads.clear();
        /*
        //如果有队列往里面加任务
        do {
            unique_lock<mutex> lock(m_mutex);
            while (!Tasks.empty()) Tasks.pop();
        } while (0);*/
        return ;
    }

    template<typename T, typename ...ARGS>
    void addOneTask(T func, ARGS... args) {
        //通过定义一个局部变量来完成加锁
        unique_lock<mutex> lock(m_mutex);//只要lock对象完成构造，就算抢占成功互斥锁，最后会自动释放
        this->Tasks.push(new Task(func, forward<ARGS>(args)...));
        m_cond.notify_one();
        return ;
    }


private:
    Task *getOneTask() {
        unique_lock<mutex> lock(m_mutex); //抢锁
        if (Tasks.empty()) {
            //等待,直到队列中存在任务
            m_cond.wait(lock);//临时释放互斥锁并等待
        }
        if (is_running == false) return nullptr;//收到stop
        Task *t = Tasks.front();
        Tasks.pop();
        return t;
    }


    bool is_running;
    int max_threads_num;
    std::mutex m_mutex;
    std::condition_variable m_cond;

    vector<thread *> threads;//线程队列
    queue<Task *> Tasks;//任务队列
};


void thread_func2(int &n) {
    n += 1;
    return ;
}

void task_func(int x) {
    cout << "task func : " << x << endl;
    return ;
}

int main() {
    /*
    Task t1(thread_func1, 3, 4);
    Task t2(thread_func1, 5, 6);
    Task t3(thread_func1, 7, 8);
    t1(), t2(), t3();

    int n = 0;
    Task t4(thread_func2, ref(n));
    t4(), t4(), t4();
    cout << n << endl;
    */

    cout << "------------------------" << endl;
    ThreadPool tp(6);
    tp.start();

    tp.addOneTask(task_func, 123);
    tp.addOneTask(task_func, 456);
    tp.addOneTask(task_func, 789);

    for (int i = 0; i < 10000000; i++) ;

    tp.stop();
    return 0;
}
