#include "../config.h"
#ifdef PYTHON
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
//#define LONG_BIT = 4 * SIZEOF_LONG

#include <irrlicht.h>
using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace gui;
using namespace scene;
using namespace io;

#include <Python.h> // fix later -has to be in this order or the formationwrapper complains

#ifdef FORMATION
#include "../Scene/Formation.h"
#endif

//#define PYTHON_MINIMALTESTs
#ifdef PYTHON_MINIMALTEST
vector<ITexture *> texture_array;

//IVideoDriver *driver = device->getVideoDriver();



static PyObject * Python::PyIrr_LoadTexture(PyObject * self,PyObject * args)
{
	//Watch this, tricky,remember to pass string ADDRESS to PyArg_ParseTuple
	char * tex_name;
	PyArg_ParseTuple(args,"s",&tex_name);
	texture_array.push_back(driver->getTexture(tex_name));
	/*The line below is sorta kludgy, but it works.It won't hold up if you remove a texture
	from the array though,so watch your step, kid. I'll leave it to you to come up with
	a more intuitive method of storing the textures*/
	return Py_BuildValue("l",texture_array.size() - 1);
};

static PyObject * Python::PyIrr_SetTexture(PyObject * self,PyObject * args)
{
	s32 tex_id,node_id;
	PyArg_ParseTuple(args,"ll",&node_id,&tex_id); //This is your new best friend, seriously
	/*Quite similar to the scanf family of functions, don't you think? It take a format
	string and some input data, and analyzes the input data and gives you the result
	in a manner specified by the format string*/
	ISceneNode * node = smgr->getSceneNodeFromId(node_id);
	if(node != NULL)
	{
		node->setMaterialTexture(0,texture_array[tex_id]);
	};
	/*This line returns a value of Py_None, which is more or less the same thing as a
	function with a return type of void in C++, in other words, no output values */
	return Py_BuildValue("");
};

static PyObject * Python::PyIrr_AddCubeSceneNode(PyObject * self,PyObject * args)
{
	s32 node_id;
	float size;
	float px,py,pz,rx,ry,rz,sx,sy,sz;
	//Damn...thats a lot of parameters :)
	PyArg_ParseTuple(args,"lffffffffff",&node_id,&size,&px,&py,&pz,&rx,&ry,&rz,&sx,&sy,&sz);
	ISceneNode * node = smgr->getSceneNodeFromId(node_id);
	if(node == NULL)
	{
		node = smgr->addCubeSceneNode(size,NULL,node_id,vector3df(px,py,pz),vector3df(rx,ry,rz),vector3df(sx,sy,sz));
		/*I forgot this initially, so I wasn't seeing anything although the script
		was compiling >_<...stupid*/
		node->setMaterialFlag(EMF_LIGHTING,false);
	}
	else
	{
		return Py_BuildValue("");
	};
	return Py_BuildValue("l",node_id);
};

static PyObject * Python::PyIrr_DrawText(PyObject * self,PyObject * args)
{

	//Must make this useful someday, not today
	char * message;
	s32 x,y,x1,y1;
	PyArg_ParseTuple(args,"sllll",&message,&x,&y,&x1,&y1);
	//The next three lines more or less give the procedure from converting a string of
	//type char* to wchar_t*...generally this is pretty useful in Irrlicht,so note well
	//int len = strlen(message) + 1;
	//wchar_t * conv_message = new wchar_t[len];
	//!mbstowcs(0,conv_message,len,message,_TRUNCATE);
	//default_font->draw(conv_message,rect<s32>(x,y,x1,y1),SColor(255,255,255,255));
	//delete [] conv_message;
	return Py_BuildValue("");


};

static PyMethodDef irr_funcs[] =
{
	{"set_texture",PyIrr_SetTexture,METH_VARARGS,"Adds a texture to a scene node"},
	{"draw_text",PyIrr_DrawText,METH_VARARGS,"Renders text to the screen with default font"},
//	{"add_cube",PyIrr_AddCubeSceneNode,METH_VARARGS,"Adds a cube scene node"},
	{"load_texture",PyIrr_LoadTexture,METH_VARARGS,"Loads a texture"},
	{NULL,NULL,0,NULL}
};

PyMODINIT_FUNC Python::init_irr(void){
	/*Note the return type of the function, which is PyMODINIT_FUNC, its
	actually more of a macro than a datatype(I think). Anyway, its essential to
	have this as the return type of a function that initializes a python module*/

Py_InitModule("irr",irr_funcs);


};

void Python::registerIrrDevice(Luna *luna1,IrrlichtDevice &Device,InGameEventReceiver event){
    luna = luna1;
    device = &Device;
    driver = device->getVideoDriver();
    smgr   = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    mEvent = event;


  //  camera = smgr->addCameraSceneNodeFPS(0, 100, .050f, -1, luna->keyMap, 8);
//camera = smgr->addCameraSceneNode();


 //   camera->setFarValue(10000);
    //camera = smgr->addCameraSceneNodeFPS();
    //  camera->setFOV(PI/2);

    m_cScene = new Scene();
    m_cScene->registerIrrDevice(*device);
  //  m_cScene->setupLights();//Scene, setup for lights.
    int lastFPS = -1;
    u32 timeStamp = device-> getTimer()-> getRealTime(),deltaTime = 0;
    device->setEventReceiver ( &mEvent);
//    device->getCursorControl()->setVisible(false);
#ifdef FPS
    Elevator::Instance()->Instance();
    ///Player::Instance()->Instance();//obsolete
    //    Collision::Instance()->Instance();
    ///Player::Instance()->setDevice(device); //obsolete
    //   Collision::Instance()->setDevice(device);
#endif
//    scene::IAnimatedMesh *mesh = (IAnimatedMesh*) smgr->getMesh("media/player/player.x");
//	scene::IAnimatedMeshSceneNode *skelNode = (IAnimatedMeshSceneNode*) smgr->addAnimatedMeshSceneNode(mesh);
	//cSkeleton skeleton; // moved externally
//	skeleton.Initialize(skelNode, 8);
	//core::vector3df pos = skeleton.getSkeletonSceneNode()->getPosition();
 //   skelNode->addShadowVolumeSceneNode();
//smgr->setShadowColor(video::SColor(150,0,0,0));
//smgr->addLightSceneNode(0, core::vector3df(0,0,0),video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 600.0f);
}


#else

////////////////////////////////////
#include "./PyFunctions.h"
////////////////////////////////////


PyMODINIT_FUNC Python::init_irr(void){
	/*Note the return type of the function, which is PyMODINIT_FUNC, its
	actually more of a macro than a datatype(I think). Anyway, its essential to
	have this as the return type of a function that initializes a python module*/

//#ifdef EXTRAS
    Py_InitModule("extras",irr_Extras);
//#endif

//    Py_InitModule("particles",irr_SPARKA);
	Py_InitModule("physics",irr_Physics);
    Py_InitModule("scene",irr_Scene);
	Py_InitModule("scene",irr_Camera);
    Py_InitModule("net",irr_Network);
	Py_InitModule("math",irr_Math);
	Py_InitModule("sound",irr_Sound);
    Py_InitModule("irr",irr_function);
	Py_InitModule("gui",irr_gui);
    Py_InitModule("scene",irr_FlagMan);
    Py_InitModule("input",irr_Input);
	Py_InitModule("image",irr_Image);
	Py_InitModule("irr",irr_FileIO);

};
#endif
void Python::ExecuteScript(irr::core::string<char> scriptname){
	/*Using it this way
	because the methods using the FILE * structure tend to go wonky
	  due to the fact that the FILE * datatype is not standardized, so you'll get problems
	  if you try to use it with a different version other than the one your Python build was
	  compiled with. Our solution looks kludgy but it works pretty well.*/
	irr::core::string<char> result;
	result = irr::core::string<char>("execfile('");
	result.append(scriptname);
	result.append("')");
	PyRun_SimpleString(result.c_str());
	/*This function was pretty annoying to write. The errors I kept on getting were textbook
	examples on why namespaces were important...seriously.It kept on confusing std::string
	with irr::core::string, but as you can see, I solved that problem by explicitly stating
	the namespace in which the string class I wanted was to be found*/
};

#endif
