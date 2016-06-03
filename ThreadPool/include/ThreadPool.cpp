#include "ThreadPool.h"

namespace threadpool{

// class ThreadPool implementation

ThreadPool::ThreadPool(size_t thread_num) : m_vThreads(thread_num), m_bQueue(thread_num)
{
	assert(thread_num);
	for (size_t i = 0; i < m_vThreads.size(); ++i)
	{
		m_vThreads[i] = new Worker(this);
	}
}

ThreadPool::~ThreadPool()
{
	Stop();
}

void ThreadPool::Start()
{
	for (size_t i = 0; i < m_vThreads.size(); ++i)
	{
		m_vThreads[i]->Start();
	}
}

void ThreadPool::Stop()
{
	for (size_t i = 0; i < m_vThreads.size(); ++i)
	{
		m_bQueue.Push(NULL);
	}
	for (size_t i = 0; i < m_vThreads.size(); ++i)
	{
		m_vThreads[i]->Join();
		delete m_vThreads[i];
	}
	m_vThreads.clear();
}

void ThreadPool::Add(ClosureInterface* task)
{
	assert(task);
	m_bQueue.Push(task);
}


// class Worker implementation

Worker::Worker(ThreadPool* pool) : m_pthreadPool(pool)
{
	assert(m_pthreadPool);
}

Worker::~Worker()
{
}

void Worker::Run()
{
	while (true)
	{
		ClosureInterface* closure = m_pthreadPool->m_bQueue.Pop();
		if (closure == NULL)
		{
			break;
		}
		try {
			closure->Run();
		}
		catch (std::exception& e) {
			XLOG(ERROR) << e.what();
		}
		catch (...) {
			XLOG(ERROR) << "unknown exception.";
		}
		delete closure;
	}
}

} // namespace threadpool
