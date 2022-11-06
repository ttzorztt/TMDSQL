main: main.o file.o DataBase.o dir.o
	g++ main.o file.o DataBase.o dir.o -o main
	./main
	# make clean
main.o: main.cpp
	g++ -c main.cpp
file.o: file.cpp
	g++ -c file.cpp
DateBase.o: DataBase.cpp
	g++ -c DataBase.cpp
dir.o: dir.cpp
	g++ -c dir.cpp
clean:
	mv *.o /tmp