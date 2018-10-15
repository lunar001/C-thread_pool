#ifndef C_THREAD_HEADER
#define C_THREAD_HEADER
#include "Thread.h"

#include <pthread.h>


/* CthreadData provides the data that runThread needs */
struct CthreadData
{
public:
	CthreadData(const Thread::Func & func)
		:func_(func)
	{}

	Thread::Func func_;


};

void * runThread(void * arg);
class CThread : Thread
{
public:
	CThread(const Func & func)
		:Thread(func), tid_(0), data_(0)
	{}
	virtual ~CThread()
	{}
	void startThread();
	void destroyThread();
	void join();
private:
	pthread_t tid_;
	CthreadData * data_;
};

#endif
