#ifndef PYGUI_H_INCLUDED
#define PYGUI_H_INCLUDED

PyMethodDef irr_gui[] =
{
	    //gui

    {"chatbox",Python::PyIrr_ChatBox,METH_VARARGS,"chatbox for chatting in/with/alone"},
//  {"render",Python::PyIrr_Render,METH_VARARGS,"PyIrr_Render"}
//  {"chatbox",Python::PyIrr_Terrain,METH_VARARGS,"pyterrain"},
	{"codeeditor",Python::PyIrr_CodeEditor,METH_VARARGS,"PyIrr_CodeEditor"}, //gui

    {"window",Python::PyIrr_GUIWindow,METH_VARARGS,"window"},
    {"panel",Python::PyIrr_GUIPanel,METH_VARARGS,"panel"},
    {"tabs",Python::PyIrr_GUITabs,METH_VARARGS,"tabs"},
    {"button",Python::PyIrr_GUIButton,METH_VARARGS,"button"},
    {"text",Python::PyIrr_GUIText,METH_VARARGS,"text"},
    {"tree",Python::PyIrr_GUITree,METH_VARARGS,"tree"},
	{"editbox",Python::PyIrr_GUIEditBox,METH_VARARGS,"editbox"},
	{"bar",Python::PyIrr_GUIBar,METH_VARARGS,"bar"},
	{"sgraph",Python::PyIrr_sineGraph2d,METH_VARARGS,"sgraph"},


	{NULL,NULL,0,NULL}

};

PyObject * Python::PyIrr_CodeEditor(PyObject * self,PyObject * args) {//active camera

bCodeEditor=1;
device->getCursorControl()->setVisible(true);

return Py_BuildValue("");
}

PyObject * Python::PyIrr_ChatBox(PyObject * self,PyObject * args){

            enum evars{create=0,add};
            char * tex_name;
            int action;
      	PyArg_ParseTuple(args,"s",&tex_name,&action);

    switch(action){
        case 0:
      chat = new gui::CGUIChatBox(  guienv, guienv->getRootGUIElement(),
                                                        230, core::rect<int>(20,40,300,500));
        break;

        case 1:
             //   for (int i=0;i < 100;i++){
 //                   chat->addItem(L"tex_name");
//                    chat->addItem(tex_name, video::SColor(250, 220, 255, 255));
             //   };
        break;
    }
	return Py_BuildValue("");
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

PyObject * Python::PyIrr_calcMath(PyObject * self,PyObject * args){

    s32 tex_id,node_id;
	PyArg_ParseTuple(args,"II",&node_id,&tex_id);
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

	return Py_BuildValue("");
}

PyObject * Python::PyIrr_DrawText(PyObject * self,PyObject * args){

IGUIFont * default_font;
	//Must make this useful someday, not today
	char * message;
	s32 x,y,x1,y1;
	PyArg_ParseTuple(args,"sllll",&message,&x,&y,&x1,&y1); //may only need x,y when using ft2
	//The next three lines more or less give the procedure from converting a string of
	//type char* to wchar_t*...generally this is pretty useful in Irrlicht,so note well
//	int len = strlen(message) + 1;
//	wchar_t * conv_message = new wchar_t[len];
	///mbstowcs(0,conv_message,len,message,_TRUNCATE);
printf("%s\n", message);
//wprintf("%s\n", model);
	//guienv->addStaticText(conv_message,rect<s32>(x,y,x1,y1),SColor(255,255,255,255));
//
//	delete [] conv_message;

//	guienv->addStaticText(L"sample text here!",rect<s32>(10,10,260,22), true);
//
//	    CGUITTFont *font2;
//    CGUITTFace face;
//        font2 = new CGUITTFont(gui);
//    font2->attach(&face,24); // scale this number with the screen
//    font2->AntiAlias=1;

    SpriteManager *sprites = new SpriteManager;
    sprites->setup(driver, driver->getTexture("data/texture.png"));

    int w = 400;
    int h = 400;

        fonts->setFontSource("data/pixel1.fnt", 256, 128);
        fonts->setup(device, sprites);
//

        fonts->drawText("the quick brown fox\njumped over\n the lazy dog", 0, 0, w, h, BmFont::ALIGN_CENTER | BmFont::ALIGN_MIDDLE);



	return Py_BuildValue("");
};

PyObject * Python::PyIrr_addHUD(PyObject * self,PyObject * args){
 //   #ifdef HUD
    int state, value;
    char * loadFile;
    PyArg_ParseTuple(args,"sff",&loadFile,&state,&value);
    enum states {openFile=0,Position,Rotation,Play,Pause};
	int istate =  states(state);

    switch (istate){
        case openFile:
                HUDENABLED=true;
                CHUD2->RegisterDevice(device);
                CHUD2->LoadHUD(loadFile);
            return Py_BuildValue("l",CHUD2);
        break;
        case 1:
                    break;

	//hud visible layer attach nodes to it
//        case 2:
}
 //   #endif

return Py_BuildValue("");
 }

PyObject * Python::PyIrr_addVideo(PyObject * self,PyObject * args){

vector3df loc;
char * videoFile;
PyArg_ParseTuple(args,"sfff",&videoFile,&loc.X,&loc.Y,&loc.Z);
        #ifdef VIDEO
        vidmaster = new CVideoMaster(device, true, 1);
        ITexture* cubeDiffuse = vidmaster->addVideoClip(videoFile, "TV", ESM_NONE, true);
        IMeshSceneNode *TV = smgr->addCubeSceneNode(50);
        TV->setScale(vector3df(1.0f, 1.0f, 0.001f));
        ///rotation ? perhaps hud /widget instance
        // Set video texture as diffuse
        TV->setMaterialTexture(0, cubeDiffuse);
        TV->setMaterialFlag(EMF_LIGHTING, false);
        //vidmaster->addVideoClip("./media/YUVTest.ogg", "YUV", dimension2du(128,128), true);
        return Py_BuildValue("l",TV);
        #endif

    //OLD VideoPlayer based on theora or maybe this is the mplayer one
        //cVideoPlayer* videoPlayer;
        //videoPlayer = new cVideoPlayer(driver, device->getTimer(), "./media/123.avi",800,600);
        //videoPlayer->setLoop(false);
        //   videoPlayer->play();

return Py_BuildValue("");
}

PyObject * Python::PyIrr_tesselateImage(PyObject * self,PyObject * args){
// maybe try to stick this into a vector renderstack for main loop to allow more than one instance
vector3df loc;
char * path;
PyArg_ParseTuple(args,"sfff",&path,&loc.X,&loc.Y,&loc.Z);
#ifdef TESSIMAGE
btesimage=1;
tesImage = new TesselatedImage(device, "media/fireball.bmp", vector3df(-600,0,500), vector3df(500, 550, 1000), vector3df(-130,50,100), 45, 1500, 10);
tesImage->startAnimation();
return Py_BuildValue("l",tesImage);
#endif
return Py_BuildValue("");
}


PyObject * Python::PyIrr_GUITabs(PyObject * self,PyObject * args){

	rect<s32>				tabctrlrect(4, 24, 40 - 4, 40 - 4);
	IGUITabControl* tabs	= guienv->addTabControl(tabctrlrect, 5115);
	IGUITab* tab1			= tabs->addTab(L"general");
	IGUITab* tab2			= tabs->addTab(L"navi");
	IGUITab* tab3			= tabs->addTab(L"settings");

	//Tab 1
//	environment->addButton(buttonrect + position2d<s32>(0, 0), tab1, 10101, L"Load GUI");
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_GUIPanel(PyObject * self,PyObject * args){

//	CGUIPanel* panel = new CGUIPanel(guienv, tab3, -1, tab3rect);

//	environment->addStaticText(L"ID", textrect + position2d<s32>(0, 0), false, true, panel);
//	environment->addEditBox(L"", textrect + position2d<s32>(0, 30), true, panel, 10301);
//

	return Py_BuildValue("");

}

PyObject * Python::PyIrr_GUIWindow(PyObject * self,PyObject * args){
float x1,y1,x2,y2;
long guienv2;
char * stra;

PyArg_ParseTuple(args,"sffff",&stra,&x1,&y1,&x2,&y2);

stringw ha=stra;

	IGUIWindow* window = guienv->addWindow(
		rect<s32>(x1 , y1 ,x2 , y2 ),
		false, // modal?
		ha.c_str());

	guienv->addStaticText(L"Please close me",
		rect<s32>(35,35,140,50),
		true, // border?
		false, // wordwrap?
		window);

	return Py_BuildValue("l",window);
}

PyObject * Python::PyIrr_GUIButton(PyObject * self,PyObject * args){
		return Py_BuildValue("");
}

PyObject * Python::PyIrr_GUIBar(PyObject * self,PyObject * args){
float x1,y1,x2,y2;
long pwindow;
int param;
PyArg_ParseTuple(args,"liffff",&pwindow,&param,&x1,&y1,&x2,&y2);
//todo put guienv here so it can be placed in windows
//  CGUIBar* healthBar[4];
CGUIBar* healthBar;
switch (param){
	case 0:
//	CGUIBar* healthBar;
  // the 1st bar will go from 0 to 255
		u8 a=20;
		healthBar = new CGUIBar(20,40, 200,60, a, driver);
		return Py_BuildValue("l",healthBar);
	break;
	case 1:
		healthBar=pwindow;
		healthBar->draw();
		return Py_BuildValue("");
	break;
}
		return Py_BuildValue("");
}

PyObject * Python::PyIrr_sineGraph2d(PyObject * self,PyObject * args){


SGraph2D* graph = new SGraph2D(
guienv, // GUI environment
guienv->getRootGUIElement(), // parent
0, // id
irr::core::recti(0,0,600,400), // GUI element boundaries
irr::core::rectf( -10.0f, -10.0f, 20.0f, 10.0f ), // graph window
true, // use marks or lines?
true // use tick marks?
);


graph->setBackgroundColor( video::SColor(255,150,150,150) );


Inc<f32> dis;
core::vector2df pt;

//dis.copy( win->getIterableXRange() );
dis.setStep( 1.0f/1000.0f );

do {
pt.X = dis.Val();
pt.Y = 10 * sin( dis.Val() );

graph->drawOnGraph( pt, video::SColor(255,255,0,0) );
} while ( !++dis );
//plotsine( graph );


graph->drop();
graph = 0;
		return Py_BuildValue("l",graph);
}

PyObject * Python::PyIrr_GUITree(PyObject * self,PyObject * args){
		return Py_BuildValue("");
}

PyObject * Python::PyIrr_GUIText(PyObject * self,PyObject * args){
		return Py_BuildValue("");
}

PyObject * Python::PyIrr_GUIEditBox(PyObject * self,PyObject * args){
//vector3df loc;
float x1,y1,x2,y2;
long pwindow;
PyArg_ParseTuple(args,"lffff",&pwindow,&x1,&y1,&x2,&y2);
IGUIWindow* window = pwindow;

   IGUIEditBox *textData = guienv->addEditBox(L"",rect<s32>(x1,y1,x2,y2),true,window,803);
   textData->setMax(5000);
   textData->setAutoScroll(true);
   textData->setMultiLine(true);
   textData->setWordWrap(true);
   		return Py_BuildValue("l",textData);
}

PyObject * Python::PyIrr_LoadShape(PyObject * self,PyObject * args){
	return Py_BuildValue("");
		//possible use would be for rendering onto shaped surfaces or accessing vertex's for placement
	}

//PyObject * Python::PyIrr_TextureAnimator(PyObject * self,PyObject * args){
//    oldNow = device->getTimer()->getRealTime();
//    time = 0;
//	    int i = 1;
//    ITexture* img[i];
//
//    img[1] = driver->getTexture("beast1.jpg");
//    img[2] = driver->getTexture("beast2.jpg");
//    img[3] = driver->getTexture("beast3.jpg");
//    img[4] = driver->getTexture("beast4.jpg");
//    img[5] = driver->getTexture("beast5.jpg");
//
//	        now = device->getTimer()->getRealTime();
//        elapsed = now - oldNow;
//        oldNow = now;
//        time += elapsed;
//
//        if (time<1000)
//        {
//            i = 1;
//        }
//        if (time>1000)
//        {
//            i = 2;
//        }
//        if (time>2000)
//        {
//            i = 3;
//        }
//        if (time>3000)
//        {
//            i = 4;
//        }
//        if (time>4000)
//        {
//            i = 5;
//        }
//        if (time>5000)
//        {
//            time = 0;
//        }
//
//        node->setMaterialTexture( 0,img[i]);
//	}

#endif // PYGUI_H_INCLUDED
