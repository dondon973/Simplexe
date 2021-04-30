

simplexe.o: simplexe.c
	gcc -c simplexe.c -o simplexe.o -Wall -g -pg

main.o: main.c
	gcc -c main.c -o main.o -Wall -g -pg

exec: main.o simplexe.o
	gcc main.o simplexe.o -Wall -g -o exec

clean:
		rm -f *.o
