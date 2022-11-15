main: main.o file.o DataBase.o dir.o Table.o super.o Lock.o Index.o
	g++ main.o file.o DataBase.o dir.o Table.o super.o Lock.o Index.o -o main
	./main
Index.o: Index.cpp
	g++ -c Index.cpp
Lock.o: Lock.cpp
	g++ -c Lock.cpp
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