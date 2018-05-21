PyMethodDef irr_Image[] =
{
    {"irotate",Python::PyIrr_iRotate,METH_VARARGS,"PyIrr_iRotate"},
	{"iscale",Python::PyIrr_iScale,METH_VARARGS,"PyIrr_iScale"},
	{"iposition",Python::PyIrr_iPosition,METH_VARARGS,"PyIrr_iPosition"},
	{"iadd",Python::PyIrr_iAdd,METH_VARARGS,"PyIrr_iAdd"},
	{"idraw",Python::PyIrr_iDraw,METH_VARARGS,"PyIrr_iAdd"},
	{"ialpha",Python::PyIrr_iAlpha,METH_VARARGS,"ialpha"},
	{"itexture",Python::PyIrr_iTexture,METH_VARARGS,"itexture"},
	{"image2d",Python::PyIrr_2Dimage,METH_VARARGS,"PyIrr_2Dimage"},
	{"set_texture",Python::PyIrr_SetTexture,METH_VARARGS,"Adds a texture to a scene node"},
	{"abb",Python::PyIrr_aBillBoard,METH_VARARGS,"billboard"},
	{"load_texture",Python::PyIrr_LoadTexture,METH_VARARGS,"Loads a texture"},
	{"set_texture",Python::PyIrr_SetTexture,METH_VARARGS,"Adds a texture to a scene node"},

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
//midpoint

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


PyObject * Python::PyIrr_2Dimage(PyObject * self,PyObject * args) {//active camera
    #ifdef Image2D
    bImage2d=1;
        //cImage*
        image = new cImage(driver->getTexture("data/sydney.bmp"),
                                    rect<s32>(0,256,512,512),rect<s32>(0,0,512,256));
       // image->SetTransparent(true);
      //  image->SetTransparentColor(SColor(0,255,0,255),driver);
      //  image->SetBilinearFilter(true);

//      draw2DImage ( const video::ITexture * texture,
//const core::rect< s32 > & destRect,
//const core::rect< s32 > & sourceRect,
//const core::rect< s32 > * clipRect = 0,
//const video::SColor *const colors = 0,
//bool useAlphaChannelOfTexture = false
//)

    #endif
//        sprites->clear();
//
//        // add sprite from tile (0,0) size(8,8)
//        Sprite *spr = sprites->addSprite(0,0,8,8);
//        spr->setPosition(20, 20);
//        spr->setScale(4.0f, 4.0f);


	return Py_BuildValue("");
}

PyObject * Python::PyIrr_aBillBoard(PyObject * self,PyObject * args) {

	char * tex_name;
	PyArg_ParseTuple(args,"s",&tex_name);

   scene::ISceneManager* smgr = device->getSceneManager();

    scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
    bill->setPosition(core::vector3df(0, 0, 3));
    bill->setMaterialTexture(0, driver->getTexture(tex_name));
    bill->setMaterialFlag(video::EMF_LIGHTING, false);
    bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    bill->setSize(core::dimension2d<f32>(250.0f, 250.0f));
    bill->setScale(core::vector3df(1, 1, 1));

}

PyObject * Python::PyIrr_LoadTexture(PyObject * self,PyObject * args){
	char * tex_name;
	PyArg_ParseTuple(args,"s",&tex_name);
	//printf("hmmm %s", tex_name);
	texture_array.push_back(driver->getTexture(tex_name));
	//The line below is sorta kludgy, but it works.It won't hold up if you remove a texture
	//from the array though,so watch your step, kid. I'll leave it to you to come up with
	//a more intuitive method of storing the textures
	return Py_BuildValue("l",texture_array.size() - 1);

	// need a texture free function
};

PyObject * Python::PyIrr_SetTexture(PyObject * self,PyObject * args){
	s32 tex_id;
	long node_id;
	PyArg_ParseTuple(args,"lI",&node_id,&tex_id); //This is your new best friend, seriously
	/*Quite similar to the scanf family of functions, don't you think? It take a format
	string and some input data, and analyzes the input data and gives you the result
	in a manner specified by the format string*/
	ISceneNode * node = node_id;//smgr->getSceneNodeFromId(node_id);
	//printf("%i",node_id);
	//printf("%i",tex_id);
	if(node != NULL)
	{
		node->setMaterialTexture(0,texture_array[tex_id]);
	};
	/*This line returns a value of Py_None, which is more or less the same thing as a
	function with a return type of void in C++, in other words, no output values */
	return Py_BuildValue("");
};
