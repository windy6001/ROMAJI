CC=gcc
CC=cl.exe


test : test.c romaji.c log.h keys.h
	$(CC) -o test test.c romaji.c  conv.c 
clean: 
	rm *.o
	rm *.obj
	rm *.exe
