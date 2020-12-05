all: testPhaseOne.exe

testPhaseOne.o: testPhaseOne.cpp LinkedNodeClass.inl LinkedNodeClass.h \
                SortedListClass.inl SortedListClass.h
	g++ -c testPhaseOne.cpp -o testPhaseOne.o

testPhaseOne.exe: testPhaseOne.o
	g++ testPhaseOne.o -o testPhaseOne.exe

clean:
	rm -rf testPhaseOne.o testPhaseOne.exe