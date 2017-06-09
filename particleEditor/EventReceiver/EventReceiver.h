#ifndef EVENT_RECEIVER_H
#define EVENT_RECEIVER_H

#include "globals.hxx"
#include "../GuiHandler/GuiHandler.h"
#include "../ParticleSystem/ParticleSystem.h"
#include "../WorldManager/WorldFile.h"

class Event_Receiver : public IEventReceiver
{
	public:
		Event_Receiver();
		virtual ~Event_Receiver();

		virtual bool OnEvent(const SEvent &evt);

    // FIXME (kjeiwa-3#1#): Seriously, passing variables back and forth from the event receiver, bonkers.. Fix.

    __inline bool getLMousePressed() { return m_bLMousePressed; }
    __inline void setLMousePressed(bool pressed) { m_bLMousePressed = pressed; }

    __inline bool getCameraChange(void) { return m_bCameraChange; };
    __inline void setCameraChange(bool change) { m_bCameraChange = change; }

    __inline void setParticleSystem(ParticleSystem &ps){
      m_cParticleSystem = &ps;
    }

    __inline void setGUIHandler(GUI_Handler &gh){
      m_cGUIHandler = &gh;
    }
    __inline void setWorldFile(WorldFile &wf){
      m_cWorldFile = &wf;
    }
    __inline void setCamera(ICameraSceneNode &cam){
      camera = &cam;
    }

    ITriangleSelector *getTriangleSelector(void){
      return selector;
    }

		IrrlichtDevice *getIrrlichtDevice();
		void            setIrrlichtDevice(IrrlichtDevice &device);

	protected:
	private:

  //! For storing speed values of the maya camera.
  vector3df m_cameraSpeed;

  enum LOAD_TYPE
  {
    LOAD_TYPE_ENV = 55462,
    LOAD_TYPE_TEXTURE
  };
  s32 m_loadType;

  struct EMITTER_SELECTION
  {
    u32 id;
    array<stringc> name;
  };
  EMITTER_SELECTION emitterSelect;

  IrrlichtDevice  *m_irrDevice;

  struct CURSOR_VALUES
  {
    float prevXValue;
    float prevYValue;
    float prevZValue;
  };
  CURSOR_VALUES m_cursorValue;

  //! Used for mouse 3d picking.
  line3d<f32> line;
  vector3df intersection;
  triangle3d<f32> tri;

  //! File to save to.
  stringc m_cFileName;

  ParticleSystem  *m_cParticleSystem;
  GUI_Handler     *m_cGUIHandler;
  WorldFile       *m_cWorldFile;

  IAnimatedMesh *mesh;
  ISceneNode *node;
  ITriangleSelector *selector;
  ICameraSceneNode *camera;

  bool m_bLMousePressed;
  bool m_bCameraChange; // Change camera.
};

#endif // EVENT_RECEIVER_H
