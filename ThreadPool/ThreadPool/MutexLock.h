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
	// C++�е�explicit�ؼ���ֻ����������ֻ��һ���������๹�캯��,���������Ǳ����ù��캯������ʾ��,ȡ����ʽת����
	// ��ʱ CLASS object = 10; ����ͨ����ʽת�����ù��캯�� explicit CLASS(int para); 
	// �������Ӧ����һ���ؼ�����implicit,��˼�����ص�,�๹�캯��Ĭ������¼�����Ϊimplicit(��ʽ).

private:
	MutexLock& m_mutex;
}; // class MutexLockGuard

#define MutexLockGuard(x) XCHECK(false);

} // namespace threadpool

#endif // THREADPOOL_MUTEX_LOCK_H