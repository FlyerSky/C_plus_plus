#pragma once

#ifndef THREADPOOL_THREAD_H
#define THREADPOOL_THREAD_H

#include "Logging.h"
#include "NonCopyable.h"

namespace threadpool {

class IThread: NonCopyable{
public:
	IThread() : isStarted(false), isJoined(false) {}

	virtual ~IThread()
	{
		if (isStarted && !isJoined)
		{
			XCHECK(!pthread_detach(m_thread));
		}
	}

	virtual void Run() = 0;

	void Start()
	{
		XCHECK(!isStarted);
		XCHECK(!pthread_create(&m_thread, NULL, work, this));
		isStarted = true;
	}

	void Join()
	{
		XCHECK(!isJoined);
		XCHECK(!pthread_join(m_thread, NULL));
		isJoined = true;
	}

private:
	static void* work(void* data)
	{
		IThread* ptr = (IThread*)data;
		ptr->Run();
		return NULL;
	}

private:
	pthread_t m_thread;
	bool isStarted;
	bool isJoined;
}; // class IThread

} // namespace threadpool

#endif // THREADPOOL_THREAD_H