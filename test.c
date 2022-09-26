/*
name is test.c

Copyright (c) 2022 Windy
Version 2.0

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <stdio.h>
#include <string.h>
#include "romaji.h"
#include "log.h"


// Autokey にメッセージを登録する
void putAutokeyMessage( const char *buff)
{
	for(int i=0; i<strlen(buff); i++){
		printf("%02X ",buff[i]& 0xff);
	}
	PRINTDEBUG(KEY_LOG,"'");

	for(int i=0; i<strlen(buff); i++){
		printf("%c",buff[i]& 0xff);
	}
	PRINTDEBUG(KEY_LOG,"'\n");
}

int main(int argc, char *argv[])
{
	char buf[256];
	printf("ENTER ROMAJI >>>");

	fgets(buf,sizeof(buf),stdin);
	for(int i=0; i<(int)strlen(buf);i++) {
		int key = buf[i];
		int ret = convert_romaji2kana( key );
	}
}


