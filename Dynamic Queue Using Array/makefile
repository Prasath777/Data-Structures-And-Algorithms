
all:	x

x:	Queue.o test_queue2.o
	g++ -o x Queue.o test_queue2.o

Queue.o:	Queue.cpp Queue.h
	g++ -c Queue.cpp

test_queue2.o:	test_queue2.cpp Queue.h
	g++ -c test_queue2.cpp

clean:	
	rm -f x *.o

