#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include "Thread.h"
#include "ThreadQueue.h"
#include <vector>

class ThreadPool
{
public:
	ThreadPool():threadNum_(0){};

	void put_task(const Thread::Func & task);/* push task into threadpool */

	void start(int num = 0); 
	void stop(); /* try to stop all the threads */

private:
	std::vector<std::shared_ptr<Thread>> threads_; /* The number of thread is limits*/
	int threadNum_;
	ThreadQueue<Thread::Func> tasks_;
	void work_(); /* The work func of ths threadpool*/
};
#endif 
