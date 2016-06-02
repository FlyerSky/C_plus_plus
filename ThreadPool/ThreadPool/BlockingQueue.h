#pragma once

#ifndef THREADPOOL_BLOCKINGQUEUE_H
#define THREADPOOL_BLOCKINGQUEUE_H

#include <queue>
#include "Condition.h"

namespace threadpool {

template<class T>
class BlockingQueue : NonCopyable {
public:
	BlockingQueue();
	void Push(const T& x);
	T Pop();
	size_t Size() const;
	bool Empty() const;

private:
	mutable MutexLock m_mutex;
	Condition m_notEmpty;
	std::queue<T> m_queue;

	// 如果类的成员函数不会改变对象的状态，那么这个成员函数一般会声明成const的。但是，有些时候，我们需要
	// 在const的函数里面修改一些跟类状态无关的数据成员，那么这个数据成员就应该被mutalbe来修饰。
	// mutable也是为了突破const的限制而设置的。被mutable修饰的变量，将永远处于可变的状态，即使在一个const函数中。

}; // class BlockingQueue

} // namespace threadpool

#endif