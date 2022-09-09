shell: main.o shell.o
	gcc main.o shell.o -o shell

main.o: main.c shell.h
	gcc -c  main.c -o main.o

shell.o: shell.c shell.h
	gcc -c shell.c -o shell.o

clean:
	rm *.o shell