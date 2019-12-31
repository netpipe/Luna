PyMethodDef irr_FileIO[] = {
    {"zistream",Python::PyIrr_zistream,METH_VARARGS,"sets camera vector"},
    {"zostream",Python::PyIrr_zostream,METH_VARARGS,"sets camera vector"},
//	{"getCamera",Python::PyIrr_GetCamera,METH_VARARGS,"getcamera vector"},
	{NULL,NULL,0,NULL}
};


PyObject * Python::PyIrr_zistream(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
//	char * t;
	PyArg_ParseTuple(args,"s",&t,&x,&y,&z);
	#ifdef COMPRESS
	//def(stdin, stdout, Z_DEFAULT_COMPRESSION); //for compression
		inf(stdin, stdout)	//zpipe decompression
    #endif
}

PyObject * Python::PyIrr_zostream(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
//	char * t;
	PyArg_ParseTuple(args,"ifff",&t,&x,&y,&z);

}
