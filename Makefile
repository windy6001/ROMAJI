test : test.c romaji.c log.h keys.h
	gcc -o test test.c romaji.c  conv.c 
clean: 
	rm *.o

