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

void* IThread::work(void* data)
{
	IThread* ptr = (IThread*)data;
	ptr->Run();
	return NULL;
}

} // namespace threadpool
