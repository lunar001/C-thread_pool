#ifndef CPP_THREAD_HEADER
#define CPP_THREAD_HEADER

#include <thread>
#include <memory>
#include "Thread.h"

class CPPThread : Thread
{
public:
	CPPThread(const Func & func)
		:Thread(func), threadp_(nullptr)
	{}
	~CPPThread()
	{}
	void startThread();
	void destroyThread();
	void join();
private:
	std::shared_ptr<std::thread> threadp_;
};
#endif
