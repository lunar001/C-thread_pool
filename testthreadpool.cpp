#include "ThreadPool.h"
#include "print.h"

void func(int i)
{
	log_info("This is thread  %d func\n", i);
	return;
}

int main()
{
	ThreadPool tp;
	int i = 0;
	for(i = 0; i < 1000; i++)
	{
		tp.put_task(std::bind(func, i));
	}
	tp.start(4);
	tp.stop();
	return 0;
}
