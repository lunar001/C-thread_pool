#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H
/* implemented as template, for we don't known the specific data type in queue*/

#include <memory>
#include <queue>

template <typename T>    
class ThreadQueue
{
public:
	ThreadQueue()
	{}
	void wait_and_pop (T & value);
	bool try_pop(T & value);
	std::shared_ptr<T> wait_and_pop();
	std::shared_pt<T> try_pop();
	void push(T new_value);
	bool empty() const;
private:
	mutable std::mutex mx_;
	std::queue<std::shared_ptr<T> > data_queue_;
	std::condition_variable cv_;
};

#endif
