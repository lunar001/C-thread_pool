#ifndef H_THREAD_HEADER
#define H_THREAD_HEADER
#include "print.h"
#include <functional>

/*class Thread is the interface, the specific thread class*/
/*implemented by pthread, c++11 thread of boost thread    */

class Thread
{
public:
	typedef  std::function<void (void)> Func; /* Task in thread*/
	Thread(const Func &func)
		:func_(func)
	{}
	Thread(const Thread & self) = delete;
	Thread(Thread && self)
	{
		func_ = std::move(self.func_);
	}

	virtual ~Thread()
	{}
	/* pure virtual function,     */ 
	/* indicates Thread is a interface*/

	virtual void startThread() = 0;                        
	virtual void join() = 0;
	virtual void destroyThread() = 0;
	Func func_;
	/* the other field will be added later */
};
#endif
