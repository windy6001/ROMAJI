#include <stdio.h>
#include <string.h>
#include "romaji.h"
#include "conv.h"
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


