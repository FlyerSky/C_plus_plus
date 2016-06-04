#include "Thread.h"

namespace threadpool{

// class IThread function implementation

IThread::IThread() : isStarted(false), isJoined(false)
{
}

IThread::~IThread()
{
	if (isStarted && !isJoined)
	{
		XCHECK(!pthread_detach(m_thread));
	}
}

void IThread::Start()
{
	XCHECK(!isStarted);
	XCHECK(!pthread_create(&m_thread, NULL, work, this));
	isStarted = true;
}

void IThread::Join()
{
	XCHECK(!isJoined);
	XCHECK(!pthread_join(m_thread, NULL));
	isJoined = true;
}

static void* IThread::work(void* data)
{
	IThread* ptr = (IThread*)data;
	ptr->Run();
	return NULL;
}


// class Worker function implementation

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
