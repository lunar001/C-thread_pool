#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H
/* implemented as template, for we don't known the specific data type in queue*/

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "print.h"

template <typename T>    
class ThreadQueue
{
public:
	ThreadQueue():overFlag_(false){}
	void wait_and_pop (T & value);
	bool try_pop(T & value);
	std::shared_ptr<T> wait_and_pop();
	std::shared_ptr<T> try_pop();
	void push(T new_value);
	bool empty();
	void over();
private:
	mutable std::mutex mx_; /* mx_ must be mutable, for const member function need to access it */
	std::queue<std::shared_ptr<T> > data_queue_;
	std::condition_variable cv_;
	/* overFlag_ avoid the threads use ThreadQueue wait at cv_ and can't over*/
	std::atomic<bool> overFlag_;
};

template <typename T>
void ThreadQueue<T>::wait_and_pop( T & value)
{
	std::unique_lock<std::mutex> lk(mx_);
	/* don't need check condition in while after wait*/
	cv_.wait(lk, [this] { return (!data_queue_.empty() || overFlag_.load());}); 
	if(overFlag_.load())
	{
		log_info("received over message\n");
		return;
	}


	value = std::move(* data_queue_.front()); /* the front element will be popped soon*/
	data_queue_.pop();

}

template <typename T>
bool ThreadQueue<T>::try_pop( T & value)
{
	std::lock_guard<std::mutex> lk(mx_);
	if(data_queue_.empty())
		return false;
	value = std::move(*data_queue_.front());
	data_queue_.pop();
	return true;
}

template <typename T>
std::shared_ptr<T> ThreadQueue<T>::wait_and_pop()
{
	std::unique_lock<std::mutex> lk(mx_);
	/* the overFlag_ dosen't add any overlad */
	cv_.wait(lk, [this]{ return (!data_queue_.empty() || overFlag_.load());});
	if(overFlag_.load())
	{
		log_info("received over message\n");
		return nullptr;/* There is no aviliable element any more */
	}
		
	std::shared_ptr<T> res = data_queue_.front();
	data_queue_.pop();
	return res;
}

template <typename T>
std::shared_ptr<T> ThreadQueue<T>::try_pop()
{
	std::lock_guard<std::mutex> lk(mx_);
	if(data_queue_.empty())
		return std::shared_ptr<T>();
	std::shared_ptr<T> res = data_queue_.front();
	data_queue_.pop();
}

template <typename T>
void ThreadQueue<T>::push(T new_value)
{
	std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value)));
	std::lock_guard<std::mutex> lk(mx_);
	data_queue_.push(data);
	cv_.notify_one(); /* notify with the lock hold, no problem */
}

template <typename T>
bool ThreadQueue<T>::empty() 
{
	std::lock_guard<std::mutex> lk(mx_);
	return data_queue_.empty();
}

template <typename T>
void ThreadQueue<T>::over()
{
	/* over set overFlag_ and wake up all thread that wait and cv_ */
	overFlag_.store(true);
	/* wake up all thread */
	cv_.notify_all();
}

#endif
