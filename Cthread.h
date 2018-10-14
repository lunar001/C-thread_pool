#include "Thread.h"

#include <pthread.h>


/* CthreadData provides the data that runThread needs */
struct CthreadData
{
public:
	CthreadData(const Thread::Func & func)
		:func_
	{}
	~CthreadData()
	{}
private:

	Thread::Func func_;


}

void * runThread(void * arg)
{
	CthreadData * data = static_cast<CthreadData *> arg;
	data->runc_();
	return (void * )0;
}
class CThread : Thread
{
public:
	Cthread(const Func & func)
		:Thread(func), tid_(0), data_(0)
	{}
	virtual ~Cthread()
	{}
	void startThread();
	void join();
private:
	pthread_t tid_;
	CthreadData * data_;
}
