main: main.o file.o DataBase.o dir.o Table.o super.o
	g++ main.o file.o DataBase.o dir.o Table.o super.o -o main
	./main
super.o: super.cpp
	g++ -c super.cpp
Table.o: Table.cpp
	g++ -c Table.cpp
main.o: main.cpp
	g++ -c main.cpp
file.o: file.cpp
	g++ -c file.cpp
DataBase.o: DataBase.cpp
	g++ -c DataBase.cpp
dir.o: dir.cpp
	g++ -c dir.cpp
clean:
	@mv *.o /tmp