gift:   gift.o scanner.o
	gcc -Wall -o gift gift.o scanner.o

scanner.o:  scanner.c scanner.h
	gcc -Wall -c scanner.c

gift.o:	gift.c scanner.h
	gcc -Wall -c gift.c


clean:	
	rm -f *.o gift

test:	gift
	cat test.dat | ./gift
