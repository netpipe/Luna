#include "EventReceiver.h"

// ------------------------------------------------------------------------
// De- / Constructor
// ------------------------------------------------------------------------
Event_Receiver::Event_Receiver():
  m_cameraSpeed(vector3df(-80,80,80)),
  intersection(vector3df(0,0,0))
  // TODO (kjeiwa-3#1#): These values should be saved and loaded.
{
  m_irrDevice = NULL;

  setLMousePressed(false);
  setCameraChange(false);
  mesh = NULL;
  node = NULL;
  selector = NULL;

  printf("[*] Event Receiver initialized.\n");
}
// ------------------------------------------------------------------------
Event_Receiver::~Event_Receiver()
{
  if(m_irrDevice != NULL)
    m_irrDevice = NULL;

  printf("[*] Event Receiver deinitialized.\n");
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
IrrlichtDevice *Event_Receiver::getIrrlichtDevice()
{
  return m_irrDevice;
}
// ------------------------------------------------------------------------
void Event_Receiver::setIrrlichtDevice(IrrlichtDevice &device)
{
  m_irrDevice = &device;
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
bool Event_Receiver::OnEvent(const SEvent &evt)
{
  if(!m_irrDevice)
  {
    printf("[ER] m_irrDevice == NULL\n");
    return false;
  }

  else if(evt.EventType == EET_KEY_INPUT_EVENT &&
    evt.KeyInput.Key == KEY_ESCAPE &&
    evt.KeyInput.PressedDown == false)
  {
    m_irrDevice->closeDevice();
    return true;
  }

  else if(evt.EventType == EET_KEY_INPUT_EVENT &&
    evt.KeyInput.Key == KEY_PRIOR &&
    evt.KeyInput.PressedDown == false)
  {
    setCameraChange(true);
    return true;
  }

  else if(evt.EventType == EET_KEY_INPUT_EVENT &&
    evt.KeyInput.Key == KEY_F5 &&
    evt.KeyInput.PressedDown == false)
  {
    if(!node)
      m_cParticleSystem->addParticleSystem(m_cGUIHandler->getCursorPos());
    else
      m_cParticleSystem->addParticleSystem(intersection);

    m_cParticleSystem->updateParticleSystem();

    stringw emitterName = L"Emitter ";
    emitterName += m_cParticleSystem->getCurrentID();
    m_cGUIHandler->addEmitterListItem(emitterName.c_str());

    emitterSelect.name.push_back(emitterName.c_str());
    return true;
  }

  //! -----------------------------------------------------
  //! Shortcuts for displaying GUI elements.
  //! -----------------------------------------------------
  if(evt.EventType == EET_KEY_INPUT_EVENT &&
    evt.KeyInput.Key == KEY_F1 &&
    evt.KeyInput.PressedDown == false)
  {
    m_cGUIHandler->createToolBox();
    return true;
  }
  if(evt.EventType == EET_KEY_INPUT_EVENT &&
    evt.KeyInput.Key == KEY_F2 &&
    evt.KeyInput.PressedDown == false)
  {
    m_cGUIHandler->createSettingsWindow();
    return true;
  }
  if(evt.EventType == EET_KEY_INPUT_EVENT &&
    evt.KeyInput.Key == KEY_F3 &&
    evt.KeyInput.PressedDown == false)
  {
    m_cGUIHandler->createEmitterList();
    return true;
  }

  //! -----------------------------------------------------
  //! Shortcut for displaying all GUI elements.
  //! -----------------------------------------------------
  if(evt.EventType == EET_KEY_INPUT_EVENT &&
    evt.KeyInput.Key == KEY_TAB &&
    evt.KeyInput.PressedDown == false)
  {
    //! Check if any of the gui windows exists.
    if( m_cGUIHandler->windowExists(IRR_WINDOW_TOOLBOX, false) ||
        m_cGUIHandler->windowExists(IRR_WINDOW_EMITTER_LIST, false) ||
        m_cGUIHandler->windowExists(IRR_WINDOW_SETTINGS, false))
    {
      m_cGUIHandler->windowExists(IRR_WINDOW_TOOLBOX, true);
      m_cGUIHandler->windowExists(IRR_WINDOW_EMITTER_LIST, true);
      m_cGUIHandler->windowExists(IRR_WINDOW_SETTINGS, true);
      return true;
    }
    else
    {
      m_cGUIHandler->createToolBox();
      m_cGUIHandler->createSettingsWindow();
      m_cGUIHandler->createEmitterList();
      return true;
    }
    return true;
  }

  if(evt.EventType == EET_MOUSE_INPUT_EVENT &&
    evt.MouseInput.Event == EMIE_MMOUSE_PRESSED_DOWN)
  {
    if(getTriangleSelector() == NULL)
      return false;

    line =
      m_irrDevice->getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates(
        m_irrDevice->getCursorControl()->getPosition(),
        camera);

		const ISceneNode *hitNode = 0;
    m_irrDevice->getSceneManager()->getSceneCollisionManager()->getCollisionPoint(
      line, getTriangleSelector(), intersection, tri, hitNode);

    //! Move slightly up above ground.
    intersection.Y += 1;
    m_cGUIHandler->setCursorPosition(intersection);

    printf("Cursor position: %f %f %f\n",
      intersection.X,
      intersection.Y,
      intersection.Z);

    return true;
  }

  if (evt.EventType == EET_GUI_EVENT)
  {
    s32 id = evt.GUIEvent.Caller->getID();
    IGUIEnvironment* env = m_irrDevice->getGUIEnvironment();

		printf("ID: %i, EventType: %i\n", id, evt.GUIEvent.EventType);

	//	if(id <= 0) return false;

		if(id == 21587 && evt.GUIEvent.EventType == 1)
		{
			printf("");
		}

    switch(evt.GUIEvent.EventType)
    {
			case EGET_ELEMENT_CLOSED:
			{
				if(id == IRR_WINDOW_EMITTER_LIST)
					m_cGUIHandler->windowExists(IRR_WINDOW_EMITTER_LIST, true);
				if(id == IRR_WINDOW_HELP)
					m_cGUIHandler->windowExists(IRR_WINDOW_HELP, true);
				if(id == IRR_WINDOW_HELP_LIST)
					m_cGUIHandler->windowExists(IRR_WINDOW_HELP_LIST, true);
				if(id == IRR_WINDOW_SETTINGS)
					m_cGUIHandler->windowExists(IRR_WINDOW_SETTINGS, true);
				if(id == IRR_WINDOW_TOOLBOX)
					m_cGUIHandler->windowExists(IRR_WINDOW_TOOLBOX, true);
				if(id == IRR_WINDOW_USER_INPUT)
					m_cGUIHandler->windowExists(IRR_WINDOW_USER_INPUT, true);
			}	break;

			case IRR_WINDOW_HELP:
			{
				m_cGUIHandler->windowExists(IRR_WINDOW_HELP, true);
				return true;
			}	break;

      case EGET_MENU_ITEM_SELECTED:
      {
				IGUIContextMenu* menu = (IGUIContextMenu*)evt.GUIEvent.Caller;
				s32 id = menu->getItemCommandId(menu->getSelectedItem());

        switch(id)
        {
          case MENU_LOAD_ENV:
          {
            m_loadType = LOAD_TYPE_ENV;
            env->addFileOpenDialog(L"Select environment file to load");
          } break;
          case MENU_FILE_SAVE_CPP:
          {
            if(m_cParticleSystem->getCurrentID() < 0)
            {
              printf("Can't save with no particles in the scene. Current ID: %i\n", m_cParticleSystem->getCurrentID());
              break;
            }
            m_cGUIHandler->getUserInputString(L"Save to C++ file", L"Enter name of file to save to", USER_INPUT_STRING_TYPE_SAVE_CPP);
          } break;
          case MENU_FILE_QUIT:
          {
            m_irrDevice->closeDevice();
          } break;
          case MENU_EDIT_SHOW_TOOLBOX:
          {
            m_cGUIHandler->createToolBox();
          } break;
          case MENU_EDIT_SHOW_EMITTER_LIST:
          {
            m_cGUIHandler->createEmitterList();
          } break;
          case MENU_HELP_USAGE:
          {
            m_cGUIHandler->createHelpWindow();
          } break;
          case MENU_EDIT_SHOW_SETTINGS:
          {
            m_cGUIHandler->createSettingsWindow();

            IGUIElement *px = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_POS_X);
            IGUIElement *py = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_POS_Y);
            IGUIElement *pz = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_POS_Z);
            IGUIElement *rx = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_ROT_X);
            IGUIElement *ry = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_ROT_Y);
            IGUIElement *rz = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_ROT_Z);
            IGUIElement *sx = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_SCL_X);
            IGUIElement *sy = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_SCL_Y);
            IGUIElement *sz = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_SCL_Z);

            vector3df pos = m_cGUIHandler->getCursorPos();
            vector3df rot = m_cGUIHandler->getCursorRot();
            vector3df scl = m_cGUIHandler->getCursorScl();

            wchar_t t1[MAXSTRING] = L"";

            swprintf(t1, MAXSTRING, L"%.2f", pos.X);            px->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", pos.Y);            py->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", pos.Z);            pz->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", rot.X);            rx->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", rot.Y);            ry->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", rot.Z);            rz->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", scl.X);            sx->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", scl.Y);            sy->setText(t1);
            swprintf(t1, MAXSTRING, L"%.2f", scl.Z);            sz->setText(t1);

            if(node)
            {
              px = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_POSITION_X);
              py = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_POSITION_Y);
              pz = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_POSITION_Z);
              rx = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_ROTATION_X);
              ry = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_ROTATION_Y);
              rz = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_ROTATION_Z);
              sx = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_SCALE_X);
              sy = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_SCALE_Y);
              sz = m_cGUIHandler->getGUIElement(IRR_TOOLBOX_ENV_SCALE_Z);

              pos = node->getPosition();
              rot = node->getRotation();
              scl = node->getScale();

              swprintf(t1, MAXSTRING, L"%.2f", pos.X);            px->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", pos.Y);            py->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", pos.Z);            pz->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", rot.X);            rx->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", rot.Y);            ry->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", rot.Z);            rz->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", scl.X);            sx->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", scl.Y);            sy->setText(t1);
              swprintf(t1, MAXSTRING, L"%.2f", scl.Z);            sz->setText(t1);
            }
          } break;
        }
      } break;

      case EGET_FILE_SELECTED:
      {
        switch(m_loadType)
        {
          case LOAD_TYPE_TEXTURE:
          {
            if(m_cParticleSystem->getCurrentID() > -1)
            {
              IGUIFileOpenDialog *dialog =
                (IGUIFileOpenDialog*)evt.GUIEvent.Caller;

              stringc file = core::stringc(dialog->getFileName()).c_str();

              s32 pos = file.findLast('/');
              stringc fileName = file.subString(pos+1, strlen(file.c_str()));

              printf("SET PARTICLE TEXTURE NAME[0]: %s\n", fileName.c_str());
              m_cParticleSystem->setParticleTexture(fileName, false);

              m_cParticleSystem->updateParticleSystem();
              //m_cGUIHandler->updateParticleTextureImage(fileName);
              m_cGUIHandler->updateParticleTextureImage(m_cParticleSystem->getParticleTexture());
            }
          } break;
          case LOAD_TYPE_ENV:
          {
            IGUIFileOpenDialog *dialog =
              (IGUIFileOpenDialog*)evt.GUIEvent.Caller;

            stringw file = core::stringw(dialog->getFileName()).c_str();

            s32 pos = file.findLast('.');
            stringw fileExt = file.subString(pos+1, wcslen(file.c_str()));

            if( (wcscmp(fileExt.c_str(), L"pk3")) == 0)
            {
              stringc file = core::stringc(dialog->getFileName()).c_str();

              s32 pos2 = file.findLast('-');
              stringc fileName = file.subString(pos2+1, pos - (pos2+1));

              fileName += L".bsp";

              m_irrDevice->getFileSystem()->addZipFileArchive(file.c_str());
              mesh = m_irrDevice->getSceneManager()->getMesh(fileName.c_str());
              if(mesh)
              {
                node = m_irrDevice->getSceneManager()->addOctTreeSceneNode(mesh->getMesh(0));
                if(node)
                {
                  node->setPosition(vector3df(0,0,0));
                }
              }
            }
            if( (wcscmp(fileExt.c_str(), L"dmf")) == 0)
            {
              stringc file = core::stringc(dialog->getFileName()).c_str();

              mesh = m_irrDevice->getSceneManager()->getMesh(file.c_str());
              if(mesh)
              {
                node = m_irrDevice->getSceneManager()->addOctTreeSceneNode(mesh->getMesh(0));
                if(node)
                {
                  //node->setPosition(vector3df(-1300, -144, -1249));
                }
              }
            }

            //! Create collision.
            if((mesh!=NULL) && (node!=NULL))
            {
              selector = m_irrDevice->getSceneManager()->createOctTreeTriangleSelector(mesh->getMesh(0), node, 128);
              node->setTriangleSelector(selector);
              selector->drop();

              ISceneNodeAnimator *anim = m_irrDevice->getSceneManager()->createCollisionResponseAnimator(
                selector, camera, vector3df(30,50,30),
                vector3df(0,0,0), vector3df(0,0,0));
              camera->addAnimator(anim);
              anim->drop();
            }
          } break;
        }
      } break;

      case EGET_BUTTON_CLICKED:
      {
        switch(id)
        {
          case IRR_TOOLBOX_PARTICLE_TEXTURE_BTN:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            m_loadType = LOAD_TYPE_TEXTURE;
            env->addFileOpenDialog(L"Select file to open");
          } break;

          case IRR_TOOLBOX_BUTTON_LOAD_PRESETS:
          {
            m_cWorldFile->loadParticleSystemPresetsXMLFile("./presets/presets.xml", *m_cParticleSystem);

            m_cGUIHandler->clearPresetNames();

            for(u32 i = 0; i < m_cParticleSystem->presetNames.size(); i++)
            {
              m_cGUIHandler->addPresetName((wchar_t *)m_cParticleSystem->presetNames[i].c_str());
            }

          } break;

          case IRR_TOOLBOX_BUTTON_SAVE_PRESETS:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            m_cWorldFile->saveParticleSystemPresetsXMLFile("./presets/presets.xml", *m_cParticleSystem);
          } break;

          case IRR_TOOLBOX_BUTTON_ADD_PRESET:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            m_cParticleSystem->addPreset(m_cGUIHandler->getPresetName());
            m_cGUIHandler->addPresetName(m_cGUIHandler->getPresetName());
          } break;

          case IRR_TOOLBOX_EMITTER_CONFIRM_NEW_EMITTER:
          {
            if(!node)
              m_cParticleSystem->addParticleSystem(m_cGUIHandler->getCursorPos());
            else
              m_cParticleSystem->addParticleSystem(intersection);
            m_cParticleSystem->updateParticleSystem();

            stringw emitterName = L"Emitter ";
            emitterName += m_cParticleSystem->getCurrentID();
            m_cGUIHandler->addEmitterListItem(emitterName.c_str());

            emitterSelect.name.push_back(emitterName.c_str());
          } break;
          case IRR_TOOLBOX_EMITTER_CONFIRM_UPDATE_EMITTER:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            m_cParticleSystem->createEmitter();
            m_cParticleSystem->updateParticleSystem();
          } break;

          case IRR_EMITTER_LIST_DELETE_EMITTER_BTN:
          {
            /*
            emitterSelect.name.erase(m_cParticleSystem->getCurrentID());
            m_cParticleSystem->deleteCurrentSystem();
            m_cGUIHandler->clearEmitterList();
            for(u32 i = 0; i < emitterSelect.name.size(); i++)
            {
              m_cGUIHandler->addEmitterListItem(emitterSelect.name[i].c_str());
            }
            */
          } break;
        }
      } break;

      case EGET_EDITBOX_ENTER:
      {
        switch(id)
        {
          //! ----------------
          //! Particle editboxes.
          //! ----------------
          case IRR_TOOLBOX_PARTICLE_SCALE_X:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticleScaleX(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_PARTICLE_SCALE_Y:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticleScaleY(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_PARTICLE_SCALE_Z:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticleScaleZ(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          } break;

          case IRR_TOOLBOX_PARTICLE_SIZE_X:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticleSizeX(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_PARTICLE_SIZE_Y:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticleSizeY(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          } break;

          case IRR_TOOLBOX_PARTICLE_POSITION_X:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticlePositionX(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          }
          case IRR_TOOLBOX_PARTICLE_POSITION_Y:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticlePositionY(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          }
          case IRR_TOOLBOX_PARTICLE_POSITION_Z:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setParticlePositionZ(atof(temp.c_str()));
            m_cParticleSystem->updateParticleSystem();
          }

          //! ----------------
          //! Emitter editboxes.
          //! ----------------
          case IRR_TOOLBOX_EMITTER_BOX_WIDTH:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterBox(
              (s32)atof(temp.c_str()),
              (s32)m_cParticleSystem->getEmitterBoxHeight(),
              (s32)m_cParticleSystem->getEmitterBoxLength()
            );
          } break;
          case IRR_TOOLBOX_EMITTER_BOX_HEIGHT:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterBox(
              (s32)m_cParticleSystem->getEmitterBoxWidth(),
              (s32)atof(temp.c_str()),
              (s32)m_cParticleSystem->getEmitterBoxLength()
            );
          } break;
          case IRR_TOOLBOX_EMITTER_BOX_LENGTH:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterBox(
              (s32)m_cParticleSystem->getEmitterBoxWidth(),
              (s32)m_cParticleSystem->getEmitterBoxHeight(),
              (s32)atof(temp.c_str())
            );
          } break;

          case IRR_TOOLBOX_EMITTER_DIRECTION_X:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterDirectionX(atof(temp.c_str()));
          } break;
          case IRR_TOOLBOX_EMITTER_DIRECTION_Y:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterDirectionY(atof(temp.c_str()));
          } break;
          case IRR_TOOLBOX_EMITTER_DIRECTION_Z:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterDirectionZ(atof(temp.c_str()));
          } break;

          case IRR_TOOLBOX_EMITTER_PARTICLES_MIN:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterParticlesMin((u32)atof(temp.c_str()));
          } break;
          case IRR_TOOLBOX_EMITTER_PARTICLES_MAX:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterParticlesMax((u32)atof(temp.c_str()));
          } break;

          case IRR_TOOLBOX_EMITTER_PARTICLES_LIFE_MIN:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterParticlesLifeMin((u32)atof(temp.c_str()));
          } break;
          case IRR_TOOLBOX_EMITTER_PARTICLES_LIFE_MAX:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterParticlesLifeMax((u32)atof(temp.c_str()));
          } break;

          case IRR_TOOLBOX_EMITTER_PARTICLES_ANGLE:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setEmitterMaxAngleDegrees((s32)atof(temp.c_str()));
          } break;

          //! ----------------
          //! Affector.
          //! ----------------
          case IRR_TOOLBOX_AFFECTOR_TIME_FORCE_LOST:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setAffectorTimeForceLost((u32)atof(temp.c_str()));
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_AFFECTOR_GRAVITY_X:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setAffectorGravity( vector3df(atof(temp.c_str()), m_cParticleSystem->getAffectorGravity().Y, m_cParticleSystem->getAffectorGravity().Z) );
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_AFFECTOR_GRAVITY_Y:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setAffectorGravity( vector3df(m_cParticleSystem->getAffectorGravity().X, atof(temp.c_str()), m_cParticleSystem->getAffectorGravity().Z) );
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_AFFECTOR_GRAVITY_Z:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setAffectorGravity( vector3df(m_cParticleSystem->getAffectorGravity().X, m_cParticleSystem->getAffectorGravity().Y, atof(temp.c_str())) );
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_AFFECTOR_FADEOUT_TIME:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cParticleSystem->setAffectorFadeOutTime((u32)atof(temp.c_str()));
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;

          //! Environment settings editboxes.
          //! ----------------
          //! Position.
          //! ----------------
          case IRR_TOOLBOX_ENV_POSITION_X:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setPosition(vector3df(atof(temp.c_str()), node->getPosition().Y, node->getPosition().Z));
          } break;
          case IRR_TOOLBOX_ENV_POSITION_Y:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setPosition(vector3df(node->getPosition().X, atof(temp.c_str()), node->getPosition().Z));
          } break;
          case IRR_TOOLBOX_ENV_POSITION_Z:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setPosition(vector3df(node->getPosition().X, node->getPosition().Y, atof(temp.c_str())));
          } break;
          //! ----------------
          //! Rotation.
          //! ----------------
          case IRR_TOOLBOX_ENV_ROTATION_X:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setRotation(vector3df(atof(temp.c_str()), node->getRotation().Y, node->getRotation().Z));
          } break;
          case IRR_TOOLBOX_ENV_ROTATION_Y:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setRotation(vector3df(node->getRotation().X, atof(temp.c_str()), node->getRotation().Z));
          } break;
          case IRR_TOOLBOX_ENV_ROTATION_Z:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setRotation(vector3df(node->getRotation().X, node->getRotation().Y, atof(temp.c_str())));
          } break;
          //! ----------------
          //! Scale.
          //! ----------------
          case IRR_TOOLBOX_ENV_SCALE_X:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setScale(vector3df(atof(temp.c_str()), node->getScale().Y, node->getScale().Z));
          } break;
          case IRR_TOOLBOX_ENV_SCALE_Y:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setScale(vector3df(node->getScale().X, atof(temp.c_str()), node->getScale().Z));
          } break;
          case IRR_TOOLBOX_ENV_SCALE_Z:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            if(node != NULL)
              node->setScale(vector3df(node->getScale().X, node->getScale().Y, atof(temp.c_str())));
          } break;

          //! Camera settings editboxes.
          //! ----------------
          //! Rotation.
          //! ----------------
          case IRR_SETTINGS_CAM_MAYA_SPEED_ROTATION:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cameraSpeed.X = atof(temp.c_str());
            // NOTE (kjeiwa-3#1#): Is this wise? I'm not so sure if this removes the old camera.
            vector3df pos = camera->getPosition();
            vector3df view = camera->getTarget();
            camera = m_irrDevice->getSceneManager()->addCameraSceneNodeMaya(0, m_cameraSpeed.X, m_cameraSpeed.Y, m_cameraSpeed.Z, -1);
            camera->setPosition(pos);
            camera->setTarget(view);
          } break;

          //! ----------------
          //! Zoom.
          //! ----------------
          case IRR_SETTINGS_CAM_MAYA_SPEED_ZOOM:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cameraSpeed.Y = atof(temp.c_str());
            vector3df pos = camera->getPosition();
            vector3df view = camera->getTarget();
            camera = m_irrDevice->getSceneManager()->addCameraSceneNodeMaya(0, m_cameraSpeed.X, m_cameraSpeed.Y, m_cameraSpeed.Z, -1);
            camera->setPosition(pos);
            camera->setTarget(view);
          } break;

          //! ----------------
          //! Translate.
          //! ----------------
          case IRR_SETTINGS_CAM_MAYA_SPEED_TRANSLATE:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cameraSpeed.Z = atof(temp.c_str());
            vector3df pos = camera->getPosition();
            vector3df view = camera->getTarget();
            camera = m_irrDevice->getSceneManager()->addCameraSceneNodeMaya(0, m_cameraSpeed.X, m_cameraSpeed.Y, m_cameraSpeed.Z, -1);
            camera->setPosition(pos);
            camera->setTarget(view);
          } break;

          //! ----------------
          //! Cursor settings.
          //! ----------------
          case IRR_SETTINGS_CURSOR_POS_X:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorPos(vector3df(atof(temp.c_str()), m_cGUIHandler->getCursorPos().Y, m_cGUIHandler->getCursorPos().Z));
          } break;
          case IRR_SETTINGS_CURSOR_POS_Y:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorPos(vector3df(m_cGUIHandler->getCursorPos().X, atof(temp.c_str()), m_cGUIHandler->getCursorPos().Z));
          } break;
          case IRR_SETTINGS_CURSOR_POS_Z:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorPos(vector3df(m_cGUIHandler->getCursorPos().X, m_cGUIHandler->getCursorPos().Y, atof(temp.c_str())));
          } break;

          case IRR_SETTINGS_CURSOR_ROT_X:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorRot(vector3df(atof(temp.c_str()), m_cGUIHandler->getCursorRot().Y, m_cGUIHandler->getCursorRot().Z));
          } break;
          case IRR_SETTINGS_CURSOR_ROT_Y:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorRot(vector3df(m_cGUIHandler->getCursorRot().X, atof(temp.c_str()), m_cGUIHandler->getCursorRot().Z));
          } break;
          case IRR_SETTINGS_CURSOR_ROT_Z:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorRot(vector3df(m_cGUIHandler->getCursorRot().X, m_cGUIHandler->getCursorRot().Y, atof(temp.c_str())));
          } break;

          case IRR_SETTINGS_CURSOR_SCL_X:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorScl(vector3df(atof(temp.c_str()), m_cGUIHandler->getCursorScl().Y, m_cGUIHandler->getCursorScl().Z));
          } break;
          case IRR_SETTINGS_CURSOR_SCL_Y:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorScl(vector3df(m_cGUIHandler->getCursorScl().X, atof(temp.c_str()), m_cGUIHandler->getCursorScl().Z));
          } break;
          case IRR_SETTINGS_CURSOR_SCL_Z:
          {
            stringc temp = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->setCursorScl(vector3df(m_cGUIHandler->getCursorScl().X, m_cGUIHandler->getCursorScl().Y, atof(temp.c_str())));
          } break;

          case IRR_INPUT_USER_STRING_EMITTER_NAME:
          {
            emitterSelect.name[emitterSelect.id] = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
            m_cGUIHandler->windowExists(IRR_WINDOW_USER_INPUT, true);
            m_cGUIHandler->clearEmitterList();
            for(u32 i = 0; i < emitterSelect.name.size(); i++)
              m_cGUIHandler->addEmitterListItem(emitterSelect.name[i].c_str());
            m_cGUIHandler->selectEmitterListItem(emitterSelect.id);
          } break;
          case IRR_INPUT_USER_STRING_SAVE_CPP_NAME:
          {
            s32 id = m_cParticleSystem->getCurrentID();
            //m_cWorldFile->saveParticleSystemToCPP("ParticleSystem.cpp", *m_cParticleSystem);
            for(s32 current = 0; current < (m_cParticleSystem->getParticleSystemCount()+1); current++)
            {
              stringc name = ((IGUIEditBox*)evt.GUIEvent.Caller)->getText();
              printf("current = %i\n", current);
              m_cParticleSystem->setCurrentID(current);
              m_cWorldFile->saveParticleSystemToCPP(
                name,
                emitterSelect.name[current],
                *m_cParticleSystem,
                (current == 0) ? false : true);
            }
            m_cParticleSystem->setCurrentID(id);
          } break;
        }
      } break;

      case EGET_SCROLL_BAR_CHANGED:
      {
        s32 pos = ((IGUIScrollBar*)evt.GUIEvent.Caller)->getPos();
        SColor prevMinCol = m_cParticleSystem->getEmitterMinStartColor();
        SColor prevMaxCol = m_cParticleSystem->getEmitterMaxStartColor();
        SColor prevTargetCol = m_cParticleSystem->getAffectorTargetColor();
        vector3df cursorPos = m_cGUIHandler->getCursorPos();
        wchar_t t1[MAXSTRING];

        switch(id)
        {
          //! -------------------------------------
          //! Emitter min & max color updates.
          //! -------------------------------------
          case IRR_TOOLBOX_EMITTER_MIN_COLOR_R_COMPONENT:
          {
            m_cParticleSystem->setEmitterMinStartColor( SColor(prevMinCol.getAlpha(), pos, prevMinCol.getGreen(), prevMinCol.getBlue()) );
            m_cGUIHandler->updateEmitterColorImage(m_cParticleSystem->getEmitterMinStartColor(), true);
          } break;
          case IRR_TOOLBOX_EMITTER_MIN_COLOR_G_COMPONENT:
          {
            m_cParticleSystem->setEmitterMinStartColor( SColor(prevMinCol.getAlpha(), prevMinCol.getRed(), pos, prevMinCol.getBlue()) );
            m_cGUIHandler->updateEmitterColorImage(m_cParticleSystem->getEmitterMinStartColor(), true);
          } break;
          case IRR_TOOLBOX_EMITTER_MIN_COLOR_B_COMPONENT:
          {
            m_cParticleSystem->setEmitterMinStartColor( SColor(prevMinCol.getAlpha(), prevMinCol.getRed(), prevMinCol.getGreen(), pos) );
            m_cGUIHandler->updateEmitterColorImage(m_cParticleSystem->getEmitterMinStartColor(), true);
          } break;

          case IRR_TOOLBOX_EMITTER_MAX_COLOR_R_COMPONENT:
          {
            m_cParticleSystem->setEmitterMaxStartColor( SColor(prevMaxCol.getAlpha(), pos, prevMaxCol.getGreen(), prevMaxCol.getBlue()) );
            m_cGUIHandler->updateEmitterColorImage(m_cParticleSystem->getEmitterMaxStartColor(), false);
          } break;
          case IRR_TOOLBOX_EMITTER_MAX_COLOR_G_COMPONENT:
          {
            m_cParticleSystem->setEmitterMaxStartColor( SColor(prevMaxCol.getAlpha(), prevMaxCol.getRed(), pos, prevMaxCol.getBlue()) );
            m_cGUIHandler->updateEmitterColorImage(m_cParticleSystem->getEmitterMaxStartColor(), false);
          } break;
          case IRR_TOOLBOX_EMITTER_MAX_COLOR_B_COMPONENT:
          {
            m_cParticleSystem->setEmitterMaxStartColor( SColor(prevMaxCol.getAlpha(), prevMaxCol.getRed(), prevMaxCol.getGreen(), pos) );
            m_cGUIHandler->updateEmitterColorImage(m_cParticleSystem->getEmitterMaxStartColor(), false);
          } break;

          //! -------------------------------------
          //! Affector target color.
          //! -------------------------------------
          case IRR_TOOLBOX_AFFECTOR_FADEOUT_TARGET_COLOR_R:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            m_cParticleSystem->setAffectorTargetColor( SColor( prevTargetCol.getAlpha(), pos, prevTargetCol.getGreen(), prevTargetCol.getBlue() ) );
            m_cGUIHandler->updateTargetColorImage(m_cParticleSystem->getAffectorTargetColor());
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_AFFECTOR_FADEOUT_TARGET_COLOR_G:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            m_cParticleSystem->setAffectorTargetColor( SColor( prevTargetCol.getAlpha(), prevTargetCol.getRed(), pos, prevTargetCol.getBlue() ) );
            m_cGUIHandler->updateTargetColorImage(m_cParticleSystem->getAffectorTargetColor());
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;
          case IRR_TOOLBOX_AFFECTOR_FADEOUT_TARGET_COLOR_B:
          {
            if(m_cParticleSystem->getCurrentID() <= -1) return false;
            m_cParticleSystem->setAffectorTargetColor( SColor( prevTargetCol.getAlpha(), prevTargetCol.getRed(), prevTargetCol.getGreen(), pos ) );
            m_cGUIHandler->updateTargetColorImage(m_cParticleSystem->getAffectorTargetColor());
            m_cParticleSystem->createAffectors();
            m_cParticleSystem->updateParticleSystem();
          } break;

          //! -------------------------------------
          //! GUI Alpha.
          //! -------------------------------------
          case IRR_SETTINGS_GUI_ALPHA:
          {
            m_cGUIHandler->setAlpha( pos );
          } break;

          //! Cursor offset.
          case IRR_SETTINGS_CURSOR_OFFSET_X:
          {
            if(m_cursorValue.prevXValue < pos)
              m_cGUIHandler->setCursorPosition( vector3df( cursorPos.X + 1, cursorPos.Y, cursorPos.Z ) );
            if(m_cursorValue.prevXValue > pos)
              m_cGUIHandler->setCursorPosition( vector3df( cursorPos.X - 1, cursorPos.Y, cursorPos.Z ) );
            swprintf(t1, MAXSTRING, L"%.2f", m_cGUIHandler->getCursorPos().X);
            IGUIElement *e = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_POS_X);
            e->setText(t1);
            m_cursorValue.prevXValue = pos;
            intersection = m_cGUIHandler->getCursorPos();
          } break;
          case IRR_SETTINGS_CURSOR_OFFSET_Y:
          {
            if(m_cursorValue.prevYValue < pos)
              m_cGUIHandler->setCursorPosition( vector3df( cursorPos.X, cursorPos.Y + 1, cursorPos.Z ) );
            if(m_cursorValue.prevYValue > pos)
              m_cGUIHandler->setCursorPosition( vector3df( cursorPos.X, cursorPos.Y - 1, cursorPos.Z ) );
            swprintf(t1, MAXSTRING, L"%.2f", m_cGUIHandler->getCursorPos().Y);
            IGUIElement *e = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_POS_Y);
            e->setText(t1);
            m_cursorValue.prevYValue = pos;
            intersection = m_cGUIHandler->getCursorPos();
          } break;
          case IRR_SETTINGS_CURSOR_OFFSET_Z:
          {
            if(m_cursorValue.prevZValue < pos)
              m_cGUIHandler->setCursorPosition( vector3df( cursorPos.X, cursorPos.Y, cursorPos.Z + 1 ) );
            if(m_cursorValue.prevZValue > pos)
              m_cGUIHandler->setCursorPosition( vector3df( cursorPos.X, cursorPos.Y, cursorPos.Z - 1 ) );
            swprintf(t1, MAXSTRING, L"%.2f", m_cGUIHandler->getCursorPos().Z);
            IGUIElement *e = m_cGUIHandler->getGUIElement(IRR_SETTINGS_CURSOR_POS_Z);
            e->setText(t1);
            m_cursorValue.prevZValue = pos;
            intersection = m_cGUIHandler->getCursorPos();
          } break;
        }
      } break;

      case EGET_COMBO_BOX_CHANGED:
      {
        if(m_cParticleSystem->getCurrentID() <= -1) return false;

        switch(id)
        {
          case IRR_TOOLBOX_COMBO_BOX_PRESETS:
          {
            s32 selectedCombo = ((gui::IGUIComboBox*)evt.GUIEvent.Caller)->getSelected();
            if( selectedCombo > -1 )
            {
              m_cParticleSystem->setPreset(selectedCombo);
              m_cGUIHandler->updateGUIElementsFromPreset(*m_cParticleSystem, selectedCombo);
            }
          } break;  //! IRR_TOOLBOX_COMBO_BOX_PRESETS

          case IRR_TOOLBOX_COMBO_BOX_MATERIAL_TYPE:
          {
            s32 selectedCombo = ((gui::IGUIComboBox*)evt.GUIEvent.Caller)->getSelected();
            m_cParticleSystem->setMaterialType(E_MATERIAL_TYPE(selectedCombo));
            m_cParticleSystem->updateParticleSystem();
          } break;  //! IRR_TOOLBOX_COMBO_BOX_MATERIAL_TYPE
        }
      } break;

      case EGET_LISTBOX_CHANGED:
      {
        switch(id)
        {
          case IRR_TOOLBOX_LIST_BOX_EMITTER_LIST:
          {
            s32 selectedList = ((gui::IGUIListBox*)evt.GUIEvent.Caller)->getSelected();
            if(selectedList > -1)
            {
              m_cParticleSystem->setCurrentID(selectedList);

              if(m_cGUIHandler->windowExists(IRR_WINDOW_TOOLBOX, false))
                m_cGUIHandler->updateGUIElementsFromCurrent(*m_cParticleSystem);

              /*
              vector3df pos = m_cParticleSystem->getParticlePosition();
              vector3df cpos = camera->getPosition();
              vector3df npos = (cpos + pos)/2;

              camera->setTarget(pos);
              if(pos != vector3df(0,0,0))
                camera->setPosition(npos);
                */
              // TODO (kjeiwa-3#5#): Center camera on selection.
            }
          } break;
        }
      } break;

      case EGET_LISTBOX_SELECTED_AGAIN:
      {
        switch(id)
        {
          case IRR_TOOLBOX_LIST_BOX_EMITTER_LIST:
          {
            s32 selectedList = ((gui::IGUIListBox*)evt.GUIEvent.Caller)->getSelected();
            if(selectedList > -1)
            {
              m_cGUIHandler->getUserInputString(L"Rename Emitter", L"Enter new name of emitter:", USER_INPUT_STRING_TYPE_EMITTER_NAME);
              emitterSelect.id = selectedList;
            }
          } break;
        } break;
      }

      case EGET_ELEMENT_FOCUS_LOST:
      case EGET_ELEMENT_FOCUSED:
      case EGET_ELEMENT_HOVERED:
      case EGET_ELEMENT_LEFT:
      case EGET_CHECKBOX_CHANGED:
      case EGET_FILE_CHOOSE_DIALOG_CANCELLED:
      case EGET_MESSAGEBOX_YES:
      case EGET_MESSAGEBOX_NO:
      case EGET_MESSAGEBOX_OK:
      case EGET_MESSAGEBOX_CANCEL:
      case EGET_TAB_CHANGED:
				return false;

    } //! switch(evt.GUIEvent.EventType)
    return true;
  }
  return false;
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//  END OF FILE.
// ------------------------------------------------------------------------
