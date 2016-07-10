#ifndef THREADPOOL_BOUNDED_BLOCKING_QUEUE_H
#define THREADPOOL_BOUNDED_BLOCKING_QUEUE_H

#include "BoundedQueue.h"

namespace threadpool {

template <class T>
class BoundedBlockingQueue : public NonCopyable {
public:
	explicit BoundedBlockingQueue(size_t maxSize)
	: m_mutex(),
	m_notEmpty(m_mutex),
	m_notFull(m_mutex),
	m_queue(maxSize)
	{
	}

	void Push(const T& x)
	{
		MutexLockGuard lock(m_mutex);
		while (m_queue.Full())
		{
			m_notFull.Wait();
		}
		assert(!m_queue.Full());
		m_queue.Push(x);
		m_notEmpty.Notify();
	}

	T Pop()
	{
		MutexLockGuard lock(m_mutex);
		while (m_queue.Empty())
		{
			m_notEmpty.Wait();
		}
		assert(!m_queue.Empty());
		T res = m_queue.Pop();
		m_notFull.Notify();
		return res;
	}

	bool Empty() const
	{
		MutexLockGuard lock(m_mutex);
		return m_queue.Empty();
	}

	bool Full() const
	{
		MutexLockGuard lock(m_mutex);
		return m_queue.Full();
	}

	size_t size() const
	{
		MutexLockGuard lock(m_mutex);
		return m_queue.size();
	}

	size_t capacity() const
	{
		return m_queue.capacity();
	}

private:
	mutable MutexLock	m_mutex;
	Condition		m_notEmpty;
	Condition		m_notFull;
	BoundedQueue<T>		m_queue;

}; // class BoundedBlockingQueue

} // namespace threadpool

#endif // THREADPOOL_BOUNDED_BLOCKING_QUEUE_H
