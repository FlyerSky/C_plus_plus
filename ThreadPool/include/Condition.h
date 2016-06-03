#pragma once

#ifndef THREADPOOL_CONDITION_H
#define THREADPOOL_CONDITION_H

#include "MutexLock.h"

namespace threadpool {

class Condition : NonCopyable {
public:
	explicit Condition(MutexLock& mutex) : m_mutex(mutex)
	{
		XCHECK(!pthread_cond_init(&m_pCond, NULL));
	}

	~Condition()
	{
		XCHECK(!pthread_cond_destroy(&m_pCond));
	}

	void Wait()
	{
		XCHECK(!pthread_cond_wait(&m_pCond, m_mutex.GetPthreadMutex()));
	}

	void Notify()
	{
		XCHECK(!pthread_cond_signal(&m_pCond));
	}

	void NotifyAll()
	{
		XCHECK(!pthread_cond_broadcast(&m_pCond));
	}

private:
	MutexLock& m_mutex;
	pthread_cond_t m_pCond;
}; // class Condition

} // namespace threadpool

#endif // THREADPOOL_CONDITION_H