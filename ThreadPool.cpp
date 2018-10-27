#include "ThreadPool.h"
#include "CPPThread.h"

void ThreadPool::work_()
{
	while(!tasks_.empty())/* if tasks_ is empty, waiting at here*/
	{
		Thread::Func task;
		tasks_.wait_and_pop(task); /* work_ may hang at here and can't be over forever */
		if(!task)
			return;
		task();
	}
}

void ThreadPool::put_task(const Thread::Func & task)
{
	tasks_.push(task);
}

void ThreadPool::start(int num) 
{
	/* num is the num of thread */
	if (num != 0)
		threadNum_ = num;
	else
		threadNum_ = 4; /* create 4 threads in thread pool now*/

	for ( int i = 0; i < threadNum_; i++)
	{
		/* make_shared need class has a copy constructor or move constructor*/
		/*std::shared_ptr<Thread> tp = std::make_shared<CPPThread>(
				CPPThread(std::bind(&ThreadPool::work_, this)));*/
		std::shared_ptr<Thread> tp(new CPPThread(std::bind(&ThreadPool::work_, this)));
		threads_.push_back(tp);
		tp->startThread();
	}
}

void ThreadPool::stop()
{
	/* set queue over, in case of there is some threads waiting at the wait_and_pop*/
	tasks_.over();
	for (auto tp : threads_)
		tp->join();
}
