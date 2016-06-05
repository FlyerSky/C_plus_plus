objects = Thread.o ThreadPool.o ThreadPool_Demo.o

demo : $(objects)
        g++ -o demo $(objects) -std=c++11 -lpthread
        ./demo

Thread.o : include/Thread.h
	g++ -c Thread.cpp
		
ThreadPool_Demo.o : include/ThreadPool.h include/StdExtension.h
        g++ -c ThreadPool_Demo.cpp

ThreadPool.o : include/ThreadPool.h
        g++ -c include/ThreadPool.cpp

clean:
        rm -rf *.o demo
