#include "Cthread.h"

void Cthread::startThread()
{
	int ret = 0;
	data = new CthreadData(func_);
	ret = pthread_create(&tid_, NULL, runThread, (void * )data);
	if(ret)
	{
		log_error("pthread_create_error\n");
		
	}
	return ;
	
}

