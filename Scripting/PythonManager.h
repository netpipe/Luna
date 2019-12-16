#ifdef PYTHON
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
//#define LONG_BIT = 4 * SIZEOF_LONG

#include <irrlicht.h>
using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace gui;
using namespace scene;
using namespace io;

#include <Python.h> // fix later -has to be in this order or the formationwrapper complains
#include "../Scene/Formation.h"
#include "./PyFunctions.h"
#include "../Scene/RainMan.h"



PyMODINIT_FUNC Python::init_irr(void){
	/*Note the return type of the function, which is PyMODINIT_FUNC, its
	actually more of a macro than a datatype(I think). Anyway, its essential to
	have this as the return type of a function that initializes a python module*/

///#ifdef EXTRAS
    Py_InitModule("extras",irr_Extras);
///#endif
 //   Py_InitModule("particles",irr_SPARKA);
	Py_InitModule("physics",irr_Physics);
    Py_InitModule("scene",irr_Scene);
	Py_InitModule("scene",irr_Camera);
    Py_InitModule("net",irr_Network);
	Py_InitModule("math",irr_Math);
	Py_InitModule("sound",irr_Sound);
    Py_InitModule("irr",irr_function);
	Py_InitModule("gui",irr_gui);
    Py_InitModule("scene",irr_FlagMan);
    Py_InitModule("input",irr_Input);
	Py_InitModule("image",irr_Image);
};

void Python::ExecuteScript(irr::core::string<char> scriptname){
	/*Using it this way
	because the methods using the FILE * structure tend to go wonky
	  due to the fact that the FILE * datatype is not standardized, so you'll get problems
	  if you try to use it with a different version other than the one your Python build was
	  compiled with. Our solution looks kludgy but it works pretty well.*/
	irr::core::string<char> result;
	result = irr::core::string<char>("execfile('");
	result.append(scriptname);
	result.append("')");
	PyRun_SimpleString(result.c_str());
	/*This function was pretty annoying to write. The errors I kept on getting were textbook
	examples on why namespaces were important...seriously.It kept on confusing std::string
	with irr::core::string, but as you can see, I solved that problem by explicitly stating
	the namespace in which the string class I wanted was to be found*/
};

#endif
