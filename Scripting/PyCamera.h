#ifndef PYCAMERA_INCLUDED
#define PYCAMERA_INCLUDED

#include <irrlicht.h>
PyMethodDef irr_Camera[] = {
    {"addCamera",Python::PyIrr_addCamera,METH_VARARGS,"sets camera vector"},
    {"setCamera",Python::PyIrr_SetCamera,METH_VARARGS,"sets camera vector"},
	{"getCamera",Python::PyIrr_GetCamera,METH_VARARGS,"getcamera vector"},
	{"screen",Python::PyIrr_getScreen,METH_VARARGS,"screenwidth"},
	{NULL,NULL,0,NULL}
};

// possibly rename to camera
PyObject * Python::PyIrr_addCamera(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
//	char * t;
	PyArg_ParseTuple(args,"ifff",&t,&x,&y,&z);
	    ICameraSceneNode *cam;



    enum eaction{normal,FPS,bind,setViewPort,CameraManager};
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

PyObject * Python::PyIrr_SetCamera(PyObject * self,PyObject * args){ //active camera // parameters for fov possibly shaders aswell
	//s32
	int x,y,z;
	long cam2;
	//int

	PyArg_ParseTuple(args,"lfff",&cam2,&x,&y,&z);
	ICameraSceneNode *cam = cam2;
//	device->setActiveCamera(cam);
    cam->setPosition(vector3df(x,y,z));


        if (bCarFollow) {
    // this is for putting the camera above the car
//        btVector3 point = m_cVehicle->getVehiclePosition();
//        camera->setPosition(vector3df(
//          (f32)point[0],
//          (f32)point[1]+10,
//          (f32)point[2]-50));
    }


//return Py_BuildValue("z",cam);
}

PyObject * Python::PyIrr_GetCamera(PyObject * self,PyObject * args){

// get  camera coords ;
	s32 x,y,z,t;
	vector3df v;
			    ICameraSceneNode *cam;
	PyArg_ParseTuple(args,"lfff",cam,&x,&y,&z);
v = vector3df(x,y,z);
//vector3df v = t->getPosition();
//cam = smgr->getActiveCamera();
return Py_BuildValue("fff",v.X,v.Y,v.Z);
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


//PyObject * Python::PyIrr_BindCamera(PyObject * self,PyObject * args)
//{
//camera->setTarget();
////camera->bindTargetAndRotation(Node);
//Py_RETURN_NONE;
//}


//device->getSceneManager()->getActiveCamera()
//sm->setActiveCamera(camera);

#endif // PYCAMERA_INCLUDED
