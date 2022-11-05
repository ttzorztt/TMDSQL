main: main.o file.o DataBase.o 
	g++ main.o file.o DataBase.o -o main
	./main
	# make clean
main.o: main.cpp
	g++ -c main.cpp
file.o: file.cpp
	g++ -c file.cpp
DateBase.o: DataBase.cpp
	g++ -c DataBase.cpp
clean:
	mv *.o /tmp