CC=gcc


test : test.c romaji.c log.h keys.h
	$(CC) -o test test.c romaji.c
clean: 
	rm *.o
	rm test
