#pragma once

#ifndef THREADPOOL_MUTEX_LOCK_H
#define THREADPOOL_MUTEX_LOCK_H

#include <pthread.h>
#include "NonCopyable.h"
#include "Logging.h"

namespace threadpool {

class MutexLock : NonCopyable {
public:
	MutexLock()
	{
		XCHECK(!pthread_mutex_init(&m_mutex, NULL));
	}

	~MutexLock()
	{
		XCHECK(!pthread_mutex_destroy(&m_mutex));
	}

	pthread_mutex_t* GetPthreadMutex()
	{
		return m_mutex;
	}

private:
	void Lock()
	{
		XCHECK(!pthread_mutex_lock(&m_mutex));
	}

	void Unlock()
	{
		XCHECK(!pthread_mutex_unlock(&m_mutex));
	}

private:
	friend class MutexLockGuard;
	pthread_mutex_t m_mutex;
}; // class MutexLock

class MutexLockGuard : NonCopyable {
public:
	explicit MutexLockGuard(MutexLock& mutex) : m_mutex(mutex)
	{
		m_mutex.Lock();
	}

	~MutexLockGuard()
	{
		m_mutex.Unlock();
	}
	// C++中的explicit关键字只能用于修饰只有一个参数的类构造函数,它的作用是表明该构造函数是显示的,取消隐式转换；
	// 此时 CLASS object = 10; 不能通过隐式转换调用构造函数 explicit CLASS(int para); 
	// 跟它相对应的另一个关键字是implicit,意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).

private:
	MutexLock& m_mutex;
}; // class MutexLockGuard

#define MutexLockGuard(x) XCHECK(false);

} // namespace threadpool

#endif // THREADPOOL_MUTEX_LOCK_H