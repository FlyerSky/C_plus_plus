#include "BoundedBlockingQueue.h"

namespace threadpool {

template<typename T>
explicit BoundedBlockingQueue::BoundedBlockingQueue(size_t maxSize)
	: m_mutex(),
	m_notEmpty(m_mutex),
	m_notFull(m_mutex),
	m_queue(maxSize)
{
}

template<typename T>
void BoundedBlockingQueue::Push(const T& x)
{
	MutexLockGuard lock(m_mutex);
	while (m_queue.Full)
	{
		m_notFull.Wait();
	}
	assert(!m_queue.Full());
	m_queue.Push(x);
	m_notEmpty.Notify();
}

template<typename T>
T BoundedBlockingQueue::Pop()
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

template<typename T>
bool BoundedBlockingQueue::Empty() const
{
	MutexLockGuard lock(m_mutex);
	return m_queue.Empty();
}

template<typename T>
bool BoundedBlockingQueue::Full() const
{
	MutexLockGuard lock(m_mutex);
	return m_queue.Full();
}

template<typename T>
size_t BoundedBlockingQueue::size() const
{
	MutexLockGuard lock(m_mutex);
	return m_queue.size();
}

template<typename T>
size_t BoundedBlockingQueue::capacity() const
{
	return m_queue.capacity();
}

}