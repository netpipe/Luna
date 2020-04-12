#include "../../config.h"
#ifdef RECAST
/*
#include <irrlicht.h>
#include <iostream>

#include "recast_util.h"
#define IRRLICHT_DIR "/home/Dev/libs/game/Irrlicht-SVN"
#define MODEL_FILE "./dungeon.obj"



using namespace irr;

//IrrlichtDevice *device = 0;
scene::ICameraSceneNode* camera = 0;
scene::ISceneNode* node = 0;
scene::ISceneNode* naviNode = 0;

RecastUtil* recast = 0;



////////////////////////////////////////////////////////////////////////////////
class EventReceiver: public IEventReceiver
{
public:

virtual bool OnEvent(const SEvent& event)
{
	if
	(
		(event.EventType == EET_KEY_INPUT_EVENT)
		&& (event.KeyInput.PressedDown == true)
	)
	{

		if (event.KeyInput.Key == irr::KEY_KEY_Q)
		{

		}
		else if (event.KeyInput.Key == irr::KEY_KEY_E)
		{

		}
		else if (event.KeyInput.Key == irr::KEY_ESCAPE)
		{
	//		device->closeDevice();
	//		device->run();
			return true;
		}
		else if (event.KeyInput.Key == irr::KEY_F1)
		{

		}
		else if (event.KeyInput.Key == irr::KEY_F2)
		{
			if (naviNode)
				naviNode->setDebugDataVisible(scene::EDS_OFF);
		}
		else if (event.KeyInput.Key == irr::KEY_F3)
		{
			bool enabled = camera->isInputReceiverEnabled();
			camera->setInputReceiverEnabled(!enabled);
//			device->getCursorControl()->setVisible(enabled);
		}
		else if (event.KeyInput.Key == irr::KEY_F4)
		{
			if (node->isVisible())
				node->setVisible(false);
			else
				node->setVisible(true);

		}
		else if (event.KeyInput.Key == irr::KEY_F5)
		{
			node->setVisible(!node->isVisible());
		}
		else if (event.KeyInput.Key == irr::KEY_KEY_A)
		{
		}
		else if (event.KeyInput.Key == irr::KEY_KEY_D)
		{
		}

		else if (event.KeyInput.Key == irr::KEY_KEY_W)
		{
		}
		else if (event.KeyInput.Key == irr::KEY_KEY_S)
		{
		}

	}
	return false;
}

};


////////////////////////////////////////////////////////////////////////////////

int mainb()
{

	video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;

	// create device

	EventReceiver receiver; //<---------------------------------------------------

//	device = createDevice(driverType, core::dimension2d<u32>(800, 600), 16, false, false, false, &receiver);
	//if (device == 0)
	//	return 1; // could not create selected driver.
	video::IVideoDriver* driver = device2->getVideoDriver();
	scene::ISceneManager* smgr = device2->getSceneManager();
	io::IFileSystem* fs = device2->getFileSystem();

	fs->addFileArchive(IRRLICHT_DIR);
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
				naviNode = smgr->addOctTreeSceneNode(smesh);
				naviNode->setDebugDataVisible(scene::EDS_FULL);
			}
			smesh->drop();
		}
	}

////////////////////////////////////////////////////////////////////////////////

	smgr->addLightSceneNode
	(
		0,
		core::vector3df(600,1100,400),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		1000.0f // radius
	);

	smgr->addLightSceneNode
	(
		0,
		core::vector3df(-600,1100,-400),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		1000.0f // radius
	);

	// create skybox
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	smgr->addSkyBoxSceneNode
	(
		driver->getTexture("media/irrlicht2_up.jpg"),
		driver->getTexture("media/irrlicht2_dn.jpg"),
		driver->getTexture("media/irrlicht2_lf.jpg"),
		driver->getTexture("media/irrlicht2_rt.jpg"),
		driver->getTexture("media/irrlicht2_ft.jpg"),
		driver->getTexture("media/irrlicht2_bk.jpg")
	);

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

	f32 camRotateSpeed = 100.0f;
	f32 camMoveSpeed = 0.02f;
	f32 camJumpSpeed = 3.0f;

	camera = smgr->addCameraSceneNodeFPS(0, camRotateSpeed, camMoveSpeed, -1, 0, 0, false, camJumpSpeed);
	camera->setFarValue(40000.f);
	//smgr->setActiveCamera(camera);

	device2->getCursorControl()->setVisible(false);



	scene::ILightSceneNode* light = 0;

	light = smgr->addLightSceneNode
	(
		0,
		core::vector3df(600,1100,400),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		1000.0f // radius
	);

	light = smgr->addLightSceneNode
	(
		0,
		core::vector3df(-600,1100,-400),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		1000.0f // radius
	);

	int lastFPS = -1;

	while (device->run())
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, 0);
		smgr->drawAll();
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"Irrlicht Engine (";
			str += driver->getName();
			str += ") FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}
	else { device->yield(); }

	if (recast) { delete recast; recast = 0; }
	//device->drop();


	return 0;
}

*/
#endif
