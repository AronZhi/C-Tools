#include <Windows.h>
#include "../String/print.hpp"
#include "../Async/MessageQueue.hpp"
#include "../Async/WorkThread.hpp"
#include <random>

class A : public WorkThread
{
public:
    void run() override
    {
		bool existed = false;
		if (_thread_exist.compare_exchange_strong(existed, true))
		{
			try
			{
				_thread.reset(new std::thread([&]() {
					_thread_run.store(true);
                    char c = 0;
					while (_thread_run.load())
					{
                        wprint("input q to quit");
						c = getchar();
                        if (c == 'q')
                        {
                            quitWithinThread();
                        }
					}
				}));
			}
			catch (std::exception& e)
			{
				if (_thread.get())
				{
					_thread.reset(nullptr);
					_thread_exist.store(false);
				}
			}
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

void testThread()
{
    /*
    std::unique_ptr<A> pa(new A());
    pa->run();
    pa->stop();
    */
    A a;
    a.run();
    a.stop();
}

int main()
{
    testThread();
    return 0;
}
