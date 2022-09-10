shell: main.o shell.o parser.o
	gcc main.o shell.o parser.o -o shell

main.o: main.c shell.h
	gcc -c  main.c -o main.o

shell.o: shell.c shell.h
	gcc -c shell.c -o shell.o

parser.o: parser.c shell.h parser.h
	gcc -c parser.c -o parser.o

clean:
	rm *.o shell