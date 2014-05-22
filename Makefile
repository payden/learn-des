all:
	gcc -g -O2 -Wall  -c util.c
	gcc -g -O2 -Wall  -c test.c
	gcc -g -O2 -Wall  -o test test.o util.o
clean:
	rm -f *.o test
