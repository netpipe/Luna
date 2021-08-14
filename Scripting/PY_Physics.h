#include "../config.h"
#ifdef PYTHON
///PHYSICS

//fix infinite falling if over level ground checks - maybe put back to point of falling off and turn down gravity untill back on solid ground. use a fall point for each player . maybe optional game exit if looping.

//PyObject * Python::PyFALLCALL(PyObject * self,PyObject * args){
// might be for futuristic vr setup if you get stuck in a game after you get out of a vehicle or something.
//}

PyMethodDef irr_Physics[] = {
    {"loadTrack",Python::PyIrr_LoadTrack,METH_VARARGS,"Load Track"},
	{"LoadShape",Python::PyIrr_LoadShape,METH_VARARGS,"Loads a texture"}, //notsure what this was
	{"ragman",Python::PyIrr_RagMan,METH_VARARGS,"PyIrr_RagMan"},
    {"load_vehicle",Python::PyIrr_LoadVehicle,METH_VARARGS,"Loads a vehicle"},
    {"chopper",Python::PyIrr_addHelicopter ,METH_VARARGS,"PyIrr_addHelicopter"},
    {"addCar",Python::PyIrr_addCar ,METH_VARARGS,"PyIrr_addCar"},
    {"bulletBlend",Python::PyIrr_BulletBlend,METH_VARARGS,"PyIrr_BulletBlend"},
    {"addHUD",Python::PyIrr_addHUD,METH_VARARGS,"PyIrr_addHUD"},
    {"opensteer",Python::PyIrr_OpenSteer,METH_VARARGS,"PyIrr_OpenSteer"},
    {"addPlayer",Python::PyIrr_addPlayer,METH_VARARGS,"PyIrr_addPlayer"},
    {"bullet",Python::PyIrr_Bullet,METH_VARARGS,"PyIrr_Bullet"},
    {"VehicleParams",Python::PyIrr_VehicleParams,METH_VARARGS,"VehicleParams"},
	{NULL,NULL,0,NULL}
	};

PyObject * Python::PyIrr_recast(PyObject * self,PyObject * args){
//io::IFileSystem* fs = device->getFileSystem();
	//fs->addFileArchive(IRRLICHT_DIR);
	//#define IRRLICHT_DIR "media"
	char * path;
	PyArg_ParseTuple(args,"s",&path);
#ifdef RECAST
	char * MODEL_FILE = path;//"./media/dungeon.obj"
	node = smgr->addOctreeSceneNode(smgr->getMesh(MODEL_FILE));
	smgr->getMeshManipulator()->setVertexColorAlpha(smgr->getMesh(MODEL_FILE), 2);

	//node->getMaterial(0).MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
	//node->getMaterial(0).MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
	node->getMaterial(0).MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;
	node->getMaterial(0).Lighting = false;
	node->setDebugDataVisible(scene::EDS_BBOX);

	scene::IMeshBuffer* buffer = smgr->getMesh(MODEL_FILE)->getMesh(0)->getMeshBuffer(0);
	if (buffer)
	{
		recast = new RecastUtil();
		if (recast->handleBuild(buffer))
		{
			scene::SMesh* smesh = new scene::SMesh();
			if (!recast->setupIrrSMeshFromRecastDetailMesh(smesh))
			{
				printf("recast->setupIrrSMeshFromRecastDetailMesh(smesh): FAILED!\n");
			}
			else
			{
				naviNode = smgr->addOctreeSceneNode(smesh);
				//naviNode->setDebugDataVisible(scene::EDS_FULL);
				naviNode->setDebugDataVisible(scene::EDS_MESH_WIRE_OVERLAY);
			}
			smesh->drop();
		}
	}
#endif
	//vector<irr::core::vector3df> lstPoints = recast->returnPath(vector3df_Start, vector3df_End);
//void RecastUtilM::resetCommonSettings()
//{
//m_cellSize = 4.0f; // 0.3f;
//m_cellHeight = 0.2f;
//m_agentHeight = 2.0f;
//m_agentRadius = 0.6f;
//m_agentMaxClimb = 0.9f;
//m_agentMaxSlope = 45.0f;
//m_regionMinSize = 8;
//m_regionMergeSize = 20;
//m_monotonePartitioning = false;
//m_edgeMaxLen = 12.0f;
//m_edgeMaxError = 1.3f;
//m_vertsPerPoly = 6.0f;
//m_detailSampleDist = 6.0f;
//m_detailSampleMaxError = 1.0f;
//}
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_VehicleParams(PyObject * self,PyObject * args){
#ifdef PHYSICS
    float state,ammount,y,z;
    int param;
    long mVehicle;
   // char * param;
    PyArg_ParseTuple(args,"liffff",&mVehicle,&param,&state,&ammount,&y,&z);
 //   vector3df* position = VehicleParam(mVehicle,param,state,ammount,y,z);
	enum eparam{reset,accelerate,reverse,ebrake,brake,lsteer,rsteer};

	Vehicle *vehicle = (Vehicle *)mVehicle;
	//if param = "accelerate"
	//	action = 1

	//std::map<std::string, eparam> nodeMap;
	//int Iparam = nodeMap[param];
	//nodeMap["Cone"] = NODES::Cone;
	//nodeMap["Cone"] = ;

//prob need one map for state too
	int Iparam=param;
	if ( state==0 ){  // use state for get and set var
       switch (Iparam){

            case eparam(reset):
             //   m_cVehicle->resetVehicle();
				vehicle->resetVehicle();
                break;

            case accelerate:
                vehicle->accelerate(1);
            break;

            case reverse:
                vehicle->reverse(1);
                break;
            case ebrake: //wind resistance
                vehicle->reverse(ammount);
                printf("ebrake");
            break;

            case brake:
            	//printf('braking');
                                vehicle->brake();
//                   if (mEvent.getKeyState(    irr::EKEY_CODE( 0x26 ) ))//KEY_UP)  ) ///| getkey.keyUP
//                            {m_cVehicle->accelerate(1);}// need gears or something haha
//                    else if (!mEvent.getKeyState(  KEY_UP) && (m_cVehicle->getState() != EVEHICLE_REVERSING))
                        //    m_cVehicle->accelerate(-1);   //wind resistance
                break;

            case lsteer:
                vehicle->steer_left();
                break;

            case rsteer:
         //       printf("steer right");
                vehicle->steer_right();
                break;
			case 7:

            case 8:
            	vehicle->renderme();
                break;
            case 9:
                vehicle->steer_reset();
                break;
            case 10:
                printf ("case 10");
//                            vector3df ha = camera->getAbsolutePosition();
//      //  printf("Jump position: %f %f %f \n", pos[0], pos[1], pos[2]);
//        camera->setPosition(vector3df( ha.X, ha.Y+40, ha.Z));
                           //     luna->m_cPhysics->createBox( btVector3(pos.X, pos.Y, pos.Z), btVector3(scl.X, scl.Y, scl.Z), 10); //weight
            break;
            case 11:
                   vehicle->setPosition(vector3df(ammount,y,z));

            break;
            case 12:
                break;
       }

    } else if (state==1) {   //get vars
	//int returnvar;
		switch (param){
			case 0:
	//				returnvar = m_cVehicle->getState();
					return Py_BuildValue("i",m_cVehicle->getState());
				break;
			case 1:
				vector3df position = vehicle->getPosition();
	///				return Py_BuildValue("l",position);
			break;
		}
    }
  return Py_BuildValue("");
  #endif
    return Py_BuildValue("");
}

int osteerinit =0;
PyObject * Python::PyIrr_OpenSteer(PyObject * self,PyObject * args){
	#ifdef OPENSTEER
	//vector3df loc;
	//char * path;
	//PyArg_ParseTuple(args,"sfff",&loc.X,&loc.Y,&loc.Z);
	PyArg_ParseTuple(args,"");
    opensteer = 1;
    // initialize graphics first !!!
//         if( osteerinit ) {
    OpenSteer::initializeGraphics(device);
    // initialize OpenSteerDemo application
	OpenSteer::OpenSteerDemo::initialize();
    OpenSteer::OpenSteerDemo::selectNextPlugIn();
 //  OpenSteer::OpenSteerDemo::selectNextPlugIn();
//       OpenSteer::OpenSteerDemo::selectNextPlugIn();
//       }else {// or restart
//    OpenSteer::OpenSteerDemo::selectNextPlugIn();
//    }
    // were going to need more to this function maybe some internal calls for things like individual paths
  #endif
//        Py_RETURN_NONE;
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_addHelicopter(PyObject * self,PyObject * args) {
	// return scene node and assign camera vector or parrent camera to scene.
	vector3df loc;
	char * path;
	PyArg_ParseTuple(args,"sfff",&path,&loc.X,&loc.Y,&loc.Z);
#ifdef CHOPPER
//active camera
  //  #ifdef CHOPPER
    IAnimatedMesh* mesh = smgr->getMesh(path);
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
    chopperControl = new ChopperControl(device, node);
    chopperControl->setEventRec( &mEvent );
    chopperEnabled = true;
 //   camera->bindTargetAndRotation(node);
 //   #endif
     //device->getSceneManager()->isCulled(node);
	return Py_BuildValue("l",chopperControl);
#endif
	return Py_BuildValue("");
}

PyObject * Python::PyIrr_BulletBlend(PyObject * self,PyObject * args) {
	vector3df loc;
	int thing;
	char *file2;
	//place open file dialogue here and get rid of this list to clean up the source
	//PyArg_ParseTuple(args,"fffi",&loc.X,&loc.Y,&loc.Z,thing);
	PyArg_ParseTuple(args,"s",&file2);

    #ifdef BULLETBLEND
    	int verboseDumpAllTypes = 0;
        int verboseDumpAllBlocks = 0;
//        const char* fileName = "../media/data/clubsilo_packed.blend";
        const char* fileName = file2;
   //    const char* fileName = "../media/data/0_FPS_Template.blend";
     //  	const char* fileName = "../media/data/PhysicsAnimationBakingDemo.blend";// 32 bit, 2.48
	//const char* fileName = "./irrkit/cube_tex_250_64bit.blend";// 64 bit, 2.48
	//const char* fileName = "./irrkit/slideshow_249.blend"; //blender 2.49b -> no conversion if using bParse
	//const char* fileName = "./irrkit/start_menu.blend"; //blender 2.49b -> no conversion if using bParse
	//const char* fileName = "./irrkit/PhysicsAnimationBakingDemo.blend";
	//const char* fileName = "./irrkit/land_rover_92.blend";//64 bit .blend test
	//const char* fileName = "./irrkit/land_rover_92_249.blend";
	//const char* fileName = "./irrkit/BigEndian.blend";
	//const char* fileName = "./irrkit/BigEndian_250.blend"; //forward compatibility
	//const char* fileName = "../media/data/hinge.blend";
	//const char* fileName = "./irrkit/PhysicsAnimationBakingDemo_250.blend";
	//const char* fileName = "./irrkit/test32bit.blend";
	//const char* fileName = "../media/data/1_water_mill.blend";//testing hierarchy (child-parent)
	//const char* fileName = "./irrkit/cube_ipo_180.blend";
	//const char* fileName = "./irrkit/cube_ipo_249b.blend";
	//const char* fileName = "./irrkit/land_rover_92_.blend";
	//const char* fileName = "./irrkit/cube_tex_204.blend"; //test exported from an old Blender 2.04 version
	//const char* fileName = "../media/data/game_250_zipped.blend";
	//const char* fileName = "./irrkit/1.blend";

     //   const char* fileName = "./game.blend";
        FILE* file = fopen(fileName,"rb");
#define TEST_ECHO_BLEND_READER
#ifdef TEST_ECHO_BLEND_READER
    	int fileLen;
        char*memoryBuffer =  btReadBuffer(file,&fileLen);

		IrrBlendNew	bulletBlendReaderNew(device ,smgr,luna->m_cPhysics->getDynamicsWorld(),logicManager);
		if (!bulletBlendReaderNew.readFile(memoryBuffer,fileLen,verboseDumpAllTypes))//if (!bulletBlendReader.openFile("./data/huge.blend"))
		{
			fclose(file);
			exit(0);
		}
		bulletBlendReaderNew.convertAllObjects(verboseDumpAllBlocks);
		fseek(file, 0, SEEK_SET); /* seek to start */
		//		m_cPhysics->dynamicsWorld->setGravity(btVector3(0,-60,0));
#else
	IrrlichtBulletBlendReader	bulletBlendReader(device,smgr,luna->m_cPhysics->getDynamicsWorld(),logicManager);
	if (!bulletBlendReader.readFile(file,verboseDumpAllTypes))
	{
//		printf("cannot read Blender file %s.\n",argv[1]);
		fclose(file);
		exit(0);
	} else
	{
		bulletBlendReader.convertAllObjects(verboseDumpAllBlocks);
	}
#endif

    #endif
     Py_RETURN_NONE;
}

PyObject * Python::PyIrr_addCar(PyObject * self,PyObject * args){
	//vehicle manager
	vector3df loc; //drop point

	float scaleT,scaleE;
	vector3df btCarScale, btModelscale,m_vehiclePosition;

	int vehicleWeight;
	float maxBreakingForce, maxEngineForce,SpeedINC;
	int Ctype=1;
	float connectionHeight,suspensionStiffness,suspensionDamping,
	suspensionCompression,rollInfluence,wheelFriction,wheelRadius,
	wheelWidth,steeringIncrement, steeringClamp, CUBE_HALF_EXTENTS ,
	wheelSpacingX,wheelScaleFactor;

	char * model,*texture;
	stringc model2,texture2;
	//std::string model3,texture3;

	//model2 =  stringc("data/models/vehicles/oldChevy-Truck.3ds";
	//texture2 = "data/models/vehicles/oldChevy.bmp";
	//float suspensionRestLength2,
	//float wheelSpacingZ2,
	//float wheelSpacingZ22,


	// 31 variables
	PyArg_ParseTuple(args,"ssfffffffffffifffifffffffffffff",&model,&texture,&scaleT,&scaleE,
	&btCarScale.X,&btCarScale.Y,&btCarScale.Z,
	&btModelscale.X,&btModelscale.Y,&btModelscale.Z,
	&m_vehiclePosition.X,&m_vehiclePosition.Y,&m_vehiclePosition.Z,

	&vehicleWeight,&maxBreakingForce, &maxEngineForce,&SpeedINC, &Ctype, &connectionHeight,&suspensionStiffness,&suspensionDamping,
	&suspensionCompression,&rollInfluence,&wheelFriction,&wheelRadius,&wheelWidth,&steeringIncrement, &steeringClamp, &CUBE_HALF_EXTENTS,
	&wheelSpacingX,&wheelScaleFactor);

	//std::string   model3(model); //new stringc(model);
	//std::string texture3(texture); //new stringc(model);

	//printf (model2.c_str());
	//printf (texture2.c_str());

	//wprintf (conv_message);

	//model2 		= "data/models/vehicles/oldChevy-Truck.3ds";
	//texture2 	= "data/models/vehicles/oldChevy.bmp";
	//printf ("collision scale checker %f%f%f \n",btCarScaleX,btCarScaleY,btCarScaleZ);
	//printf ("car model scale checker %f%f%f \n",btModelscaleX,btModelscaleY,btModelscaleZ);
	//printf ("car model scale checker %f%f%f \n",m_vehiclePositionX,m_vehiclePositionY,m_vehiclePositionZ);
	//printf ("wheelSpacingX %f wheelScaleFactor %f \n",wheelSpacingX,wheelScaleFactor);
	//model3 		 = model;
	//texture3	 = texture;

	//todo figure out stringc copy to string

	//strcpy(model,model2); // possibly a 20 char limitation
	//strcpy(texture,texture2);

	//str(model,model2);
	//str(texture,texture2);
#ifdef PHYSICS
    #ifdef BULLETCAR
    bCar=1;
         Vehicle* m_cVehicle = new Vehicle;
         m_cVehicle->registerIrrDevice(*device);
         #ifdef PHYSICS
         m_cVehicle->registerPhysics(*luna->m_cPhysics);
         #endif
         m_cVehicle->registerScene(*m_cScene);
         m_cVehicle->registerCamera(camera);

        m_cVehicle->SetParams(
        scaleT,scaleE,
        btVector3(btCarScale.X,btCarScale.Y,btCarScale.Z),
		btVector3(btModelscale.X,btModelscale.Y,btModelscale.Z),
		btVector3(m_vehiclePosition.X,m_vehiclePosition.Y,m_vehiclePosition.Z),
        vehicleWeight,maxBreakingForce, maxEngineForce,SpeedINC,
        Ctype, connectionHeight,suspensionStiffness,suspensionDamping,
        suspensionCompression,rollInfluence,
        wheelFriction,wheelRadius,wheelWidth,steeringIncrement, steeringClamp, CUBE_HALF_EXTENTS,
        wheelSpacingX,wheelScaleFactor);

        m_cVehicle->initPhysics(stringc(model),stringc(texture));

//         m_cVehicle->setEventRec();
//     //!testing second vehicle
 //if second car

//      m_cVehicle2 = new Vehicle;
//       m_cVehicle2->registerIrrDevice(*device);
//        m_cVehicle2->registerPhysics(*luna->m_cPhysics);
//       m_cVehicle2->registerScene(*m_cScene);
//		m_cVehicle2->reverse(1223);
//       m_cVehicle2->initPhysics(stringc(model),stringc(texture));
//       #define CAR2
//       m_cVehicle2->setVehiclePosition(vector3df(10,0,10));
//       ISceneNode* nodee = smgr->addCubeSceneNode(1);
//       btVector3 btCarScale = m_cVehicle2->btCarScale;
//        node->setScale(vector3df(btCarScale[0],btCarScale[1],btCarScale[2]));
//        node->setMaterialFlag(video::EMF_LIGHTING, false);

  //   Vehicles->push_back(m_cVehicle);
return Py_BuildValue("l",m_cVehicle);
#endif
#endif
return Py_BuildValue("");

}

PyObject * Python::PyIrr_Bullet(PyObject * self,PyObject * args){
return Py_BuildValue("");
}

PyObject * Python::PyIrr_RagMan(PyObject * self,PyObject * args){
// params node id and mesh ?
    #ifdef RAGDOLL
    v_RagDolls.push_back(new RagDoll(luna->m_cPhysics->getDynamicsWorld(),smgr, btVector3(0,55,0), btScalar(5.0)));
    #endif
return Py_BuildValue("");
}

PyObject * Python::PyIrr_LoadVehicle(PyObject * self,PyObject * args){
	 return Py_BuildValue("");
	}

PyObject * Python::PyIrr_LoadTrack(PyObject * self,PyObject * args){
	#ifdef TERRAIN
	#ifdef PHYSICS
		tr.setIdentity();
		#endif
	#endif
    int param,state,ammount;
    char * path;
    //char * file;
    std::string path2;
    PyArg_ParseTuple(args,"siii",&path,&param,&ammount,&state);
    path2 = path;

    #ifdef LOADLEVELS
	stringc rootdir = "./";

	//path* rootdir = device->getFileSystem()->getAbsolutePath(path)
	stringc filedir = device->getFileSystem()->getFileDir (path);
	stringc file = device->getFileSystem()->getFileBasename (path);
	//rootdir = device->getFileSystem()->getWorkingDirectory();
	rootdir = device->getFileSystem()->getAbsolutePath(rootdir);
	stringc absFile = device->getFileSystem()->getAbsolutePath(path);
     // for security specify the data/levels folder.
     // make the levels in pathname dynamic.

	irr::core::stringc extension;

	irr::core::getFileNameExtension(extension, path);
	printf ("extenstion is %s", extension.c_str());

	int tscale=param ;
    vector3df trackScale = vector3df(tscale,tscale,tscale); //50
    vector3df trackPosition = vector3df(0,0.0f,0);
	IAnimatedMeshSceneNode *node;
	IAnimatedMesh *mesh;
	if ( extension == ".irr"){
		device->getFileSystem()->changeWorkingDirectoryTo(filedir.c_str());
		device->getSceneManager()->loadScene(absFile);  // LOADSCENE not LOADTRACK
		rfm(smgr->getRootSceneNode());
		device->getFileSystem()->changeWorkingDirectoryTo(rootdir.c_str());
		return Py_BuildValue("");
	}else{
     //   device->getFileSystem()->changeWorkingDirectoryTo("../../");
        device->getFileSystem()->changeWorkingDirectoryTo(filedir.c_str());
        mesh = device->getSceneManager()->getMesh(absFile); //.c_str()+file.c_str()
  //  IAnimatedMesh *mesh = device->getSceneManager()->getMesh(path2.c_str());

		device->getSceneManager()->getMeshManipulator()->scaleMesh(mesh,trackScale);
		node = device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
//         if(!m_irrDevice) return;
		smgr->getMeshManipulator()->makePlanarTextureMapping(
		mesh, 0.004f);
   // if(!mesh || !node) return;
    node->setAutomaticCulling(EAC_OFF);
     node->setMaterialFlag(EMF_LIGHTING, true);
    // node->setScale(trackScale);
    // node->setRotation(vector3df(45,90.f,110));
    node->setPosition(trackPosition);
     //   m_cVehicle->loadLevel(track.c_str());
		device->getFileSystem()->changeWorkingDirectoryTo(rootdir.c_str());
	#ifndef PHYSICS
	#ifdef IRRCD
    metaSelector = device->getSceneManager()->createMetaTriangleSelector();
    selector = device->getSceneManager()->createOctTreeTriangleSelector(mesh,node,128);
    node->setTriangleSelector(selector);
    metaSelector->addTriangleSelector(selector);
    selector->drop();

    //meshbuffer converter to IMesh
    // scene::SMesh* mesh2 = new SMesh; // dont really need this
    // mesh2->addMeshBuffer (meshBuffer2);
    // mesh2->drop();

    scene::ISceneNodeAnimator* anim;
	anim = device->getSceneManager()->createCollisionResponseAnimator(
		metaSelector, camera, core::vector3df(30,60,30),
		core::vector3df(0,0,0),   /// MAIN irrGRAVITY
		core::vector3df(0,10,0));
    camera->addAnimator(anim);
   // m_cInGameEvents.chopperControl->onCollision(anim);
    anim->drop();
	metaSelector->drop();
#endif
#endif

#ifdef PHYSICS
    tr.setOrigin(btVector3(trackPosition.X, trackPosition.Y, trackPosition.Z));
    btTriangleMesh *collisionMesh = new btTriangleMesh();

  //  m_cScene->setGenericMaterial(node, 0);

    int meshCount = mesh->getMeshBufferCount();
        printf("MESHBUFFER COUNT %d /n",meshCount);

        for (int i=0; i < meshCount ; i++)//!load all meshes for CD
        {
            //  meshBuffer2->append( mesh->getMeshBuffer(i) );
          //  m_cScene->setGenericMaterial(node, i); //outdoor sun lumenation
            luna->m_cPhysics->convertIrrMeshBufferBtTriangleMesh(mesh->getMeshBuffer(i), collisionMesh, vector3df(1,1,1));
            //decalManager->addMesh(mesh->getMeshBuffer(i));
        }

    btBvhTriangleMeshShape *trackShape = new btBvhTriangleMeshShape(collisionMesh, true);
    btRigidBody *test = luna->m_cPhysics->localCreateRigidBody(0, tr, trackShape, node);
#endif
//        // Create a meta triangle selector to hold several triangle selectors.
//        scene::IMetaTriangleSelector * metaSelector = smgr->createMetaTriangleSelector();
//        m_cVehicle->recursiveFillMetaSelector( smgr->getRootSceneNode(), metaSelector );
//
//        scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
//                metaSelector, camera, core::vector3df(5,5,5),
//                core::vector3df(0,0,0));
//        metaSelector->drop(); // I'm done with the meta selector now
//        camera->addAnimator(anim);
//        anim->drop(); // I'm done with the animator now
//
//        //reads xml model names then removes the node
//        ISceneNode *node = 0;
//        u32 i = 0;
//
//        while((node = device->getSceneManager()->getSceneNodeFromName("powercell", 0)))
//         {
//
//            if(node)
//             {
//                //   PowerCell::Instance()->Add(node->getPosition());
//                node->remove();
//                printf("powercell Node removed");
//                i++;
//             }
//        while((node = device->getSceneManager()->getSceneNodeFromName("playerstart2", 0)))
//         {
//            if(node)
//             {
//                //   PowerCell::Instance()->Add(node->getPosition());
//                node->remove();
//                printf("playerStart Node removed");
//                i++;
//             }
//         }
//         }
return Py_BuildValue("l",test);
	}

    #endif
      return Py_BuildValue("");
}

void Python::rfm(ISceneNode* node ) //level loader
{
  //
  // the following if is basically the same as ISceneNode_assignTriangleSelector
  //
//  Output::Instance()->w("Node name is: %s \n",node->getName());
 // Output::Instance()->w("Node id is: %d \n",node->getID());
 // Output::Instance()->w("Node type: ");

  if(strcmp(node->getName(), "elevator") == 0)
  {
  	node->setMaterialType(EMT_LIGHTMAP_M4);
  	node->setMaterialFlag(EMF_LIGHTING, false);
  //  Elevator::Instance()->Add(node);
  //  Elevator::Instance()->elevatorStart = node->getAbsolutePosition();
  }

//   if(strcmp(node->getName(), "wheel") == 0)
//  {
//		 vector3df wheels node->getAbsolutePosition();
//		node->setPosition(wheels);
//  }

  if(strcmp(node->getName(), "obstacle") == 0)
  {
	//	Obstacle::Instance()->Add(node);
  }
  if(strcmp(node->getName(), "level") == 0)
  {
    //! Enable fog for all materials on the level node.
    /*
    u32 materialCount = node->getMaterialCount();
    for(s32 i = 0; i < materialCount; i++)
    {
      node->getMaterial(i).FogEnable = false;
    }
    */
//    node->setMaterialFlag(EMF_FOG_ENABLE, true);
//    node->setMaterialType(EMT_LIGHTMAP_M4);
//    node->setMaterialFlag(EMF_LIGHTING, false);
	}
	if(strcmp(node->getName(), "glass") == 0)
	{
//    node->setMaterialTexture(1,	irrDevice->getVideoDriver()->getTexture("StageData/glass.tga"));
//    node->setMaterialFlag(EMF_LIGHTING, false);
//    node->setMaterialFlag(EMF_FOG_ENABLE, false);
//    node->setMaterialType(EMT_TRANSPARENT_REFLECTION_2_LAYER);
//
//    SColor col = SColor(255,37,207,243);
//    for(s32 i = 0; i < node->getMaterialCount(); i++)
//    {
//			node->getMaterial(i).Shininess = 0.0f;
//			node->getMaterial(i).DiffuseColor = col;
//			node->getMaterial(i).EmissiveColor = col;
//			node->getMaterial(i).AmbientColor = col;
//			node->getMaterial(i).SpecularColor = col;
//			node->getMaterial(i).MaterialTypeParam = 0.01;
//    }
	}

	if (node->getType() ==   ESNT_UNKNOWN)
	{
	}
	if (node->getType() ==   ESNT_MESH)
	{
      io::IAttributes* attribs = device->getFileSystem()->createEmptyAttributes();
      if (attribs)
        {// get the mesh name out
         node->serializeAttributes(attribs);
         core::stringc name = attribs->getAttributeAsString("Mesh");
         attribs->drop();
         // get the animated mesh for the object
         scene::IAnimatedMesh* mesh = device->getSceneManager()->getMesh(name.c_str());
         if (mesh)
         {
//            Output::Instance()->w("\tAdding triangle selector for mesh\n");
           // scene::ITriangleSelector* selector =
           // device->getSceneManager()->createTriangleSelector(mesh->getMesh(0), node);
           // node->setTriangleSelector(selector);
           // metaSelector->addTriangleSelector(selector);
           // selector->drop();

            node->setMaterialFlag(video::EMF_LIGHTING, true);
            node->getMaterial(0).Shininess = 100.0f;
            node->getMaterial(0).DiffuseColor = SColor(255,255,255,255);
            node->getMaterial(0).EmissiveColor = SColor(255,255,255,255);
            node->getMaterial(0).AmbientColor = SColor(255,255,255,255);
            node->getMaterial(0).SpecularColor = SColor(255,255,255,255);
            node->getMaterial(0).MaterialTypeParam = 0.01;

            //node->getMaterial(0).MaterialType = EMT_ONETEXTURE_BLEND;
            //node->setFlag(EMF_TRILINEAR_FILTER, true);
            #ifdef TERRAIN
            #ifdef PHYSICS
			tr.setOrigin(btVector3(0,0,0));
		#endif
		#endif

		#ifdef PHYSICS
			btTriangleMesh *collisionMesh = new btTriangleMesh();
		#endif
//#define PYTHON
  //  m_cScene->setGenericMaterial(node, 0);

    int meshCount = mesh->getMeshBufferCount();
	printf("MESHBUFFER COUNT %d /n",meshCount);

	for (int i=0; i < meshCount ; i++)//!load all meshes for CD
	{
            //  meshBuffer2->append( mesh->getMeshBuffer(i) );
          //  m_cScene->setGenericMaterial(node, i); //outdoor sun lumenation
          #ifdef PHYSICS
            luna->m_cPhysics->convertIrrMeshBufferBtTriangleMesh(mesh->getMeshBuffer(i), collisionMesh, vector3df(1,1,1));
            //decalManager->addMesh(mesh->getMeshBuffer(i));
            #endif
	}
 #ifdef PHYSICS
	btBvhTriangleMeshShape *trackShape = new btBvhTriangleMeshShape(collisionMesh, true);
    btRigidBody *test = luna->m_cPhysics->localCreateRigidBody(0, tr, trackShape, node);
 #endif
		}
	}
  }
  if (node->getType() ==   ESNT_ANIMATED_MESH)
//    Output::Instance()->w("Animated Mesh! \n\n");
  if (node->getType() ==   ESNT_SKY_BOX)
//    Output::Instance()->w("SkyBox! \n\n");
  if (node->getType() ==   ESNT_CAMERA_FPS)
//    Output::Instance()->w("Fps Camera! \n\n");
  if (node->getType() ==   ESNT_CAMERA_MAYA )
//    Output::Instance()->w("Maya Camera! \n\n");
  if (node->getType() ==   ESNT_CAMERA )
//    Output::Instance()->w("STD Camera! \n");
  if (node->getType() ==   ESNT_PARTICLE_SYSTEM )
//    Output::Instance()->w("Particles! \n\n");
  if (node->getType() ==   ESNT_LIGHT  )
  {
//    Output::Instance()->w("Light! \n\n");
  }
  if (node->getType() ==   ESNT_OCTREE)
  {
      // Occ Trees are for land
//      Output::Instance()->w("Occtree! \n");
      io::IAttributes* attribs = device->getFileSystem()->createEmptyAttributes();
      if (attribs)
        {// get the mesh name out
         node->serializeAttributes(attribs);
         core::stringc name = attribs->getAttributeAsString("Mesh");
         attribs->drop();
         // get the animated mesh for the object
         scene::IAnimatedMesh* mesh = device->getSceneManager()->getMesh(name.c_str());
         if (mesh)
         {
           // scene::ITriangleSelector* selector =
           // device->getSceneManager()->createOctTreeTriangleSelector(mesh->getMesh(0), node, 128);
           // node->setTriangleSelector(selector);
          //  metaSelector->addTriangleSelector(selector);
           // selector->drop();
                //tr.setOrigin(btVector3(trackPosition.X, trackPosition.Y, trackPosition.Z));
//         btTriangleMesh *collisionMesh = new btTriangleMesh();
//
//  //  m_cScene->setGenericMaterial(node, 0);
//
//    int meshCount = mesh->getMeshBufferCount();
//        printf("MESHBUFFER COUNT %d /n",meshCount);
//
//        for (int i=0; i < meshCount ; i++)//!load all meshes for CD
//        {
//            //  meshBuffer2->append( mesh->getMeshBuffer(i) );
//          //  m_cScene->setGenericMaterial(node, i); //outdoor sun lumenation
//            luna->m_cPhysics->convertIrrMeshBufferBtTriangleMesh(mesh->getMeshBuffer(i), collisionMesh, vector3df(1,1,1));
//            //decalManager->addMesh(mesh->getMeshBuffer(i));
//        }
//
//    btBvhTriangleMeshShape *trackShape = new btBvhTriangleMeshShape(collisionMesh, true);
//    btRigidBody *test = luna->m_cPhysics->localCreateRigidBody(0, tr, trackShape, node);
         }

     }

  }
  // now recurse on children...
  core::list<scene::ISceneNode*>::ConstIterator begin = node->getChildren().begin();
  core::list<scene::ISceneNode*>::ConstIterator end   = node->getChildren().end();

  for (; begin != end; ++begin)
    rfm(*begin);
}

//Collision::Instance()->createRootCollision();

//material system for friction / lusture / magnetic / density
#endif
