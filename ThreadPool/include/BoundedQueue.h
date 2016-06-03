#pragma once

#ifndef THREADPOOL_BOUNDED_QUEUE_H
#define THREADPOOL_BOUNDED_QUEUE_H

#include <vector>
#include <fstream>
#include <cassert>

namespace threadpool {

using namespace std;

template <class T>
class BoundedQueue {
public:
	explicit BoundedQueue(size_t capacity)
	     : m_capacity(capacity), m_circular_buffer(capacity)
	{
		m_head = 0;
		m_tail = 0;
		m_size = 0;
		assert(m_capacity);
	}

	~BoundedQueue()
	{
	}

	void Clear()
	{
		m_head = 0;
		m_tail = 0;
		m_size = 0;
	}

	bool Empty() const
	{
		return m_size == 0;
	}

	bool Full() const
	{
		return m_capacity == m_size;
	}

	size_t Size() const
	{
		return m_size;
	}

	size_t Capacity() const
	{
		return m_capacity;
	}

	void Push(const T& t)
	{
		assert(!Full());
		m_circular_buffer[m_tail] = t;
		m_tail = (m_tail + 1) % m_capacity;
		++m_size;
	}

	T Pop()
	{
		assert(!Empty());
		size_t oldPos = m_head;
		m_head = (m_head + 1) % m_capacity;
		--m_size;
		return m_circular_buffer[oldPos];
	}

private:
	size_t m_head;
	size_t m_tail;
	size_t m_size;
	const size_t m_capacity;
	vector<T> m_circular_buffer;

}; // class BoundedQueue

} // namespace threadpool

#endif // THREADPOOL_BOUNDED_QUEUE_H
