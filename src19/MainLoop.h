//this is a copy of the DevLoop.h to be used for main release binary target compiles
#ifdef NDEBUG
#define DSOUND
if ( !device->run() ) return 0;
guienv->clear();
smgr->clear();

//camera = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
//camera->setFOV(PI/2);
    #ifdef PostProcess
     //PostProcessing
        IPostProc* ppRenderer = new CRendererPostProc( smgr, dimension2du( 1024, 512 ),
                                                    true, true, SColor( 255u, 100u, 101u, 140u ) );

        CEffectPostProc* ppBlurDOF = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLURDOF );
        CEffectPostProc* ppBlur = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLUR, 0.00081f );
                            ppBlur->setQuality( PPQ_GOOD );
    #endif

        #ifdef DSOUNDs
        manager = cAudio::createAudioManager(true);  // broken has to be done from main
       if(manager)
       {
         //   luna->manager->initialize(luna->manager->getAvailableDeviceName(0));
            mysound = manager->create("bling","./media/bling.ogg",false);
            mysound->play2d(true);

    //        return Py_BuildValue("l",manager);
        }
        #endif



#define PYTHON
    #ifdef PYTHON
        Python::registerIrrDevice(this,*device,m_cInGameEvents);
        Py_Initialize();            //Initialize Python
        Python::init_irr();         //Initialize our module
        Python::ExecuteScript("./media/Lscript.pys"); //Using our handy dandy script execution function
         //Python::PyIrr_LoadVehicle(m_cVehicle);
        //Python::PyIrr_addTerrain("1");
    #endif

// Scene, setup for lights.
//  m_cScene = new Scene();
//  m_cScene->registerIrrDevice(*device);
//  m_cScene->setupLights();
//   scene::ILightSceneNode* light = smgr->addLightSceneNode( 0, core::vector3df(100,100,100),
//                                                       video::SColorf(1,1,1,1), 1000.0f );
//    device->getCursorControl()->setVisible(false);

//Create player.
//  m_cPlayer = new Player();
//   m_cPlayer->registerIrrlichtDevice(*device);
//   m_cPlayer->initialize();
//   m_cPlayer->setParent(camera);

//    device->getGUIEnvironment()->
//            addImage( driver->getTexture("data/textures/crosshairs/crosshair1.png"),
//                      core::position2d<s32>((resolution[0]/2)-64,(resolution[1]/2)-64));
//    //Timers
    int lastFPS = -1;
    u32 timeStamp = device-> getTimer()-> getRealTime(),deltaTime = 0;
    u32 then = device->getTimer()->getTime();
//   AddShader();

			net::SOutPacket packet;
    while ( device->run() && !this->m_cInGameEvents.Quit )
    {

//            CheckKeyStates();
//                //Physics Timers
//                    deltaTime = device->getTimer()->getRealTime() - timeStamp;
//                    timeStamp = device->getTimer()->getRealTime();
//                    m_cPhysics->updatePhysics(deltaTime);
//                    m_cVehicle->renderme();
//                   // m_cVehicle2->renderme();
//                   // adevice->playAll();
        const u32 now = device->getTimer()->getTime();
		frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

Python::PreRender();

        driver->beginScene ( true, true, SColor ( 0, 0, 0, 0 ) );

    // run the main event processing loop
        Python::render();
        #ifdef PostProcess
            ppBlur->render( NULL );
            //	ppBlurDOF->render( NULL );
        #endif

        #ifdef DSOUND
//            if(manager){
//                if(mysound && !mysound->isPlaying())
//                {
//                    mysound->setVolume(0.5);
//                    Set the IAudio Sound to play2d and loop
//                   mysound->play2d(true);
//                }
//            }
        #endif


             //  device->sleep(5);
//                btVector3 pos = m_cVehicle->getVehiclePosition();
//                vector3df ha = vector3df(pos[0], pos[1]+5, pos[2]);
//               btVector3 pos;
//               vector3df ha ;
//    packet << "handshake";  // seems this has to be sent first or nothing works
//    netManager->sendOutPacket(packet);
 // process network messages
        smgr->drawAll();
        guienv->drawAll();
        Python::preEnd();
        driver->endScene();
        Python::CheckKeyStates();
        //CheckKeyStates(); obsolete python does it above
        int fps = driver->getFPS();
		if (lastFPS != fps)
		{
			core::stringw tmp(L"Luna Engine [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;
			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
    //slows it down to a reasonable screenlag
    handleMessages();
		}

//device->sleep(1,0);
}//end of runmain

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

#endif // NDEBUG
