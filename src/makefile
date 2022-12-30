TMDSQL: mainl.o filel.o DataBasel.o dirl.o Tablel.o superl.o Lockl.o Indexl.o TablePCBl.o shelll.o Userl.o menuOutputl.o TMDSQL.exe
	g++ -static mainl.o filel.o DataBasel.o dirl.o Tablel.o superl.o Lockl.o Indexl.o TablePCBl.o  shelll.o Userl.o menuOutputl.o -o TMDSQL
	./TMDSQL
TMDSQL.exe: mainw.o filew.o DataBasew.o dirw.o Tablew.o superw.o Lockw.o Indexw.o TablePCBw.o shellw.o Userw.o menuOutputw.o
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK mainw.o filew.o DataBasew.o dirw.o Tablew.o superw.o Lockw.o Indexw.o TablePCBw.o shellw.o Userw.o menuOutputw.o -o TMDSQL.exe
	# wine TMDSQL.exe
menuOutputl.o: menuOutput.cpp
	g++ -static -c menuOutput.cpp -o menuOutputl.o
menuOutputw.o: menuOutput.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c menuOutput.cpp -o menuOutputw.o
Userl.o: User.cpp
	g++ -static -c User.cpp -o Userl.o
Userw.o: User.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c User.cpp -o Userw.o
TablePCBl.o: TablePCB.cpp
	g++ -static -c TablePCB.cpp -o TablePCBl.o
TablePCBw.o: TablePCB.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c TablePCB.cpp -o TablePCBw.o
Indexl.o: Index.cpp
	g++ -static -c Index.cpp -o Indexl.o
Indexw.o: Index.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c Index.cpp -o Indexw.o
Lockl.o: Lock.cpp
	g++ -static -c Lock.cpp -o Lockl.o
Lockw.o: Lock.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c Lock.cpp -o Lockw.o
superl.o: super.cpp
	g++ -static -c super.cpp -o superl.o
superw.o: super.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c super.cpp -o superw.o
Tablel.o: Table.cpp
	g++ -static -c Table.cpp -o Tablel.o
Tablew.o: Table.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c Table.cpp -o Tablew.o
mainl.o: main.cpp
	g++ -static -c main.cpp -o mainl.o
mainw.o: main.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c main.cpp -o mainw.o
filel.o: file.cpp
	g++ -static -c file.cpp -o filel.o
filew.o: file.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c file.cpp -o filew.o
DataBasel.o: DataBase.cpp
	g++ -static -c DataBase.cpp -o DataBasel.o
DataBasew.o: DataBase.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c DataBase.cpp -o DataBasew.o
dirl.o: dir.cpp
	g++ -static -c dir.cpp -o dirl.o
dirw.o: dir.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c dir.cpp -o dirw.o
shelll.o: shell.cpp
	g++ -static -c shell.cpp -o shelll.o
shellw.o: shell.cpp
	x86_64-w64-mingw32-g++ -static -finput-charset=UTF-8 -fexec-charset=GBK -c shell.cpp -o shellw.o
clean:
	@mv *.o /tmp