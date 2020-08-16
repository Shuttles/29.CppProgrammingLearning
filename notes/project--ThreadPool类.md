# 0.需求

1. 线程是计算机中非常重要的资源，必须保证程序开线程的数量得到限制！
2. 得使得线程数量不会因为任务的增加而增加

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1ghq3ep7sbwj30kr0dmdla.jpg)

![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1ghq3vg1gxuj30lm0gpjwx.jpg)







# 1.Task类

1. 首先得封装一个Task类，参数是==函数地址，函数实参==

2. 用到的技术：

   + 首先要把函数和参数列表==绑定==到一起--用`bind`
   + 传入的可能是函数，可能是函数对象，所以得把它们统一成可调用对象--`function`
   + 传入的是==任意类型==的函数--`template`

3. 例子：

   ```c++
   #include <functional>
   
   class Task {
   public:
       //构造函数
       //因为要传入任意类型的函数，所以得用模板
       template<typename T, typename ...ARGS> 
       Task(T func, ARGS... args) {
           this->func = std::bind(func, forward<ARGS>(args)...);//利用bind将函数和参数列表封装成一个可调用对象。
           //forward是为了让参数列表以正确的类型向前传递！！！
       }
       void operator()() {//不需要形参，因为bind中已经有了参数列表了
           this->func();//调用函数对象
           return ;
       }
           
   private:
       function<void()> func;                 //利用function封装一个可调用对象作为成员属性,这里暂时只传返回值是void的可调用对象，不用传入参数列表，因为bind会绑定参数列表
   };
   
   //试验函数
   void thread_func1(int a, int b) {
       cout << a << " + " << b << " = " << a + b << endl;
       return ;
   }
   
   int main()  {
       Task t1(thread_func1, 3, 4);
       Task t2(thread_func1, 5, 6);
       Task t3(thread_func1, 7, 8);
       t1(), t2(), t3();                      //通过operator()调用真正的work函数
       
       return 0;
   }
   ```

4. 如何确定自己真正能写出这样一个类？

   + 只看main函数中的使用，自己试着一步一步从外部到内部实现这个类！





# 2.ThreadPool类

1. 
2. 技术点：
   + 将线程入口函数设置为成员函数，因为其很有可能==访问成员属性==



## 2.1框架

1. 例子

   ```c++
   class ThreadPool {
   public:
       ThreadPool(int n = 5) : is_runing(false), max_threads_num(n) {}
       
       //初始化--创建线程对象并加入线程队列
       void start() {
           if (is_running == true) return ;
           is_running = true;
           //初始化线程对象
           for (int i = 0; i < n; i++) {
               //以成员方法worker作为线程入口！
           	threads.push_back(new thread(&ThreadPool::worker, this));//成员函数比较特殊，要传其地址必须加上&，而普通函数的函数名就代表其地址！
           }  
           return ;
       }    
       
       //线程入口
       void worker() {
           cout << "worker : I am a worker" << endl;
       } 
       
       //停止
       void stop() {
           if (is_running == false) return ;
           is_running = false;
           for (int i = 0; i < this->max_threads_num; i++) {
               threads[i]->join();//等待这个线程结束！
               delete threads[i];//回收线程空间
           }
           threads.clear();//回收vector
           return ;
       }
      
   private:
       bool is_running;
       int max_threads_num;
       vector<thread *> threads;//线程队列
       
   };
   
   int main() {
       ThreadPool tp(6);
       tp.start();
       tp.stop();
       return 0;
   }
   ```

   



## 2.2线程入口函数--worker函数

### 附：原子操作

1. 与代码量无关
2. 插入不进来其他操作，就是原子操作



### 附：线程安全

1. 临界资源：

   多线程环境中有多个线程都可以访问到的资源

2. 多线程环境下临界资源的正确使用。如果==可能出错==，那就是非线程安全的！

   + 比如说，一个cnt变量，多线程环境下，可能同时对其+1(但是应该各+1 总共+2)

3. 解决方案：

   + 加互斥锁`mutex`

     > 即在使用临界资源前加锁，使用后解锁，这样就保证了同时只有一个线程使用这个临界资源
     >
     > 加锁方法一：通过定义一个局部变量
     >
     > ```c++
     > unique_lock<mutex> lock(mutex);
     > //当构造完成就说明当前线程抢到互斥锁
     > //当局部变量被销毁就自动解锁了
     > ```
     >
     > 

     + 如果要==等待==某种资源，那就要配上条件变量`condition`，所谓的***<u>条件</u>***只是逻辑上的理解

       > 比如`getOneTask中`等待任务队列中有任务的情况
       >
       > ![img](https://wx1.sinaimg.cn/mw690/005LasY6gy1ghsr2e2tfmj315h0e9guo.jpg)
       >
       > 
       >
       > 

   + 其他方式





### 2.2.1 版本1.0

1. 代码实现

   ```c++
   #include <mutex>
   #include <condition_variable>
   
   
   class ThreadPool {
   public:
       ThreadPool(int n = 5) : is_runing(false), max_threads_num(n), m_mutex(), m_cond {}
       
       //初始化--创建线程对象并加入线程队列
       void start()；
       
       //线程入口函数
       void worker() {
           while (is_running) {
               //取任务
               //运行任务
               //释放任务
               Task *t = this->getOneTask();
               if (t == nullptr) break;//这个是最后改完stop才想到的！这是跳出循环的地方！因为stop中发信号把is_running改成了false
               (*t)();
               delete t;
           }
       } 
       
       //停止
       void stop()  {
           if (is_running == false) return ;
           //如果有线程在wait任务，那么join肯定等不结束！所以如果想stop，就得发信号通知所有线程让他们歇菜！
           do {//用dowhile控制lock的作用域！！
               unique_lock <mutex> lock(m_mutex);//修改is_running前得加锁！
               is_running = false; 
               m_cond.notify_all();
           } while (0);
           for (int i = 0; i < this->max_threads_num; i++) {
               threads[i]->join();//等待这个线程结束！
               delete threads[i];//回收线程空间
           }
           threads.clear();//回收vector
           //清空任务队列
           do {
               unique_lock <mutex> lock(m_mutex);
               while (!Tasks.empty()) Tasks.pop();
           } while (0);
           return ;
       }
           
       template<typename T, typename ...ARGS>
       void addOneTask(T func, ARGS... args) {
           unique_lock<mutex> lock(m_mutex);//这个局部变量一旦完成构造，就说明当前线程抢到了互斥锁，出了这个函数，局部变量就销毁了，相当于自动解锁！！！
           this->Tasks.push(new Task(func, forward<ARGS>(args)...));  
           m_cond.notify_one();//只通知一个线程条件已成熟
           return ;
       };
      
   private:
       Task *getOneTask() {
           unique_lock<mutex> lock(m_mutex);//抢锁
           if (Tasks.empty()) {
               //等待，直到队列中存在任务
               m_cond.wait(lock);//条件变量必须配合互斥锁使用！
               //先临时释放锁，阻塞，等到条件成熟(接收到信号)，就继续加锁，往下执行
           }
           if (is_runing == false) return nullptr;//这个是最后改完stop才想到的！
           Task *t = Tasks.front();
           Tasks.pop();
           return t;
       }
       
       bool is_running;
       int max_threads_num;
       mutex m_mutex;
       condition_variable m_cond;
       
       vector<thread *> threads;//线程队列
       queue<Task *> Tasks;
       
   };
   
   void task_func(int x) {
       cout << "task func : " << x << endl;
       return 0;
   }
   
   int main() {
       ThreadPool tp(6);
       tp.start();
       
       tp.addOneTask(task_func, 123);
       tp.addOneTask(task_func, 456);
       tp.addOneTask(task_func, 456);
       
       for (int i = 0; i < 100000; i++) ;//等待任务执行完，防止有任务没执行就stop了！
       
       tp.stop();
       return 0;
   }
   ```

2. getOneTask流程

   ![img](https://wx4.sinaimg.cn/mw690/005LasY6gy1ghsrn06u7tj30ti0cwahp.jpg)

3. 关于线程的：

   + 临界资源使用前要==加锁==，使用后要解锁
   + 如果要等待某种条件，要用==条件变量==
   + ==结束所有线程==也得用条件变量发信号，否则会一直阻塞



如果while中不加is_running，那么若信号时stop发出的，但是还是会继续循环！那就卡住了！



### 2.2.2 版本2.0

1. 上一个版本在macos下会***<u>报错</u>***！

2. 问题就出在这段代码：

   ```c++
   template<typename T, typename ...ARGS>
   void addOneTask(T func, ARGS... args) {
       unique_lock<mutex> lock(m_mutex);//这个局部变量一旦完成构造，就说明当前线程抢到了互斥锁，出了这个函数，局部变量就销毁了，相当于自动解锁！！！
       this->Tasks.push(new Task(func, forward<ARGS>(args)...));  
       m_cond.notify_one();//只通知一个线程条件已成熟
       return ;
   };
   
   Task *getOneTask() {
       unique_lock<mutex> lock(m_mutex);//抢锁
       if (Tasks.empty()) {
           //等待，直到队列中存在任务
           m_cond.wait(lock);//条件变量必须配合互斥锁使用！
           //先临时释放锁，阻塞，等到条件成熟(接收到信号)，就继续加锁，往下执行
        }
       if (is_runing == false) return nullptr;//这个是最后改完stop才想到的！
       Task *t = Tasks.front();
       Tasks.pop();
       return t;
   }
   ```

   + 问题就出在第11行的if！

   + 有可能在addOneTask解锁后，被别的线程抢到锁，看到任务队列中有任务，就取走任务了！(也就是不执行代码11~15行！)

     等到原本该抢到锁的线程抢到锁后，此时任务队列就有可能为空！这样pop就会出错！

     所以必须在==接收到信号后再判断一下==！

   + 只需把11行的if改成while

   + `BUT`还得注意一点，因为stop也会发出信号，那么这样如果收到信号后再判断一下队列还是为空，就会继续循环等待！

     所以就得把11行改成`while (is_running && Tasks.empty)`，只要两个条件有一个不满足，就会跳出循环。





### 2.2.3 版本3.0

1. 在版本1.0的main函数中，用了一个for循环来等待任务被执行完毕后才stop，但是真实环境远比这复杂，也不能这么傻X地来等待。

2. 新需求：

   ***<u>当调用stop时，会让调用stop前已经存在线程池中的任务执行完毕(调用stop后加入的任务不执行)，然后再结束。</u>***

   ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1ghsu3udra4j30sd0e2dly.jpg)

3. 思路：

   + 原来的is_running改个名--running，不能删，因为防止==多次==start或stop！
   + 让每一个线程都存储一个`is_running`变量
   + 在stop代码中，往任务队列中添加`max_thread_num`个特殊任务，任务就干一件事--将当前线程的`is_running`改成false

   ![img](https://wx3.sinaimg.cn/mw690/005LasY6gy1ghsvgcreu6j30kk0lqgrl.jpg)

   + 这样就在代码第17行跳出循环，最终结束work函数，这样stop中join函数也会结束，最终结束线程池。

   + 问题来了：如何在每个线程中存储一个`is_running`呢？

     其实很简单，用map做个映射就行了！

   

   ```c++
   #include <mutex>
   #include <condition_variable>
   
   
   class ThreadPool {
   public:
       ThreadPool(int n = 5) : max_threads_num(n), m_mutex(), m_cond(), running(false) {}
       
       //初始化--创建线程对象并加入线程队列
       void start()；
       
       //线程入口函数
       void worker() {
           std::thread::id id = std::this_thread::get_id();//获得线程id
           is_running[id] = true;
           
           while (is_running[id]) {//特殊任务会把is_runing[id]改成false
               Task *t = this->getOneTask();
               (*t)();
               delete t;
           }
       } 
       
       //停止
       void stop()  {
           if (running == false) return ;
           //以添加特殊方式的任务的形式结束
           for (int i = 0; i < this->max_threads_num; i++) {
               this->addOneTask(&ThreadPool::stop_task, this);
           }
           
           for (int i = 0; i < this->max_threads_num; i++) {
               threads[i]->join();
               delete threads[i];
           }
           threads.clear();//回收vector
           running = false;
       }
           
       template<typename T, typename ...ARGS>
       void addOneTask(T func, ARGS... args) ;
      
   private:
       void stop_task() {
           std::thread::id id = std::this_thread::get_id();//获得线程id
           is_running[id] = false;
           return ;
       }
       
       Task *getOneTask() {
           unique_lock<mutex> lock(m_mutex);//抢锁
           while (Tasks.empty()) {
               //等待，直到队列中存在任务
               m_cond.wait(lock);//条件变量必须配合互斥锁使用！
               //先临时释放锁，阻塞，等到条件成熟(接收到信号)，就继续加锁，往下执行
           }
           Task *t = Tasks.front();
           Tasks.pop();
           return t;
       }
       
   
       int max_threads_num;
       mutex m_mutex;
       condition_variable m_cond;
       
       vector<thread *> threads;//线程队列
       queue<Task *> Tasks;
       std::map<std::thread::id, bool> is_running;//线程id到bool的映射
       
   };
   
   int main() {
       ThreadPool tp(6);
       tp.start();
       
       tp.addOneTask(task_func, 123);
       tp.addOneTask(task_func, 456);
       tp.addOneTask(task_func, 456);
       tp.addOneTask(task_func, 123);
       tp.addOneTask(task_func, 456);
       tp.addOneTask(task_func, 456);
       tp.addOneTask(task_func, 123);
       tp.addOneTask(task_func, 456);
       tp.addOneTask(task_func, 456);
       
       tp.stop();
       tp.addOneTask(task_func, 123);
       tp.addOneTask(task_func, 456);
       tp.addOneTask(task_func, 456);//stop后添加的任务不会执行！
       return 0;
   }
   ```

   





# 3.利用ThreadPool类

1. 需求：

   利用这个线程池类，开5个线程计算1000000以内的素数个数！

2. 代码

   ```c++
   int cnt = 0;
   
   int is_prime(int x) {
       if (x <= 1) return 0;
       for (int i = 2; i * i <= x; i++) {
           if (x % i == 0) return 0;
       }
       return 1;
   }
   
   void count_prime(int l, int r) {
       for (int i = l; i <= r; i++) {
           //cnt是临界资源，得加锁，但是太没必要了，所以就利用GNU环境下的无锁化工具！
           if (is_prime(i)) __sync_fetch_and_add(&cnt, 1);
       }
       return ;
   }
   
   int main() {
       ThreadPool tp(5);
       tp.start();
       
       for (int i = 0, j = 1; i < 5; i++, j += 200000) {
           tp.addOneTask(count_prime, j, j + 200000 - 1);
       }
       
       tp.stop();
       
       cout << "cnt = " << cnt << endl;
       return 0;
   }
   ```

   

