#ifndef WORK_THREAD
#define WORK_THREAD

#include <memory>
#include <atomic>
#include <thread>

class WorkThread
{
public:
    WorkThread() : _thread_run(false), _thread_exist(false), _thread(nullptr) {}
    virtual ~WorkThread() { stop(); }

    void stop(bool force_stop = false)
    {
        if (force_stop)
            _thread_run.load(false);
        
        if (_thread_exist.load())
        {
            _thread->join();
            _thread.reset(nullptr);
            _thread_exist.store(false);
        }
    }

    virtual bool run() = 0;
    /*
    void run()
    {
        if (！_thread_exist.load())
        {
            _thread.reset(new std::thread([&](){
                _thread_exist.store(true);
                _thread_run.store(true);
                while (_thread_run.load())
                {
                    // TODO: ...
                }
            }));
            return true;
        }
        return false;
    }
    */

    bool isRunning() { return _thread_run.load(); }

    void quitWithinThread() { _thread_run.store(false); }

protected:
    std::atomic_bool _thread_run;
    std::atomic_bool _thread_exist;
    std::unique_ptr<std::thread> _thread;
};

#endif // WORK_THREAD