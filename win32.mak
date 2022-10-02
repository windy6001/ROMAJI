# 1. open Developer Command line
# 2. nmake -f win32.mak

CC=cl


test : test.cpp romaji.cpp log.h keys.h
	$(CC) /utf-8 test.cpp romaji.cpp
clean: 
	del *.obj
	del test.exe
