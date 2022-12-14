/*
name is test.c

Copyright (c) 2022 Windy
Version 2.1

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

int utf8_flag  = 0;

// ****************************************************************************
//   １バイトの半角カタカナを、UTF-8 の半角カタカナに変換する (半角カタカナのみ対応)
// ****************************************************************************
char *toUTF8katakana( unsigned char c)
{
	static char outBuff[256];
	char *p;
	int  utf8;

	memset(outBuff,0,sizeof(outBuff));
	p= outBuff;

	if( 0xa0 <= c && c <=0xbf) {
		utf8 = 0xEFBD00+ c;
	}else if( 0xc0 <= c && c<= 0xdf) {
		utf8 = 0xEFBDC0+ c;
	}

	*p = (utf8>>16)& 0xff; p++;
	*p = (utf8>>8) & 0xff; p++;
	*p = (utf8)    & 0xff; p++;
	*p = 0;
	return outBuff;
}

void putAutokeyMessage( const char *buff)
{
	for(int i=0; i<strlen(buff); i++){
		printf("%02X ",buff[i]& 0xff);
	}
	PRINTDEBUG(KEY_LOG,"'");

	for(int i=0; i<strlen(buff); i++){
		if( !utf8_flag ) {
			printf("%c",buff[i]& 0xff);
		} else {
			printf("%s",toUTF8katakana(buff[i] &0xff));
		}
	}

	PRINTDEBUG(KEY_LOG,"'\n");
}

int main(int argc, char *argv[])
{
	Romaji *romaji = new Romaji();

	char buf[256];
	if( argc >1) {
		if( strcmp(argv[1],"-utf8")==0) {
			utf8_flag =1;
			printf("UTF-8 is ON \n");
		} else {
			printf("UTF-8 is OFF \n");
		}
	}
	printf("ENTER ROMAJI >>>");

	fgets(buf,sizeof(buf),stdin);
	for(int i=0; i<strlen(buf);i++) {
		int key = buf[i];
		int ret = romaji->convertRomaji2kana( key );
		if( ret == HENKAN_SUCCESS ) {
			putAutokeyMessage( romaji->convertKana2Katakana( romaji->getResult()));
		}
	}
}


