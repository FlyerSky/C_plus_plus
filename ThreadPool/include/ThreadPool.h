#pragma once

#ifndef THREADPOOL_THREAD_POOL_H
#define THREADPOOL_THREAD_POOL_H

#include "Thread.h"
#include "BlockingQueue.h"
#include "BoundedBlockingQueue.h"
#include "Closure.h"

namespace threadpool {

class ThreadPool : NonCopyable {
public:
	ThreadPool(size_t thread_num);
	~ThreadPool();

	void Start();
	void Stop();
	void Add(ClosureInterface* task);
	
private:
	friend class Worker;
	vector<IThread*> m_vThreads;
	BoundedBlockingQueue<ClosureInterface*> m_bQueue;
};  // class ThreadPool


class Worker : public IThread {
public:
	Worker(ThreadPool* pool);
	virtual ~Worker();

	virtual void Run();

private:
	ThreadPool* m_pthreadPool;
};  // class Worker

} // namespace threadpool

#endif
