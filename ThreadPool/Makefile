objects = ThreadPool.o ThreadPool_Demo.o

demo : $(objects)
	g++ -o demo $(objects) -std=c++11 -lpthread

ThreadPool_Demo.o : include/ThreadPool.h include/StdExtension.h
	g++ -c ThreadPool_Demo.cpp

ThreadPool.o : include/ThreadPool.h include/Thread.h include/BlockingQueue.h \
include/BoundedBlockingQueue.h include/Closure.h include/BoundedQueue.h
	g++ -c include/ThreadPool.cpp

clear:
	rm -rf *.o demo
