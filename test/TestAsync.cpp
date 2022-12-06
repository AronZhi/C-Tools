#include <Windows.h>
#include "../String/print.hpp"
#include "../Async/MessageQueue.hpp"
#include "../Async/ThreadItem.hpp"
#include "../Async/ThreadWork.hpp"
#include <random>

class TestWork : public ThreadWork
{
    void work()
    {
        wprint("input q to quit");
        char c = getchar();
        if (c == 'q')
            quit(true);
    }
};

int getRand(int min, int max)
{
    std::random_device rd;
    return (rd() % (max - min + 1)) + min;
}

void test_messsageQueu()
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

        while (!msg_queue.empty())
        {
            std::shared_ptr<int> p = msg_queue.pop();
            wprint("continue pop: ", *p);
        }
        });

    push_thread.join();
    pop_thread.join();
    getchar();
}

void test_thread()
{
    ThreadItem t1(new TestWork());
    t1.run();
    t1.stop();
    wprint("run again");
    t1.run();
    t1.stop();
}

int main()
{
    test_thread();
    return 0;
}
