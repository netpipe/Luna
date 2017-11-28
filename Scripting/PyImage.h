PyMethodDef irr_Image[] =
{
    {"irotate",Python::PyIrr_iRotate,METH_VARARGS,"PyIrr_iRotate"},
	{"iscale",Python::PyIrr_iScale,METH_VARARGS,"PyIrr_iScale"},
	{"iposition",Python::PyIrr_iPosition,METH_VARARGS,"PyIrr_iPosition"},
	{"iadd",Python::PyIrr_iAdd,METH_VARARGS,"PyIrr_iAdd"},
	{"idraw",Python::PyIrr_iDraw,METH_VARARGS,"PyIrr_iAdd"},
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

PyObject * Python::PyIrr_iDraw(PyObject * self,PyObject * args){
   	long node_id;
   	s32 scene;
	float size;



	//Damn...thats a lot of parameters :)
	PyArg_ParseTuple(args,"l",&node_id);
	cImage* node = node_id;

	node->Draw(smgr);

return Py_BuildValue("");

}

PyObject * Python::PyIrr_iAdd(PyObject * self,PyObject * args){
   //	s32 node_id;
//	float size;
   	float px,py,pz,rx,ry,rz,sx,sy,sz;
	//Damn...thats a lot of parameters :)
	//PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);

core::recti nsize(50,500,50,100);
core::recti textpos(50,500,50,100);

video::ITexture* images = driver->getTexture("./media/axe.jpg");
	//driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));


cImage* aImage = new cImage(images, nsize, textpos);


return Py_BuildValue("l",aImage);

}


