//#ifdef EXTRAS
/// extra stuff that should eventually find a new file to go into.

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
        {"codeeditor",Python::PyIrr_CodeEditor,METH_VARARGS,"PyIrr_CodeEditor"},
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

PyObject * Python::PyIrr_lensFlare(PyObject * self,PyObject * args){
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

PyObject * Python::PyIrr_realCloud(PyObject * self,PyObject * args){
	// add 1st cloud layer
	cloudLayer1 = new scene::CloudSceneNode(smgr->getRootSceneNode(), smgr);
	cloudLayer1->setTranslation(core::vector2d<f32>(0.008f, 0.0f));
	cloudLayer1->getMaterial(0).setTexture(0, driver->getTexture("data/clouds/cloud01.png"));
	cloudLayer1->setCloudHeight(0.5f, 0.1f, -0.05f);
	// add 2nd cloud layer
	cloudLayer2 = new scene::CloudSceneNode(smgr->getRootSceneNode(), smgr);
	cloudLayer2->setTranslation(core::vector2d<f32>(0.006f, 0.003f));
	cloudLayer2->getMaterial(0).setTexture(0, driver->getTexture("data/clouds/cloud02.png"));
	cloudLayer2->setCloudHeight(0.4f, 0.05f, -0.1f);
	cloudLayer2->setTextureScale(0.5f);
	// add 3rd cloud layer
	cloudLayer3 = new scene::CloudSceneNode(smgr->getRootSceneNode(), smgr);
	cloudLayer3->setTranslation(core::vector2d<f32>(0.006f, 0.003f));
	cloudLayer3->getMaterial(0).setTexture(0, driver->getTexture("data/clouds/cloud03.png"));
	cloudLayer3->setCloudHeight(0.35f, 0.0f, -0.15f);
	cloudLayer3->setTextureScale(0.4f);
};

PyObject * Python::PyIrr_bitCloud(PyObject * self,PyObject * args){
#ifndef Bitcloud
        clouds = new scene::CCloudSceneNode(
                smgr->getRootSceneNode(), smgr,
                    device->getTimer(), 666, core::vector3df(0,0,0), core::vector3df(0,0,0), core::vector3df(1,1,1));

        video::ITexture * txture = driver->getTexture("./media/cloudgen/cloud.tga");
        srand(time(NULL));
        clouds->setLOD(1);
        clouds->setMaxDepth(1);
            clouds->setMaterialFlag(video::EMF_LIGHTING, false);
        clouds->setMaterialFlag(video::EMF_FOG_ENABLE, true);
    //    clouds->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
        srand(rand());
        clouds->makeRandomCloud(22); //cloudseed
        clouds->setMaterialTexture( 0, txture );
        clouds->setPosition(core::vector3df(0,1000,0));
        camera->setFarValue (20000.0f);
        scene::ISceneNodeAnimator* cloudsCycle = smgr->createFlyCircleAnimator(core::vector3df(100.0f,0.0f,100.0f), 15000.0f, 0.000006f, core::vector3df(0.f, 1.f, 1.f), 0.4f);
            clouds->addAnimator(cloudsCycle);
            cloudsCycle->drop();
        return Py_BuildValue("l",clouds);
#endif
           Py_RETURN_NONE;
};

PyObject * Python::PyIrr_omareDemo(PyObject * self,PyObject * args){
        //Omare's CloudGen
        int nClouds =0;
        int max =10;
        while (nClouds<max)
            {
                int	cloud_x=rand()%2000;
                int cloud_y=rand()%2000;
                int cloud_z=rand()%2000;
                IBillboardSceneNode* cloudgen = smgr->addBillboardSceneNode(0,core::dimension2d<f32>(200, 100));
                cloudgen->setPosition(core::vector3df(cloud_x,cloud_y,cloud_z));
                cloudgen->setMaterialFlag(video::EMF_LIGHTING, false);
                cloudgen->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
                 cloudgen->setMaterialTexture(0,	driver->getTexture("./media/cloudgen/cloud.jpg"));
                 printf("cloud generated");
                nClouds=nClouds+1;
            };
                       Py_RETURN_NONE;
};

PyObject * Python::PyIrr_beam(PyObject * self,PyObject * args){
	scene::CBeamNode* beam = new scene::CBeamNode(smgr->getRootSceneNode(), smgr, -1, "./data/textures/sceneNodes/laserlf6.png" , "data/textures/sceneNodes/beam.png" );
	beam->setLine(core::vector3df(0,0,0), core::vector3df(100,100,100), 5.0f);
	beam->drop();
    return Py_BuildValue("l",beam);
}

PyObject * Python::PyIrr_lightning(PyObject * self,PyObject * args){
        ISceneNode* sphere = smgr->addSphereSceneNode(10);
        sphere->setPosition(vector3df(50,50,50));
        sphere->setMaterialFlag(EMF_LIGHTING,false);
        sphere->setMaterialTexture(0,driver->getTexture("./data/textures/sceneNodes/water006.jpg"));

        irr::scene::CBoltSceneNode* lightning = new irr::scene::CBoltSceneNode(smgr->getRootSceneNode(), smgr, -1,"./data/textures/sceneNodes/light01_1.bmp");
        lightning->setLine(irr::core::vector3df(50,50,50), irr::core::vector3df(0,0,0), 100, 5,10,3, false,10.0f, irr::video::SColor(255,0,0,255));
        lightning->drop();
    Py_RETURN_NONE;
}

PyObject * Python::PyIrr_skyDome(PyObject * self,PyObject * args){
        smgr->addSkyDomeSceneNode(driver->getTexture( "data/textures/skydomes/skydome_1_2048x512.jpg" ), 60,60,1,2);
    Py_RETURN_NONE;
}



PyObject * Python::PyIrr_Occlusion(PyObject * self,PyObject * args) {//active camera
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
    Py_RETURN_NONE;
}

PyObject * Python::PyIrr_Compass(PyObject * self,PyObject * args) {//active camera
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
           Py_RETURN_NONE;
  }



PyObject * Python::PyIrr_RelayChat(PyObject * self,PyObject * args) {//active camera
    #ifdef IRRc
   //  device->getCursorControl()->setVisible(true);
    #endif
    #ifdef IRRc
        app = new Application(device);
        app->registerIrrDevice(device);
        app->init();
    #endif
        Py_RETURN_NONE;
}






PyObject * Python::PyIrr_BlindBoids(PyObject * self,PyObject * args) {//active camera
#ifdef BOIDS
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
#endif
//Py_RETURN_NONE;
return Py_BuildValue("");
}

//#endif
