#include "ThreadQueue.h"

#include <iostream>
#include <functional>
#include "Thread.h"
#include "Cthread.h"
#include "CPPThread.h"

#include <stdio.h>

#define NUM 100000

Thread_Queue<int> q;
void push_func()
{
	/* push_func will generate random number and push it into q*/
	int i = 0;
	
	for (i = 0; i < NUM; i++)
	{
		int value = rand();
		q.push(value);
	}
	return;
}
void try_pop_func()
{
	/* pop_func will pop element from q */
	int i = 0;
	while(!q.empty())
	{
		int value;
		if(q.try_pop(value))
			i++;
	}
	std::cout << "i = " << i << std::endl;
	return ;

}

void wait_and_pop_func()
{
	int num = 0;
	while(!q.empty())
	{
		int value;
		q.wait_and_pop(value);
	//	std::cout << "value = " << value << std::endl;
		num ++;
	}
	std::cout << "num = " << num << std::endl;

	return ;
}


int main()
{
	CThread th1(push_func);
	CThread th2(push_func);

	CPPThread cpt1(try_pop_func);
	CPPThread cpt2(wait_and_pop_func);

	th1.startThread();
	th2.startThread();
	cpt1.startThread();
	cpt2.startThread();
	th1.join();
	th2.join();
	cpt1.join();
	cpt2.join();
	th1.destroyThread();
	th2.destroyThread();
	cpt1.destroyThread();
	cpt2.destroyThread();

	return 0;


}
