#include "include/ThreadPool.h"
#include "include/StdExtension.h"
#include <unistd.h>

using namespace std;

const size_t THREAD_NUM = 4;

class Foo
{
public:
	void Append(char c)
	{
		threadpool::MutexLockGuard lock(m_mutex);
		str.push_back(c);
		usleep(10 * 1000);
	}

	string GetStr()
	{
		return str;
	}

private:
	string str;
	threadpool::MutexLock m_mutex;
};

void DemoFunction()
{
	Foo foo;
	cout << foo.GetStr() << endl;
	
	threadpool::ThreadPool thread_pool(THREAD_NUM);
	thread_pool.Start();
	for (size_t i = 0; i < 26; i++)
	{
		char c = i % 10 + '0';
		thread_pool.Add(threadpool::NewClosure(&foo, &Foo::Append, c));
	}
	thread_pool.Stop();
	cout << foo.GetStr() << endl;
}

int main()
{
	DemoFunction();
	return 0;
}
