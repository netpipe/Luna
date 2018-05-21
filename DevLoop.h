#ifndef NDEBUG // if debug build then do this one
#define PostProcess




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
struct SAppContext
{
	IrrlichtDevice *device;
	CGUIEditBoxIRB * codeEditor;
	IGUIContextMenu * menu;
};

class MyEventReceiver : public IEventReceiver
{
public:
	MyEventReceiver(SAppContext & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

			case EGET_SCROLL_BAR_CHANGED:
				break;

			case EGET_BUTTON_CLICKED:
				break;

			case gui::EGET_MENU_ITEM_SELECTED:
				{
					IGUIContextMenu* menu = (IGUIContextMenu*)event.GUIEvent.Caller;
					s32 item = menu->getItemCommandId(menu->getSelectedItem());
					switch (item)
					{
						case MENU_QUIT:
							//Context.device->closeDevice();
							Python::bCodeEditor=3;
							break;
						case MENU_UNDO:
							Context.codeEditor->undo();
							break;
						case MENU_REDO:
							Context.codeEditor->redo();
							break;
						case MENU_CUT:
							Context.codeEditor->cut();
							break;
						case MENU_COPY:
							Context.codeEditor->copy();
							break;
						case MENU_PASTE:
							Context.codeEditor->paste();
							break;
						case MENU_DELETE:
							Context.codeEditor->deleteText();
							break;
						case MENU_LINECOUNT:
							{
								bool visible = Context.codeEditor->isLineCountDisplayed();
								Context.codeEditor->setDisplayLineCount(!visible);
							}
							break;
						case MENU_ENGLISH:
							{
								// Change the text of the menu in English
								Context.menu->setItemText(0,L"File");
								Context.menu->setItemText(1,L"Edit");
								Context.menu->setItemText(2,L"Display");

								IGUIContextMenu * submenu;
								submenu = Context.menu->getSubMenu(0);
								submenu->setItemText(0,L"Quit");

								submenu = Context.menu->getSubMenu(1);
								submenu->setItemText(0,L"Cut");
								submenu->setItemText(1,L"Copy");
								submenu->setItemText(2,L"Paste");
								submenu->setItemText(3,L"Delete");
								submenu->setItemText(5,L"Undo");
								submenu->setItemText(6,L"Redo");

								submenu = Context.menu->getSubMenu(2);
								submenu->setItemText(0,L"Toggle linecount display");
								// Change the checked state of the language
								submenu->setItemChecked(1,true);
								submenu->setItemChecked(2,false);

								// Set the elements text of the codeEditor in english
								Context.codeEditor->setElementText(Context.codeEditor->CM_CUT,L"Cut");
								Context.codeEditor->setElementText(Context.codeEditor->CM_COPY,L"Copy");
								Context.codeEditor->setElementText(Context.codeEditor->CM_DELETE,L"Delete");
								Context.codeEditor->setElementText(Context.codeEditor->CM_PASTE,L"Paste");
								Context.codeEditor->setElementText(Context.codeEditor->CM_UNDO,L"Undo");
								Context.codeEditor->setElementText(Context.codeEditor->CM_REDO,L"Redo");
								Context.codeEditor->setElementText(Context.codeEditor->BT_LINECOUNT,
									L"Toggle linecount display");


							}
							break;
						case MENU_FRENCH:
							{
								// Change the text of the menus in French
								Context.menu->setItemText(0,L"Fichier");
//								Context.menu->setItemText(1,L"Édition");
								Context.menu->setItemText(2,L"Affichage");

								IGUIContextMenu * submenu;
								submenu = Context.menu->getSubMenu(0);
								submenu->setItemText(0,L"Quitter");

								submenu = Context.menu->getSubMenu(1);
								submenu->setItemText(0,L"Couper");
								submenu->setItemText(1,L"Copier");
								submenu->setItemText(2,L"Coller");
								submenu->setItemText(3,L"Effacer");
								submenu->setItemText(5,L"Annuler");
								submenu->setItemText(6,L"Refaire");

								submenu = Context.menu->getSubMenu(2);
								submenu->setItemText(0,L"Basculer affichage des lignes");
								// Change the checked state of the language
								submenu->setItemChecked(1,false);
								submenu->setItemChecked(2,true);

								// Set the elements text of the codeEditor in french
								Context.codeEditor->setElementText(Context.codeEditor->CM_CUT,L"Couper");
								Context.codeEditor->setElementText(Context.codeEditor->CM_COPY,L"Copier");
								Context.codeEditor->setElementText(Context.codeEditor->CM_DELETE,L"Effacer");
								Context.codeEditor->setElementText(Context.codeEditor->CM_PASTE,L"Coller");
								Context.codeEditor->setElementText(Context.codeEditor->CM_UNDO,L"Annuler");
								Context.codeEditor->setElementText(Context.codeEditor->CM_REDO,L"Refaire");
								Context.codeEditor->setElementText(Context.codeEditor->BT_LINECOUNT,
									L"Basculer affichage des lignes");

							}
							break;

					}
					break;
				}


			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext & Context;
};






if ( !device->run() ) return 0;
    guienv->clear();
    smgr->clear();
	// Init the Custom GUI


#define PYTHON
#ifdef PYTHON
    //Python
        Python::registerIrrDevice(this,*device,m_cInGameEvents);
        Py_Initialize();            //Initialize Python
        Python::init_irr();         //Initialize our module
        //Py_SetProgramName(), Py_SetPythonHome(), PyEval_InitThreads(), PyEval_ReleaseLock(), and PyEval_AcquireLock()
        //https://docs.python.org/2/c-api/init.html
        ///todo check for empty or missing files or impliment the using command
        Python::ExecuteScript("./functions-list.pys"); // this is for testing
		//Python::PyIrr_LoadVehicle(m_cVehicle);
        //Python::PyIrr_addTerrain("1");
#endif

    //camera = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
	//smgr->addCameraSceneNodeFPS();



    u32 then = device->getTimer()->getTime();
    int lastFPS;


/**
/////////////////////////////////////
//      DEVLOOP  //////////////////
///////////////////////////////////
**/

	IGUIWindow* windows = guienv->addWindow(
		rect<s32>(100 , 100 , 800 , 800 ),
		false, // modal?
		L"Test window");


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
	MyEventReceiver receiver(context);

	// And tell the device to use our custom event receiver.
	device->setEventReceiver(&receiver);

	codeEditor->setEnabled(0);
	codeEditor->setVisible(false);
	menu->setVisible(false);
	windows->setVisible(false);

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
  char * loader = "./RACING/racer/main.pys";
   loader = "./APP/cowsynth/main.pys";

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



//        #ifdef PostProcess
//			ppBlurDOF->render( NULL );
//            ppBlur->render( NULL );
//
//        #endif


 //       rt->render();

		if (Python::bCodeEditor==1	){
			Python::bCodeEditor=0;
			codeEditor->setEnabled(true);
			codeEditor->setVisible(true);
			menu->setVisible(true);
			menu->setEnabled(true);
			windows->setVisible(true);
			device->setEventReceiver(&receiver);
			device->getCursorControl()->setVisible(true);
		}else if (Python::bCodeEditor == 3	){

			codeEditor->setEnabled(0);
			codeEditor->setVisible(false);
			menu->setVisible(false);
			menu->setEnabled(false);
			windows->setVisible(false);
		}
		#ifdef PYTHON  //need this so endscene can be done before checkkeystates.
        Python::preEnd();
          Python::CheckKeyStates();
    //      CheckKeyStates(); //check onEvent for any need to check keys
    // loop for key checking and loop for game  only execute script if there was an event
// pick a game directory and look for main.pys
			Python::ExecuteScript(irr::core::stringc(loader));
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


//#ifdef HUD
// //     delete vidmaster;
//#endif
//    #ifdef BOIDS
//     delete flock;
//    #endif
//
//    #ifdef PostProcess
//	 delete ppBlurDOF;
//	 delete ppBlur;
//	 delete ppRenderer;
//    #endif
//
//	#ifdef ATMOSPHERE
//     delete atmo;
//    #endif
//
//	#ifdef ReflectiveWater
//	 delete water;
//	#endif
//
//	#ifdef RAG
//		for (std::vector<RagDoll*>::iterator it = v_RagDolls.begin(); it != v_RagDolls.end(); ++it)
//            (*it)->~RagDoll();
//	#endif
//
//	//delete CHUD2;
//	//delete m_cVehicle;
//
//	#ifdef COMPASS
//	 delete Compass1;
//	#endif
//
//	#ifdef FLAG     // should be the flagmanager
//	delete irrFlagNode;
//	#endif
//
//	#ifdef FLAG2     // should be the flagmanager
//	delete flag;
//	#endif

	#ifdef PYTHON
		Py_Finalize();
    #endif

    #ifdef DSOUND
		manager->releaseAllSources();
		manager->shutDown();
        cAudio::destroyAudioManager(manager);
    #endif
    #ifdef PHYSICS
	clearBodies();
	#endif



	#ifdef SPARKA
	cout << "\nSPARK FACTORY BEFORE DESTRUCTION :" << endl;
	SPKFactory::getInstance().traceAll();
	SPKFactory::getInstance().destroyAll();
	cout << "\nSPARK FACTORY AFTER DESTRUCTION :" << endl;
	SPKFactory::getInstance().traceAll();
	device->drop();
	#endif

//	delete videoPlayer;
#endif

/*
//		// I'm just using a basic cube scene node for the glass pane, "scaled to flatness".
//		ISceneNode* GlassPane = smgr->addCubeSceneNode();
//		GlassPane->setScale(vector3df(100,150,1));
//		GlassPane->setPosition(core::vector3df(0,0,0));
//		GlassPane->setRotation(vector3df(0,60,0));
//
//		// Here I make a RTT for the refraction, you can use a higher res one if you want,
//		// I chose 512^2 for compatibility. I also load the normalmap.
//		ITexture* RTTTex = driver->addRenderTargetTexture(dimension2du(512,512));
//		ITexture* NormMap = driver->getTexture("shaders/glass-bubble/media/NormalMap.png");
//
//		GlassPane->setMaterialTexture(0, RTTTex);
//		GlassPane->setMaterialTexture(1, NormMap);
//
//		io::path vshader = "shaders/glass-bubble/GlassV.glsl";
//        io::path pshader = "shaders/glass-bubble/GlassP.glsl";
//
//		video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
//
//		// I create the shader material for the glass pane.
//		s32 GlassMat = gpu->addHighLevelShaderMaterialFromFiles(vshader,"main",EVST_VS_2_0,pshader,"main",EPST_PS_2_0,0);
//
//		GlassPane->setMaterialType(E_MATERIAL_TYPE(GlassMat));
*/
