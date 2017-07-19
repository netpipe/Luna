
//lacking the manager part but still good in theroy
// impliment vector stashing of multiple flags and culling when not visible to save resources



PyMethodDef irr_FlagMan[] =
{
	{"flag1",Python::PyIrr_Flag1,METH_VARARGS,"Adds a simple flag to a scene node"},
	{"flag2",Python::PyIrr_Flag2,METH_VARARGS,"Adds a realistic flag to a scene node"},
    {NULL,NULL,0,NULL}
};


PyObject * Python::PyIrr_Flag1(PyObject * self,PyObject * args) //flag one better for speed less realistic
{
#ifdef FLAG
flag1 = true;
// flag scene node


// demo veriables
	vector3df	GravityVec(0, -9.8f, 0);
	bool	doWind 			= true;
	bool	showWire		= false;
	bool	pausePhysics	= false;

SMaterial Mat;
		Mat.Lighting		= false;
		Mat.BackfaceCulling = false;

	// Create the Flag Scene Node (dont forget to drop() it afterwards)
		irrFlagNode = new SimpleFlagNode
		(
			10, 20,		// flag dimensions (change to whatever size required, or scale the node later)
			10, 20,		// flag tesselation (good default value)

			Mat,		// initial material properties
			GravityVec,	// gravity (depends on the scale of the scene and the tesselation)

			2,			// iterations (change at your own peril)
			1.99f,		// spring-stiffness (change at your own peril)

			smgr->getRootSceneNode(), smgr, -1	// parent, irrlicht scene manager, ID
		);

		if( !irrFlagNode ) return 0; // unknown error

	// assign a texture and enable alpha transparency (id is always 0)
		irrFlagNode->getMaterial(0).setTexture( 0, driver->getTexture( "media/Flags/agnostechdemo1200912132.png" ) );
		irrFlagNode->getMaterial(0).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;


	// node can be manipulated like any other irrlicht node
		irrFlagNode->setScale( vector3df(10) );
#endif
     Py_RETURN_NONE;
};

PyObject * Python::PyIrr_Flag2(PyObject * self,PyObject * args) //more realistic with shader
{
#ifdef FLAG2
flag2 = true;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

	ILogger* output = device->getLogger();

	path vsFileName = "./shaders/Flag/flag_shader.vert";
	path psFileName = "./shaders/Flag/flag_shader.frag";

	if(!driver->queryFeature(EVDF_PIXEL_SHADER_1_1) && !driver->queryFeature(EVDF_ARB_FRAGMENT_PROGRAM_1))
	{
		output->log("WARNING: Pixel shaders disabled because of missing driver/hardware support.");
		psFileName = "";
	}

	if(!driver->queryFeature(EVDF_VERTEX_SHADER_1_1) && !driver->queryFeature(EVDF_ARB_VERTEX_PROGRAM_1))
	{
		output->log("WARNING: Vertex shaders disabled because of missing driver/hardware support.");
		vsFileName = "";
	}

	IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
	int materialType = 0;
	FlagShaderCallBack* cb = new FlagShaderCallBack();
	if(gpu)
	{
// add your own light settings here
		cb->setAmbient(SColorf(0.1f,0.1f,0.1f,1.0f));
		cb->setDiffuse(SColorf(1.0f,1.0f,1.0f,1.0f));
		cb->setTranslucency(SColorf(0.0f,0.0f,0.0f,0.0f));
		cb->setLight(0);	// use the first light
		cb->setSampler(0);

		materialType = gpu->addHighLevelShaderMaterialFromFiles(vsFileName, "main", EVST_VS_1_1,
												psFileName, "main", EPST_PS_1_1,cb, EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
		cb->drop();
	}

	IImage* vertweightmap = driver->createImageFromFile("media/Flags/weightmap.tga");

// create a couple of perlin generators
	//Perlin1D* pgen1 = new Perlin1D(128,5,0.05f,2.0f,rand());
	//Perlin1D* pgen2 = new Perlin1D(128,6,0.04f,2.0f,rand());
		struct osn_context *pgen1;
		struct osn_context *pgen2;
	open_simplex_noise(rand(), &pgen1);
	open_simplex_noise(rand(), &pgen2);

// create a wind generator, there maybe issues/bugs with the direction handling
	CWindGen* wind = new CWindGen(vector3df(0.0f,0.0f,1.0f),30.0,pgen1,0.5f,1.5f,pgen2);

// create the flag
	CFlagSceneNode* flag = new CFlagSceneNode(smgr->getRootSceneNode(),smgr,345,wind,20.0f,16,12,20.0f,0.994f,
						0.05f,vector3df(0.0f,-0.08f,0.0f),vertweightmap);
	flag->getMaterial(0).setTexture(0, driver->getTexture("media/Flags/agnostechdemo1200912132.png"));
	flag->getMaterial(0).MaterialType = (E_MATERIAL_TYPE)materialType;
	flag->setPosition(vector3df(0.0f,0.0f,0.0f));

// drop the weight map

	vertweightmap->drop();

//	ILightSceneNode* lightnode = smgr->addLightSceneNode();
//	lightnode->setLightType(ELT_DIRECTIONAL);
//	lightnode->setRotation(vector3df(30.0f, -25.0f, 0.0f));
//	lightnode->setPosition(vector3df(6.7f, 32.0f,-11.0f));

//	ICameraSceneNode* cam = smgr->addCameraSceneNodeMaya();
//	cam->setPosition(vector3df(150,0,0));
//	cam->setTarget(vector3df(0,0,0));
#endif
     Py_RETURN_NONE;
};

PyObject * Python::PyIrr_skyDome(PyObject * self,PyObject * args){
     char * path;
   //  std::string p;
    PyArg_ParseTuple(args,"s",&path);
   // p = path;

        smgr->addSkyDomeSceneNode(driver->getTexture( path ), 60,60,1,2);

return Py_BuildValue("");
}

PyObject * Python::PyIrr_lightning(PyObject * self,PyObject * args){
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
switch(param){
    case 0:
        ISceneNode* sphere = smgr->addSphereSceneNode(10);
        sphere->setPosition(vector3df(50,50,50));
        sphere->setMaterialFlag(EMF_LIGHTING,false);
        sphere->setMaterialTexture(0,driver->getTexture("./data/textures/sceneNodes/water006.jpg"));

        irr::scene::CBoltSceneNode* lightning = new irr::scene::CBoltSceneNode(smgr->getRootSceneNode(), smgr, -1,"./data/textures/sceneNodes/light01_1.bmp");
        lightning->setLine(irr::core::vector3df(50,50,50), irr::core::vector3df(0,0,0), 100, 5,10,3, false,10.0f, irr::video::SColor(255,0,0,255));
        lightning->drop();
    }
//return Py_BuildValue("l",lightning);
}

PyObject * Python::PyIrr_omareDemo(PyObject * self,PyObject * args){
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
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

PyObject * Python::PyIrr_bitCloud(PyObject * self,PyObject * args){
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
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

PyObject * Python::PyIrr_realCloud(PyObject * self,PyObject * args){
    // possibly set weather from here
        int param,state,Vehicle,ammount;
    PyArg_ParseTuple(args,"liii",&Vehicle,&param,&ammount,&state);
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


PyObject * Python::PyIrr_addTerrain(PyObject * self,PyObject * args) {//active camera

vector3df loc;
int a1f,a2f,a3f;
//PyArg_ParseTuple(args,"fffi",&loc.X,&loc.Y,&loc.Z,&btree);
PyArg_ParseTuple(args,"iiii",&a1f,&a2f,&a3f,&btree);
#ifdef TERRAIN
     terr = new Terrain;
        terr->registerIrrDevice(*device);
        terr->registerPhysics(*luna->m_cPhysics);
        terr->Init();

        // position, rotation, scale, LOD
       long ret = terr->Render( vector3df( a1f,a2f,a3f), vector3df(0,0.0f,0),   vector3df(1,0.20f,1),3);

    return Py_BuildValue("l",ret); // not sure if you can do this ?
#else
return Py_BuildValue("0");
#endif
}


PyObject * Python::PyIrr_atmosphere(PyObject * self,PyObject * args){
  //check if enabled already otherwise return true for main loop
    #ifdef ATMOSPHERE
    bAtmosphere =1;
   // ATMOsphere *atmo;
    atmo=new ATMOsphere;
    atmo->start(device,driver,smgr->getRootSceneNode(),smgr,624);
    atmo->setDaysPerDay(1000);
    return Py_BuildValue("l",atmo);
    #endif
return Py_BuildValue("0");
}


PyObject * Python::PyIrr_WaterPlane(PyObject * self,PyObject * args){

    #ifdef ReflectiveWater
            char * script;

            float scaleX,scaleY,scaleZ,locX,locY,locZ;
            int wavespeed,refractionfactor,waveheight,wavedisplacement;

            PyArg_ParseTuple(args,"sllll",&script,&wavespeed,&refractionfactor,&waveheight,&wavedisplacement);

            bWater=1;
            water = new CReflectedWater("ReflectedWater", device, smgr, -1, 180, 100,
            dimension2du(512,512));

            ISceneNode *waternode = water->m_waternode;
            waternode->setPosition(vector3df(0, 50, 100));
            water->m_WaveDisplacement /= 0.5f;
            water->m_WaveHeight *= 4.0f;
            water->m_WaveSpeed *= 1.0f;
            water->m_RefractionFactor = 0.51f;
            return Py_BuildValue("l",water);
    #endif
return Py_BuildValue("");
}


PyObject * Python::PyIrr_Trees(PyObject * self,PyObject * args) //more realistic with shader
{

	  ITerrainSceneNode* terr;
	//Terrain *terr;
	char * action;
	char * bush;
	int x,y,z;
	//PyArg_ParseTuple(args,"fffi",&loc.X,&loc.Y,&loc.Z,&btree);
	PyArg_ParseTuple(args,"silll",&action,&terr,&x,&y,&z);
    // open terrain tree layout could probably even load grass sametime.
	if (action = "addTree")
{
	    // change addTree to Trees so you can put more functionality into it
    // should be able to cull these aswell as remove them
    // vector stack of loaded tree's
    // refer to tidbits for just one tree's worth of code

    // create a vector stack store the tree pointers in it
    // call add tree one by one push to treemanager.
    // render tree shadow bake to terrain


//    vector3df aha = vector3df(x,y,z);
    //      int tree =  terr->MakeTrees(aha , 1);
      //  if(btree == 1){

    //    }
//return Py_BuildValue("l",tree);
}


};


