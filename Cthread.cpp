#include "Cthread.h"

void * runThread(void * arg)
{
	CthreadData * data = static_cast<CthreadData *> (arg);
	data->func_();
	return (void * )0;
}
void CThread::startThread()
{
	int ret = 0;
	data_ = new CthreadData(func_);
	ret = pthread_create(&tid_, NULL, runThread, (void * )data_);
	if(ret)
	{
		log_error("pthread_create_error\n");
		
	}
	return ;
	
}

void CThread::destroyThread()
{
	if(data_)
		delete data_;
}
void CThread::join()
{
	pthread_join(tid_, NULL);
}

