#pragma once

#ifndef THREADPOOL_BLOCKINGQUEUE_H
#define THREADPOOL_BLOCKINGQUEUE_H

#include <queue>
#include "Condition.h"

namespace threadpool {

template<class T>
class BlockingQueue : NonCopyable {
public:
	BlockingQueue();
	void Push(const T& x);
	T Pop();
	size_t Size() const;
	bool Empty() const;

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