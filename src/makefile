main: main.o file.o DateBase.o 
	g++ main.o file.o DateBase.o -o main
	# make clean
main.o: main.cpp
	g++ -c main.cpp
file.o: file.cpp
	g++ -c file.cpp
DateBase.o: DateBase.cpp
	g++ -c DateBase.cpp
clean:
	mv *.o /tmp