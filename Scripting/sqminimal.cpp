// minimalSqPlus.cpp
// A minimal example and an example with a simple class.
// Example for use with the remote debugger is also shown.
// Created 10/08/05, John Schultz
// Free for any use.

#include <stdio.h>
#include <stdarg.h>
#include <sqplus.h>

using namespace SqPlus;

// Define MINIMAL_EXAMPLE for minimal HelloWorld example.
#define MINIMAL_EXAMPLE

// Define USE_REMOTE_DEBUGGER to use the remote debugger. See the example and docs in the sqdbg directory for
// more information.
//#define USE_REMOTE_DEBUGGER // Remote debugger must be started after the program is launched.
#ifdef USE_REMOTE_DEBUGGER
#include "sqrdbg.h"
#endif

// The following pragmas can be used to link the correct library for Debug/Release builds
// without requiring the application to include the associated Squirrel projects.
// (The libraries must be created before compiling this example).
// Set SQ_REL_PATH as needed for your application.

#define SQ_REL_PATH "../"

#ifdef _DEBUG
#pragma comment(lib,SQ_REL_PATH "lib/squirrelD.lib")
#pragma comment(lib,SQ_REL_PATH "lib/sqstdlibD.lib")
#ifdef USE_REMOTE_DEBUGGER
#pragma comment(lib,SQ_REL_PATH "lib/sqdbglibD.lib")
#endif
#pragma comment(lib,SQ_REL_PATH "lib/sqplusD.lib")
#else // Release
#pragma comment(lib,SQ_REL_PATH "lib/squirrel.lib")
#pragma comment(lib,SQ_REL_PATH "lib/sqstdlib.lib")
#ifdef USE_REMOTE_DEBUGGER
#pragma comment(lib,SQ_REL_PATH "lib/sqdbglib.lib")
#endif
#pragma comment(lib,SQ_REL_PATH "lib/sqplus.lib")
#endif

#ifdef USE_REMOTE_DEBUGGER
void printSQDBGError(HSQUIRRELVM v) {
  const SQChar *err;
  sq_getlasterror(v);
  if(SQ_SUCCEEDED(sq_getstring(v,-1,&err))) {
    printf("SQDBG error : %s",err);
  }else {
    printf("SQDBG error",err);
  } // if
  sq_poptop(v);
} // printSQDBGError
#endif

static void printFunc(HSQUIRRELVM v,const SQChar * s,...) {
  static SQChar temp[2048];
  va_list vl;
  va_start(vl,s);
  vsprintf( temp,s,vl);
  puts(temp);
  va_end(vl);
} // printFunc

class MyClass {
public:
  int classVal;
  // See examples in testSqPlus2.cpp for passing arguments to the constructor (including variable arguments).
  MyClass() : classVal(123) {}
  bool process(int iVal,const char * sVal) {
    printf("classVal: %d, iVal: %d, sVal %s\n",classVal,iVal,sVal);
    classVal += iVal;
    return iVal > 1;
  } // process
};

#ifdef MINIMAL_EXAMPLE

int mainw(int argc,char * argv[]) {
  SquirrelVM::Init();
  SquirrelObject helloWorld = SquirrelVM::CompileBuffer("print(\"Hello World\");");
  SquirrelVM::RunScript(helloWorld);
  SquirrelVM::Shutdown();
  printf("Press RETURN to exit.");
  getchar();
} // main

#else

int main(int argc,char * argv[]) {
  SquirrelVM::Init();
  // This example shows how to redirect print output to your own custom
  // print function (the default handler prints to stdout).
  sq_setprintfunc(SquirrelVM::GetVMPtr(),printFunc);

#ifdef USE_REMOTE_DEBUGGER
  HSQREMOTEDBG rdbg = sq_rdbg_init(SquirrelVM::GetVMPtr(),1234,SQTrue);
  if(rdbg) {
    // Enable debug info generation (for the compiler).
    sq_enabledebuginfo(SquirrelVM::GetVMPtr(),SQTrue);
    printf("Waiting for SQDBG connection...");
    // Suspends the app until the debugger client connects.
    if(SQ_SUCCEEDED(sq_rdbg_waitforconnections(rdbg))) {
      printf("SQDBG: connected.\n");
    } // if
  } else {
    printSQDBGError(SquirrelVM::GetVMPtr());
    return 0;
  } // if
#endif

  // See examples in testSqPlus2.cpp for script read-only vars, constants,
  // static/global functions, variable arguments, constructor arguments,
  // passing/returning classes/structs by value or by address, etc.
  SQClassDef<MyClass>("MyClass").
    func(MyClass::process,"process").
    var(&MyClass::classVal,"classVal");

  SquirrelObject helloSqPlus = SquirrelVM::CompileBuffer("\
   local myClass = MyClass();                           \n\
   local rVal = myClass.process(1,\"MyClass1\");        \n\
   print(\"Returned: \"+(rVal ? \"true\" : \"false\")); \n\
   rVal = myClass.process(2,\"MyClass2\");              \n\
   print(\"Returned: \"+(rVal ? \"true\" : \"false\")); \n\
   print(\"classVal: \"+myClass.classVal);              \n\
 ");
  SquirrelVM::RunScript(helloSqPlus);

#ifdef USE_REMOTE_DEBUGGER
  if (rdbg) {
    sq_rdbg_shutdown(rdbg);
  } // if
#endif

  SquirrelVM::Shutdown();

  printf("Press RETURN to exit.");
  getchar();

  return 0;

} // main

#endif

// minimalSqPlus.cpp

