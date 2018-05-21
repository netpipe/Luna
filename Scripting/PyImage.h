PyMethodDef irr_Image[] =
{
    {"irotate",Python::PyIrr_iRotate,METH_VARARGS,"PyIrr_iRotate"},
	{"iscale",Python::PyIrr_iScale,METH_VARARGS,"PyIrr_iScale"},
	{"iposition",Python::PyIrr_iPosition,METH_VARARGS,"PyIrr_iPosition"},
	{"iadd",Python::PyIrr_iAdd,METH_VARARGS,"PyIrr_iAdd"},
	{"idraw",Python::PyIrr_iDraw,METH_VARARGS,"PyIrr_iAdd"},
	{"ialpha",Python::PyIrr_iAlpha,METH_VARARGS,"ialpha"},
	{"itexture",Python::PyIrr_iTexture,METH_VARARGS,"itexture"},
	{NULL,NULL,0,NULL}
};


PyObject * Python::PyIrr_iRotate(PyObject * self,PyObject * args){
   	long node_id;
	float rot;

	PyArg_ParseTuple(args,"lf",&node_id,&rot);
	cImage* node = node_id;

	node->SetRotation(rot);
     //   irr::f32 GetRotation() { return Rotation; };
return Py_BuildValue("l",node_id);

}

PyObject * Python::PyIrr_iScale(PyObject * self,PyObject * args){
   	long node_id;
   	float X,Y;
//	float size;
	PyArg_ParseTuple(args,"lff",&node_id,&X,&Y);
	cImage* node = node_id;
	irr::core::vector2df news;
	news.X=(X*-1);
	news.Y=(Y*-1); // not sure why but had to invert values

	node->SetScale(news);


return Py_BuildValue("");

}

PyObject * Python::PyIrr_iPosition(PyObject * self,PyObject * args){
   	long node_id;
   	float X,Y;
//	float size;
	PyArg_ParseTuple(args,"lff",&node_id,&X,&Y);
	cImage* node = node_id;

irr::core::position2di newpos;
newpos.X=X;
newpos.Y=Y;
node->SetPosition(newpos);
return Py_BuildValue("");

}

PyObject * Python::PyIrr_iDraw(PyObject * self,PyObject * args){
   	long node_id;
//draw all in vector image stack

	PyArg_ParseTuple(args,"l",&node_id);
	cImage* node = node_id;

	node->Draw(smgr);

return Py_BuildValue("");

}

PyObject * Python::PyIrr_iAdd(PyObject * self,PyObject * args){
   //	s32 node_id;
//	float size;
//bImage2d =1;
	char * texture;
   	float x1,y1,x2,y2,xx1,yy1,xx2,yy2;
	//Damn...thats a lot of parameters :)
	PyArg_ParseTuple(args,"sffffffff",&texture,&x1,&y1,&x2,&y2,&xx1,&yy1,&xx2,&yy2);

core::recti nsize(x1,y1,x2,y2);
core::recti textpos(xx1,yy1,xx2,yy2);

video::ITexture* images = driver->getTexture(texture);
	//driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));


cImage* aImage = new cImage(images, nsize, textpos);


return Py_BuildValue("l",aImage);

}

PyObject * Python::PyIrr_iTexture(PyObject * self,PyObject * args){
   	long node_id;
   	char *texture;
   	int type;

	PyArg_ParseTuple(args,"lsi",&node_id,&texture,&type);
	cImage* node = node_id;
	video::ITexture* images = driver->getTexture(texture);

//return Py_BuildValue("l",images);

	node->SetTexture(images);
	return Py_BuildValue("l",images);
}

PyObject * Python::PyIrr_iAlpha(PyObject * self,PyObject * args){
   	long node_id;
//draw all in vector image stack

	//Damn...thats a lot of parameters :)
	PyArg_ParseTuple(args,"l",&node_id);
	cImage* node = node_id;

	node->Draw(smgr);
}
