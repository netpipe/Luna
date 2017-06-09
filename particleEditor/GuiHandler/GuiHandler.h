#ifndef GUI_HANDLER_H
#define GUI_HANDLER_H

#include "globals.hxx"
#include "ParticleSystem/ParticleSystem.h"

class GUI_Handler
{
	public:
		GUI_Handler();
		virtual ~GUI_Handler();

    void initEnvironment();
    void createGUI();
    void createToolBox();
    void draw();

    void createSettingsWindow();
    void createHelpWindow();

    void createEmitterList();
    void addEmitterListItem(stringw text);
    void populateEmitterList(void);
    void selectEmitterListItem(u32 id){
      m_irrGUIListBox_emitterList->setSelected(id);
    }
    void clearEmitterList(){
      m_irrGUIListBox_emitterList->clear();
      m_aEmitterNames.clear();
    }

    void getUserInputString(wchar_t *title, wchar_t *message, int type);

    void logText(wchar_t *text);

    void showMouseCursor(void);
    void hideMouseCursor(void);

    //! Cursor marker helpers.
    inline void setCursorPos(vector3df pos){
      printf("Cursor pos: %f %f %f\n", pos.X, pos.Y, pos.Z);
      m_cursorMarker->setPosition(pos);
    }
    inline void setCursorRot(vector3df rot){
      printf("Cursor rot: %f %f %f\n", rot.X, rot.Y, rot.Z);
      m_cursorMarker->setRotation(rot);
    }
    inline void setCursorScl(vector3df scl){
      printf("Cursor scl: %f %f %f\n", scl.X, scl.Y, scl.Z);
      m_cursorMarker->setScale(scl);
    }
    inline vector3df getCursorPos(void){
      return m_cursorMarker->getPosition();
    }
    inline vector3df getCursorRot(void){
      return m_cursorMarker->getRotation();
    }
    inline vector3df getCursorScl(void){
      return m_cursorMarker->getScale();
    }

    IrrlichtDevice *getIrrlichtDevice();
		void            setIrrlichtDevice(IrrlichtDevice &device);

		IVideoDriver   *getVideoDriver();
		void            setVideoDriver(IVideoDriver &driver);

		ISceneManager  *getSceneManager();
		void            setSceneManager(ISceneManager &sceneManager);

    IGUIEnvironment *getGUIEnvironment(void);

    __inline IGUIFont *getGUIFont(void) { return m_irrGUIFont; }

    __inline wchar_t *getPresetName(void) { return (wchar_t*)m_irrGUIEditBox_presetName->getText(); }

    __inline void addPresetName(wchar_t *name) { m_irrGUIComboBox_presets->addItem(name); }
    __inline void clearPresetNames(void) { m_irrGUIComboBox_presets->clear(); }

    __inline void setCursorPosition(vector3df pos){
      m_cursorPosition = pos;
      if(m_cursorMarker != NULL)
        m_cursorMarker->setPosition(m_cursorPosition);
    }

    void updateGUIElementsFromPreset(ParticleSystem &pParticleSystem, int index);
    void updateGUIElementsFromCurrent(ParticleSystem &pParticleSystem);
    void updateEmitterColorImage(SColor col, bool min);
    void updateTargetColorImage(SColor col);
    void updateParticleTextureImage(stringc &image);

    inline void setAlpha(s32 value){
      for (s32 i=0; i<gui::EGDC_COUNT ; ++i)
      {
        video::SColor col = m_irrGUIEnv->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(value);
        m_irrGUIEnv->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
      }
    }

    bool windowExists(s32 id, bool remove){
      IGUIEnvironment* env = m_irrDevice->getGUIEnvironment();
      IGUIElement* root = env->getRootGUIElement();
      IGUIElement* e = root->getElementFromId(id, true);
      if (!e) return false;
      else {
        if(remove)
        {
          e->remove();
          return false;
        }
        else
          return true;
      }
    }
    IGUIElement *getGUIElement(s32 id){
      IGUIEnvironment* env = m_irrDevice->getGUIEnvironment();
      IGUIElement* root = env->getRootGUIElement();
      IGUIElement* e = root->getElementFromId(id, true);
      return e ? (e) : (NULL);
    }

    void setWorkDir(stringc dir){
      workDir = dir;
      printf("[GH] Workdir: %s\n", workDir.c_str());
    }

	protected:

    char *updateEmitterColorImage(int ih, int iw, SColor col);

	private:

    stringc workDir;

    //! Set this to true to show borders of static text labels & display all windows at startup.
    bool displayDevVersion;

    //! Array for storing emitter names, used in the emitter listbox.
    array<stringw> m_aEmitterNames;

    IAnimatedMeshSceneNode  *m_cursorMarker;
    vector3df m_cursorPosition;

    IGUIEnvironment *m_irrGUIEnv;
    ISceneManager   *m_irrSceneManager;
    IrrlichtDevice  *m_irrDevice;
    IVideoDriver    *m_irrVideoDriver;

    IGUISkin      *m_irrGUISkin;
    IGUIFont      *m_irrGUIFont;
    IGUIFont      *m_irrGUIFontFixed;

    IGUIListBox   *m_irrGUIListBox_logBox;
    IGUIListBox   *m_irrGUIListBox_emitterList;

    IGUIComboBox  *m_irrGUIComboBox_presets;
    IGUIComboBox  *m_irrGUIComboBox_materialType;

    //! For displaying the min and max start color of the particle emitter.
    ITexture  *m_emitterMinStartColor_tex;
    ITexture  *m_emitterMaxStartColor_tex;
    IGUIImage *m_emitterMinStartColor_img;
    IGUIImage *m_emitterMaxStartColor_img;
    char      *m_emitterMinStartColor_dat;
    char      *m_emitterMaxStartColor_dat;

    //! For displaying fade out particle affector target color.
    ITexture  *m_affectorFadeOutTargetColor_tex;
    IGUIImage *m_affectorFadeOutTargetColor_img;
    char      *m_affectorFadeOutTargetColor_dat;

    //! For displaying the particle texture in the gui.
    ITexture  *m_particle_tex;
    IGUIImage *m_particle_img;

    IImage *img;

    IGUIImage     *m_irrGUIImage_irrLogo;
    IGUIImage     *m_irrGUIImage_particleLogo;
    IGUIImage     *m_irrGUIImage_crossHair;

    IGUIScrollBar *m_irrGUIScrollBar_minRColorComponent;
    IGUIScrollBar *m_irrGUIScrollBar_minGColorComponent;
    IGUIScrollBar *m_irrGUIScrollBar_minBColorComponent;

    IGUIScrollBar *m_irrGUIScrollBar_maxRColorComponent;
    IGUIScrollBar *m_irrGUIScrollBar_maxGColorComponent;
    IGUIScrollBar *m_irrGUIScrollBar_maxBColorComponent;

    IGUIScrollBar *m_irrGUIScrollBar_affectorFadeOutTargetColorR;
    IGUIScrollBar *m_irrGUIScrollBar_affectorFadeOutTargetColorG;
    IGUIScrollBar *m_irrGUIScrollBar_affectorFadeOutTargetColorB;

    IGUIWindow  *m_irrGUIWindow_toolBox;
    IGUIWindow  *m_irrGUIWindow_emitterList;
    IGUIWindow  *m_irrGUIWindow_settings;
    IGUIWindow  *m_irrGUIWindow_userInputString;

    IGUIContextMenu *m_irrGUIContextMenu;
    IGUIContextMenu *m_irrGUISubMenu;

    IGUIEditBox  *m_irrGUIEditBox_presetName;

    //! For receiving input from the user.
    IGUIWindow  *m_editBoxWindow;
    IGUIEditBox *m_editBox;

    //! Store editboxes for entering values from presets.
    IGUIEditBox *m_editBox_EMITTER_BOX_WIDTH;
    IGUIEditBox *m_editBox_EMITTER_BOX_HEIGHT;
    IGUIEditBox *m_editBox_EMITTER_BOX_LENGTH;
    IGUIEditBox *m_editBox_EMITTER_DIRECTION_X;
    IGUIEditBox *m_editBox_EMITTER_DIRECTION_Y;
    IGUIEditBox *m_editBox_EMITTER_DIRECTION_Z;
    IGUIEditBox *m_editBox_EMITTER_PARTICLES_MIN;
    IGUIEditBox *m_editBox_EMITTER_PARTICLES_MAX;
    IGUIEditBox *m_editBox_EMITTER_PARTICLES_LIFE_MIN;
    IGUIEditBox *m_editBox_EMITTER_PARTICLES_LIFE_MAX;
    IGUIEditBox *m_editBox_EMITTER_PARTICLES_ANGLE;

    IGUIEditBox *m_editBox_PARTICLE_SCALE_X;
    IGUIEditBox *m_editBox_PARTICLE_SCALE_Y;
    IGUIEditBox *m_editBox_PARTICLE_SCALE_Z;
    IGUIEditBox *m_editBox_PARTICLE_SIZE_X;
    IGUIEditBox *m_editBox_PARTICLE_SIZE_Y;
    IGUIEditBox *m_editBox_PARTICLE_POSITION_X;
    IGUIEditBox *m_editBox_PARTICLE_POSITION_Y;
    IGUIEditBox *m_editBox_PARTICLE_POSITION_Z;

    IGUIEditBox *m_editBox_AFFECTOR_FADEOUT_TIME;
    IGUIEditBox *m_editBox_AFFECTOR_GRAVITY_X;
    IGUIEditBox *m_editBox_AFFECTOR_GRAVITY_Y;
    IGUIEditBox *m_editBox_AFFECTOR_GRAVITY_Z;
    IGUIEditBox *m_editBox_AFFECTOR_TIME_FORCE_LOST;

    //! Cursor settings editboxes.
    //IGUIEditBox *m_editBox_SETTINGS_CURSOR_POS_X;
    //IGUIEditBox *m_editBox_SETTINGS_CURSOR_POS_Y;
    //IGUIEditBox *m_editBox_SETTINGS_CURSOR_POS_Z;
};

#endif // GUI_HANDLER_H
