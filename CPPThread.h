#ifndef CPP_THREAD_HEADER
#define CPP_THREAD_HEADER

#include <thread>
#include <memory>
#include "Thread.h"

class CPPThread : public Thread
{
public:
	CPPThread(const Func & func)
		:Thread(func), threadp_(nullptr)
	{}
	CPPThread(CPPThread && self):Thread(std::move(self))
	
	{
		threadp_ = std::move(self.threadp_);
	}
	~CPPThread()
	{}
	void startThread();
	void destroyThread();
	void join();
private:
	std::shared_ptr<std::thread> threadp_;
};
#endif
