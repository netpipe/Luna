#ifdef NDEBUG // if debug build then do this one
#include "config.h"
    enum GUI_ELEMENTS
{
	MENU_QUIT = 200,
	MENU_UNDO,
	MENU_REDO,
	MENU_CUT,
	MENU_PASTE,
	MENU_COPY,
	MENU_DELETE,
	MENU_LINECOUNT,
	MENU_ENGLISH,
	MENU_FRENCH,
};

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
#ifdef CODEEDITOR
struct SAppContext
{
	IrrlichtDevice *device;
	CGUIEditBoxIRB * codeEditor;
	IGUIContextMenu * menu;
};
#endif
//if ( !device->run() ) return 0;
//    guienv->clear();
 //   smgr->clear();
	// Init the Custom GUI

#ifdef PYTHON
    //Python
  //      Python::registerIrrDevice(this,*device,m_cInGameEvents);
 //       Py_Initialize();            //Initialize Python
 //       Python::init_irr();         //Initialize our module
        //Py_SetProgramName(), Py_SetPythonHome(), PyEval_InitThreads(), PyEval_ReleaseLock(), and PyEval_AcquireLock()
        //https://docs.python.org/2/c-api/init.html
        ///todo check for empty or missing files or impliment the using command
//        Python::ExecuteScript("./functions-list.pys"); // this is for testing
		//Python::PyIrr_LoadVehicle(m_cVehicle);
        //Python::PyIrr_addTerrain("1");
#endif

    //camera = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
	//smgr->addCameraSceneNodeFPS();



  //  u32 then = device->getTimer()->getTime();
  //  int lastFPS;


/**
/////////////////////////////////////
//      DEVLOOP  //////////////////
///////////////////////////////////
**/
#ifdef CODEEDITOR


	guienv->createSkin(EGST_WINDOWS_METALLIC);
	IGUISkin*  skin = guienv->getSkin();
	skin->setColor(EGDC_HIGH_LIGHT ,video::SColor(192,222,237,243));
	skin->setColor(EGDC_BUTTON_TEXT  ,video::SColor(255,30,30,30));
	skin->setColor(EGDC_HIGH_LIGHT_TEXT ,video::SColor(255,30,30,30));
	skin->setColor(EGDC_3D_DARK_SHADOW  ,video::SColor(255,56,56,56));
	skin->setColor(EGDC_3D_SHADOW  ,video::SColor(255,85,85,85));
	skin->setColor(EGDC_3D_FACE  ,video::SColor(255,170,170,170));
	IGUIFont*  font = guienv->getFont("media/editor/fonts/arial10.xml");
	if (font)
      skin->setFont(font);

	windows->setVisible(true);


	device->setWindowCaption(L"Code editor example, using IRRlicht 1.7.2");

	// Create the menus for the example with it default language (English)
	IGUIContextMenu * menu = guienv->addMenu(0,-1);
	menu->addItem(L"File",0,true,true);
	menu->addItem(L"Edit",1,true,true);
	menu->addItem(L"Display",2,true,true);

	IGUIContextMenu * file_submenu;
    file_submenu = menu->getSubMenu(0);
	file_submenu->addItem(L"Quit",MENU_QUIT);

	IGUIContextMenu * edit_submenu;
    edit_submenu = menu->getSubMenu(1);
	edit_submenu->addItem(L"Cut",MENU_CUT);
	edit_submenu->addItem(L"Copy",MENU_COPY);
	edit_submenu->addItem(L"Paste",MENU_PASTE);
	edit_submenu->addItem(L"Delete",MENU_PASTE);
	edit_submenu->addSeparator();
	edit_submenu->addItem(L"Undo",MENU_UNDO);
	edit_submenu->addItem(L"Redo",MENU_REDO);

	IGUIContextMenu * display_submenu;
    display_submenu = menu->getSubMenu(2);
	display_submenu->addItem(L"Toggle linecount display",MENU_LINECOUNT,true,false,false,false);
	display_submenu->addItem(L"English",MENU_ENGLISH,true,false,true,false);
//	display_submenu->addItem(L"Français",MENU_FRENCH,true,false,false,false);

	// Define the example text of the Code editor box
	stringw exampletext = L"// Welcome to the code editor example\n//This example use the c++ style of code to highlight\n\nStrings:\"Here is some text\"\n";
	exampletext += L"C++ Keywords: this, if, else, break, switch, case, while\n\n";
	exampletext += L"custom keywords highlight: Hybrid, CuteAlien, Bitplane\n";
	exampletext += L"custom group highlight 1: (Text is colored between the parenthesis)\n";
	exampletext += L"custom group highlight 2: Feature(This is a demo of a feature and should work on multiple lines of text.)\n";
	exampletext += L"custom group highlight 2: Feature(Single line text)\n";
	exampletext += L"custom line highlight: remark: This line will be highlighted.";



//	guienv->addImage(driver->getTexture( "media/irrlichtlogo.jpg"),
//			position2d<int>(10,10));


//	CGUIEditBoxIRB * codeEditor = new CGUIEditBoxIRB(exampletext.c_str(),true,true,guienv,guienv->getRootGUIElement(),-1,rect<s32>(20,60,600,400),device);
	CGUIEditBoxIRB * codeEditor = new CGUIEditBoxIRB(exampletext.c_str(),true,true,guienv,windows,-1,rect<s32>(10,40,driver->getScreenSize().Width-20,driver->getScreenSize().Height-20),device);
////CGUIEditBoxIRB* codeEditor = new CGUIEditBoxIRB(exampletext.c_str(),
////                       true,
////					   true,
////                       guienv,
////                       -1,
////                       25,
////                       //myRect(10,40,driver->getScreenSize().Width-220,driver->getScreenSize().Height-260),
////					   rect<s32>(20,60,600,400),
////					   device);
//
//

//codeEditor->FrameRect=rect<s32>(200,60,600,400);
	// Recolor the background with pure white
	codeEditor->setBackgroundColor(SColor(255,240,240,240));
	// Recolor the linecount GUI element
	codeEditor->setLineCountColors(SColor(255,32,32,32),SColor(200,64,120,180),SColor(255,200,200,224));
	// Recolor the selection colors
	codeEditor->setSelectionColors(SColor(180,0,96,64),SColor(255,255,255,255),SColor(180,0,128,96));

	// Allow the code editor to use syntax highlighting based on C++ keywords
	codeEditor->addCppKeywords();

	// Allow the code editor to use syntax highlighting based on LUA keywords
	//codeEditor->addLUAKeywords();


	// Set the pointers so the event manager can manipulate their objects
	SAppContext context;
	context.device = device;
	context.codeEditor = codeEditor;
	context.menu = menu;

	// Then create the event receiver, giving it that context structure.
//	MyEventReceiver receiver(context);

	// And tell the device to use our custom event receiver.
//	device->setEventReceiver(&receiver);

	codeEditor->setEnabled(0);
	codeEditor->setVisible(false);
	menu->setVisible(false);
//	windows->setVisible(false);
//	windows->setVisible(true);
//	windows->setVisible(false);
//		IGUIWindow* windowss = guienv->addWindow(
//		rect<s32>(1 , 1 ,222 , 222 ),
//		false, // modal?
//		L"mhm");

			Python::bCodeEditor=0;
			windows->setVisible(true);
			codeEditor->setEnabled(true);
			codeEditor->setVisible(true);
			menu->setVisible(true); // only seems to work when called from here
			menu->setEnabled(true);
			windows->setVisible(true);
			//device->setEventReceiver(&receiver);
			device->getCursorControl()->setVisible(true);
            device->setResizable(true);
#endif

device->getCursorControl()->setVisible(true);
//    	IrrAssimp assimp(smgr);
//    IAnimatedMesh* mesh = assimp.getMesh("media/dwarf.x");
////	if (!mesh /*|| !meshNoAssimp*/)
////	{
////		device->drop();
////		return 1;
////	}
//
//	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
//	node->setAnimationSpeed(mesh->getAnimationSpeed());
//

//irr::core::string dir = "RACING/racer";
	//irr::core::::string dir2 = "./" + dir2.c_str() + "/main.pys";
//	printf("%s",dir2.c_str());
//	char* convert = strdup(dir2.c_str());
	//char* convert = const_cast<char*>(dir2.c_str());
//			char * dir2 = "/RACING/racer/";
//			char *dir ;
//				strcat (dir, ".");
//				strcat(dir, dir2);
//				strcat(dir, "main.pys");
//				puts (dir);
 // char * loader = "./RACING/racer/main.pys";
//   loader = "./APP/cowsynth/main.pys";
#ifdef OLD
    while ( device->run() && !this->m_cInGameEvents.Quit ) //&& !this->m_cInGameEvents.Quit
    {
        const u32 now = device->getTimer()->getTime();
		frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		#ifdef PYTHON
        Python::PreRender();
        driver->beginScene ( true, true, SColor ( 0, 0, 0, 0 ) );
        Python::render();
		#else
		driver->beginScene ( true, true, SColor ( 0, 0, 0, 0 ) );
		#endif

        smgr->drawAll();
		//	device->setEventReceiver(&receiver);


//        #ifdef PostProcess
//        if (bPProcess){
//			ppBlurDOF->render( NULL );
//            ppBlur->render( NULL );
//			}
//        #endif


 //       rt->render();

		#ifdef PYTHON  //need this so endscene can be done before checkkeystates.
        Python::preEnd();
          Python::CheckKeyStates();
    //      CheckKeyStates(); //check onEvent for any need to check keys
    // loop for key checking and loop for game  only execute script if there was an event
// pick a game directory and look for main.pys
		//	Python::ExecuteScript(irr::core::stringc(loader));
			//Python::ExecuteScript("./RACING/racer/main.pys");
		guienv->drawAll();
        driver->endScene();
		#else
		guienv->drawAll();
        driver->endScene();
		#endif

        int fps = driver->getFPS();
		if (lastFPS != fps)
		{
			core::stringw tmp(L"Luna Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
     //  device->sleep(5); // pythonize this
    }
#endif
#endif
