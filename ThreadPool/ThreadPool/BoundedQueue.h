#pragma once

#ifndef THREADPOOL_BOUNDED_QUEUE_H
#define THREADPOOL_BOUNDED_QUEUE_H

#include <vector>
#include <fstream>
#include <cassert>

namespace threadpool{

using namespace std;

template<class T>
class BoundedQueue {
public:
	explicit BoundedQueue(size_t capacity);
	~BoundedQueue();
	void Clear();
	bool Empty() const;
	bool Full() const;
	size_t Size() const;
	size_t Capacity() const;
	void Push(const T& t);
	T Pop();

private:
	size_t m_head;
	size_t m_tail;
	size_t m_size;
	const size_t m_capacity;
	vector<T> m_circular_buffer;

}; // class BoundedQueue

} // namespace threadpool

#endif // THREADPOOL_BOUNDED_QUEUE_H