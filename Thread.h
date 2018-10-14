
#include "print.h"
#include <functional>

/*class Thread is the interface, the specific thread class*/
/*implemented by pthread, c++11 thread of boost thread    */

class Thread
{
public:
	typedef  function<void (void)> Func; /* Task in thread*/
	Thread(const Func &func)
		:func_(func)
	{}
	virtual ~Thread()
	{}
	/* pure virtual function,     */ 
	/* indicates Thread is a interface*/

	virtual void startThread() = 0;                        
	virtual void join();  
private:
	Func func_;
	/* the other field will be added later */
}
