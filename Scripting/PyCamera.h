#ifndef PYCAMERA_INCLUDED
#define PYCAMERA_INCLUDED
#include "../config.h"
#ifdef PYTHON
//#include <irrlicht.h>
PyMethodDef irr_Camera[] = {
    {"addCamera",Python::PyIrr_addCamera,METH_VARARGS,"sets camera vector"},
    {"setCamera",Python::PyIrr_SetCamera,METH_VARARGS,"sets camera vector"},
	{"getCamera",Python::PyIrr_GetCamera,METH_VARARGS,"getcamera vector"},
    {"fpsweapon",Python::PyIrr_fpsWeapon,METH_VARARGS,"PyIrr_fpsWeapon"},
    {"bindCamera",Python::PyIrr_BindCamera,METH_VARARGS,"PyIrr_BindCamera"},


	{NULL,NULL,0,NULL}
};

// possibly rename to camera
PyObject * Python::PyIrr_addCamera(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
	//	char * t;
	PyArg_ParseTuple(args,"ifff",&t,&x,&y,&z);
	ICameraSceneNode *cam;
	//    enum eaction{normal,FPS,bind,setViewPort,CameraManager};
	//std::map<std::string, eaction> nodeMap;
	//nodeMap[t];
	//std::map<std::string, X> xmap = boost::map_list_of("A", A)("B", B)("C",C);
    switch(t){
    case 1:
        cam = smgr->addCameraSceneNode();
        		device->setEventReceiver ( &mEvent);
       // cam->setTarget(vector3df(0,0,0));
        break;

    case 2:
        cam = smgr->addCameraSceneNodeFPS();
       // cam->setTarget(vector3df(0,0,0));
       	device->getCursorControl()->setVisible(false);
		cam->setFarValue(10000.0f);
		cam->setPosition(vector3df(x,y,z));
	//cam->setNearValue(0.1f);
        break;

    case 3:
		keyMap[0].Action = EKA_MOVE_FORWARD;    keyMap[0].KeyCode = KEY_KEY_W;
		keyMap[1].Action = EKA_MOVE_FORWARD;    keyMap[1].KeyCode = KEY_KEY_W;
		keyMap[2].Action = EKA_MOVE_BACKWARD;   keyMap[2].KeyCode = KEY_KEY_S;
		keyMap[3].Action = EKA_MOVE_BACKWARD;   keyMap[3].KeyCode = KEY_KEY_S;
		keyMap[4].Action = EKA_STRAFE_LEFT;     keyMap[4].KeyCode = KEY_KEY_A;
		keyMap[5].Action = EKA_STRAFE_LEFT;     keyMap[5].KeyCode = KEY_KEY_A;
		keyMap[6].Action = EKA_STRAFE_RIGHT;    keyMap[6].KeyCode = KEY_KEY_D;
		keyMap[7].Action = EKA_STRAFE_RIGHT;    keyMap[7].KeyCode = KEY_KEY_D;

		cam = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
		device->setEventReceiver ( &mEvent);
		device->getCursorControl()->setVisible(false);
		cam->setFarValue(10000.0f);
		cam->setPosition(vector3df(x,y,z));
		//cam->setNearValue(0.1f);
		break;
	case 4:
			cam = smgr->addCameraSceneNodeMaya();
		//	cam->setPosition(vector3df(150,0,0));
			cam->setTarget(vector3df(0,0,0));

	// case CameraManager:
        //if active camera not = new camera push to camera manager
    // some kind of vector stack for camera management
	//     ICameraSceneNode *gcamera[3] = {0,0,0};
        break;
	//    case bind:
	//          camera[2]->bindTargetAndRotation(true);

///eaction(setViewPort):
//    case setViewPort:
//        driver->setViewPort(rect);
//        break;
}




//    if (t==1){
//        cam = smgr->addCameraSceneNode();
//    } else if (t==2){
//        cam = smgr->addCameraSceneNodeFPS();
//        //  cam->setPosition(vector3df(50,50,50));
//    }else if (t==3){
//            cam = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
//    }else if (t==4){
//    // some kind of vector stack for camera management
////     ICameraSceneNode *gcamera[3] = {0,0,0};
//    }case eaction(t)  {
////          camera[2]->bindTargetAndRotation(true);
//    }else if (t==6){
//        driver->setViewPort(rect);
//    }


 return Py_BuildValue("l",cam);
}


PyObject * Python::PyIrr_fpsWeapon(PyObject * self,PyObject * args){
// need to attach to bones and/or nodes here
    #ifdef FPS
	bFPS = 1;
    long pcam;
    int param;
    PyArg_ParseTuple(args,"li",&pcam,&param);
    ICameraSceneNode* camera = (ICameraSceneNode*)pcam;
    device->getGUIEnvironment()->addImage( driver->getTexture("../media/data/textures/crosshairs/crosshair1.png"),
                                            core::position2d<s32>((luna->resolution[0]/2)-64,(luna->resolution[1]/2)-64));

    switch(param){
        case 0:
        {
              IAnimatedMesh*   gunmesh = smgr->getMesh("../media/data/models/weapons/M4/3d_person/M4A1d.3ds");
              scene::IAnimatedMeshSceneNode* agun;
              agun = smgr->addAnimatedMeshSceneNode(gunmesh);
              if (agun)
              {
                agun->setMaterialTexture(0, driver->getTexture("../media/data/models/weapons/M4/1st_person/M4A1.jpg"));
                agun->setScale(core::vector3df(1.2f, 1.2f, 1.2f));
                agun->setPosition(core::vector3df(180.f,1.5f,0.f));
                agun->setRotation(core::vector3df(0.f,0.f,90.f));
                //agun->apply_light2node(agun);
                agun->addShadowVolumeSceneNode();
              }
              gunmesh->drop();
           // scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeFPS(0, 100.0f, .5f,-1,keyMap,8);
                                      // cam->setPosition(core::vector3df(-200,100,200));
                                     //  cam->setTarget(core::vector3df(0,0,0));
            camera->setFOV(PI/2);
            camera->setFarValue(7000);

            M4 = new firstPersonWeapon(device, camera);
            //  apply_light2node(M4->getNode());
            device->setEventReceiver(M4);

            return Py_BuildValue("l",M4);

        }break;

        case 1:
        {
//                M4->LEFTBUTTONCLICKED=true;
//                M4->RIGHTBUTTONCLICKED=true;
        }break;
    }
#endif

return Py_BuildValue("");
}

PyObject * Python::PyIrr_SetCamera(PyObject * self,PyObject * args){ //active camera // parameters for fov possibly shaders aswell
	//s32
	float x,y,z;
	long cam2;
	int type;
	//int
	PyArg_ParseTuple(args,"ilfff",&type,&cam2,&x,&y,&z);
	ICameraSceneNode *cam ;
	//ICameraSceneNode *cam = (ICameraSceneNode *)cam2;
	//	ICameraSceneNode *cam = cam2;
	if (type == 3){
	}else{
	//ICameraSceneNode *cam = (ICameraSceneNode *)cam2;
	cam = (ICameraSceneNode *)cam2;
	}
//	device->setActiveCamera(cam);
	switch (type){
		case 0:
		cam->setPosition(vector3df(x,y,z));
	//	cam->setPosition(vector3df(0,20,0));
		break;
	case 1:
		cam->setRotation(vector3df(x,y,z));
		break;
	case 2:
		       // if (bCarFollow) {
    // this is for putting the camera above the car
      //  btVector3 point = m_cVehicle->getVehiclePosition();
//        camera->setPosition(vector3df(
//          (f32)point[0],
//          (f32)point[1]+10,
//          (f32)point[2]-50));
  //  }
    break;
}
// add lookat parameter and add call to mainloop for updates


return Py_BuildValue("");
}

PyObject * Python::PyIrr_GetCamera(PyObject * self,PyObject * args){

// get  camera coords ;
	s32 x,y,z,t;
	vector3df v;
	int param;
	long cam2;

	PyArg_ParseTuple(args,"li",&cam2,&param);
	ICameraSceneNode *cam = (ICameraSceneNode*)cam2;
	//v = vector3df(x,y,z);


    if (param==0){
		cam = smgr->getActiveCamera();
		return Py_BuildValue("l");
    } else if (param==1){
    		v = cam->getPosition();
    	return Py_BuildValue("f", v.X);
    }else if (param==2){
    		v = cam->getPosition();
    	return Py_BuildValue("f", v.Y);
    }else if (param==3){
    		v = cam->getPosition();
    	return Py_BuildValue("f", v.Z);
    }

	return Py_BuildValue("");
}


//PyObject * Python::PyIrr_setEvent(PyObject * self,PyObject * args){
//}

//PyObject * Python::PyIrr_Camera(PyObject * self,PyObject * args)
//{
//
//	s32 x,y,z,t;
//	vector3df v;
//			    ICameraSceneNode *cam;
//	PyArg_ParseTuple(args,"sllll",cam,&x,&y,&z);
//
//v = vector3df(x,y,z);
//
//
////vector3df v = t->getPosition();
////cam = smgr->getActiveCamera();
//return Py_BuildValue("l",v);
//}


PyObject * Python::PyIrr_BindCamera(PyObject * self,PyObject * args)
{
long cam2,node_id;
	PyArg_ParseTuple(args,"ll",&cam2,&node_id);
	ICameraSceneNode *cam = (ICameraSceneNode*)cam2;
	ISceneNode *Node = (ISceneNode*)node_id;
    //cam->setTarget();
    cam->bindTargetAndRotation(Node);

Py_RETURN_NONE;
}


//device->getSceneManager()->getActiveCamera()
//sm->setActiveCamera(camera);

#endif // PYCAMERA_INCLUDED
#endif
