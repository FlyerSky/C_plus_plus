#ifndef THREADPOOL_NONCOPYABLE_H
#define THREADPOOL_NONCOPYABLE_H

namespace threadpool {

class NonCopyable {
protected:
	NonCopyable() {}
	~NonCopyable() {}

private:
	NonCopyable(const NonCopyable& );
	const NonCopyable& operator=(const NonCopyable& );
}; // class NonCopyable

} // namespace threadpool

#endif // THREADPOOL_NONCOPYABLE_H
