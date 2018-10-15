#include "CPPThread.h"

void CPPThread::startThread()
{
	threadp_ = std::make_shared<std::thread>(func_);
	return;
}

void CPPThread::destroyThread()
{
	return;
}

void CPPThread::join()
{
	return threadp_->join();
}
