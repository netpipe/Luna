#ifndef PYCAMERA_INCLUDED
#define PYCAMERA_INCLUDED

#include <irrlicht.h>
// possibly rename to camera
PyObject * Python::PyIrr_addCamera(PyObject * self,PyObject * args){
	s32 x,y,z,t;
//	char * t;
	PyArg_ParseTuple(args,"llll",&t,&x,&y,&z);
	    ICameraSceneNode *cam;



    enum eaction{normal,FPS,bind,setViewPort,CameraManager};
//std::map<std::string, eaction> nodeMap;
//nodeMap[t];
//std::map<std::string, X> xmap = boost::map_list_of("A", A)("B", B)("C",C);
    switch(t){
    case 1:
        cam = smgr->addCameraSceneNode();
        break;

    case 2:
        cam = smgr->addCameraSceneNodeFPS();
        //  cam->setPosition(vector3df(50,50,50));
        break;

    case 3:
		cam = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
		break;

    case CameraManager:
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
	int x,y,z,cam2;
	//int

	PyArg_ParseTuple(args,"llll",&cam2,&x,&y,&z);
 //cam->setActiveCamera(cam);
 ICameraSceneNode *cam = cam2;
    cam->setPosition(vector3df(x,y,z));

return Py_BuildValue("z",cam);
}

PyObject * Python::PyIrr_GetCamera(PyObject * self,PyObject * args){

// get  camera coords ;
	s32 x,y,z,t;
	vector3df v;
			    ICameraSceneNode *cam;
	PyArg_ParseTuple(args,"sllll",cam,&x,&y,&z);
v = vector3df(x,y,z);
//vector3df v = t->getPosition();
//cam = smgr->getActiveCamera();
return Py_BuildValue("lll",v.X,v.Y,v.Z);
}

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
