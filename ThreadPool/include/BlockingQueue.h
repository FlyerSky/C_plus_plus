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

	// �����ĳ�Ա��������ı�����״̬����ô�����Ա����һ���������const�ġ����ǣ���Щʱ��������Ҫ
	// ��const�ĺ��������޸�һЩ����״̬�޹ص����ݳ�Ա����ô������ݳ�Ա��Ӧ�ñ�mutalbe�����Ρ�
	// mutableҲ��Ϊ��ͻ��const�����ƶ����õġ���mutable���εı���������Զ���ڿɱ��״̬����ʹ��һ��const�����С�

}; // class BlockingQueue

} // namespace threadpool

#endif
