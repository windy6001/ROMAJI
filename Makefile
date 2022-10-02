CC=g++


test : test.cpp romaji.cpp log.h keys.h
	$(CC) -o test test.cpp romaji.cpp
clean: 
	rm *.o
	rm test
