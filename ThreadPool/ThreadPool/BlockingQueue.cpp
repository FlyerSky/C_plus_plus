#include "BlockingQueue.h"

namespace threadpool {

template<class T>
BlockingQueue::BlockingQueue() : m_mutex(), m_notEmpty(m_mutex), m_queue()
{
}

template<class T>
void BlockingQueue::Push(const T& x)
{
	MutexLockGuard lock(m_mutex);
	m_queue.push(x);
	m_notEmpty.Notify();
}

template<class T>
T BlockingQueue::Pop()
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

template<class T>
size_t BlockingQueue::Size() const
{
	MutexLockGuard lock(m_mutex);
	return m_queue.size();
}

template<class T>
bool BlockingQueue::Empty() const
{
	return Size() == 0;
}

}