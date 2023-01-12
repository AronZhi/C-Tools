#include <Windows.h>
#include "../String/print.hpp"
#include "../Async/MessageQueue.hpp"
#include "../Async/WorkThread.hpp"
#include "../Async/ThreadPool.hpp"
#include <random>

class A : public WorkThread
{
protected:
    void work()
    {
		char c = 0;
        while (_thread_run.load())
		{
            wprint("input q to quit");
			c = getchar();
            if (c == 'q')
                stop();
		}
	}
};

int getRand(int min, int max)
{
    std::random_device rd;
    return (rd() % (max - min + 1)) + min;
}

void testMesssageQueu()
{
    MessageQueue<int> msg_queue;
    std::atomic_bool stop(false);

    std::thread push_thread([&]() {
        while (!stop.load())
        {
            int n = getRand(1, 20);
            int* p = new int(n);
            wprint("push: ", n);
            msg_queue.push(p);
            Sleep(n * 10);
        }
    });

    std::thread pop_thread([&]() {
        while (!stop.load())
        {
            std::shared_ptr<int> p = msg_queue.pop();
            wprint("pop: ", *p);
            if ((*p % 5) == 0)
                stop.store(true);
        }
    });

    push_thread.join();
    pop_thread.join();
    getchar();
}

void testWorkThread()
{
    /*
    std::unique_ptr<A> pa(new A());
    pa->run();
    pa->stop();
    pa->join();
    */
    A a;
    a.run();
    a.stop();
    a.join();
}

void testThreadPool()
{
    ThreadPool pool;
    pool.run(3);

    pool.add([](){
        wprint(" this is a no capture lambda task");
    });

    std::shared_ptr<int> pnum = std::make_shared<int>(100);
    pool.add([pnum](){
        wprint(" this is a capture lambda task", *pnum);
    });
    
    Sleep(3000);
    pool.stop();
    pool.join();
}

int main()
{
    testMesssageQueu();
    return 0;
}
