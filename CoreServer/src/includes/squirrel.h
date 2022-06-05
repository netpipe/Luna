#ifdef SQUIRREL
#ifndef H_SQUIRREL
#define H_SQUIRREL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#include <conio.h>
#endif

#include "squirrel.h"
#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdaux.h>


#ifdef SQUNICODE
#define scfprintf fwprintf
#define scfopen	_wfopen
#define scvprintf vfwprintf
#else
#define scfprintf fprintf
#define scfopen	fopen
#define scvprintf vfprintf
#endif



class Squirrel
{
    Squirrel();
    ~Squirrel();
    public:
    void PrintUsage();
    void PrintVersionInfos();
    SQInteger quit();

    void call_foo(HSQUIRRELVM v, int n,float f,const SQChar *s);

    int getargs();
    int LoadFile(char *filename);
    int Write(char *arg);
    void Interactive( );

	char* argv;

int do_main( );
const SQChar *filename;
};
#endif // SQUIRREL
#endif
