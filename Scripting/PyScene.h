#ifdef PYTHON

#ifdef CSG
//#include "../Scene/IrrCSG/CSG/primitives.h"
//#include "../Scene/IrrCSG/CSG/CSG.h"
#include "../Scene/IrrCSG/LunaCSG.h"
//
//meshMesh mesh;
//
//SMesh* m_pMesh = NULL;
#endif

///SCENENODES and SCENESTUFF STUFF  -- included from pyfunctions
///TERRAIN


PyMethodDef irr_Scene[] =
{
/*
startphysics
loadlevel - subloader for tracks or levels
ragdoll - needs a manager
network connect / info / manager interface
script reload and compile function
reminder to actually check the names match with unstable ide's and whatnot
*/

	{"drawtext",Python::PyIrr_DrawText,METH_VARARGS,"Renders text to the screen with default font"},
	{"add_cube",Python::PyIrr_AddCubeSceneNode,METH_VARARGS,"Adds a cube scene node"},

	{"Reset",Python::PyIrr_Reset,METH_VARARGS,"Reset various parts of scripting system"},
	{"addAMesh",Python::PyIrr_addAnimatedMesh,METH_VARARGS,"PyIrr_addAnimatedMesh"},
	{"addMesh",Python::PyIrr_LoadMesh,METH_VARARGS,"PyIrr_addMesh"},
    {"addModel",Python::PyIrr_loadModel,METH_VARARGS,"load model"},
    {"loadTrack",Python::PyIrr_LoadTrack,METH_VARARGS,"loadTrack"},
    {"loadLevel",Python::PyIrr_LoadLevel,METH_VARARGS,"loadLevel"},
	{"Light",Python::PyIrr_Light,METH_VARARGS,"Light"},
	//input
    {"using",Python::PyIrr_using,METH_VARARGS,"for opening scripts within scripts"},
    {"recast",Python::PyIrr_recast,METH_VARARGS,"recast navigation"},
    {"addWheel",Python::PyIrr_recast,METH_VARARGS,"recast navigation"},
    {"media",Python::PyIrr_media,METH_VARARGS,"media"},
    {"rotation",Python::PyIrr_setRotation,METH_VARARGS,"rotation"},
	{"screen",Python::PyIrr_getScreen,METH_VARARGS,"screenwidth"},


	//scene
    {"tesselate",Python::PyIrr_tesselateImage,METH_VARARGS,"PyIrr_tesselateImage"},
    {"atmosphere",Python::PyIrr_atmosphere,METH_VARARGS,"PyIrr_atmosphere"},

    {"addvideo",Python::PyIrr_addVideo,METH_VARARGS,"PyIrr_addVideo"},
    {"decals",Python::PyIrr_DecalManager,METH_VARARGS,"PyIrr_DecalManager"},
    {"addwater",Python::PyIrr_WaterPlane,METH_VARARGS,"water plane reflective"},
    {"setPosition",Python::PyIrr_setPosition,METH_VARARGS,"setPosition"},
    {"getPosition",Python::PyIrr_getPosition,METH_VARARGS,"getPosition"},
    {"addSphereNode",Python::PyIrr_addSphereNode,METH_VARARGS,"addSphereNode"},

    {"addTerrain",Python::PyIrr_addTerrain,METH_VARARGS,"PyIrr_addTerrain"},
    {"addTree",Python::PyIrr_Trees,METH_VARARGS,"PyIrr_addTree"},
	{"addHUD",Python::PyIrr_addHUD,METH_VARARGS,"PyIrr_addHUD"},
    {"exportScene",Python::PyIrr_ExportScene,METH_VARARGS,"PyIrr_ExportScene"},
    {"SPARK",Python::PyIrr_SPARKA,METH_VARARGS,"SPARK MANAGER"},
    {"grass",Python::PyIrr_FWGrass,METH_VARARGS,"grass"},
    {"postprocess",Python::PyIrr_PostProcess,METH_VARARGS,"postProcess"},
    {"CSG",Python::PyIrr_CSG,METH_VARARGS,"CSG"},

    //Physics
    {"setVelocity",Python::PyIrr_setVelocity,METH_VARARGS,"setVelocity"},

    //Timers


    {"delete",Python::PyIrr_Delete,METH_VARARGS,"delete"},


	{NULL,NULL,0,NULL}
};



int btree=0;


PyObject * Python::PyIrr_CSG(PyObject * self,PyObject * args){
   // printf("loading animated mesh\n");

    char *meshPath;
	PyArg_ParseTuple(args,"s",&meshPath);

	meshMesh mesh;
	initializeMesh(mesh);
	//meshInitializeBox(&mesh, -0.5, 50.5, -50.5, 50.5, -0.5, 0.5);
	SMesh* pMesh = CreateIrrMesh(mesh);

	meshMesh csgMesh = CreateCSGMesh(pMesh);

	SMesh* pIrrMesg = CreateIrrMesh(csgMesh);

	IMeshSceneNode* meshnode = smgr -> addMeshSceneNode(pMesh);
	meshnode->setMaterialFlag(video::EMF_BACK_FACE_CULLING, false);

}

//
//PyObject * Python::PyIrr_LoadAnimatedMesh(PyObject * self,PyObject * args){
//	 return Py_BuildValue("");  }

//
PyObject * Python::PyIrr_LoadMesh(PyObject * self,PyObject * args){
	  return Py_BuildValue("");  }


//
PyObject * Python::PyIrr_addAnimatedMesh(PyObject * self,PyObject * args){
   // printf("loading animated mesh\n");

    char *meshPath;
	PyArg_ParseTuple(args,"s",&meshPath);
       IAnimatedMesh *mesh = smgr->getMesh( meshPath );
//        irr::core::stringc extension;
    //   irr::core::getFileNameExtension(extension, value1);

    	scene::ISceneNode* node = 0;
    printf("loading animated mesh\n");

	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	//	node = smgr->addMeshSceneNode(mesh->getMesh(0));
    //    node = smgr->addAnimatedMeshSceneNode( mesh );

        node->setAutomaticCulling(EAC_OFF);
     node->setMaterialFlag(EMF_LIGHTING, true);
   //     node->getMaterial(0).ZWriteEnable=1;
   //     node->getMaterial(0).BackfaceCulling = true;

    // possibly need a delete through scripting side

return Py_BuildValue("l",mesh);
};

// for loading/creating archives paths and other stuff, should include xml loader
PyObject * Python::PyIrr_media(PyObject * self,PyObject * args){

    char *value1,*value2;
    PyArg_ParseTuple(args,"ss",&value1,&value2);

    if (value1 = "add"){
    device->getFileSystem()->addZipFileArchive(value2);
    printf("adding zip archive to paths\n");
    }
    return Py_BuildValue("");

}

// assimp mesh importer model loader
PyObject * Python::PyIrr_loadModel(PyObject * self,PyObject * args) { // if treepointer passed remove it ModelFactory

    int action;
    char * type,*value1,*value2;
    #ifdef ASSIMP
IrrAssimp assimp(smgr);
    PyArg_ParseTuple(args,"ssi",&value1,&value2,&action);
  //  PyArg_ParseTuple(args,"sss",&value1,&value2,&type);

    action=0;
  //  Assimp::Importer importer;
    irr::core::stringc extension;
   // irr::core::stringc path;
 //  printf ("model loading %s",value1);
//       io::path path;
//    path.append(value1);

   irr::core::getFileNameExtension(extension, value1);
   printf ("extenstion is %s", extension.c_str());
 //   bool extsupport= importer.IsExtensionSupported (extension.c_str());
 //   printf ("%b",extsupport);
 //   path = value1
IAnimatedMeshSceneNode* node;


//                printf ("loading b3d");
//            IAnimatedMesh* mesh = assimp.getMesh(value1);
//            IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
//            //node->setAnimationSpeed(mesh->getAnimationSpeed());
//                node->setDebugDataVisible(scene::EDS_SKELETON | scene::EDS_BBOX_ALL);
//                node->setMaterialTexture( 0, driver->getTexture(value2) );

    enum eaction{load=0,get,set,setTexture,animation};
//    std::map<std::string, eaction> nodeMap;
//    int Iaction nodeMap[action]

switch(action){
    case set:
//                node->setAnimationSpeed(mesh->getAnimationSpeed());
        break;
    case setTexture:            // setting texture would be neat too.

        break;
    case eaction(get):
 //               ISceneNode *node = smgr->getSceneNodeFromId(type);
//                  vector3df position = node->getPosition();
	return Py_BuildValue("l",node);
        break;

    case load: //load models // textures
//if (extsupport){

    //OVERLAPPING TEXT MOVEMENT FUNCTION FOR  | |  LISTS
    //    3DS//    BLEND (Blender)//    DAE/Collada//    FBX//    IFC-STEP//    ASE//    DXF//    HMP//    MD2//    MD3//    MD5
    //    MDC//    MDL//    NFF//    PLY//    STL//    X//    OBJ//    OpenGEX//    SMD//    LWO//    LXO//    LWS//    TER//    AC3D
    //    MS3D//    COB//    Q3BSP//    XGL//    CSM//    BVH//    B3D//    NDO//    Ogre Binary//    Ogre XML//    Q3D//    ASSBIN (Assimp custom format)
    //    glTF (partial)//    3MF
    //Additionally, some formats are supported by dependency on non-free code or external SDKs (not built by default):
    //    C4D (https://github.com/acgessler/assimp-cinema4d)
    //Exporters:
    ////    DAE (Collada)//    STL//    OBJ//    PLY//    X//    3DS
    //    JSON (for WebGl, via https://github.com/acgessler/assimp2json)
    //    ASSBIN//    STEP//    glTF (partial)

        //tecan make sure that renamed files dont trick the parser into loading them. sec
        // The assimp loader is in a separate system and not directly as a meshLoader to give the choice to use Irrlicht or Assimp for mesh loading to the user, in function of the format for example
       //     IrrAssimp assimp(smgr);

        //IAnimatedMesh* meshNoAssimp = smgr->getMesh("Media/ninja.b3d");
        //  assimp.exportMesh(mesh, "obj", "Media/export.obj");
                if ( extension == ".irrmesh" ){ //extension == "b3d"){
                printf ("loading irrmesh");
                      //   IrrAssimp assimp(smgr);
            IAnimatedMesh* mesh = assimp.getMesh(value1);
        //    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
             node = smgr->addAnimatedMeshSceneNode( mesh );
            node->setAnimationSpeed(mesh->getAnimationSpeed()); // Fixed by r5097
            //IAnimatedMeshSceneNode* nodeNoAssimp = smgr->addAnimatedMeshSceneNode( meshNoAssimp );


//            	if (!mesh /*|| !meshNoAssimp*/)
//                {
//                    device->drop();
//                    return 1;
//                }

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
            //     node->setPosition(vector3df(300,300,300));
        }


        if ( extension == ".x" ){ //extension == "b3d"){
                printf ("loading x");
                      //   IrrAssimp assimp(smgr);
            IAnimatedMesh* mesh = assimp.getMesh(value1);
        //    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
             node = smgr->addAnimatedMeshSceneNode( mesh );
            node->setAnimationSpeed(mesh->getAnimationSpeed()); // Fixed by r5097
            //IAnimatedMeshSceneNode* nodeNoAssimp = smgr->addAnimatedMeshSceneNode( meshNoAssimp );


//            	if (!mesh /*|| !meshNoAssimp*/)
//                {
//                    device->drop();
//                    return 1;
//                }

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
            //     node->setPosition(vector3df(300,300,300));
        }

            if ( extension == ".bsp" ){
                printf ("loading bsp");
                //    IrrAssimp assimp(smgr);
            IAnimatedMesh* mesh = assimp.getMesh(value1);
        //  IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
            node = smgr->addAnimatedMeshSceneNode( mesh );

//    int tscale=20 ;
//    vector3df trackScale = vector3df(tscale,tscale,tscale); //50
//    vector3df trackPosition = vector3df(0,0.0f,0);
//
//        IAnimatedMesh *mesh = device->getSceneManager()->getMesh(path);
//  //  IAnimatedMesh *mesh = device->getSceneManager()->getMesh(path2.c_str());
//
//    device->getSceneManager()->getMeshManipulator()->scaleMesh(mesh,trackScale);
//    IAnimatedMeshSceneNode *node = device->getSceneManager()->addAnimatedMeshSceneNode(mesh);


            //node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
           // node->setAnimationSpeed(mesh->getAnimationSpeed()); // Fixed by r5097
            //IAnimatedMeshSceneNode* nodeNoAssimp = smgr->addAnimatedMeshSceneNode( meshNoAssimp );

//            	if (!mesh /*|| !meshNoAssimp*/)
//                {
//                    device->drop();
//                    return 1;
//                }

            if (node /*&& nodeNoAssimp*/)
            {
                //node->setMaterialFlag(EMF_LIGHTING, false);
               // node->setDebugDataVisible(scene::EDS_SKELETON | scene::EDS_BBOX_ALL);
                //node->setScale(core::vector3df(100, 100, 100));

                //nodeNoAssimp->setPosition(core::vector3df(100, 0, 0));
                //nodeNoAssimp->setMaterialFlag(EMF_LIGHTING, false);
                //node->setMD2Animation(scene::EMAT_STAND);
            //    node->setMaterialTexture( 0, driver->getTexture(value2) );
            }
        }



        if ( extension == ".b3d" ){ //extension == "b3d"){
                printf ("loading b3d");
            // IrrAssimp assimp(smgr);
            IAnimatedMesh* mesh = assimp.getMesh(value1);
       //     IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
            node = smgr->addAnimatedMeshSceneNode( mesh );
            node->setAnimationSpeed(mesh->getAnimationSpeed()); // Fixed by r5097
            //IAnimatedMeshSceneNode* nodeNoAssimp = smgr->addAnimatedMeshSceneNode( meshNoAssimp );


//            	if (!mesh /*|| !meshNoAssimp*/)
//                {
//                    device->drop();
//                    return 1;
//                }

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

//        if (extension ==".bvh"){
//               IAnimatedMesh* mesh = assimp.getMesh(path);//"Media/B02.bvh"
//            IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
//            node->setAnimationSpeed(mesh->getAnimationSpeed()); // Fixed by r5097
//            //IAnimatedMeshSceneNode* nodeNoAssimp = smgr->addAnimatedMeshSceneNode( meshNoAssimp );
//
//            if (node /*&& nodeNoAssimp*/)
//            {
//                //node->setMaterialFlag(EMF_LIGHTING, false);
//                node->setDebugDataVisible(scene::EDS_SKELETON | scene::EDS_BBOX_ALL);
//                //node->setScale(core::vector3df(100, 100, 100));
//
//                //nodeNoAssimp->setPosition(core::vector3df(100, 0, 0));
//                //nodeNoAssimp->setMaterialFlag(EMF_LIGHTING, false);
//                //node->setMD2Animation(scene::EMAT_STAND);
//                node->setMaterialTexture( 0, driver->getTexture(value2 ));
//                	return Py_BuildValue("l",node);
//            }
//        }


//        if (!mesh /*|| !meshNoAssimp*/)
//        {
//            device->drop();
//        return Py_BuildValue("0");
//        }

        break;
    }

	return Py_BuildValue("l",node);
	#else
//	        }
	        	return Py_BuildValue("");
    #endif
}

//
PyObject * Python::PyIrr_Reset(PyObject * self,PyObject * args){
    //would like to have a reset and compile function here maybe dynamically load all the
    //clear all models
    //save then reload externally before recompiling

    //shutdown/restart python and load a noscript loaded screen.
return Py_BuildValue("0");
}
PyObject * Python::PyIrr_setRotation(PyObject * self,PyObject * args){
    long node_id;
    float x,y,z;
    PyArg_ParseTuple(args,"lfff",&node_id,&x,&y,&z);
    ISceneNode *node = (ISceneNode*)node_id;
    node->setRotation(vector3df(x,y,z));

 return Py_BuildValue("");
}

PyObject * Python::PyIrr_setPosition(PyObject * self,PyObject * args){
    long node_id;
    float x,y,z;
    int bullet;
    PyArg_ParseTuple(args,"lifff",&node_id,&bullet,&x,&y,&z);

    if (bullet == 1){
            #ifdef PHYSICS
            btRigidBody *test = (btRigidBody *)node_id;
            test->translate(btVector3 (x,y,z));
            #endif
    }else if (bullet == 3){
        #ifdef TERRAIN
            Terrain* mnode = (Terrain*)node_id;
            vector3df newpos;
            //ITerrainSceneNode* node=mnode->terrain;
            newpos = vector3df(x,y,z)-mnode->terrain->getPosition();

            mnode->terrain->setPosition(vector3df(x,y,z));

            mnode->mRigidBody->translate(btVector3 (newpos.X,newpos.Y,newpos.Z));

         //   btRigidBody *test = mnode->mRigidBody;

#endif
    }else if (bullet == 4){
        #ifdef TERRAIN
            Terrain* mnode =(Terrain*)node_id;
            vector3df newpos;
            //ITerrainSceneNode* node=mnode->terrain;
            newpos = vector3df(x,y,z)-mnode->cubeSceneNode->getPosition();

            mnode->cubeSceneNode->setPosition(vector3df(x,y,z));
            mnode->mRigidBody->translate(btVector3 (newpos.X,newpos.Y,newpos.Z));

         //   btRigidBody *test = mnode->mRigidBody;
#endif
}else if (bullet == 0){
    ISceneNode * node = (ISceneNode *)node_id;// could also get from name smgr->getSceneNodeFromId(node_id);
    	if(node != NULL)
        {
            node->setPosition(vector3df(x,y,z));
            printf("%i %i %i",x,y,z);
        }
    else{
    printf ("nodeID not valid");
    }
    }



return Py_BuildValue("");
}


PyObject * Python::PyIrr_getPosition(PyObject * self,PyObject * args){
    //not teste
    s32 node_id;

    PyArg_ParseTuple(args,"llll",&node_id);
    ISceneNode *node = smgr->getSceneNodeFromId(node_id);
    vector3df position = node->getPosition();
///return Py_BuildValue("l",position);
}


PyObject * Python::PyIrr_setVelocity(PyObject * self,PyObject * args){

//    ISceneNode *node;
    long node;
    float x,y,z;
	PyArg_ParseTuple(args,"lfff",&node,&x,&y,&z);
	#ifdef PHYSICS
	btRigidBody * test = (btRigidBody *)node;
// if bullet or irrlicht scene node handle methods differently
// inirtia calculation
//	node->setPosition(vector3df(x,y,z));
    test->setAngularVelocity(btVector3(x,y,z));
    #endif
    return Py_BuildValue("");
}


PyObject * Python::PyIrr_AddCubeSceneNode(PyObject * self,PyObject * args){
	s32 node_id;
	float size;
	float px,py,pz,rx,ry,rz,sx,sy,sz;

	PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);
	ISceneNode * node = smgr->getSceneNodeFromId(node_id);

        //with physics
       // vector3df pos = camera->getPosition();
       // vector3df scl = vector3df(1,1,1);
      //  luna->m_cPhysics->createBox( btVector3(pos.X, pos.Y, pos.Z), btVector3(scl.X, scl.Y, scl.Z), 10); //weight

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


return Py_BuildValue("l",node);//node_id);
};


PyObject * Python::PyIrr_addSphereNode(PyObject * self,PyObject * args){

    float x,y,z;
   // u8 texture;
    float radius, mass;
    char * texture;
	PyArg_ParseTuple(args,"sfffff",&texture,&x,&y,&z,&radius,&mass);
#ifdef PHYSICS
	btRigidBody *test;

  //  scene::ISceneNode * node_id = smgr->addSphereSceneNode(20); //radius  polycount , parent , id , position,rotation, scale
    //IVideoDriver::createImageFromFile().  //textures and heightmap
       //if ( icount > 15){ //sphere limiter
//            vector3df pos = camera->getPosition(); //causes crash currently
//            vector3df rot = camera->getRotation();

    //    vector3df scl = vector3df(1,1,1);
    //    luna->m_cPhysics->createBox( btVector3(x, y, z), btVector3(scl.X, scl.Y, scl.Z), 10); //weight

          //  bingo=1;
        //    if (bingo) { // suposed to only create 1 sphere then transport you to it if its made already
             //   luna->m_cPhysics->createSphere( btVector3(pos.X, pos.Y, pos.Z),2,5);
            test = luna->m_cPhysics->createSphere( texture, btVector3(x, y, z),radius,mass);

//                //ha2->setAngularVelocity(btVector3(400,400,400));
        //        bingo= false;
       //     } else {
               // btVector3 pos2 = ha2->getCenterOfMassPosition();
               // camera->setPosition(vector3df(pos2[0],pos2[1],pos2[2]));
        //    }
//return Py_BuildValue("");
return Py_BuildValue("l",test);
#endif
};




PyObject * Python::PyIrr_PostProcess(PyObject * self,PyObject * args){
#ifdef PostProcess
#define GL_OLDMONITOR "uniform float randNum,time,v0;uniform sampler2D texture1;float rand(in float s){return sin(gl_TexCoord[0].x*(1009.0+s*10.0)+tan(gl_TexCoord[0].y*(1090.0+s*100.0)+tan(gl_TexCoord[0].x*111.0+s*10000.0))+s*4.0+gl_TexCoord[0].y*10000.0)*0.5+0.5;}float tear(in float y){return (y-0.8)*0.01/(y*y*y*y+2.0);}void main(void){float c=dot(texture2D(texture1,vec2(floor(gl_TexCoord[0].x*500.0)*0.002+tear((gl_TexCoord[0].y-1.2+mod(time*0.1,1.4))*50.0)*rand(randNum)*5.0*v0,floor(gl_TexCoord[0].y*200.0)*0.005+floor(fract(time*0.1+randNum*0.1)*1.1)*0.03*v0)),vec4(0.2,0.5,0.3,0.0));gl_FragColor=(texture2D(texture1,vec2(gl_TexCoord[0].x+tear(tan(gl_TexCoord[0].y*10.0+time*2.0))*v0,gl_TexCoord[0].y))*(1.0-0.7*v0)+c*0.7*v0+vec4(rand(randNum))*0.1*v0)*(1.0-(sin(gl_TexCoord[0].y*400.0)*0.05+(pow(abs(gl_TexCoord[0].x*2.0-1.0),4.0)+pow(abs(gl_TexCoord[0].y*2.0-1.0),4.0))*0.5)*v0);}"
#define DX_OLDMONITOR "sampler2D s;float randNum,time,v0;float rand(in float2 t,in float s){return frac(t.x*(1009.0+s*10.0)+tan(t.y*(1090.0+s*100.0)+t.x*111.0)+t.y*10000.0)-0.5;}float tear(in float y){return (y-0.8)*0.01/(y*y*y*y+2.0);}float4 main(float2 t:TEXCOORD0):COLOR{float c=dot(tex2D(s,float2(t.x+tear(frac(t.y-time*0.2)*70.0-35.0)*(rand(t,randNum)+0.5)*4.0,floor(t.y*200.0)*0.005)),float4(0.2,0.5,0.3,0.0));return tex2D(s,t)*(1.0-0.7*v0)+(c*0.7+float4(0.1,0.1,0.1,0.0)*rand(t,randNum))*(1.0-sin(t.y*400.0)*0.05-(pow(abs(t.x-0.5),4.0)+pow(abs(t.y-0.5),4.0))*8.0)*v0;}"

// This monitor effect is NOT supported, and has been known to have problems. I encourage you to use the officially supported PP_MONITOR effect instead in your programs.

// A much simpler shader; this will add a constant number (set by parameters) to the rgba channels
#define GL_A_SIMPLER_SHADER "uniform float v0;uniform sampler2D texture1;void main(void){gl_FragColor=texture2D(texture1,gl_TexCoord[0].xy)+v0;}"
#define DX_A_SIMPLER_SHADER "sampler2D s;float v0;float4 main(float2 t:TEXCOORD0):COLOR{return tex2D(s,t)+v0;}"

	//PostProcessing
        IPostProc* ppRenderer = new CRendererPostProc( smgr, dimension2du( 1024, 512 ),
                                                    true, true, SColor( 255u, 100u, 101u, 140u ) );
        ppBlurDOF   = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLURDOF );
         ppBlur          = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), PP_BLUR, 0.00081f );
//		CEffectPostProc* ppInvert = new CEffectPostProc( ppRenderer, dimension2di( 1024, 512 ), PP_INVERT );
//	CEffectPostProc* ppBlur = new CEffectPostProc( ppInvert, dimension2di( 1024, 512 ), PP_BLUR, 0.01f );
	ppMine = new CEffectPostProc( ppRenderer, dimension2du( 1024, 512 ), GL_OLDMONITOR, DX_OLDMONITOR, EPST_PS_1_2, EPST_PS_2_0, EMT_SOLID, PPF_FROMCODE, 1.0f );

        ppBlur->setQuality( PPQ_GOOD );
        	ppMine->setRequiredVariables( 1, true, true ); // (number of input parameters, uses time?, uses randNum?)

ppMine->setTimer( device->getTimer( ) );

        bPProcess=1;
        return Py_BuildValue("l",ppRenderer);
#endif
return Py_BuildValue("");
}


PyObject * Python::PyIrr_ExportScene(PyObject * self,PyObject * args){
    char * path;
    PyArg_ParseTuple(args,"s",&path);

        device->getSceneManager()->saveScene(path);
  return Py_BuildValue("");
}

PyObject * Python::PyIrr_LoadLevel(PyObject * self,PyObject * args){
#ifdef TERRAIN
tr.setIdentity();
#endif
    int param,state,ammount;
    char * path;
    std::string path2;
    PyArg_ParseTuple(args,"siii",&path,&param,&ammount,&state);
    path2 = path;

     //   device->getFileSystem()->changeWorkingDirectoryTo("../../");
     //   device->getFileSystem()->changeWorkingDirectoryTo("extra/");

//         if(!m_irrDevice) return;
    int tscale=20 ;
    vector3df trackScale = vector3df(tscale,tscale,tscale); //50
    vector3df trackPosition = vector3df(0,0.0f,0);

        IAnimatedMesh *mesh = device->getSceneManager()->getMesh(path);
  //  IAnimatedMesh *mesh = device->getSceneManager()->getMesh(path2.c_str());

    device->getSceneManager()->getMeshManipulator()->scaleMesh(mesh,trackScale);
    IAnimatedMeshSceneNode *node = device->getSceneManager()->addAnimatedMeshSceneNode(mesh);


    // node->setScale(trackScale);
    // node->setRotation(vector3df(45,90.f,110));
    node->setPosition(trackPosition);


     //   m_cVehicle->loadLevel(track.c_str());
     //   device->getFileSystem()->changeWorkingDirectoryTo("../");

#ifdef IRRCDs
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
    luna->m_cPhysics->localCreateRigidBody(0, tr, trackShape, node);
#endif

return Py_BuildValue("");
}
PyObject * Python::PyIrr_Light(PyObject * self,PyObject * args){ //active camera // parameters for fov possibly shaders aswell
	//s32
	float x,y,z;
	int t;
	char * s;
	scene::ISceneNode* node = 0;
//		Material.Lighting = false;
	PyArg_ParseTuple(args,"ifffs",&t,&x,&y,&z,&s);
 //cam->setActiveCamera(cam);
  //  node->setAutomaticCulling(EAC_FRUSTUM_BOX);
node = smgr->addLightSceneNode(0, core::vector3df(x,y,z),
		video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);

//	video::SLight l;
//			scene::ILightSceneNode *light = smgr->addLightSceneNode(0,core::vector3df(50,100,50),video::SColorf(1,1,1,1.f),100);
//	l = light->getLightData();
//	l.Type = video::ELT_POINT;
//	l.AmbientColor = video::SColorf(.35,.35,.35);
//	l.SpecularColor = video::SColorf(.7,.7,.5);
//	l.DiffuseColor = video::SColorf(1,1,1);
//	l.CastShadows = true;
//	light->setLightData( l );

return Py_BuildValue("l",node);
}


PyObject * Python::PyIrr_getScreen(PyObject * self,PyObject * args) {
    int type;
    PyArg_ParseTuple(args,"i",&type);
    if (type == 0){
        return Py_BuildValue("i",driver->getViewPort().getWidth());
    }
    else if (type == 1){

        return Py_BuildValue("i",driver->getViewPort().getHeight());
    }
//const irr::core::dimension2du& screenSize = driver->getScreenSize();
//irr::core::vector2df screenSize(driver.getViewPort().getWidth(), driver.getViewPort().getHeight());

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
#endif
