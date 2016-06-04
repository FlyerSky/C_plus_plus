#pragma once

#ifndef THREADPOOL_THREAD_H
#define THREADPOOL_THREAD_H

#include "Logging.h"
#include "NonCopyable.h"

namespace threadpool {

class IThread: NonCopyable{
public:
	IThread();
	virtual ~IThread();

	virtual void Run() = 0;
	void Start();
	void Join();

private:
	static void* work(void* data);

private:
	pthread_t m_thread;
	bool isStarted;
	bool isJoined;
}; // class IThread


class Worker : public IThread {
public:
	Worker(ThreadPool* pool);
	virtual ~Worker();

	virtual void Run();

private:
	ThreadPool* m_pthreadPool;
};  // class Worker


} // namespace threadpool

#endif // THREADPOOL_THREAD_H