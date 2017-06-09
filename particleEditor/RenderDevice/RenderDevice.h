#ifndef RENDERDEVICE_H
#define RENDERDEVICE_H

#include "globals.hxx"
#include "../EventReceiver/EventReceiver.h"
#include "../WorldManager/WorldManager.h"
#include "LoadingScreen.h"
#include "../Helpers/Timer.h"
#include "../ParticleSystem/ParticleSystem.h"
#include "version.h"

/*! \brief  RenderDevice class.
 *          This class wraps the other classes.
 *          We call this from our main function to setup our initial settings.
 */
class RenderDevice
{
  public:

    RenderDevice(
      E_DRIVER_TYPE driverType = EDT_OPENGL,
      dimension2d<u32>dimension = dimension2d<u32>(1280,720),
      u32 bitDepth = 32,
      bool fullScreen = false,
      bool stencilBuffer = false,
      bool vSync = false,
      IEventReceiver *receiver = 0
    );

    virtual ~RenderDevice();

    //!
    void initialize(void);
    void initializeStaticWorld(void);
    void initializeCamera(void);

    void renderLoop(void);

    void checkEvents(void);
    void updateTimedEvents(void);
    void updateFPS(void);

    void switchCamera(void);

    void loadWorldFile(bool parentDir);
    void saveWorldFile(void);

    void setWorkDir(stringc dir){
      workDir = dir;
      printf("[RD] Workdir: %s\n", workDir.c_str());
      m_cWorldFile->setWorkDir(workDir);
      m_cParticleSystem->setWorkDir(workDir);
      m_cGUIHandler->setWorkDir(workDir);
    }

    //! Inlined functions.
    IrrlichtDevice __inline *getIrrlichtDevice(void) {
      return m_irrDevice;
    }

    ICameraSceneNode *getCurrentCamera(void){
      switch(m_s32CurrentCamera)
      {
        case CAMERA_STYLE_MAYA:
          return m_MAYAcamera;
        case CAMERA_STYLE_FPS:
          return m_FPScamera;
        default:
          return m_MAYAcamera;
      }
    }

  protected:
  private:

  stringc workDir;

  s32 m_windowWidth;   // Width of the window.
  s32 m_windowHeight;  // Height of the window.
  s32 m_windowBPP;     // Bits per pixel.

  E_DRIVER_TYPE m_driverType;

  IrrlichtDevice  *m_irrDevice;
  IVideoDriver    *m_irrVideoDriver;
  ISceneManager   *m_irrSceneManager;

  //! Custom classes.
  Event_Receiver  *m_cEventReceiver;
  GUI_Handler     *m_cGUIHandler;
  World_Manager   *m_cWorldManager;
  LoadingScreen   *m_cLoadingScreen;
  Timer           *m_cTimer;
  ParticleSystem  *m_cParticleSystem;
  WorldFile       *m_cWorldFile;

  ICameraSceneNode    *m_FPScamera;
  ICameraSceneNode    *m_MAYAcamera;
  s32 m_s32CurrentCamera;

  IAnimatedMesh           *m_gridMesh;
  ISceneNode              *m_gridNode;

  //! Used to create collision response animator.
  IAnimatedMesh       *m_sceneMesh;
  ISceneNode          *m_sceneNode;
  //ITriangleSelector   *m_irrTriangleSelector;
  ISceneNodeAnimator  *m_irrSceneNodeAnimator;

  int m_lastFPS;
  int m_fps;
};

#endif // RENDERDEVICE_H
