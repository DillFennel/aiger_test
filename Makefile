all: main

main: aiger.o func.o
	gcc aiger.o func.o -o main.out

func.o:
	g++ -c func.cpp -o func.o

aiger.o:
	gcc -c aiger.c -o aiger.o

clean:
	rm -rf *.o *.gch main