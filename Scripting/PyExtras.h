//#ifdef EXTRAS
/// extra stuff that should eventually find a new file to go into.

//"s" (string) [char *]
//    Convert a null-terminated C string to a Python object. If the C string pointer is NULL, None is used.
//"s#" (string) [char *, int]
//    Convert a C string and its length to a Python object. If the C string pointer is NULL, the length is ignored and None is returned.
//"z" (string or None) [char *]
//    Same as "s".
//"z#" (string or None) [char *, int]
//    Same as "s#".
//"u" (Unicode string) [Py_UNICODE *]
//    Convert a null-terminated buffer of Unicode (UCS-2) data to a Python Unicode object. If the Unicode buffer pointer is NULL, None is returned.
//"u#" (Unicode string) [Py_UNICODE *, int]
//    Convert a Unicode (UCS-2) data buffer and its length to a Python Unicode object. If the Unicode buffer pointer is NULL, the length is ignored and None is returned.
//"u" (Unicode string) [Py_UNICODE *]
//    Convert a null-terminated buffer of Unicode (UCS-2) data to a Python Unicode object. If the Unicode buffer pointer is NULL, None is returned.
//"u#" (Unicode string) [Py_UNICODE *, int]
//    Convert a Unicode (UCS-2) data buffer and its length to a Python Unicode object. If the Unicode buffer pointer is NULL, the length is ignored and None is returned.
//"i" (integer) [int]
//    Convert a plain C int to a Python integer object.
//"b" (integer) [char]
//    Same as "i".
//"h" (integer) [short int]
//    Same as "i".
//"l" (integer) [long int]
//    Convert a C long int to a Python integer object.
//"c" (string of length 1) [char]
//    Convert a C int representing a character to a Python string of length 1.
//"d" (float) [double]
//    Convert a C double to a Python floating point number.
//"f" (float) [float]
//    Same as "d".
//"O" (object) [PyObject *]
//    Pass a Python object untouched (except for its reference count, which is incremented by one). If the object passed in is a NULL pointer, it is assumed that this was caused because the call producing the argument found an error and set an exception. Therefore, Py_BuildValue() will return NULL but won't raise an exception. If no exception has been raised yet, PyExc_SystemError is set.
//"S" (object) [PyObject *]
//    Same as "O".
//"U" (object) [PyObject *]
//    Same as "O".
//"N" (object) [PyObject *]
//    Same as "O", except it doesn't increment the reference count on the object. Useful when the object is created by a call to an object constructor in the argument list.
//"O&" (object) [converter, anything]
//    Convert anything to a Python object through a converter function. The function is called with anything (which should be compatible with void *) as its argument and should return a ``new'' Python object, or NULL if an error occurred.
//"(items)" (tuple) [matching-items]
//    Convert a sequence of C values to a Python tuple with the same number of items.
//"[items]" (list) [matching-items]
//    Convert a sequence of C values to a Python list with the same number of items.
//"{items}" (dictionary) [matching-items]
//    Convert a sequence of C values to a Python dictionary. Each pair of consecutive C values adds one item to the dictionary, serving as key and value, respectively.



PyMethodDef irr_Extras[] =
{
        {"omaredemo",Python::PyIrr_omareDemo,METH_VARARGS,"loads omares plane demo or maybe clouds"},
        {"bitcloud",Python::PyIrr_bitCloud,METH_VARARGS,"Soft Fluffy clouds / not working atm"},
        {"lightning",Python::PyIrr_lightning,METH_VARARGS,"lightning scene node pretty neat takes 2 points"},
        {"beam",Python::PyIrr_beam,METH_VARARGS,"its a fricken laser beam"},
        {"skydome",Python::PyIrr_skyDome,METH_VARARGS,"skydome"},
        {"lensFlare",Python::PyIrr_lensFlare,METH_VARARGS,"lensFlare"},
        {"blindboids",Python::PyIrr_BlindBoids,METH_VARARGS,"blindside boids demo"},
        {"occlusionTest",Python::PyIrr_Occlusion,METH_VARARGS,"occlusion"},
        {"compass",Python::PyIrr_Compass,METH_VARARGS,"PyIrr_Compas"},
        {"realCloud",Python::PyIrr_realCloud,METH_VARARGS,"PyIrr_realCloud"},
        {"codeeditor",Python::PyIrr_CodeEditor,METH_VARARGS,"PyIrr_CodeEditor"}, //gui
        {"irc",Python::PyIrr_RelayChat,METH_VARARGS,"relaychat"},
        {NULL,NULL,0,NULL}
};

PyObject * Python::PyIrr_FormationDemo(PyObject * self,PyObject * args){
    #ifdef FORMATIONDEMO
    // FORMATION DEMO
    //WrapperClass::Formation *
    formationDemo=1;
     formation =
        new WrapperClass::Formation(vector3df(0,0,0), 100.f, 5, 30, 100.f, 100.f, smgr);
    	///const irr::core::aabbox3df& tb = terrain->getBoundingBox();
    #endif
//formation->process(deltaTime);
Py_RETURN_NONE;
};


PyObject * Python::PyIrr_CodeEditor(PyObject * self,PyObject * args) {//active camera

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
//
//// Declare a structure to hold some context for the event receiver so that it
//// has it available inside its OnEvent() method.
//struct SAppContext
//{
//	IrrlichtDevice *device;
//	CGUIEditBoxIRB * codeEditor;
//	IGUIContextMenu * menu;
//};
//
//class MyEventReceiver : public IEventReceiver
//{
//public:
//	MyEventReceiver(SAppContext & context) : Context(context) { }
//
//	virtual bool OnEvent(const SEvent& event)
//	{
//		if (event.EventType == EET_GUI_EVENT)
//		{
//			s32 id = event.GUIEvent.Caller->getID();
//			IGUIEnvironment* env = Context.device->getGUIEnvironment();
//
//			switch(event.GUIEvent.EventType)
//			{
//
//			case EGET_SCROLL_BAR_CHANGED:
//				break;
//
//			case EGET_BUTTON_CLICKED:
//				break;
//
//			case gui::EGET_MENU_ITEM_SELECTED:
//				{
//					IGUIContextMenu* menu = (IGUIContextMenu*)event.GUIEvent.Caller;
//					s32 item = menu->getItemCommandId(menu->getSelectedItem());
//					switch (item)
//					{
//						case MENU_QUIT:
//							Context.device->closeDevice();
//							break;
//						case MENU_UNDO:
//							Context.codeEditor->undo();
//							break;
//						case MENU_REDO:
//							Context.codeEditor->redo();
//							break;
//						case MENU_CUT:
//							Context.codeEditor->cut();
//							break;
//						case MENU_COPY:
//							Context.codeEditor->copy();
//							break;
//						case MENU_PASTE:
//							Context.codeEditor->paste();
//							break;
//						case MENU_DELETE:
//							Context.codeEditor->deleteText();
//							break;
//						case MENU_LINECOUNT:
//							{
//								bool visible = Context.codeEditor->isLineCountDisplayed();
//								Context.codeEditor->setDisplayLineCount(!visible);
//							}
//							break;
//						case MENU_ENGLISH:
//							{
//								// Change the text of the menu in English
//								Context.menu->setItemText(0,L"File");
//								Context.menu->setItemText(1,L"Edit");
//								Context.menu->setItemText(2,L"Display");
//
//								IGUIContextMenu * submenu;
//								submenu = Context.menu->getSubMenu(0);
//								submenu->setItemText(0,L"Quit");
//
//								submenu = Context.menu->getSubMenu(1);
//								submenu->setItemText(0,L"Cut");
//								submenu->setItemText(1,L"Copy");
//								submenu->setItemText(2,L"Paste");
//								submenu->setItemText(3,L"Delete");
//								submenu->setItemText(5,L"Undo");
//								submenu->setItemText(6,L"Redo");
//
//								submenu = Context.menu->getSubMenu(2);
//								submenu->setItemText(0,L"Toggle linecount display");
//								// Change the checked state of the language
//								submenu->setItemChecked(1,true);
//								submenu->setItemChecked(2,false);
//
//								// Set the elements text of the codeEditor in english
//								Context.codeEditor->setElementText(Context.codeEditor->CM_CUT,L"Cut");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_COPY,L"Copy");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_DELETE,L"Delete");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_PASTE,L"Paste");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_UNDO,L"Undo");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_REDO,L"Redo");
//								Context.codeEditor->setElementText(Context.codeEditor->BT_LINECOUNT,
//									L"Toggle linecount display");
//
//
//							}
//							break;
//						case MENU_FRENCH:
//							{
//								// Change the text of the menus in French
//								Context.menu->setItemText(0,L"Fichier");
////								Context.menu->setItemText(1,L"Édition");
//								Context.menu->setItemText(2,L"Affichage");
//
//								IGUIContextMenu * submenu;
//								submenu = Context.menu->getSubMenu(0);
//								submenu->setItemText(0,L"Quitter");
//
//								submenu = Context.menu->getSubMenu(1);
//								submenu->setItemText(0,L"Couper");
//								submenu->setItemText(1,L"Copier");
//								submenu->setItemText(2,L"Coller");
//								submenu->setItemText(3,L"Effacer");
//								submenu->setItemText(5,L"Annuler");
//								submenu->setItemText(6,L"Refaire");
//
//								submenu = Context.menu->getSubMenu(2);
//								submenu->setItemText(0,L"Basculer affichage des lignes");
//								// Change the checked state of the language
//								submenu->setItemChecked(1,false);
//								submenu->setItemChecked(2,true);
//
//								// Set the elements text of the codeEditor in french
//								Context.codeEditor->setElementText(Context.codeEditor->CM_CUT,L"Couper");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_COPY,L"Copier");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_DELETE,L"Effacer");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_PASTE,L"Coller");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_UNDO,L"Annuler");
//								Context.codeEditor->setElementText(Context.codeEditor->CM_REDO,L"Refaire");
//								Context.codeEditor->setElementText(Context.codeEditor->BT_LINECOUNT,
//									L"Basculer affichage des lignes");
//
//							}
//							break;
//
//					}
//					break;
//				}
//
//
//			default:
//				break;
//			}
//		}
//
//		return false;
//	}
//
//private:
//	SAppContext & Context;
//};


    ///
//
//	guienv->createSkin(EGST_WINDOWS_METALLIC);
//	IGUISkin*  skin = guienv->getSkin();
//	skin->setColor(EGDC_HIGH_LIGHT ,video::SColor(192,222,237,243));
//	skin->setColor(EGDC_BUTTON_TEXT  ,video::SColor(255,30,30,30));
//	skin->setColor(EGDC_HIGH_LIGHT_TEXT ,video::SColor(255,30,30,30));
//	skin->setColor(EGDC_3D_DARK_SHADOW  ,video::SColor(255,56,56,56));
//	skin->setColor(EGDC_3D_SHADOW  ,video::SColor(255,85,85,85));
//	skin->setColor(EGDC_3D_FACE  ,video::SColor(255,170,170,170));
//	IGUIFont*  font = guienv->getFont("media/editor/fonts/arial10.xml");
//	if (font)
//      skin->setFont(font);
//
//	device->setWindowCaption(L"Code editor example, using IRRlicht 1.7.2");
//
//	// Create the menus for the example with it default language (English)
//	IGUIContextMenu * menu = guienv->addMenu(0,-1);
//	menu->addItem(L"File",0,true,true);
//	menu->addItem(L"Edit",1,true,true);
//	menu->addItem(L"Display",2,true,true);
//
//	IGUIContextMenu * file_submenu;
//    file_submenu = menu->getSubMenu(0);
//	file_submenu->addItem(L"Quit",MENU_QUIT);
//
//	IGUIContextMenu * edit_submenu;
//    edit_submenu = menu->getSubMenu(1);
//	edit_submenu->addItem(L"Cut",MENU_CUT);
//	edit_submenu->addItem(L"Copy",MENU_COPY);
//	edit_submenu->addItem(L"Paste",MENU_PASTE);
//	edit_submenu->addItem(L"Delete",MENU_PASTE);
//	edit_submenu->addSeparator();
//	edit_submenu->addItem(L"Undo",MENU_UNDO);
//	edit_submenu->addItem(L"Redo",MENU_REDO);
//
//	IGUIContextMenu * display_submenu;
//    display_submenu = menu->getSubMenu(2);
//	display_submenu->addItem(L"Toggle linecount display",MENU_LINECOUNT,true,false,false,false);
//	display_submenu->addItem(L"English",MENU_ENGLISH,true,false,true,false);
////	display_submenu->addItem(L"Français",MENU_FRENCH,true,false,false,false);
//
//	// Define the example text of the Code editor box
//	stringw exampletext = L"// Welcome to the code editor example\n//This example use the c++ style of code to highlight\n\nStrings:\"Here is some text\"\n";
//	exampletext += L"C++ Keywords: this, if, else, break, switch, case, while\n\n";
//	exampletext += L"custom keywords highlight: Hybrid, CuteAlien, Bitplane\n";
//	exampletext += L"custom group highlight 1: (Text is colored between the parenthesis)\n";
//	exampletext += L"custom group highlight 2: Feature(This is a demo of a feature and should work on multiple lines of text.)\n";
//	exampletext += L"custom group highlight 2: Feature(Single line text)\n";
//	exampletext += L"custom line highlight: remark: This line will be highlighted.";
//
//	// Init the Custom GUI
//	//CGUIEditBoxIRB * codeEditor = new CGUIEditBoxIRB(exampletext.c_str(),true,true,guienv,guienv->getRootGUIElement(),-1,rect<s32>(20,60,600,400),device);
//CGUIEditBoxIRB* codeEditor = new CGUIEditBoxIRB(exampletext.c_str(),
//                       true,
//					   true,
//                       guienv,
//                       -1,
//                       25,
//                       //myRect(10,40,driver->getScreenSize().Width-220,driver->getScreenSize().Height-260),
//					   rect<s32>(20,60,600,400),
//					   device);
//
//
//	// Recolor the background with pure white
//	codeEditor->setBackgroundColor(SColor(255,240,240,240));
//	// Recolor the linecount GUI element
//	codeEditor->setLineCountColors(SColor(255,32,32,32),SColor(200,64,120,180),SColor(255,200,200,224));
//	// Recolor the selection colors
//	codeEditor->setSelectionColors(SColor(180,0,96,64),SColor(255,255,255,255),SColor(180,0,128,96));
//
//	// Allow the code editor to use syntax highlighting based on C++ keywords
//	codeEditor->addCppKeywords();
//
//	// Allow the code editor to use syntax highlighting based on LUA keywords
//	//codeEditor->addLUAKeywords();
//
//
//	// Set the pointers so the event manager can manipulate their objects
//	SAppContext context;
//	context.device = device;
//	context.codeEditor = codeEditor;
//	context.menu = menu;
//
//	// Then create the event receiver, giving it that context structure.
//	MyEventReceiver receiver(context);
//
//	// And tell the device to use our custom event receiver.
//	device->setEventReceiver(&receiver);


return Py_BuildValue("");
}



PyObject * Python::PyIrr_lensFlare(PyObject * self,PyObject * args){
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
   //     scene::IMeshSceneNode* sunMeshNode;
    sunMeshNode = smgr->addSphereSceneNode(1, 1, smgr->getRootSceneNode());
    sunMeshNode->setMaterialTexture(0, driver->getTexture("media/mesh.png"));
    sunMeshNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    sunMeshNode->setMaterialFlag(video::EMF_LIGHTING, false);
    sunMeshNode->setScale(core::vector3d<f32>(600, 600, 600));
	//scene::CSceneNodeAnimatorFollowCamera* sunAnim = new scene::CSceneNodeAnimatorFollowCamera(core::vector3df(-8000, 4000, 750));
	//sunMeshNode->addAnimator(sunAnim);
	//sunAnim->drop();
    #ifdef FLARE
    lensFlareNode = new LensFlareSceneNode(sunMeshNode, smgr,1);
    lensFlareNode->setMaterialTexture(0, driver->getTexture("media/flare.png"));
        driver->addOcclusionQuery(sunMeshNode, sunMeshNode->getMesh());
    #endif
    #ifdef FLARE2
    //lensFlareNode->setMaterialTexture(0, driver->getTexture("media/flare.png"));
    //lensFlareNode2 = new CLensFlareSceneNode(sunMeshNode, smgr,123,core::vector3d<f32>(0,0,0));
    #endif
    blensFlare=1;
Py_RETURN_NONE;
}



PyObject * Python::PyIrr_motionTrail(PyObject * self,PyObject * args) {

        s32 node_id;
    int x,y,z;
    PyArg_ParseTuple(args,"llll",&node_id,&x,&y,&z);
    //    if (btrailNode){
       //     rt->
  //  }
//    btrailNode=1
	video::ITexture* tex = driver->getTexture( "media/portal7.bmp" );
    rt = new RibbonTrailSceneNode( device, camera, -1 );
//	rt->setPosition( core::vector3df( 0, -10, 300 ) );
    rt->setMaterialTexture( 0, tex );
   rt->setPoint1( core::vector3df(  50, 0, 0 ) );
    rt->setPoint2( core::vector3df( -50, 0, 0 ) );
    rt->setMaxDistance( 10 );
	rt->setMaxQuads( 5000 );
    rt->setStartingAlpha( 100 );
	rt->setShowDebug( true );
	rt->setEnabled( true );

return Py_BuildValue("l",rt);
}


PyObject * Python::PyIrr_beam(PyObject * self,PyObject * args){
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
	scene::CBeamNode* beam = new scene::CBeamNode(smgr->getRootSceneNode(), smgr, -1, "./data/textures/sceneNodes/laserlf6.png" , "data/textures/sceneNodes/beam.png" );
	beam->setLine(core::vector3df(0,0,0), core::vector3df(100,100,100), 5.0f);
	beam->drop();
    return Py_BuildValue("l",beam);
}


PyObject * Python::PyIrr_Occlusion(PyObject * self,PyObject * args) {//active camera
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
#ifdef occlusion
        bOcclusion = 1;
        Renderer22 RenderMan(device, SColor(0, 10,10,10));
        // RenderMan.addSky("data/models/occlusion/gradient3.bmp");
        // RenderMan.addLight();

        RenderMan.loadModel("data/models/occlusion/etage.b3d", vector3df(0,0,0));
        // RenderMan.addCam(.1f, vector3df(40,70,40), vector3df(0,0,1000), true);
        RenderMan.addCam(camera);
        // RenderMan.addMy3DScene("models/bedroom1/bedroom.my3d", 0,0,0);
        RenderMan.initGUI();
#endif
return Py_BuildValue("");
}


PyObject * Python::PyIrr_Compass(PyObject * self,PyObject * args) {//active camera
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
    #ifdef COMPASS
    bCompass=true;
        ///Compass
           core::rect<s32> CompassRect;
            CompassRect.UpperLeftCorner.X = 50;
            CompassRect.UpperLeftCorner.Y = 50;
            CompassRect.LowerRightCorner.X = 150;
            CompassRect.LowerRightCorner.Y = 150;

            gui::IGUIElement* pgRootGuiElement = guienv->getRootGUIElement();

            Compass1 = new Compass( CompassRect, guienv, pgRootGuiElement );
            video::ITexture * CompassBodyTexture =   driver->getTexture("media/compass/compass_body.png");
            video::ITexture * CompassNeedleTexture =   driver->getTexture("media/compass/compass_needle.png");
            Compass1->SetCompassBodyTexture( CompassBodyTexture );
            Compass1->SetCompassNeedleTexture( CompassNeedleTexture );
    #endif
return Py_BuildValue("");
  }


PyObject * Python::PyIrr_RelayChat(PyObject * self,PyObject * args) {//active camera
    int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);

    #ifdef IRRc
   //  device->getCursorControl()->setVisible(true);
    #endif
    #ifdef IRRc
        app = new Application(device);
        app->registerIrrDevice(device);
        app->init();
    #endif
return Py_BuildValue("");
}


PyObject * Python::PyIrr_BlindBoids(PyObject * self,PyObject * args) {//active camera
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
#ifdef BOIDS
switch (param){
case 0:


 if  (bBlindBoids != true){

 }else {
         bBlindBoids = true;
        const irr::f32 borders[4] = { 1.0f, 222, 1.0f, 222}; //Xmin, Xmax, Zmin, Zmax
       // Flock* flock;

        flock = new Flock( irr::core::vector3df(0.0f, 0.0f, 0.0f), borders);
        flock->registerScene(*smgr);
        	//create flock
//        	flock->boidSelector = smgr->createMetaTriangleSelector();
        irr::scene::IMesh* meshy = smgr->getMesh("./media/dwarf.x");
        //add boids to flock
        for (irr::u32 i = 0; i < 30; ++i)
		flock->addBoid(meshy);

        irr::video::SMaterial mat;
        mat.TextureLayer[0].Texture = driver->getTexture("media/boids/star.bmp");
        mat.EmissiveColor = irr::video::SColor(255, 255, 0, 0);
        mat.SpecularColor = irr::video::SColor(0, 0, 0, 0);
        mat.DiffuseColor =  irr::video::SColor(0, 0, 0, 0);
        mat.Shininess = 128.0f;
        mat.NormalizeNormals = true;
        irr::scene::IMeshSceneNode* const cube = smgr->addCubeSceneNode(50.0f, 0, -1, irr::core::vector3df(0, 100, 0.0f));
        cube->getMesh()->setHardwareMappingHint(irr::scene::EHM_STATIC);
        cube->getMaterial(0) = mat;

        selecta = smgr->createTriangleSelector(cube->getMesh(), cube);
        cube->setTriangleSelector(selecta);

        flock->setTarget(irr::core::vector3df(0.0f, 0.0f, 0.0f));
        flock->setPaused(false);
        //selector->addTriangleSelector(selecta);
        //	selecta->drop();
 }

    break;
case 1:
    break
;case 2:
break;
}
#endif
//Py_RETURN_NONE;
return Py_BuildValue("");
}

//#endif
