#ifndef PYGUI_H_INCLUDED
#define PYGUI_H_INCLUDED

//rename this to PyVIDEO later

PyObject * Python::PyIrr_ChatBox(PyObject * self,PyObject * args){
    gui::CGUIChatBox* chat = new gui::CGUIChatBox(  guienv, guienv->getRootGUIElement(),
                                                    230, core::rect<int>(20,40,300,500));

    for (int i=0;i < 100;i++){
        chat->addItem(L"(john) Kill that thing...");
        chat->addItem(L"(firestaff) lol", video::SColor(250, 220, 255, 255));
        chat->addItem(L"(juli) that's too big", video::SColor(0, 220, 0, 255));
        chat->addItem(L"(john) Kill that thing...");
        chat->addItem(L"(firestaff) lol", video::SColor(220, 220, 255, 255));
        chat->addItem(L"(juli) that's too big", video::SColor(0, 220, 0, 255));
    };
    //pretty basic needs some work....


    Py_RETURN_NONE;
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
    #endif
        Py_RETURN_NONE;
}

PyObject * Python::PyIrr_LoadTexture(PyObject * self,PyObject * args){
	//Watch this, tricky,remember to pass string ADDRESS to PyArg_ParseTuple
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
	s32 tex_id,node_id;
	PyArg_ParseTuple(args,"II",&node_id,&tex_id); //This is your new best friend, seriously
	/*Quite similar to the scanf family of functions, don't you think? It take a format
	string and some input data, and analyzes the input data and gives you the result
	in a manner specified by the format string*/
	ISceneNode * node = smgr->getSceneNodeFromId(node_id);
	printf("%i",node_id);
	printf("%i",tex_id);
	if(node != NULL)
	{
		node->setMaterialTexture(0,texture_array[tex_id]);
	};
	/*This line returns a value of Py_None, which is more or less the same thing as a
	function with a return type of void in C++, in other words, no output values */
	return Py_BuildValue("");
};


IGUIFont * default_font;

PyObject * Python::PyIrr_DrawText(PyObject * self,PyObject * args){

	//Must make this useful someday, not today
	char * message;
	s32 x,y,x1,y1;
	PyArg_ParseTuple(args,"sllll",&message,&x,&y,&x1,&y1);
	//The next three lines more or less give the procedure from converting a string of
	//type char* to wchar_t*...generally this is pretty useful in Irrlicht,so note well
	int len = strlen(message) + 1;
	wchar_t * conv_message = new wchar_t[len];
	///mbstowcs(0,conv_message,len,message,_TRUNCATE);
	//guienv->addStaticText(conv_message,rect<s32>(x,y,x1,y1),SColor(255,255,255,255));
	delete [] conv_message;
	return Py_BuildValue("");
};
PyObject * Python::PyIrr_addHUD(PyObject * self,PyObject * args) //active camera
{
    #ifdef HUD
    HUDENABLED=true;
        CHUD2->RegisterDevice(device);
        CHUD2->LoadHUD("data/HUD.xml");
    return Py_BuildValue("l",CHUD2);
    #endif

return Py_BuildValue("");
 }

/// GUI
PyObject * Python::PyIrr_addVideo(PyObject * self,PyObject * args){

vector3df loc;

char * videoFile;

PyArg_ParseTuple(args,"sfff",&videoFile,&loc.X,&loc.Y,&loc.Z);
        #ifdef VIDEO
        vidmaster = new CVideoMaster(device, true, 1);
        ITexture* cubeDiffuse = vidmaster->addVideoClip(videoFile, "TV", ESM_NONE, true);
        IMeshSceneNode *TV = smgr->addCubeSceneNode(50);
        TV->setScale(vector3df(1.0f, 1.0f, 0.001f));
        // Set video texture as diffuse
        TV->setMaterialTexture(0, cubeDiffuse);
        TV->setMaterialFlag(EMF_LIGHTING, false);
        //vidmaster->addVideoClip("./media/YUVTest.ogg", "YUV", dimension2du(128,128), true);
        return Py_BuildValue("l",vidmaster);
        #endif

    //OLD VideoPlayer based on theora or maybe this is the mplayer one
        //cVideoPlayer* videoPlayer;
        //videoPlayer = new cVideoPlayer(driver, device->getTimer(), "./media/123.avi",800,600);
        //videoPlayer->setLoop(false);
        //   videoPlayer->play();

       ///end of dont run list

return Py_BuildValue("");
}



PyObject * Python::PyIrr_CodeEditor(PyObject * self,PyObject * args) {//active camera


//    Py_RETURN_NONE;
return Py_BuildValue("");
}



PyObject * Python::PyIrr_tesselateImage(PyObject * self,PyObject * args){
// maybe try to stick this into a vector renderstack for main loop to allow more than one instance
//vector3df loc;
//PyArg_ParseTuple(args,"fff",&loc.X,&loc.Y,&loc.Z);
#ifdef TESSIMAGE
btesimage=1;
tesImage = new TesselatedImage(device, "media/fireball.bmp", vector3df(-600,0,500), vector3df(500, 550, 1000), vector3df(-130,50,100), 45, 1500, 10);
tesImage->startAnimation();
return Py_BuildValue("l",tesImage);
#endif
return Py_BuildValue("");
}
#endif // PYGUI_H_INCLUDED
