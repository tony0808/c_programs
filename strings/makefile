string: main.o string.o
	gcc main.o string.o -o string

main.o: main.c string.h
	gcc -c main.c -o main.o

string.o: string.c string.h
	gcc -c string.c -o string.o

clean:
	rm -f *.o string