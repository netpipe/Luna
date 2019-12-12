#ifdef NDEBUG // if debug build then do this one
#define PostProcess




if ( !device->run() ) return 0;
    guienv->clear();
    smgr->clear();
	// Init the Custom GUI


//#define PYTHON
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
		//	device->setEventReceiver(&receiver);


//        #ifdef PostProcess
//			ppBlurDOF->render( NULL );
//            ppBlur->render( NULL );
//
//        #endif


 //       rt->render();

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
