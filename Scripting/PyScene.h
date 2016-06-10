///SCENENODES and SCENESTUFF STUFF  -- included from pyfunctions
///TERRAIN

int btree=0;
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
        terr->Render( vector3df( a1f,a2f,a3f), vector3df(0,0.0f,0),   vector3df(1,0.20f,1),3);

    return Py_BuildValue("l",terr); // not sure if you can do this ?
#endif
return Py_BuildValue("0");
}


PyObject * Python::PyIrr_addTree(PyObject * self,PyObject * args) { // if treepointer passed remove it
    // change addTree to Trees so you can put more functionality into it
    // should be able to cull these aswell as remove them
    // vector stack of loaded tree's
    // refer to tidbits for just one tree's worth of code

    // create a vector stack store the tree pointers in it
    // call add tree one by one push to treemanager.
    // render tree shadow bake to terrain
      Terrain *terr;

    // open terrain tree layout could probably even load grass sametime.
    PyArg_ParseTuple(args,"i",&terr);
    vector3df aha = vector3df(3,3,3);
          int tree =  terr->MakeTrees(aha , 1);
      //  if(btree == 1){

    //    }
return Py_BuildValue("l",tree);
}


PyObject * Python::PyIrr_loadModel(PyObject * self,PyObject * args) { // if treepointer passed remove it ModelFactory


int value1,value2;
char * type,action;

    PyArg_ParseTuple(args,"sll",&type,&value1,&value2,&action);

    enum eaction{loadModel,get,set,animation,};

        switch(action){
    case set:
        break;

        case eaction(eget):     //
                ISceneNode *node = smgr->getSceneNodeFromId(type);
                vector3df position = node->getPosition();
            break;

        case loadModel: //load models // textures


//OVERLAPPING TEXT MOVEMENT FUNCTION FOR  | |  LISTS
//    3DS//    BLEND (Blender)//    DAE/Collada//    FBX//    IFC-STEP//    ASE//    DXF//    HMP//    MD2//    MD3//    MD5
//    MDC//    MDL//    NFF//    PLY//    STL//    X//    OBJ//    OpenGEX//    SMD//    LWO//    LXO//    LWS//    TER//    AC3D
//    MS3D//    COB//    Q3BSP//    XGL//    CSM//    BVH//    B3D//    NDO//    Ogre Binary//    Ogre XML//    Q3D//    ASSBIN (Assimp custom format)
//    glTF (partial)//    3MF

//Additionally, some formats are supported by dependency on non-free code or external SDKs (not built by default):
//
//    C4D (https://github.com/acgessler/assimp-cinema4d)
//
//Exporters:
////    DAE (Collada)//    STL//    OBJ//    PLY//    X//    3DS
//    JSON (for WebGl, via https://github.com/acgessler/assimp2json)
//    ASSBIN//    STEP//    glTF (partial)

        //device->setWindowCaption(L"IrrAssimp Demo");

        IVideoDriver* driver = device->getVideoDriver();
        ISceneManager* smgr = device->getSceneManager();
        IGUIEnvironment* guienv = device->getGUIEnvironment();

    //tecan make sure that renamed files dont trick the parser into loading them. sec

        // The assimp loader is in a separate system and not directly as a meshLoader to give the choice to use Irrlicht or Assimp for mesh loading to the user, in function of the format for example
        IrrAssimp assimp(smgr);

        //IAnimatedMesh* meshNoAssimp = smgr->getMesh("Media/ninja.b3d");
      //  assimp.exportMesh(mesh, "obj", "Media/export.obj");

        if (!mesh /*|| !meshNoAssimp*/)
        {
            device->drop();
    ///		return 1;
        return Py_BuildValue("1");
        }

    if (type =="b3d"){
            IAnimatedMesh* mesh = assimp.getMesh(value1);
        IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
        node->setAnimationSpeed(mesh->getAnimationSpeed()); // Fixed by r5097
        //IAnimatedMeshSceneNode* nodeNoAssimp = smgr->addAnimatedMeshSceneNode( meshNoAssimp );

        if (node /*&& nodeNoAssimp*/)
        {
            //node->setMaterialFlag(EMF_LIGHTING, false);
            node->setDebugDataVisible(scene::EDS_SKELETON | scene::EDS_BBOX_ALL);
            //node->setScale(core::vector3df(100, 100, 100));

            //nodeNoAssimp->setPosition(core::vector3df(100, 0, 0));
            //nodeNoAssimp->setMaterialFlag(EMF_LIGHTING, false);
            //node->setMD2Animation(scene::EMAT_STAND);
            node->setMaterialTexture( 0, driver->getTexture(value2) );
        }
    }


    if (type =="bvh"){
           IAnimatedMesh* mesh = assimp.getMesh("Media/B02.bvh");
        IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
        node->setAnimationSpeed(mesh->getAnimationSpeed()); // Fixed by r5097
        //IAnimatedMeshSceneNode* nodeNoAssimp = smgr->addAnimatedMeshSceneNode( meshNoAssimp );

        if (node /*&& nodeNoAssimp*/)
        {
            //node->setMaterialFlag(EMF_LIGHTING, false);
            node->setDebugDataVisible(scene::EDS_SKELETON | scene::EDS_BBOX_ALL);
            //node->setScale(core::vector3df(100, 100, 100));

            //nodeNoAssimp->setPosition(core::vector3df(100, 0, 0));
            //nodeNoAssimp->setMaterialFlag(EMF_LIGHTING, false);
            //node->setMD2Animation(scene::EMAT_STAND);
            node->setMaterialTexture( 0, driver->getTexture(value2 ));
            	return Py_BuildValue("l",node);
        }

    }

               break;

        }
	return Py_BuildValue("l",node);
}



PyObject * Python::PyIrr_Reset(PyObject * self,PyObject * args){
    //would like to have a reset and compile function here maybe dynamically load all the
    //clear all models
    //save then reload externally before recompiling

    //shutdown/restart python and load a noscript loaded screen.
return Py_BuildValue("0");
}



///
PyObject * Python::PyIrr_setPosition(PyObject * self,PyObject * args){
    s32 node_id;
    int x,y,z;
    PyArg_ParseTuple(args,"llll",&node_id,&x,&y,&z);
    ISceneNode * node = smgr->getSceneNodeFromId(node_id);
    	if(node != NULL)
	{
    node->setPosition(vector3df(x,y,z));
	}

   // printf("%i",node_id);
return Py_BuildValue("");
}

PyObject * Python::PyIrr_getPosition(PyObject * self,PyObject * args){
    //not teste
    s32 node_id;

    PyArg_ParseTuple(args,"llll",&node_id);
    ISceneNode *node = smgr->getSceneNodeFromId(node_id);
    vector3df position = node->getPosition();
return Py_BuildValue("l",position);
}


PyObject * Python::PyIrr_setVelocity(PyObject * self,PyObject * args){

//    ISceneNode *node;
//    int x,y,z;
//	PyArg_ParseTuple(args,"slll",&node,&x,&y,&z);
// if bullet or irrlicht scene node handle methods differently
// inirtia calculation
//	node->setPosition(vector3df(x,y,z));
return Py_BuildValue("0");
}


PyObject * Python::PyIrr_AddCubeSceneNode(PyObject * self,PyObject * args){
	s32 node_id;
	float size;
	float px,py,pz,rx,ry,rz,sx,sy,sz;
	//Damn...thats a lot of parameters :)
	PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);
	ISceneNode * node = smgr->getSceneNodeFromId(node_id);
	if(node == NULL)
	{
		node = smgr->addCubeSceneNode(size,NULL,node_id,
                                vector3df(px,py,pz),
                                vector3df(rx,ry,rz),
                                vector3df(sx,sy,sz));

		node->setMaterialFlag(EMF_LIGHTING,false);

		//node->setPosition(vector3df(50,50,50));
	}
	else
	{
		return Py_BuildValue("");
	};
return Py_BuildValue("l",node_id);
};


PyObject * Python::PyIrr_addSphereNode(PyObject * self,PyObject * args){

    int x,y,z;
   // u8 texture;
    float radius;
	PyArg_ParseTuple(args,"sllll",&radius,&x,&y,&z);
    scene::ISceneNode * node_id = smgr->addSphereSceneNode(20); //radius  polycount , parent , id , position,rotation, scale
//IVideoDriver::createImageFromFile().  //textures and heightmap

//return Py_BuildValue("");
return Py_BuildValue("l",node_id);
};


PyObject * Python::PyIrr_addAnimatedMesh(PyObject * self,PyObject * args){
IAnimatedMesh *mesh ;
s32 meshPath;
	PyArg_ParseTuple(args,"s",&meshPath);
    mesh->getMesh(meshPath);

return Py_BuildValue("l",mesh);
};





PyObject * Python::PyIrr_pauseGame(PyObject * self,PyObject * args){
    luna->m_cInGameEvents.Quit=true;
    }

PyObject * Python::PyIrr_exit(PyObject * self,PyObject * args){
    luna->m_cInGameEvents.Quit=true;
}



/*
int setvideo (){// graphics combo
    gui::IGUIComboBox* box = guienv->addComboBox(
    core::rect<s32>(250,4,350,23),
    0,
    108
  );
  box->addItem(L"No filtering");
  box->addItem(L"Bilinear");
  box->addItem(L"Trilinear");
  box->addItem(L"Anisotropic");
  box->addItem(L"Isotropic");
*/

// NETWORKING PLAYER DATA
// crouching
// loc,rot or normal,look angle,head/camera normal(seperate from body
// model, chat, decals, csgmodifier
