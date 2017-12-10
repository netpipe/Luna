
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
		float x,y,z;
		char * texture;
    PyArg_ParseTuple(args,"sfff",&texture,&x,&y,&z);
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
		SimpleFlagNode	*irrFlagNode = new SimpleFlagNode
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
		irrFlagNode->getMaterial(0).setTexture( 0, driver->getTexture(texture ) );
		irrFlagNode->getMaterial(0).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;


	// node can be manipulated like any other irrlicht node
		irrFlagNode->setScale( vector3df(10) );
		irrFlagNode->setPosition (vector3df (x,y,z));
#endif
     return Py_BuildValue("l",irrFlagNode);;
};

PyObject * Python::PyIrr_Flag2(PyObject * self,PyObject * args) //more realistic with shader
{
	float x,y,z;
		char * texture;
    PyArg_ParseTuple(args,"sfff",&texture,&x,&y,&z);

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
	flag->getMaterial(0).setTexture(0, driver->getTexture(texture));
	flag->getMaterial(0).MaterialType = (E_MATERIAL_TYPE)materialType;
	flag->setPosition(vector3df(x,y,z));

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

//vector3df loc;
char * tex;
char * hmap;
char * dmap;
float sx,sy,sz,cx,cy,cz;
int type;
PyArg_ParseTuple(args,"iffffffsss",&type,&cx,&cy,&cz,&sx,&sy,&sz,&hmap,&tex,&dmap);
    vector3df t_position = vector3df(cx,cy,cz);
    vector3df t_rotation = vector3df(0,0,0);
    vector3df t_scale = vector3df(sx,sy,sz);

    		 terr = new Terrain;
			terr->registerIrrDevice(*device);
			terr->registerPhysics(*luna->m_cPhysics);
			terr->Init();

if ( type == 1 ){
	//#ifdef TERRAIN
//		 terr = new Terrain;
//			terr->registerIrrDevice(*device);
//			terr->registerPhysics(*luna->m_cPhysics);


			// position, rotation, scale, LOD
		   //ISceneNode* body =
		    terr->Render( tex,vector3df( cx,cy,cz), vector3df(0,0.0f,0),   vector3df(1,0.20f,1),3);

		return Py_BuildValue("l",terr); // not sure if you can do this ?
	//#else
	//return Py_BuildValue("0");
	//#endif
}else if ( type == 2 ) {
		terr->Terrain2(t_position,t_scale,hmap,tex,dmap);
//		scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
//		hmap,
//		0,					// parent node
//		-1,					// node id
//		t_position,		// position
//		t_rotation,		// rotation
//		t_scale,	// scale
//		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
//		4,					// maxLOD
//		scene::ETPS_17,				// patchSize
//		4					// smoothFactor
//		);
//
//	terrain->setMaterialFlag(video::EMF_LIGHTING, false);
//
//	terrain->setMaterialTexture(0,
//			driver->getTexture(tex));
//	terrain->setMaterialTexture(1,
//			driver->getTexture(dmap));
//
//	terrain->setMaterialType(video::EMT_DETAIL_MAP);
//
//	scene::CDynamicMeshBuffer* mesh = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
//
//	 terrain->getMeshBufferForLOD (*mesh ,2);
//
//
//   btVector3 vertices[3];
//   s32 j,k;
//   btTriangleMesh *  mTriMesh = new btTriangleMesh();
//
//   const irr::u32 vertexCount = mesh->getVertexCount();
//   const irr::u32 indexCount = mesh->getIndexCount();
//
//            irr::video::S3DVertex2TCoords* mb_vertices = (irr::video::S3DVertex2TCoords*)mesh->getVertexBuffer().getData();
//
//   u16* mb_indices = mesh->getIndices();
//
//   for(j=0;j<indexCount;j+=3)
//   {
//      for (k=0;k<3;k++)
//      {
//         s32 index = mb_indices[j+k];
//         vertices[k] = btVector3(
//            mb_vertices[index].Pos.X*terrain->getScale().X,
//            mb_vertices[index].Pos.Y*terrain->getScale().Y,
//            mb_vertices[index].Pos.Z*terrain->getScale().Z);
//      }
//      mTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
//   }
//	mesh->drop();
//
//   btCollisionShape* mShape = new btBvhTriangleMeshShape(mTriMesh, true);
//
//   btDefaultMotionState* state =   new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
//      btVector3(terrain->getPosition().X,terrain->getPosition().Y,terrain->getPosition().Z)));
//
//   btRigidBody* mRigidBody = new btRigidBody(0, state, mShape, btVector3(0, 0, 0));
//   mRigidBody->setCollisionFlags(mRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
//   luna->m_cPhysics->getDynamicsWorld()->addRigidBody(mRigidBody);

return Py_BuildValue("l",terr);
}

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
int waterType=2;
            char * script;

            float scaleX,scaleY,scaleZ,locX,locY,locZ;
            float wavespeed,refractionfactor,waveheight,wavedisplacement;
            float x,y,z,bigness;

            PyArg_ParseTuple(args,"sffff",&script,&wavespeed,&refractionfactor,&waveheight,&wavedisplacement);

	if (waterType==1){
    #ifdef ReflectiveWater


            bWater=1;
            water = new CReflectedWater("ReflectedWater", device, smgr, -1, 10, 100,
            dimension2du(512,512));

            ISceneNode *waternode = water->m_waternode;
            waternode->setPosition(vector3df(0, 50, 100));
          //  waternode->setRotation(vector3df(20, 0, 0));
            water->m_WaveDisplacement /= 0.5f;
            water->m_WaveHeight *= 2.0f;
            water->m_WaveSpeed *= 1.0f;
            water->m_RefractionFactor = 0.51f;
            return Py_BuildValue("l",water);
    #endif
}else{
    const f32 width = 512.0f;
	const f32 height = 512.0f;
	stringc resourcePath="./";

	RealisticWaterSceneNode* water = new RealisticWaterSceneNode(smgr, width, height, resourcePath);
	smgr->getRootSceneNode()->addChild(water);
	}
return Py_BuildValue("");
}

PyObject * Python::PyIrr_FWGrass(PyObject * self,PyObject * args){
	char * dmap;
	float sx,sy,sz,cx,cy,cz;
	int type;
	PyArg_ParseTuple(args,"s",&dmap);

    GrassGenerator::CGrassGenerator* grassGenInstance = new CGrassGenerator(device);

	grassGenInstance->load("./data/vegData/input.xml");
    grassGenInstance->process();
    std::cout << "PROCESSED" << std::endl;

    grassGenInstance->writeOut("./data/vegData/output.grs");
    std::cout << "DONE" << std::endl;
    delete grassGenInstance;



	device->getFileSystem()->addFolderFileArchive("./data/vegData/");
	GrassLoader::loadGrass(dmap,smgr,
							16.f,8.f,36.f,
							40.f,43.f,46.f);
return Py_BuildValue("");
}

PyObject * Python::PyIrr_Trees(PyObject * self,PyObject * args) //more realistic with shader
{
	long terr;
	char *action;
	char * bush;
	float cx,cy,cz;
	int type;
	//PyArg_ParseTuple(args,"fffi",&loc.X,&loc.Y,&loc.Z,&btree);
	PyArg_ParseTuple(args,"silfff",&action,&type,&terr,&cx,&cy,&cz);

	//1 for klasger , KornJungle has both JTree and jungle

    // open terrain tree layout could probably even load grass sametime.
//	if ( action == 0 )
//	{
		//		if (terraintype){
	//	Terrain *terr2=terr;
//		}else{
//		}
	    // change addTree to Trees so you can put more functionality into it
    // should be able to cull these aswell as remove them
    // vector stack of loaded tree's
    // refer to tidbits for just one tree's worth of code

    // create a vector stack store the tree pointers in it
    // call add tree one by one push to treemanager.
    // render tree shadow bake to terrain
		//vector3df aha = vector3df(x,y,z);
		//CTreeSceneNode* tree = terr2->MakeTrees(aha , 1,"Tree");
		//	scene::SMeshBuffer mesh = tree->midmesh();
		//		tree->setRotation( core::vector3df(1,1,0) );
		//	scene::IMeshBuffer* mesh = tree->MidLODMeshBuffer;//HighLODMeshBuffer;
	//		printf ("fucking tree range %f",tree->MidRange);
      //  if(btree == 1){

    //    });
     //   tree->rotation(btQuaternion( btVector3(0,1,0), PI ));

     if (action == "1" ){ //klasgers trees
		//if (action == "Tree"){
		CTreeGenerator* generator = 0;
		//vector <CTreeSceneNode*> tree2;
		CTreeSceneNode* tree2;

			video::ITexture* billTexture = 0;
			video::ITexture* leafTexture = 0;

		struct STreeDesignFiles
		{
			const c8* DesignFile;
			const c8* TreeTextureFile;
			const c8* LeafTextureFile;
			const c8* BillTextureFile;
		};

		struct STreeDesign
		{
			CTreeGenerator* Generator;
			video::ITexture* TreeTexture;
			video::ITexture* LeafTexture;
			video::ITexture* BillTexture;
		};

			const s32 NUM_TREE_DESIGNS = 4;

		const STreeDesignFiles treeDesignFiles[NUM_TREE_DESIGNS] = {
				{ "./data/trees/Oak.xml", "./data/textures/trees/OakBark.png", "./data/textures/trees/OakLeaf.png", "./data/textures/trees/OakBillboard.png" },
				{ "./data/trees/Aspen.xml", "./data/textures/trees/AspenBark.png", "./data/textures/trees/AspenLeaf.png", "./data/textures/trees/AspenBillboard.png" },
				{ "./data/trees/Pine.xml", "./data/textures/trees/PineBark.png", "./data/textures/trees/PineLeaf.png", "./data/textures/trees/PineBillboard.png" },
				{ "./data/trees/Willow.xml", "./data/textures/trees/WillowBark.png", "./data/textures/trees/WillowLeaf.png", "./data/textures/trees/WillowBillboard.png" }
			};


		STreeDesign treeDesigns [NUM_TREE_DESIGNS];
		s32 currentTreeDesign = 0;
		core::vector3df lightDir=vector3df(-100.0f,-10.0f,-100.0f);
		s32 seed = 0;



				for ( s32 i=0; i<NUM_TREE_DESIGNS; i++ )
			{
				treeDesigns[i].Generator = new CTreeGenerator( smgr );
				io::IXMLReader* xml = device->getFileSystem()->createXMLReader( treeDesignFiles[i].DesignFile );
				treeDesigns[i].Generator->loadFromXML( xml );
				xml->drop();
				treeDesigns[i].TreeTexture = driver->getTexture( treeDesignFiles[i].TreeTextureFile );
				treeDesigns[i].LeafTexture = driver->getTexture( treeDesignFiles[i].LeafTextureFile );
				treeDesigns[i].BillTexture = driver->getTexture( treeDesignFiles[i].BillTextureFile );
			}
			video::E_MATERIAL_TYPE leafMaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
			leafMaterialType = (video::E_MATERIAL_TYPE) driver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles(
				"shaders/trees/leaves.vert",
				"main",
				EVST_VS_2_0,
				"shaders/trees/leaves.frag",
				"main", EPST_PS_2_0 , 0 , EMT_TRANSPARENT_ALPHA_CHANNEL_REF , 0 );

				//int treeType = treetype;
		   // for(int i=0; i < 12; i++){
				tree2 = new CTreeSceneNode( smgr->getRootSceneNode(), smgr );
				seed = type; //rand()%4;
				tree2->setup( treeDesigns[seed].Generator, seed, treeDesigns[seed].BillTexture );
				tree2->getLeafNode()->setMaterialTexture( 0, treeDesigns[seed].LeafTexture );
				tree2->setMaterialTexture( 0, treeDesigns[seed].TreeTexture );

				bool lightsEnabled = 1;
				if ( lightsEnabled )
				tree2->getLeafNode()->applyVertexShadows( lightDir, 1.0f, 0.25f );

				tree2->getLeafNode()->setMaterialType( leafMaterialType );
				tree2->setMaterialFlag( video::EMF_LIGHTING, 0 );
				tree2->setScale(core::vector3df(0.5f,0.5f,0.5f));
				tree2->setPosition(core::vector3df(cx,cy,cz));
				tree2->setMaterialType(video::EMT_NORMAL_MAP_SOLID);
				tree2->drop(); //this was disabled not sure why
			//}
			//return pointer to treenode
		   // return (tree2);

//	tr.setOrigin(btVector3(0,30,0));
//         btTriangleMesh *collisionMesh = new btTriangleMesh();
//             m_cScene->setGenericMaterial(node, 0);

//        int meshCount = mesh->getMeshBufferCount();
//        printf("MESHBUFFER COUNT %d /n",meshCount);
//
//        for (int i=0; i < meshCount ; i++)//!load all meshes for CD
//        {
//              meshBuffer2->append( mesh->getMeshBuffer(i) );
//            m_cScene->setGenericMaterial(node, i); //outdoor sun lumenation
	//            luna->m_cPhysics->convertIrrMeshBufferBtTriangleMesh(mesh, collisionMesh, vector3df(1,1,1));
//            decalManager->addMesh(mesh->getMeshBuffer(i));
//        }

//    btBvhTriangleMeshShape *trackShape = new btBvhTriangleMeshShape(collisionMesh, true);
//    btRigidBody *test = luna->m_cPhysics->localCreateRigidBody(0, tr, trackShape, tree);
//test->setWorldTransform(btQuaternion( btVector3(0,1,0), PI ));


	return Py_BuildValue("l",tree2);
	}else{ //kornjungles trees
//		if (terraintype){
//		Terrain *terr2=terr;
//		}else{
//		}
	ITerrainSceneNode* terrain=terr;
	if (action = "jungle"){
 	    jungleScene::Jungle *jungle =
        new jungleScene::Jungle(
                10240, // world size
                8,// chunk size. "chunk size" * "chunk size" = "tree count per chunk"
                16,// max tree dimension diameter
                4,// tree circular detail
                terr,
                smgr,
                -1);

    smgr->getRootSceneNode()->addChild(jungle);
    jungle->getMaterial(0).setTexture(0, driver->getTexture("data/textures/trees/kornJungle/bark.png"));
    jungle->getMaterial(0).setTexture(1, driver->getTexture("data/textures/trees/kornJungle/bark_normal.png"));
    jungle->getMaterial(0).MaterialType = EMT_NORMAL_MAP_SOLID;
    jungle->getMaterial(0).Shininess = 0.0f;

    jungle->getMaterial(1).setFlag(EMF_BACK_FACE_CULLING, false);
    jungle->getMaterial(1).setTexture(0,driver->getTexture("data/textures/trees/kornJungle/leaf.png"));
    jungle->getMaterial(1).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
    // start growing trees

    for(u32 i = 0 ; i < 1000 ; i++)
    {
        f32 cx = 100.0f + rand()%10040;
        f32 cy = 100.0f + rand()%10040;
        int type = rand()%8+1;
        int seed = rand();
        //trees
        switch(type)
        {
            case(1):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    16,// segment
                    5,// min rot
                    30,// max rot
                    800.0f, // length
                    8, // branching count
                    7.5f, // max radius;
                    3, // ground root
                    200.0f, // leaf_width
                    200.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    0, //leaf type
                    0, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(2):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    25,// segment
                    0,// min rot
                    15,// max rot
                    800.0f, // length
                    4, // branching count
                    25.0f, // max radius;
                    4, // ground root
                    400.0f, // leaf_width
                    400.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    1, //leaf type
                    1, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(3):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    32,// segment
                    0,// min rot
                    15,// max rot
                    400.0f, // length
                    4, // branching count
                    5.0f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    2, //leaf type
                    2, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(4):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    32,// segment
                    5,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    20.0f, // max radius;
                    4, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    3, //leaf type
                    3, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(5):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    12,// segment
                    10,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    7.5f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    4, //leaf type
                    4, // bark type
                    seed, // seed
                    true
                    );
                break;
            }
            case(6):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    12,// segment
                    15,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    5.0f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    5, //leaf type
                    5, // bark type
                    seed, // seed
                    true
                   );
                break;
            }
            case(7):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                    14,// segment
                    4,// min rot
                    20,// max rot
                    400.0f, // length
                    4, // branching count
                    10.0f, // max radius;
                    3, // ground root
                    100.0f, // leaf_width
                    100.0f, // leaf height
                    2, // leaf segments
                    1.0, // leaf stiffness
                    6, //leaf type
                    6, // bark type
                    seed, // seed
                    true
                   );
                break;
            }
            case(8):
            {
                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
                   20,// segment
                   0,// min rot
                   30,// max rot
                   400.0f, // length
                   6, // branching count
                   10.0f, // max radius;
                   3, // ground root
                   200.0f, // leaf_width
                   200.0f, // leaf height
                   2, // leaf segments
                   1.0, // leaf stiffness
                   7, //leaf type
                   7, // bark type
                   seed, // seed
                    true
                   );
                    break;
            }
        }
    }
    return Py_BuildValue("l",jungle);
	}

	if (action == "JTree"){
		 	    jungleScene::Jungle *jungle =
        new jungleScene::Jungle(
                10240, // world size
                8,// chunk size. "chunk size" * "chunk size" = "tree count per chunk"
                16,// max tree dimension diameter
                4,// tree circular detail
                terr,
                smgr,
                -1);

		int seed = rand();
		switch(type){
				case(1):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
						16,// segment
						5,// min rot
						30,// max rot
						800.0f, // length
						8, // branching count
						7.5f, // max radius;
						3, // ground root
						200.0f, // leaf_width
						200.0f, // leaf height
						2, // leaf segments
						1.0, // leaf stiffness
						0, //leaf type
						0, // bark type
						seed, // seed
						true
						);
					break;
				}
				case(2):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
						25,// segment
						0,// min rot
						15,// max rot
						800.0f, // length
						4, // branching count
						25.0f, // max radius;
						4, // ground root
						400.0f, // leaf_width
						400.0f, // leaf height
						2, // leaf segments
						1.0, // leaf stiffness
						1, //leaf type
						1, // bark type
						seed, // seed
						true
						);
					break;
				}
				case(3):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
						32,// segment
						0,// min rot
						15,// max rot
						400.0f, // length
						4, // branching count
						5.0f, // max radius;
						3, // ground root
						100.0f, // leaf_width
						100.0f, // leaf height
						2, // leaf segments
						1.0, // leaf stiffness
						2, //leaf type
						2, // bark type
						seed, // seed
						true
						);
					break;
				}
				case(4):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
						32,// segment
						5,// min rot
						20,// max rot
						400.0f, // length
						4, // branching count
						20.0f, // max radius;
						4, // ground root
						100.0f, // leaf_width
						100.0f, // leaf height
						2, // leaf segments
						1.0, // leaf stiffness
						3, //leaf type
						3, // bark type
						seed, // seed
						true
						);
					break;
				}
				case(5):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
						12,// segment
						10,// min rot
						20,// max rot
						400.0f, // length
						4, // branching count
						7.5f, // max radius;
						3, // ground root
						100.0f, // leaf_width
						100.0f, // leaf height
						2, // leaf segments
						1.0, // leaf stiffness
						4, //leaf type
						4, // bark type
						seed, // seed
						true
						);
					break;
				}
				case(6):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
						12,// segment
						15,// min rot
						20,// max rot
						400.0f, // length
						4, // branching count
						5.0f, // max radius;
						3, // ground root
						100.0f, // leaf_width
						100.0f, // leaf height
						2, // leaf segments
						1.0, // leaf stiffness
						5, //leaf type
						5, // bark type
						seed, // seed
						true
					   );
					break;
				}
				case(7):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
						14,// segment
						4,// min rot
						20,// max rot
						400.0f, // length
						4, // branching count
						10.0f, // max radius;
						3, // ground root
						100.0f, // leaf_width
						100.0f, // leaf height
						2, // leaf segments
						1.0, // leaf stiffness
						6, //leaf type
						6, // bark type
						seed, // seed
						true
					   );
					break;
				}
				case(8):
				{
					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
					   20,// segment
					   0,// min rot
					   30,// max rot
					   400.0f, // length
					   6, // branching count
					   10.0f, // max radius;
					   3, // ground root
					   200.0f, // leaf_width
					   200.0f, // leaf height
					   2, // leaf segments
					   1.0, // leaf stiffness
					   7, //leaf type
					   7, // bark type
					   seed, // seed
						true
					   );
						break;
				}
			}
				return Py_BuildValue("l",jungle);
		}


	}
return Py_BuildValue("");
};


//PyMethodDef irr_SPARKA[] = {
//    {"SPARK",Python::PyIrr_SPARKA,METH_VARARGS,"SPARK MANAGER"},
//	{NULL,NULL,0,NULL}
//};

PyObject * Python::PyIrr_SPARKA(PyObject * self,PyObject * args) //active camera
{

#ifdef SPARKA
    bSPARK = 1;
    float angleY = 10.0f;
    float angleX = -45.0f;
    float camPosZ = 5.0f;
    const float PI = 3.14159265358979323846f;
    //scene::ICameraSceneNode* cam = NULL;
    bool smokeEnabled = true;

    //   cam = smgr->addCameraSceneNode(0,core::vector3df(camPosZ*sinf(angleX*core::DEGTORAD)*sinf((90.0f-angleY)*core::DEGTORAD),
    //       camPosZ*cosf((90.0f-angleY)*core::DEGTORAD),camPosZ*cosf(angleX*core::DEGTORAD)*sinf((90.0f-angleY)*core::DEGTORAD)),
    //       core::vector3df());
    //   cam->setNearValue(0.05f);

	// plane
    core::array<video::S3DVertex2TCoords> pVertices;
    pVertices.set_used(4);
    core::array<u16> pIndices;
    pIndices.set_used(6);
    for(int y=0; y<2; y++){
        for(int x=0; x<2; x++){
            pVertices[x+2*y].Pos = core::vector3df((x*2-1)*5.0f,-1.2f,(y*2-1)*5.0f);
            pVertices[x+2*y].Normal = core::vector3df(0,1,0);
            pVertices[x+2*y].TCoords = core::vector2df((x*2-1)*5.0f,(y*2-1)*5.0f);
            pVertices[x+2*y].TCoords2 = core::vector2df((f32)x,(f32)y);
            pVertices[x+2*y].Color = video::SColor(255,255,255,255);
        }
    }
    pIndices[0] = 0;
    pIndices[1] = 2;
    pIndices[2] = 1;
    pIndices[3] = 2;
    pIndices[4] = 3;
    pIndices[5] = 1;
 //    scene::IMeshBuffer* buff
    buff = new scene::CMeshBuffer<video::S3DVertex2TCoords>;
    buff->append(pVertices.pointer(),4,pIndices.pointer(),6);
    buff->getMaterial().MaterialType = video::EMT_LIGHTMAP;
    buff->getMaterial().TextureLayer[0].Texture = driver->getTexture("media/SPARK/grass.bmp");
    buff->getMaterial().TextureLayer[1].Texture = driver->getTexture("media/SPARK/lightmap3.bmp");
    buff->getMaterial().Lighting = false;
    scene::SMesh* mesh = new scene::SMesh; mesh->addMeshBuffer(buff);
    scene::IMeshSceneNode* plane = smgr->addMeshSceneNode(mesh);

	// random seed
	randomSeed = device->getTimer()->getRealTime();
	// Sets the update step
	System::setClampStep(true,0.1f);			// clamp the step to 100 ms
	System::useAdaptiveStep(0.001f,0.01f);		// use an adaptive step from 1ms to 10ms (1000fps to 100fps)

	// Inits Particle Engine

	// Renderers
	IRRQuadRenderer* fireRenderer = IRRQuadRenderer::create(device);
	fireRenderer->setScale(0.3f,0.3f);
	fireRenderer->setTexture(driver->getTexture("media/SPARK/fire2.bmp"));
	fireRenderer->setTexturingMode(TEXTURE_2D);
	fireRenderer->setBlending(BLENDING_ADD);
	fireRenderer->enableRenderingHint(DEPTH_WRITE,false);
	fireRenderer->setAtlasDimensions(2,2);

	IRRQuadRenderer* smokeRenderer = IRRQuadRenderer::create(device);
	smokeRenderer->setScale(0.3f,0.3f);
	smokeRenderer->setTexture(driver->getTexture("media/SPARK/explosion.png"));
	smokeRenderer->setTexturingMode(TEXTURE_2D);
	smokeRenderer->setBlending(BLENDING_ALPHA);
	smokeRenderer->enableRenderingHint(DEPTH_WRITE,false);
	smokeRenderer->setAtlasDimensions(2,2);

	// Models
	Model* fireModel = Model::create(FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA | FLAG_SIZE | FLAG_ANGLE | FLAG_TEXTURE_INDEX,
		FLAG_RED | FLAG_GREEN | FLAG_ALPHA | FLAG_ANGLE,
		FLAG_RED | FLAG_GREEN | FLAG_TEXTURE_INDEX | FLAG_ANGLE,
		FLAG_SIZE);
	fireModel->setParam(PARAM_RED,0.8f,0.9f,0.8f,0.9f);
	fireModel->setParam(PARAM_GREEN,0.5f,0.6f,0.5f,0.6f);
	fireModel->setParam(PARAM_BLUE,0.3f);
	fireModel->setParam(PARAM_ALPHA,0.4f,0.0f);
	fireModel->setParam(PARAM_ANGLE,0.0f,2.0f * PI,0.0f,2.0f * PI);
	fireModel->setParam(PARAM_TEXTURE_INDEX,0.0f,4.0f);
	fireModel->setLifeTime(1.0f,1.5f);

	Interpolator* interpolator = fireModel->getInterpolator(PARAM_SIZE);
	interpolator->addEntry(0.5f,2.0f,5.0f);
	interpolator->addEntry(1.0f,0.0f);

	Model* smokeModel = Model::create(FLAG_RED | FLAG_GREEN | FLAG_BLUE | FLAG_ALPHA | FLAG_SIZE | FLAG_ANGLE | FLAG_TEXTURE_INDEX,
		FLAG_RED | FLAG_GREEN | FLAG_SIZE | FLAG_ANGLE,
		FLAG_TEXTURE_INDEX | FLAG_ANGLE,
		FLAG_ALPHA);
	smokeModel->setParam(PARAM_RED,0.3f,0.2f);
	smokeModel->setParam(PARAM_GREEN,0.25f,0.2f);
	smokeModel->setParam(PARAM_BLUE,0.2f);
	smokeModel->setParam(PARAM_ALPHA,0.2f,0.0f);
	smokeModel->setParam(PARAM_SIZE,5.0,10.0f);
	smokeModel->setParam(PARAM_TEXTURE_INDEX,0.0f,4.0f);
	smokeModel->setParam(PARAM_ANGLE,0.0f,2.0f * PI,0.0f,2.0f * PI);
	smokeModel->setLifeTime(5.0f,5.0f);

	interpolator = smokeModel->getInterpolator(PARAM_ALPHA);
	interpolator->addEntry(0.0f,0.0f);
	interpolator->addEntry(0.2f,0.2f);
	interpolator->addEntry(1.0f,0.0f);

	// Emitters
	// The emitters are arranged so that the fire looks realistic
	StraightEmitter* fireEmitter1 = StraightEmitter::create(Vector3D(0.0f,1.0f,0.0f));
	fireEmitter1->setZone(Sphere::create(Vector3D(0.0f,-1.0f,0.0f),0.5f));
	fireEmitter1->setFlow(40);
	fireEmitter1->setForce(1.0f,2.5f);

	StraightEmitter* fireEmitter2 = StraightEmitter::create(Vector3D(1.0f,0.6f,0.0f));
	fireEmitter2->setZone(Sphere::create(Vector3D(0.15f,-1.2f,0.075f),0.1f));
	fireEmitter2->setFlow(15);
	fireEmitter2->setForce(0.5f,1.5f);

	StraightEmitter* fireEmitter3 = StraightEmitter::create(Vector3D(-0.6f,0.8f,-0.8f));
	fireEmitter3->setZone(Sphere::create(Vector3D(-0.375f,-1.15f,-0.375f),0.3f));
	fireEmitter3->setFlow(15);
	fireEmitter3->setForce(0.5f,1.5f);

	StraightEmitter* fireEmitter4 = StraightEmitter::create(Vector3D(-0.8f,0.5f,0.2f));
	fireEmitter4->setZone(Sphere::create(Vector3D(-0.255f,-1.2f,0.225f),0.2f));
	fireEmitter4->setFlow(10);
	fireEmitter4->setForce(0.5f,1.5f);

	StraightEmitter* fireEmitter5 = StraightEmitter::create(Vector3D(0.1f,0.8f,-1.0f));
	fireEmitter5->setZone(Sphere::create(Vector3D(-0.075f,-1.2f,-0.3f),0.2f));
	fireEmitter5->setFlow(10);
	fireEmitter5->setForce(0.5f,1.5f);

	smokeEmitter = SphericEmitter::create(Vector3D(0.0f,1.0f,0.0f),0.0f,0.5f * PI);
	smokeEmitter->setZone(Sphere::create(Vector3D(),1.2f));
	smokeEmitter->setFlow(25);
	smokeEmitter->setForce(0.5f,1.0f);

	// Groups
	fireGroup = Group::create(fireModel,135);
	fireGroup->addEmitter(fireEmitter1);
	fireGroup->addEmitter(fireEmitter2);
	fireGroup->addEmitter(fireEmitter3);
	fireGroup->addEmitter(fireEmitter4);
	fireGroup->addEmitter(fireEmitter5);
	fireGroup->setRenderer(fireRenderer);
	fireGroup->setGravity(Vector3D(0.0f,3.0f,0.0f));
	fireGroup->enableAABBComputing(true);

	smokeGroup = Group::create(smokeModel,135);
	smokeGroup->addEmitter(smokeEmitter);
	smokeGroup->setRenderer(smokeRenderer);
	smokeGroup->setGravity(Vector3D(0.0f,0.4f,0.0f));
	smokeGroup->enableAABBComputing(true);

	// System
	particleSystem = IRRSystem::create(smgr->getRootSceneNode(),smgr);
	particleSystem->addGroup(smokeGroup);
	particleSystem->addGroup(fireGroup);
	particleSystem->enableAABBComputing(true);

	// setup some useful variables
//	float time=(f32)device->getTimer()->getTime() / 1000.0f,oldtime,deltaTime;
	float step = 0.0f;
	float lastLightTime = 0;

	cout << "\nSPARK FACTORY AFTER INIT :" << endl;
	SPKFactory::getInstance().traceAll();

	return Py_BuildValue("");
#endif
}

