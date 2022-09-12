#include <stdio.h>

#define KEY_LOG 1

#ifdef KEY_LOG
#define PRINTDEBUG(flag,...) if(flag) fprintf(stdout, __VA_ARGS__);
#else
#define PRINTDEBUG(flag,...)
#endif
