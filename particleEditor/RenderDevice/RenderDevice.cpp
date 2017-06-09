#include "RenderDevice.h"
#include <iostream>
#include <time.h>

/*! \brief  RenderDevice constructor.
 *
 */
RenderDevice::RenderDevice(
  E_DRIVER_TYPE driverType, dimension2d<u32>dimension, u32 bitDepth,
  bool fullScreen, bool stencilBuffer, bool vSync,
  IEventReceiver *receiver
) :
  m_windowWidth (dimension.Width),
  m_windowHeight (dimension.Height),
  m_windowBPP (bitDepth)
{
  m_irrDevice = createDevice(
    driverType, dimension, bitDepth, fullScreen, stencilBuffer, vSync, receiver);

  if(m_irrDevice == NULL)
  {
    throw "Failed to create display device.";
  }

  m_irrVideoDriver  = m_irrDevice->getVideoDriver();
  m_irrSceneManager = m_irrDevice->getSceneManager();

  /*! Basic irrlicht setup done.
   *  Time to setup our custom classes.
   */

  //! Create custom class pointers.
  m_cEventReceiver  = new Event_Receiver();
  m_cGUIHandler     = new GUI_Handler();
  m_cWorldManager   = new World_Manager();
  m_cParticleSystem = new ParticleSystem(*m_irrSceneManager, *m_irrVideoDriver);
  m_cWorldFile      = new WorldFile();

  m_cWorldFile->setIrrlichtDevice(*m_irrDevice);

  m_cEventReceiver->setParticleSystem(*m_cParticleSystem);
  m_cEventReceiver->setGUIHandler(*m_cGUIHandler);
  m_cEventReceiver->setWorldFile(*m_cWorldFile);

  m_cTimer = new Timer(*m_irrDevice);
  m_cTimer->Update();

  //! Pass irrlicht class pointers to our custom classes.
  m_cEventReceiver->setIrrlichtDevice(*m_irrDevice);
  m_cGUIHandler->setSceneManager(*m_irrSceneManager);
  m_cGUIHandler->setIrrlichtDevice(*m_irrDevice);
  m_cGUIHandler->setVideoDriver(*m_irrVideoDriver);
  m_cWorldManager->setIrrlichtDevice(*m_irrDevice);
  m_cWorldManager->setVideoDriver(*m_irrVideoDriver);
  m_cWorldManager->setSceneManager(*m_irrSceneManager);
}

/*! \brief  RenderDevice destructor.
 *
 */
RenderDevice::~RenderDevice()
{
  printf("Shutting down...\n");
  //m_cGUIHandler->showMouseCursor();

  if(m_cParticleSystem)
  {
    printf("\tDeleting particle system\n");
    delete m_cParticleSystem;
  }

  if(m_cEventReceiver)
  {
    printf("\tDeleting event receiver\n");
    delete m_cEventReceiver;
  }

  if(m_cGUIHandler)
  {
    printf("\tDeleting gui handler\n");
    delete m_cGUIHandler;
  }

  if(m_cWorldManager)
  {
    printf("\tDeleting world manager\n");
    delete m_cWorldManager;
  }

  if(m_cTimer)
  {
    printf("\tDeleting timer\n");
    delete m_cTimer;
  }

  if(m_irrDevice)
  {
    printf("\tDropping device\n");
    /// FIXME (Kjell#1#): Sigh, well, we're crashing here if there's a particle system in the scene. Not sure why yet.
    //m_irrDevice->drop();
    //delete m_irrDevice;
  }

  printf("\tDone!\n");
}

/*! \brief  Custom class initialization.
 *
 */
void RenderDevice::initialize(void)
{
  printf("[RD] Initialization...\n");

  //! Basic initialization of custom classes.
  m_cGUIHandler->initEnvironment();
  m_cLoadingScreen  = new LoadingScreen(*m_irrVideoDriver, *m_cGUIHandler->getGUIEnvironment());

  printf("\t...static world\n");

  m_cLoadingScreen->updateProgressBar(10, L"Loading environment...");
  this->initializeStaticWorld();

  printf("\t...cameras\n");

  m_cLoadingScreen->updateProgressBar(50, L"Loading...");
  this->initializeCamera();

  printf("\t...other\n");

  //! Other initialization.
  m_cLoadingScreen->updateProgressBar(70, L"Loading...");
  m_irrDevice->setEventReceiver(m_cEventReceiver);

  m_cLoadingScreen->updateProgressBar(100, L"Loading...");
	m_irrVideoDriver->setFog(video::SColor(0,56,0,80), EFT_FOG_EXP, 250, 1500, 0.6f, true, true);

  printf("\t...gui\n");

  m_cGUIHandler->createGUI();

  m_fps = 0;
  m_lastFPS = -1;

  printf("\t...particle system\n");

  m_cParticleSystem->initializeSystem();

  delete m_cLoadingScreen;

  printf("\t...done\n");
}

/*! \brief  Initialize static world.
 *
 */
void RenderDevice::initializeStaticWorld(void)
{
  //! Add lights.
  //m_cWorldManager->setLightColor(SColorf(250,240,250));
  //m_cWorldManager->setLightRadius(256);
  //m_cWorldManager->addLight(vector3df(-150,180,-150));

  m_cLoadingScreen->updateProgressBar(25, L"Loading environment...");

  //! Add environment.
  m_cWorldManager->setResourcePath("./models/");

  //m_cWorldManager->addAnimatedMeshNode("grid.x");
  //m_cWorldManager->setAnimatedMeshProperties(vector3df(0,0,0),vector3df(-90,0,0),vector3df(4.0f,4.0f,4.0f),0.0f,false);

  //! Add skybox.
  m_cWorldManager->setResourcePath(PATH_SKYBOX);
  m_cWorldManager->addSkyBox();
}

/*! \brief  Initialize cameras.
 *
 */
void RenderDevice::initializeCamera(void)
{
  printf("1\n");
  float farClipValue = 3000.0f;
  //float nearClipValue = 2.0f;

  printf("2\n");
  //! Create FPS style camera.
  SKeyMap keyMap[8];
  keyMap[0].Action = EKA_MOVE_FORWARD;
  keyMap[0].KeyCode = KEY_UP;
  keyMap[1].Action = EKA_MOVE_FORWARD;
  keyMap[1].KeyCode = KEY_KEY_W;

  keyMap[2].Action = EKA_MOVE_BACKWARD;
  keyMap[2].KeyCode = KEY_DOWN;
  keyMap[3].Action = EKA_MOVE_BACKWARD;
  keyMap[3].KeyCode = KEY_KEY_S;

  keyMap[4].Action = EKA_STRAFE_LEFT;
  keyMap[4].KeyCode = KEY_LEFT;
  keyMap[5].Action = EKA_STRAFE_LEFT;
  keyMap[5].KeyCode = KEY_KEY_A;

  keyMap[6].Action = EKA_STRAFE_RIGHT;
  keyMap[6].KeyCode = KEY_RIGHT;
  keyMap[7].Action = EKA_STRAFE_RIGHT;
  keyMap[7].KeyCode = KEY_KEY_D;

  printf("3\n");
  m_FPScamera = m_irrSceneManager->addCameraSceneNodeFPS(0, 100.0f, 180.0f, -1, keyMap, 8);
  m_FPScamera->setPosition(core::vector3df(0,-300,0));
  //m_FPScamera->setNearValue(nearClipValue);
  m_FPScamera->setFarValue(farClipValue);
  m_FPScamera->setPosition(vector3df(10,10,10));
  m_FPScamera->setTarget(vector3df(0,0,0));

  //printf("FPS Camera FOV: %i\n",m_FPScamera->getFOV());

  printf("4\n");
  //! Create Maya style camera.
  m_MAYAcamera = m_irrSceneManager->addCameraSceneNodeMaya(0, -80, 80, 80, -1);
  //m_MAYAcamera->setNearValue(nearClipValue);
  m_MAYAcamera->setFarValue(farClipValue);
  m_MAYAcamera->setPosition(vector3df(10,10,10));
  m_MAYAcamera->setTarget(vector3df(0,0,0));

  printf("5\n");
  m_cEventReceiver->setCamera(*m_MAYAcamera);

  printf("6\n");
  m_s32CurrentCamera = CAMERA_STYLE_MAYA;
  switchCamera();
  printf("7\n");
}

void RenderDevice::switchCamera(void)
{
  switch( m_s32CurrentCamera )
  {
    case CAMERA_STYLE_MAYA:
    {
      m_irrSceneManager->setActiveCamera(m_MAYAcamera);
      m_s32CurrentCamera = CAMERA_STYLE_FPS;
      /// FIXME (Kjell#1#): What the %#&# is up with this not working????????!
      //m_cGUIHandler->showMouseCursor();
      printf("Camera mode set to MAYA.\n");
    } break;
    case CAMERA_STYLE_FPS:
    {
      m_irrSceneManager->setActiveCamera(m_FPScamera);
      m_s32CurrentCamera = CAMERA_STYLE_MAYA;
      //m_cGUIHandler->hideMouseCursor();
      printf("Camera mode set to FPS.\n");
    } break;
  }
}

void RenderDevice::checkEvents(void)
{
  //! Do we want to change camera view?
  if(m_cEventReceiver->getCameraChange())
  {
    switchCamera();
    m_cEventReceiver->setCameraChange(false);
  }
}

f32 step = 0.9f;
void RenderDevice::updateTimedEvents(void)
{
  m_cTimer->Update();

  for(f32 factor = 0; factor < m_cTimer->getTimeFactor(); factor+=1.0f)
  {
    this->checkEvents();
  }
}

void RenderDevice::updateFPS(void)
{
  m_fps = m_irrVideoDriver->getFPS();
  if(m_lastFPS != m_fps)
  {
    stringw str = L"Irrlicht Particle Editor [build ";
    str += AutoBuildNumber;
    str += "] [";
    str += m_irrVideoDriver->getName();
    str += "] FPS:";
    str += m_fps;

    m_irrDevice->setWindowCaption(str.c_str());
    m_lastFPS = m_fps;
  }
}

/*! \brief  Render loop.
 *
 */
void RenderDevice::renderLoop(void)
{
  while(m_irrDevice->run())
  {
    m_irrVideoDriver->beginScene(true, true, SColor(0,0,0,0));

    m_irrSceneManager->drawAll();

    //! Draw other GUI elements. (Menu, toolbox, ...)
    m_cGUIHandler->draw();

    m_irrVideoDriver->endScene();

    this->updateTimedEvents();
    this->updateFPS();
  }
}
