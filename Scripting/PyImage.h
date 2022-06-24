#ifdef PYTHON
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
	{"remove_texture",Python::PyIrr_rTexture,METH_VARARGS,"Adds a texture to a scene node"},

	{"checkbounds",Python::PyIrr_icheckBounds,METH_VARARGS,"checkBounds"},
	{"getbounds",Python::PyIrr_igetBounds,METH_VARARGS,"getbounds"},
	{"loadfont",Python::PyIrr_LoadSpriteFont,METH_VARARGS,"loadfont"},

	{"height",Python::PyIrr_iGetHeight,METH_VARARGS,"PyIrr_iGetHeight"},
	{"width",Python::PyIrr_iGetWidth,METH_VARARGS,"PyIrr_iGetOHeight"},
	{"oheight",Python::PyIrr_iGetOHeight,METH_VARARGS,"PyIrr_iGetOHeight"},
	{"owidth",Python::PyIrr_iGetOWidth,METH_VARARGS,"PyIrr_iGetOWidth"},

	{"scolor",Python::PyIrr_isetColor,METH_VARARGS,"PyIrr_isetColor"},
	{"gcolor",Python::PyIrr_igetColor,METH_VARARGS,"PyIrr_igetColor"},
	{"transparency",Python::PyIrr_iTransparent,METH_VARARGS,"PyIrr_iTransparent"},
	{"filter",Python::PyIrr_iFilter,METH_VARARGS,"PyIrr_iFilter"},

	{NULL,NULL,0,NULL}
};


PyObject * Python::PyIrr_iRotate(PyObject * self,PyObject * args){
   	long node_id;
	float rot;

	PyArg_ParseTuple(args,"lf",&node_id,&rot);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;

	node->SetRotation(rot);
     //   irr::f32 GetRotation() { return Rotation; };
return Py_BuildValue("l",node_id);
#endif
return Py_BuildValue("");
}

PyObject * Python::PyIrr_iScale(PyObject * self,PyObject * args){
   	long node_id;
   	float X,Y;
//	float size;
	PyArg_ParseTuple(args,"lff",&node_id,&X,&Y);
		#ifdef Image2D
	cImage* node = (cImage*)node_id;
	irr::core::vector2df news;
//	news=vector2df(node->OrigImageRect.UpperLeftCorner.X-node->OrigImageRect.LowerRightCorner.X,node->OrigImageRect.UpperLeftCorner.Y-node->OrigImageRect.LowerRightCorner.Y);
	news.X=(X*-1);
	news.Y=(Y*-1);
//
//	news.X=(X*-1)*X;
//	news.Y=(Y*-1)*Y; // not sure why but had to invert values
//	news.X=news.X*X;
//	news.Y=news.Y*Y;
//news=vector2df(atof(node->OrigImageRect.LowerRightCorner.X),atof(node->OrigImageRect.LowerRightCorner.Y));
//LowerRightCorner
//news.Y=(node->OrigImageRect.Y);
  //  node->OrigImageRect().W;
	node->SetScale(news);

#endif
return Py_BuildValue("");

}

PyObject * Python::PyIrr_iPosition(PyObject * self,PyObject * args){
   	long node_id;
   	float X,Y;
//	float size;
	PyArg_ParseTuple(args,"lff",&node_id,&X,&Y);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	//if its -1 for x val return center position or use getbounds
	irr::core::position2di newpos;
	newpos.X=X;
	newpos.Y=Y;
	node->SetPosition(newpos);
#endif
return Py_BuildValue("");

}


PyObject * Python::PyIrr_isetColor(PyObject * self,PyObject * args){
   	long node_id;
   	int r,g,b;
	PyArg_ParseTuple(args,"liii",&node_id,&r,&g,&b);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	node->SetColor(irr::video::SColor(255,255,255,0));
	#endif

return Py_BuildValue("1");

}
PyObject * Python::PyIrr_igetColor(PyObject * self,PyObject * args){
   	long node_id;
	PyArg_ParseTuple(args,"liii",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	irr::video::SColor ret =node->GetColor();


return Py_BuildValue("l",&ret);

	#else
return Py_BuildValue("");
	#endif
}
PyObject * Python::PyIrr_iTransparent(PyObject * self,PyObject * args){
   	long node_id;
   	int param;
//draw all in vector image stack
//midpoint

	PyArg_ParseTuple(args,"li",&node_id,&param);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;

//	switch(param){
//	case 0:
//	//	node->SetTransparentColor(1);
//	case 1:
//	//	node->GetTransparentColor(1);
//	case 2:
//	//	node->GetTransparent(1);
//	case 3:
//	//	node->SetTransparent(1);
//	}
	#endif

return Py_BuildValue("");

}

PyObject * Python::PyIrr_iFilter(PyObject * self,PyObject * args){
   	long node_id;
   	int filter;
   	int ret;
	PyArg_ParseTuple(args,"li",&node_id,&filter);
	// might use a string later for this
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
//	switch(filter){
//	case 0:
////		node->SetTrilinearFilter();
//	case 1:
////		node->SetAnisotropicFilter();
//	case 2:
//	//	int ret =node->GetAnisotropicFilter();
//	case 3:
//	//	node->SetBilinearFilter();
//	case 4:
//	//	int ret =node->GetBilinearFilter();
//	case 5:
//	//	int ret =node->GetTrilinearFilter();
//	}
return Py_BuildValue("i",ret);
	#endif

}

PyObject * Python::PyIrr_iGetOHeight(PyObject * self,PyObject * args){
   	long node_id;
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	int ret =node->GetOrigHeight();
	#else

return Py_BuildValue("");
#endif

}

PyObject * Python::PyIrr_iGetOWidth(PyObject * self,PyObject * args){
   	long node_id;
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	int ret =node->GetOrigWidth();
return Py_BuildValue("f",ret);
#else
return Py_BuildValue("");
	#endif

}

PyObject * Python::PyIrr_iGetHeight(PyObject * self,PyObject * args){
   	long node_id;
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	int ret = node->GetHeight();

return Py_BuildValue("f",ret);
	#else
return Py_BuildValue("");
#endif

}

PyObject * Python::PyIrr_iGetWidth(PyObject * self,PyObject * args){
   	long node_id;
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	int ret =node->GetWidth();

return Py_BuildValue("f",ret);
#else
return Py_BuildValue("");
#endif

}

PyObject * Python::PyIrr_iDraw(PyObject * self,PyObject * args){
   	long node_id;
//draw all in vector image stack
//midpoint
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;

	node->Draw(smgr);
	#endif

return Py_BuildValue("");

}

PyObject * Python::PyIrr_iAdd(PyObject * self,PyObject * args){
    //	s32 node_id;
	//	float size;
	char * texture;
   	float x1,y1,x2,y2,xx1,yy1,xx2,yy2;
	//thats a lot of parameters
	PyArg_ParseTuple(args,"sffffffff",&texture,&x1,&y1,&x2,&y2,&xx1,&yy1,&xx2,&yy2);
#ifdef Image2D
	core::recti nsize(x1,y1,x2,y2);
	core::recti textpos(xx1,yy1,xx2,yy2);
	video::ITexture* images = driver->getTexture(texture);
		//driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));
	cImage* aImage = new cImage(images, nsize, textpos);
return Py_BuildValue("l",aImage);
#endif
return Py_BuildValue("");
}

PyObject * Python::PyIrr_iTexture(PyObject * self,PyObject * args){
   	long node_id;
   	char *texture;
   	int type;
	PyArg_ParseTuple(args,"lsi",&node_id,&texture,&type);
	#ifdef Image2D
		cImage* node = (cImage*)node_id;
		video::ITexture* images = driver->getTexture(texture);
		node->SetTexture(images);
	return Py_BuildValue("l",images);
	#endif
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_iAlpha(PyObject * self,PyObject * args){
   	long node_id;
	//draw all in vector image stack
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
		cImage* node = (cImage*)node_id;

		node->Draw(smgr);
	#endif
	return Py_BuildValue("");
}


PyObject * Python::PyIrr_2Dimage(PyObject * self,PyObject * args) {//active camera
    #ifdef Image2D
    bImage2d=1;
        //cImage*
        image = new cImage(driver->getTexture("../media/sydney.bmp"),
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
return Py_BuildValue("l",image);
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
	PyArg_ParseTuple(args,"li",&node_id,&tex_id); //This is your new best friend, seriously
	/*Quite similar to the scanf family of functions, don't you think? It take a format
	string and some input data, and analyzes the input data and gives you the result
	in a manner specified by the format string*/
	ISceneNode * node = (ISceneNode *)node_id;//smgr->getSceneNodeFromId(node_id);
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

PyObject * Python::PyIrr_rTexture(PyObject * self,PyObject * args){
	//refresh, remove, recurse or find texture
	// reload seems to work with png not jpg for now.
	s32 tex_id;
	long node_id;
	int rload;
	PyArg_ParseTuple(args,"lsi",&node_id,&tex_id,&rload); //This is your new best friend, seriously

	stringc test ;
	test += tex_id;
	ITexture *textmp;
    switch (rload){
        case 0:{ // get from texture name "./texture/picture4.jpg"
///            textmp = driver->getTexture( tex_id );
      ///      driver->removeTexture( textmp );
        }break;
        case 1:{ // get from existing pointer
///        textmp = node_id;
  ///      driver->removeTexture( textmp );
        }break;
        case 2:{        //reload texture
    // get from texture name "./texture/picture4.jpg"
        driver->getTexture( test );
        }break;
        case 3:{
            textmp = driver->findTexture( test );
        }break;
    }

	return Py_BuildValue("l",textmp);
};

PyObject * Python::PyIrr_igetBounds(PyObject * self,PyObject * args){
	long node_id;
	irr::core::recti rect;
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;

	rect = node->GetBoundRect();
	return Py_BuildValue("l",&rect);
	#endif
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_icheckBounds(PyObject * self,PyObject * args){
	long node_id;
	irr::core::recti rect;
	PyArg_ParseTuple(args,"l",&node_id);
	#ifdef Image2D
	cImage* node = (cImage*)node_id;
	rect = node->GetBoundRect();

	return Py_BuildValue("l",&rect);
	#endif
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_LoadSpriteFont(PyObject * self,PyObject * args){
	long node_id;
	char *stringy;
	//irr::core::recti rect;
	PyArg_ParseTuple(args,"s",&stringy);
	gui::IGUIFont* font2 =
	device->getGUIEnvironment()->getFont(stringy);
	return Py_BuildValue("l",font2);
}

//PyObject * Python::PyIrr_Draw(PyObject * self,PyObject * args){
//			if (font2)
//				font2->draw(L"Also mixing with 3d graphics is possible.",
//					core::rect<s32>(130,20,300,60),
//					video::SColor(255,time % 255,time % 255,255));
//
#endif
