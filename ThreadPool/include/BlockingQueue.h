#pragma once

#ifndef THREADPOOL_BLOCKINGQUEUE_H
#define THREADPOOL_BLOCKINGQUEUE_H

#include <queue>
#include "Condition.h"

namespace threadpool {

template<class T>
class BlockingQueue : NonCopyable {
public:
	BlockingQueue() : m_mutex(), m_notEmpty(m_mutex), m_queue()
	{
	}

	void Push(const T& x)
	{
		MutexLockGuard lock(m_mutex);
		m_queue.push(x);
		m_notEmpty.Notify();
	}

	T Pop()
	{
		MutexLockGuard lock(m_mutex);
		while (m_queue.empty())
		{
			m_notEmpty.Wait();
		}
		assert(!m_queue.empty());
		T front(m_queue.front());
		m_queue.pop();
		return front;
	}

	size_t Size() const
	{
		MutexLockGuard lock(m_mutex);
		return m_queue.size();
	}

	bool Empty() const
	{
		return Size() == 0;
	}

private:
	mutable MutexLock m_mutex;
	Condition m_notEmpty;
	std::queue<T> m_queue;

	// 如果类的成员函数不会改变对象的状态，那么这个成员函数一般会声明成const的。但是，有些时候，我们需要
	// 在const的函数里面修改一些跟类状态无关的数据成员，那么这个数据成员就应该被mutalbe来修饰。
	// mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。

}; // class BlockingQueue

} // namespace threadpool

#endif
