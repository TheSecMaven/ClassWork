words: words.o scanner.o 
	gcc -Wall -o words words.o scanner.o 

scanner.o:  scanner.c scanner.h
	gcc -Wall -c scanner.c


clean:  
	rm -f *.o words

test:   words
	./words
