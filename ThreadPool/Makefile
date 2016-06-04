objects = Thread.o ThreadPool.o ThreadPool_Demo.o

demo : $(objects)
	g++ -o demo $(objects) -std=c++11 -lpthread
	./demo

ThreadPool_Demo.o : include/ThreadPool.h include/StdExtension.h
	g++ -c ThreadPool_Demo.cpp

ThreadPool.o : include/ThreadPool.h include/Thread.h include/BlockingQueue.h \
include/BoundedBlockingQueue.h include/Closure.h include/BoundedQueue.h
	g++ -c include/ThreadPool.cpp

Thread.o : include "Logging.h" include "NonCopyable.h"
	g++ -c include/Thread.c
	
clean:
	rm -rf *.o demo
