#ifndef PYCAMERA_INCLUDED
#define PYCAMERA_INCLUDED
#include <irrlicht.h>


PyObject * Python::PyIrr_addCamera(PyObject * self,PyObject * args)
{
	s32 x,y,z,t;
	PyArg_ParseTuple(args,"llll",&t,&x,&y,&z);
	    ICameraSceneNode *cam;

    if (t==1){
        cam = smgr->addCameraSceneNode();
    } else if (t==2){
        cam = smgr->addCameraSceneNodeFPS();
        //  cam->setPosition(vector3df(50,50,50));
    }else if (t==3){
            cam = smgr->addCameraSceneNodeFPS(0, 100, .1f, -1, keyMap, 8);
    }

 return Py_BuildValue("l",cam);
}


PyObject * Python::PyIrr_SetCamera(PyObject * self,PyObject * args) //active camera
{
	s32 x,y,z,t;
		    ICameraSceneNode *cam;
	PyArg_ParseTuple(args,"zllll",&cam,&x,&y,&z);
 //cam->setActiveCamera(cam);
    cam->setPosition(vector3df(x,y,z));

return Py_BuildValue("z",cam);
}


PyObject * Python::PyIrr_GetCamera(PyObject * self,PyObject * args)
{
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


//PyObject * Python::PyIrr_BindCamera(PyObject * self,PyObject * args)
//{
//camera->setTarget();
////camera->bindTargetAndRotation(Node);
//Py_RETURN_NONE;
//}


//device->getSceneManager()->getActiveCamera()
//sm->setActiveCamera(camera);

#endif // PYCAMERA_INCLUDED
