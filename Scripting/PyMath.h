#include "../config.h"
#ifdef PYTHON

PyMethodDef irr_Math[] =
{
    {"calculate",Python::PyIrr_calcMath,METH_VARARGS,"calculate"},
    {"rand",Python::PyIrr_Rand,METH_VARARGS,"calculate"},



	{NULL,NULL,0,NULL}
};



PyObject * Python::PyIrr_calcMath(PyObject * self,PyObject * args){

    s32 tex_id,node_id;
	PyArg_ParseTuple(args,"II",&node_id,&tex_id);
	#ifdef SCALC
    SCalcExpr *calc = new SCalcExpr();

	// try to parse the string
	if (!calc->readExpr("min(clamp(PI*2.5*round(3.9)/PI,1,2), 3)"))
	{
			// readExpr() will show a detailed error message
			printf("Invalid expression!\n");
			return(0);
	}

	f32 f;
	// Calculate the result
	if (!calc->calcExpr(NULL, f))
	{
			// calcExpr() will show a detailed error message
			printf("can't calculate expression\n");
			return(0);
	}

	delete calc;

	printf("Result = %0.3f\n", f);
#endif
	return Py_BuildValue("");
}

//rand function

PyObject * Python::PyIrr_Rand(PyObject * self,PyObject * args){
    int x,y;
	//PyArg_ParseTuple(args,"ff",&x,&y);
	//srand(x);
	return Py_BuildValue("i",rand());
}

#endif
