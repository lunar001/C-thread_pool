#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include "Cthread.h"

void func()
{
	log_info("hello world\n");

}

int main()
{
	CThread cthread(func);
	cthread.startThread();
	cthread.destroyThread();
	cthread.join();

	return 0;
}
