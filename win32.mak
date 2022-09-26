# 1. open Developer Command line
# 2. nmake -f win32.mak

CC=cl


test : test.c romaji.c log.h keys.h
	$(CC) /utf-8 test.c romaji.c
clean: 
	del *.obj
	del test.exe
