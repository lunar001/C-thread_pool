#include "Thread.h"

namespace CurrentThread
{
	/* Those variables are just global variables */
	/* that defined in namespace CurrentThread   */
	__thread int threadid = 0;
	__thread char threadidString[32];
	__thread int threadidStringlength = 6;


	void CurrentThread::catcheTid()
	{
		if(threadid == 0)
			threadid = gettid();
	}

}
