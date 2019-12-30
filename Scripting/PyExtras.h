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
        {"lensflare",Python::PyIrr_lensFlare,METH_VARARGS,"lensFlare"},
        {"blindboids",Python::PyIrr_BlindBoids,METH_VARARGS,"blindside boids demo"},
        {"occlusionTest",Python::PyIrr_Occlusion,METH_VARARGS,"occlusion"},
        {"compass",Python::PyIrr_Compass,METH_VARARGS,"PyIrr_Compas"},
        {"realCloud",Python::PyIrr_realCloud,METH_VARARGS,"PyIrr_realCloud"},


        {NULL,NULL,0,NULL}
};

PyObject * Python::PyIrr_FormationDemo(PyObject * self,PyObject * args){
    #ifdef FORMATION
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
        int param;
        float x,y,z;
    PyArg_ParseTuple(args,"ifff",&param,&x,&y,&z);
    #ifdef FLARE
        scene::IMeshSceneNode* sunMeshNode;
    sunMeshNode = smgr->addSphereSceneNode(1, 1, smgr->getRootSceneNode());
    sunMeshNode->setMaterialTexture(0, driver->getTexture("media/mesh.png"));
    sunMeshNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
    sunMeshNode->setMaterialFlag(video::EMF_LIGHTING, false);
    sunMeshNode->setScale(core::vector3d<f32>(600, 600, 600));
    sunMeshNode->setPosition(vector3df (x,y,z));
	//scene::CSceneNodeAnimatorFollowCamera* sunAnim = new scene::CSceneNodeAnimatorFollowCamera(core::vector3df(-8000, 4000, 750));
	//sunMeshNode->addAnimator(sunAnim);
	//sunAnim->drop();
    if (param){
    #ifdef FLARE
    lensFlareNode = new LensFlareSceneNode(sunMeshNode, smgr,1);
    lensFlareNode->setMaterialTexture(0, driver->getTexture("media/flare.png"));
        driver->addOcclusionQuery(sunMeshNode, sunMeshNode->getMesh());
          //  blensFlare=1;
            bFlare2=1;
    #endif
    }else{
    #ifdef FLARE2
    lensFlareNode2 = new CLensFlareSceneNode(sunMeshNode, smgr,123,core::vector3d<f32>(x,y,z));
        lensFlareNode2->getMaterial(0).setTexture(0, driver->getTexture("media/flares.jpg"));
         blensFlare=1;
    #endif

    }

#endif
Py_RETURN_NONE;
}



PyObject * Python::PyIrr_motionTrail(PyObject * self,PyObject * args) {

        s32 node_id;
    int x,y,z;
    PyArg_ParseTuple(args,"llll",&node_id,&x,&y,&z);
    #ifdef RIBBONTRAIL
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
#endif
}


PyObject * Python::PyIrr_beam(PyObject * self,PyObject * args){
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
    #ifdef EXTRAS
	scene::CBeamNode* beam = new scene::CBeamNode(smgr->getRootSceneNode(), smgr, -1, "./data/textures/sceneNodes/laserlf6.png" , "data/textures/sceneNodes/beam.png" );
	beam->setLine(core::vector3df(0,0,0), core::vector3df(100,100,100), 5.0f);
	beam->drop();
    return Py_BuildValue("l",beam);
    #endif
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


PyObject * Python::PyIrr_Compass(PyObject * self,PyObject * args) {
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


PyObject * Python::PyIrr_BlindBoids(PyObject * self,PyObject * args) {//active camera
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"iiii",&Vehicle,&param,&ammount,&state);
//        const u32 now = device->getTimer()->getTime();
//        const f32 frameDeltaTime = (f32)(now - then) / 1000.0f; // Time in seconds
//        then = now;
#ifdef BOIDS
switch (param){
// if  (bBlindBoids = true){
case 0:
         bBlindBoids = true;
        const irr::f32 borders[4] = { 1.0f, 222, 1.0f, 222}; //Xmin, Xmax, Zmin, Zmax
       // Flock* flock;

        flock = new Flock( irr::core::vector3df(0.0f, 0.0f, 0.0f), borders);
        flock->registerScene(*smgr);
        	//create flock
//        	flock->boidSelector = smgr->createMetaTriangleSelector();
        irr::scene::IMesh* meshy = smgr->getMesh("./media/dwarf.x");
        //add boids to flock
        for (irr::u32 i = 0; i < 10; ++i)
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
//        selector->addTriangleSelector(selecta);
//        	selecta->drop();
// } else
//{
//    	//void update(irr::scene::ITriangleSelector* const
//            //        selector, const irr::f32 deltaTime,
//            //        const bool scatterFlock) const;
//
//    flock->update(selecta,1,0);
//}
    break;
case 1:
    break;
//case 2:
//break;
}
#endif
//Py_RETURN_NONE;
return Py_BuildValue("");
}

//#endif
