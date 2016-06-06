/*
void Squirrel::PrintUsage()
{
	scfprintf(stderr,_SC("usage: sq <options> <scriptpath [args]>.\n")
		_SC("Available options are:\n")
		_SC("   -c              compiles the file to bytecode(default output 'out.cnut')\n")
		_SC("   -o              specifies output file for the -c option\n")
		_SC("   -c              compiles only\n")
		_SC("   -d              generates debug infos\n")
		_SC("   -v              displays version infos\n")
		_SC("   -h              prints help\n"));
}

#define _INTERACTIVE 0
#define _DONE 2
*/
#include "includes/squirrel.h"
HSQUIRRELVM v; // i put this here because in the class it causes problems


#define _DONE 2



#if defined(_MSC_VER) && defined(_DEBUG)
int MemAllocHook( int allocType, void *userData, size_t size, int blockType,
   long requestNumber, const unsigned char *filename, int lineNumber)
{
//	if(requestNumber==585)_asm int 3;
	return 1;
}
#endif

void Squirrel::PrintVersionInfos()
{
	scfprintf(stdout,_SC("%s %s (%d bits)\n"),SQUIRREL_VERSION,SQUIRREL_COPYRIGHT,sizeof(SQInteger)*8);
}


SQInteger Squirrel::quit()
{
	int *done;
	sq_getuserpointer(v,-1,(SQUserPointer*)&done);
	*done=1;
	return 0;
}

void printfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);
	scvprintf(stdout, s, vl);
	va_end(vl);
}

void errorfunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);
	scvprintf(stderr, s, vl);
	va_end(vl);
}



int Squirrel::Write(char *arg){
	char * output = NULL;
			const SQChar *filename=NULL;
#ifdef SQUNICODE
			mbstowcs(temp,argv[arg],strlen(argv[arg]));
			filename=temp;
#else
			filename=argv;
#endif

			arg++;

			//sq_pushstring(v,_SC("ARGS"),-1);
			//sq_newarray(v,0);

			//sq_createslot(v,-3);
			//sq_pop(v,1);
			if(1) {
				if(SQ_SUCCEEDED(sqstd_loadfile(v,filename,SQTrue))){
					SQChar *outfile = _SC("out.cnut");
					if(output) {
#ifdef SQUNICODE
						int len = (int)(strlen(output)+1);
						mbstowcs(sq_getscratchpad(v,len*sizeof(SQChar)),output,len);
						outfile = sq_getscratchpad(v,-1);
#else
						outfile = output;
#endif
					}
					if(SQ_SUCCEEDED(sqstd_writeclosuretofile(v,outfile)))
						return _DONE;
				}
			}
}


int Squirrel::LoadFile(char *filename){
				if(SQ_SUCCEEDED(sqstd_dofile(v, filename, SQFalse, SQTrue))) {

                    call_foo(v,1,2.5,_SC("teststring"));

                sq_pop(v,1); //pops the root table
                sq_close(v);
					return _DONE;
				}
				/*
				if(SQ_SUCCEEDED(sqstd_loadfile(v,filename,SQTrue))) {
					int callargs = 1;
					sq_pushroottable(v);
					//for(int i=arg;i<argc;i++)
					//{
						const SQChar *a;
#ifdef SQUNICODE
						int alen=(int)strlen(filename);
						a=sq_getscratchpad(v,(ipad(v,-1),filename,alen);
						sq_getscratchpad(vnt)(alen*sizeof(SQChar)));
						mbstowcs(sq_getscratch,-1)[alen] = _SC('\0');
#else
						a=filename;
#endif
						sq_pushstring(v,a,-1);
						callargs++;
						//sq_arrayappend(v,-2);
					//}
					sq_call(v,callargs,SQFalse,SQTrue);
					return _DONE;
				}
				*/
}


void Squirrel::call_foo(HSQUIRRELVM v, int n,float f,const SQChar *s)
{
	SQInteger top = sq_gettop(v); //saves the stack size before the call
	sq_pushroottable(v); //pushes the global table
	sq_pushstring(v,_SC("foo"),-1);
	if(SQ_SUCCEEDED(sq_get(v,-2))) { //gets the field 'foo' from the global table
		sq_pushroottable(v); //push the 'this' (in this case is the global table)
		sq_pushinteger(v,n);
		sq_pushfloat(v,f);
		sq_pushstring(v,s,-1);
		sq_call(v,4,SQFalse,SQTrue); //calls the function
	}
	sq_settop(v,top); //restores the original stack size
}




int Squirrel::do_main()
{


	const SQChar *filename=NULL;
#if defined(_MSC_VER) && defined(_DEBUG)
	_CrtSetAllocHook(MemAllocHook);
#endif

	v=sq_open(1024);
    sqstd_seterrorhandlers(v); //registers the default error handlers

	sq_setprintfunc(v,printfunc,printfunc);

	sq_pushroottable(v);

	sqstd_register_bloblib(v);
	sqstd_register_iolib(v);
	sqstd_register_systemlib(v);
	sqstd_register_mathlib(v);
	sqstd_register_stringlib(v);

	//aux library
	//sets error handlers
	sqstd_seterrorhandlers(v);

//Do Squirrel Functions and calls here
	//	Interactive();


#if defined(_MSC_VER) && defined(_DEBUG)
	_getch();
	_CrtMemDumpAllObjectsSince( NULL );
#endif
	return 0;
}









/*

void Squirrel::Interactive()
{

#define MAXINPUT 1024
	SQChar buffer[MAXINPUT];
	SQInteger blocks =0;
	SQInteger string=0;
	SQInteger retval=0;
	SQInteger done=0;
	PrintVersionInfos();

	sq_pushroottable(v);
	sq_pushstring(v,_SC("quit"),-1);
	sq_pushuserpointer(v,&done);
//	sq_newclosure(v,quit,1);
	sq_setparamscheck(v,1,NULL);
	sq_createslot(v,-3);
	sq_pop(v,1);

    while (!done)
	{
		SQInteger i = 0;
		scprintf(_SC("\nsq>"));
		for(;;) {
			int c;
			if(done)return;
			c = getchar();
			if (c == _SC('\n')) {
				if (i>0 && buffer[i-1] == _SC('\\'))
				{
					buffer[i-1] = _SC('\n');
				}
				else if(blocks==0)break;
				buffer[i++] = _SC('\n');
			}
			else if (c==_SC('}')) {blocks--; buffer[i++] = (SQChar)c;}
			else if(c==_SC('{') && !string){
					blocks++;
					buffer[i++] = (SQChar)c;
			}
			else if(c==_SC('"') || c==_SC('\'')){
					string=!string;
					buffer[i++] = (SQChar)c;
			}
			else if (i >= MAXINPUT-1) {
				scfprintf(stderr, _SC("sq : input line too long\n"));
				break;
			}
			else{
				buffer[i++] = (SQChar)c;
			}
		}
		buffer[i] = _SC('\0');

		if(buffer[0]==_SC('=')){
			scsprintf(sq_getscratchpad(v,MAXINPUT),_SC("return (%s)"),&buffer[1]);
			memcpy(buffer,sq_getscratchpad(v,-1),(scstrlen(sq_getscratchpad(v,-1))+1)*sizeof(SQChar));
			retval=1;
		}
		i=scstrlen(buffer);
		if(i>0){
			SQInteger oldtop=sq_gettop(v);
			if(SQ_SUCCEEDED(sq_compilebuffer(v,buffer,i,_SC("interactive console"),SQTrue))){
				sq_pushroottable(v);
				if(SQ_SUCCEEDED(sq_call(v,1,retval,SQTrue)) &&	retval){
					scprintf(_SC("\n"));
					sq_pushroottable(v);
					sq_pushstring(v,_SC("print"),-1);
					sq_get(v,-2);
					sq_pushroottable(v);
					sq_push(v,-4);
					sq_call(v,2,SQFalse,SQTrue);
					retval=0;
					scprintf(_SC("\n"));
				}
			}

			sq_settop(v,oldtop);
		}
	}
}
*/
