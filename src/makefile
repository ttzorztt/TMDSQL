main: main.o file.o DataBase.o dir.o table.o
	g++ main.o file.o DataBase.o dir.o table.o -o main
	./main
table.o: table.cpp
	g++ -c table.cpp
main.o: main.cpp
	g++ -c main.cpp
file.o: file.cpp
	g++ -c file.cpp
DataBase.o: DataBase.cpp
	g++ -c DataBase.cpp
dir.o: dir.cpp
	g++ -c dir.cpp
clean:
	mv *.o /tmp