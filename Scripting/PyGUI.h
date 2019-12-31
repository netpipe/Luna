#ifndef PYGUI_H_INCLUDED
#define PYGUI_H_INCLUDED
#ifdef PYTHON
#include <iostream> // for strings
using namespace std;

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
	{"slider",Python::PyIrr_GUIslider,METH_VARARGS,"slider"},

	{NULL,NULL,0,NULL}

};

PyObject * Python::PyIrr_CodeEditor(PyObject * self,PyObject * args) {//active camera
#ifdef EDITOR
bCodeEditor=1;
device->getCursorControl()->setVisible(true);



//return Py_BuildValue("l",luna->receiver);
#endif
return Py_BuildValue("");
}

const wchar_t* char2wchar(const char* indata)
{
	std::string UTF8String;
	static std::wstring UTF16String;
	UTF8String = indata;
	UTF16String.resize(UTF8String.length());
	std::copy(UTF8String.begin(), UTF8String.end(), UTF16String.begin());
	return UTF16String.c_str();
}

PyObject * Python::PyIrr_ChatBox(PyObject * self,PyObject * args){

            enum evars{create=0,add};
            char * tex_name;
            char * message;
            int action;
      	PyArg_ParseTuple(args,"si",&message,&action);
#ifdef EXTRAS
    switch(action){
        case 0:

        //vectorChat.pushback =new gui::CGUIChatBox(  guienv, guienv->getRootGUIElement(),
          //                                              230, core::rect<int>(20,40,300,500));

      chat = new gui::CGUIChatBox(  guienv, guienv->getRootGUIElement(),
                                                        230, core::rect<int>(20,40,300,500));
        break;

        case 1:
//        string messagestr = message;
//	char message2[300];
//
//	mbstowcs(message,message2,300);
	//mbtowc(message,message2,300);

	///wchar_t* message2 = char2wchar(message);

      //  chat->addItem(message);
             //   for (int i=0;i < 100;i++){
 //                   chat->addItem(L"tex_name");
//                    chat->addItem(tex_name, video::SColor(250, 220, 255, 255));
             //   };
        break;
                case 2:
				chat->clear();

                break;
    }
    #endif
	return Py_BuildValue("");
}





PyObject * Python::PyIrr_DrawText(PyObject * self,PyObject * args){

long font;
	//Must make this useful someday, not today
	char * message;
	s32 x,y,x1,y1;
	PyArg_ParseTuple(args,"lsllll",&font,&message,&x,&y,&x1,&y1); //may only need x,y when using ft2
IGUIFont * font2 = (IGUIFont *)font;

				//if (font2)
				font2->draw(message,
					core::rect<s32>(x,y,x1,y1),
					video::SColor(255, 255, 255,255));

	//The next three lines more or less give the procedure from converting a string of
	//type char* to wchar_t*...generally this is pretty useful in Irrlicht,so note well
//	int len = strlen(message) + 1;
//	wchar_t * conv_message = new wchar_t[len];
//	mbstowcs(0,conv_message,len,message,_TRUNCATE);
//printf("%s\n", mess0age);
//wprintf("%s\n", model);
//	guienv->addStaticText(conv_message,rect<s32>(x,y,x1,y1),SColor(255,255,255,255));
//
//	delete [] conv_message;

	guienv->addStaticText(L"sample text here!",rect<s32>(10,10,260,22), true);

	 //   CGUITTFont *font2;
//    CGUITTFace face;
//        font2 = new CGUITTFont(gui);
//    font2->attach(&face,24); // scale this number with the screen
//    font2->AntiAlias=1;
//
//    SpriteManager *sprites = new SpriteManager;
//    sprites->setup(driver, driver->getTexture("./data/texture.png"));
//
//    int w = 400;
//    int h = 400;
//
//        fonts->setFontSource("data/pixel1.fnt", 256, 128);
//        fonts->setup(device, sprites);
//        sprites->clear();
//
//        // add sprite from tile (0,0) size(8,8)
//        Sprite *spr = sprites->addSprite(0,0,8,8);
//        spr->setPosition(20, 20);
//        spr->setScale(4.0f, 4.0f);
//
//        fonts->drawText("the quick brown fox\njumped over\n the lazy dog", 0, 0, w, h, BmFont::ALIGN_CENTER | BmFont::ALIGN_MIDDLE);
//


	return Py_BuildValue("");
};

PyObject * Python::PyIrr_addHUD(PyObject * self,PyObject * args){
 //   #ifdef HUD
    int state, value;
    char * loadFile;
    PyArg_ParseTuple(args,"sff",&loadFile,&state,&value);
    #ifdef HUD
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
#endif
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
	#ifdef TESSELATE
		btesimage=1;
		tesImage = new TesselatedImage(device, "media/fireball.bmp", vector3df(-600,0,500), vector3df(500, 550, 1000), vector3df(-130,50,100), 45, 1500, 10);
		tesImage->startAnimation();
		return Py_BuildValue("l",tesImage);
	#endif
return Py_BuildValue("");
}


PyObject * Python::PyIrr_GUITabs(PyObject * self,PyObject * args){

	rect<s32>				tabctrlrect(4, 24, 40 - 4, 40 - 4);
	IGUITabControl* tabs	;//= guienv->addTabControl(tabctrlrect, 5115);
	IGUITab* tab1			= tabs->addTab(L"general");
	IGUITab* tab2			= tabs->addTab(L"navi");
	IGUITab* tab3			= tabs->addTab(L"settings");
//guienv->addTabControl(tabctrlrect, 5115)
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
	float x1,y1,x2,y2;
	long guienv2,window2;
	char * stra;
	PyArg_ParseTuple(args,"lsffff",&window2,&stra,&x1,&y1,&x2,&y2);
//	wchar_t *text = stra;
	stringw ha=stra;
IGUIWindow* window=(IGUIWindow*)window2;
IGUIButton *button =	guienv->addButton (
											rect<s32> ( x1,y1,x2,y2  ),
											window, 105, ha.c_str());
		//window->setEnabled(1);

		return Py_BuildValue("l",button);
}

PyObject * Python::PyIrr_GUIBar(PyObject * self,PyObject * args){
float x1,y1,x2,y2;
long pwindow;
int param;
int ammount;

// todo clickable set option for controlling sliders and things

PyArg_ParseTuple(args,"liffffi",&pwindow,&param,&x1,&y1,&x2,&y2,&ammount);
//todo put guienv here so it can be placed in windows
//  CGUIBar* healthBar[4];
CGUIBar* healthBar;
//printf("param is %i",param);
	if (param == 0) {
//	CGUIBar* healthBar;
  // the 1st bar will go from 0 to 255
		printf("creating bar \n");
		u8 a=20;
		healthBar = new CGUIBar(x1,y1, x2,y2, a, driver);
		return Py_BuildValue("l",healthBar);
	}

	if (param == 1) {
	//	printf("drawing window \n");
		healthBar=(CGUIBar* )pwindow;
		healthBar->setValue(ammount);
		healthBar->draw();
		return Py_BuildValue("");
//		break;
	}

		return Py_BuildValue("");
}

PyObject * Python::PyIrr_sineGraph2d(PyObject * self,PyObject * args){
#ifdef SGRAPH2D

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
pt.X = dis.Val()*10;
pt.Y = 10 * sin( dis.Val() );

graph->drawOnGraph( pt, video::SColor(255,255,0,0) );
} while ( !++dis );
//plotsine( graph );


graph->drop();
graph = 0;
		return Py_BuildValue("l",graph);
		#endif
}

PyObject * Python::PyIrr_GUITree(PyObject * self,PyObject * args){
		return Py_BuildValue("");
}

PyObject * Python::PyIrr_GUIText(PyObject * self,PyObject * args){
		return Py_BuildValue("");
}

PyObject * Python::PyIrr_GUIslider(PyObject * self,PyObject * args){
float x1,y1,x2,y2;
int ammount;
long pwindow;

// you can use 0 as pwindow to place without a window
PyArg_ParseTuple(args,"lffffi",&pwindow,&x1,&y1,&x2,&y2,&ammount);

IGUIWindow* window=(IGUIWindow*)pwindow;

	IGUIScrollBar* scrollbar = guienv->addScrollBar(true,
			rect<s32>(x1, y1, x2, y2), window,  0);
//	scrollbar->setMax(255);
//	scrollbar->setPos(255);
//	setSkinTransparency( scrollbar->getPos(), env->getSkin());

	// set scrollbar position to alpha value of an arbitrary element
	//env->getSkin()->getColor(EGDC_WINDOW).getAlpha()
//	scrollbar->setPos(ammount);
		return Py_BuildValue("l",scrollbar);
}

PyObject * Python::PyIrr_GUIEditBox(PyObject * self,PyObject * args){
//vector3df loc;
float x1,y1,x2,y2;
long pwindow;
PyArg_ParseTuple(args,"lffff",&pwindow,&x1,&y1,&x2,&y2);
IGUIWindow* window = (IGUIWindow*)pwindow;

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
#endif // PYGUI_H_INCLUDED
