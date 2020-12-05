all: testPhaseOne.exe

testPhaseOne.o: testPhaseOne.cpp LinkedNodeClass.inl LinkedNodeClass.h \
                SortedListClass.inl SortedListClass.h \
                FIFOQueueClass.inl FIFOQueueClass.h \
                EventClass.h
	g++ -c testPhaseOne.cpp -o testPhaseOne.o

EventClass.o: EventClass.cpp EventClass.h
	g++ -c EventClass.cpp -o EventClass.o

testPhaseOne.exe: testPhaseOne.o EventClass.o
	g++ testPhaseOne.o EventClass.o -o testPhaseOne.exe

clean:
	rm -rf testPhaseOne.o EventClass.o testPhaseOne.exe