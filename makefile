all: proj5.exe

CarClass.o: CarClass.cpp CarClass.h
	g++ -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h
	g++ -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp \
    IntersectionSimulationClass.h \
    SortedListClass.inl SortedListClass.h \
    FIFOQueueClass.inl FIFOQueueClass.h \
    EventClass.h CarClass.h
	g++ -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o  

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o 

project5.o: project5.cpp IntersectionSimulationClass.h
	g++ -c project5.cpp -o project5.o

proj5.exe: CarClass.o EventClass.o IntersectionSimulationClass.o \
    random.o project5.o
	g++ CarClass.o EventClass.o IntersectionSimulationClass.o \
      random.o project5.o -o proj5.exe

clean:
	rm -rf project5.o CarClass.o EventClass.o \
         IntersectionSimulationClass.o random.o \
         proj5.exe