#ifndef THREAD_WORK
#define THREAD_WORK

#define WORK_NO_ERROR 0

class ThreadWork
{
protected:
	int _error;
	bool _quit;

public:
	ThreadWork() : _error(WORK_NO_ERROR), _quit(false) {}
	virtual ~ThreadWork() {}

	virtual void work() = 0;

	bool isQuit() { return _quit; }
	void quit(bool status) { _quit = status; }

	int getLastError() { return _error; }
	void setError(int num) { _error = num; }

	virtual void clean()
	{
		_error = WORK_NO_ERROR;
		_quit = false;
	}
};

#endif // THREAD_WORK