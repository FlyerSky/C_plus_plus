#pragma once

#ifndef THREADPOOL_BOUNDED_BLOCKING_QUEUE_H
#define THREADPOOL_BOUNDED_BLOCKING_QUEUE_H

#include "BoundedQueue.h"

namespace threadpool {

template<typename T>
class BoundedBlockingQueue : NonCopyable {
public:
	explicit BoundedBlockingQueue(size_t maxSize);
	void Push(const T& x);
	T Pop();
	bool Empty() const;
	bool Full() const;
	size_t size() const;
	size_t capacity() const;

private:
	mutable MutexLock	m_mutex;
	Condition			m_notEmpty;
	Condition			m_notFull;
	BoundedQueue<T>		m_queue;

}; // class BoundedBlockingQueue

} // namespace threadpool

#endif // THREADPOOL_BOUNDED_BLOCKING_QUEUE_H