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

    // open terrain tree layout could probably even load grass sametime.
        if(btree == 1){
            terr->MakeTrees();
        }
return Py_BuildValue("1");
}


PyObject * Python::PyIrr_Reset(PyObject * self,PyObject * args){
    //would like to have a reset and compile function here maybe dynamically load all the
    //clear all models
    //save then reload externally before recompiling

    //shutdown/restart python and load a noscript loaded screen.
return Py_BuildValue("0");
}


//simple cube no physics. returns nodeid
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
	}
	else
	{
		return Py_BuildValue("0");
	};
return Py_BuildValue("l",node_id);
};

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
