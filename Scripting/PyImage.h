PyMethodDef irr_Image[] =
{
    {"irotate",Python::PyIrr_iRotate,METH_VARARGS,"PyIrr_iRotate"},
	{"iscale",Python::PyIrr_iScale,METH_VARARGS,"PyIrr_iScale"},
	{"iposition",Python::PyIrr_iPosition,METH_VARARGS,"PyIrr_iPosition"},
	{"iadd",Python::PyIrr_iAdd,METH_VARARGS,"PyIrr_iAdd"},
	{NULL,NULL,0,NULL}
};


PyObject * Python::PyIrr_iRotate(PyObject * self,PyObject * args){
   	s32 node_id;
//	float size;
//   	float px,py,pz,rx,ry,rz,sx,sy,sz;
	//Damn...thats a lot of parameters :)
//	PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);

return Py_BuildValue("l",node_id);

}

PyObject * Python::PyIrr_iScale(PyObject * self,PyObject * args){
   	s32 node_id;
//	float size;
//   	float px,py,pz,rx,ry,rz,sx,sy,sz;
	//Damn...thats a lot of parameters :)
//	PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);

return Py_BuildValue("l",node_id);

}

PyObject * Python::PyIrr_iPosition(PyObject * self,PyObject * args){
   	s32 node_id;
//	float size;
//   	float px,py,pz,rx,ry,rz,sx,sy,sz;
	//Damn...thats a lot of parameters :)
//	PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);

return Py_BuildValue("l",node_id);

}

PyObject * Python::PyIrr_iAdd(PyObject * self,PyObject * args){
   	s32 node_id;
//	float size;
//   	float px,py,pz,rx,ry,rz,sx,sy,sz;
	//Damn...thats a lot of parameters :)
//	PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);

return Py_BuildValue("l",node_id);

}
