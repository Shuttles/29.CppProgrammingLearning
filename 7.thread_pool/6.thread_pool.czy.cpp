/*************************************************************************
	> File Name: 34.thread_pool.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 四  8/13 16:07:49 2020
 ************************************************************************/

#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace haizei {
class Task {
public:
    template<typename T, typename ...ARGS>
    Task(T func, ARGS... args) {
        this->func = std::bind(func, std::forward<ARGS>(args)...);
    }
    void operator()() {
        this->func();
        return ;
    }
    ~Task() {}

private:
    std::function<void()> func;
};

class ThreadPool {
public :
    ThreadPool(int n = 5) 
    : is_running(false), 
    max_threads_num(n),
    m_mutex(),
    m_cond() {}
    void start() {
        if (is_running) return ;
        is_running = true;
        for (int i = 0; i < this->max_threads_num; i++) {
            threads.push_back(new std::thread(&ThreadPool::worker, this));
        }
        return ;
    }
    void worker() {
        while (is_running) {
            Task *t = this->getOneTask();
            if (t == nullptr) break;
            (*t)();
            delete t;//回收任务空间
        }
        return ;
    }
    void stop() {
        if (is_running == false) return ;
        //运行 调用stop前还留在任务队列中的任务
        int remaining_task_num = task_queue.size();
        while (!task_queue.empty()) {
            
        }

        do {
            std::unique_lock<std::mutex> lock(m_mutex);
            is_running = false;
            m_cond.notify_all();//通知所有线程你们该歇菜了，所以最后才会依次take
        } while (0);
        for (int i = 0; i < this->max_threads_num; i++) {
            threads[i]->join();
            delete threads[i];
        }
        threads.clear();
        return ;
    }

    template<typename T, typename ...ARGS>
    void addOneTask(T func, ARGS...args) {
        std::unique_lock<std::mutex> lock(m_mutex);
        std::cout << std::this_thread::get_id() << " add one task" << std::endl;
        this->task_queue.push(new Task(func, std::forward<ARGS>(args)...));
        m_cond.notify_one();
        return ;
    }

private:
    Task *getOneTask() {
        std::unique_lock<std::mutex> lock(m_mutex); // 抢碗
        while (is_running && task_queue.empty()) {//while会多判断一次！！
            std::cout << std::this_thread::get_id() << " wait one task" << std::endl;
            m_cond.wait(lock);
        }// 等待，直到队列中存在任务
        if (is_running == false) return nullptr;
        std::cout << std::this_thread::get_id() << " take one task" << std::endl;
        Task *t = task_queue.front();
        task_queue.pop();
        return t;
    }

    bool is_running;
    int max_threads_num;
    std::vector<std::thread *> threads;
    std::queue<Task *> task_queue;
    
    std::mutex m_mutex;
    std::condition_variable m_cond;
};
} // end of namespace haizei

void thread_func1(int a, int b) {
    std::cout << a << " + " << b << " = " << a + b << std::endl;
    return ;
}

void thread_func2(int &n) {
    n += 1;
    return ;
}

void (*func)();

void task_func(int x) {
    std::cout << "task func : " << x << std::endl;
    return ;
}

int main() {
    haizei::Task t1(thread_func1, 3, 4);
    haizei::Task t2(thread_func1, 5, 6);
    haizei::Task t3(thread_func1, 7, 8);
    t1(), t2(), t3();
    int n = 0;
    
    haizei::Task t4(thread_func2, std::ref(n));
    t4(), t4(), t4();
    std::cout << n << std::endl;

    haizei::ThreadPool tp(6);
    tp.start();
    tp.addOneTask(task_func, 123);
    tp.addOneTask(task_func, 456);
    tp.addOneTask(task_func, 789);
    //for (int i = 0; i < 100000000; i++) ;//等待所有任务都执行完毕
    tp.stop();
    std::cout << "hello world" << std::endl;
    return 0;
}
