#include "BoundedQueue.h"

namespace threadpool {

template <class T>
explicit BoundedQueue::BoundedQueue(size_t capacity) : m_capacity(capacity), m_circular_buffer(capacity)
{
	m_head = 0;
	m_tail = 0;
	m_size = 0;
	assert(m_capacity);
}

template <class T>
BoundedQueue::~BoundedQueue()
{
}

template <class T>
void BoundedQueue::Clear()
{
	m_head = 0;
	m_tail = 0;
	m_size = 0;
}

template <class T>
bool BoundedQueue::Empty() const
{
	return m_size == 0;
}

template <class T>
bool BoundedQueue::Full() const
{
	return m_capacity == m_size;
}

template <class T>
size_t BoundedQueue::Size() const
{
	return m_size;
}

template <class T>
size_t BoundedQueue::Capacity() const
{
	return m_capacity;
}

template <class T>
void BoundedQueue::Push(const T& t)
{
	assert(!Full);
	m_circular_buffer[m_tail] = t;
	m_tail = (m_tail + 1) % m_capacity;
	++m_size;
}

template <class T>
T BoundedQueue::Pop()
{
	assert(!Empty());
	size_t oldPos = m_head;
	m_head = (m_head + 1) % Capacity;
	--m_size;
	return m_circular_buffer[oldPos];
}

}