#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include "Cthread.h"
#include "CPPThread.h"

void func()
{
	log_info("hello world\n");
	log_warning("hello world\n");
	log_error("hello world\n");
	log_debug("hello world\n");

}

int main()
{
	CThread cthread(func);
	cthread.startThread();
	cthread.join();
	cthread.destroyThread();
	CPPThread cppthread(func);
	cppthread.startThread();
	cppthread.join();
	cppthread.destroyThread();	


	return 0;
}
