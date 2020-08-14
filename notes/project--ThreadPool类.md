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
       
       //初始化
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

