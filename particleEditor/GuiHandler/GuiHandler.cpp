#include "GuiHandler.h"


// ------------------------------------------------------------------------
// De- / Constructor
// ------------------------------------------------------------------------
GUI_Handler::GUI_Handler():
  displayDevVersion(false),
  m_cursorMarker(NULL),
  m_cursorPosition(vector3df(0,0,0))
{
  m_irrDevice   = NULL;
  m_irrGUIEnv   = NULL;
  m_irrGUISkin  = NULL;
  m_irrGUIFont  = NULL;

  m_irrGUIImage_irrLogo     = NULL;
  m_irrGUIImage_particleLogo = NULL;

  m_irrGUIListBox_logBox = NULL;

  m_irrVideoDriver = NULL;

  printf("[*] GUI Handler initialized.\n");
}
// ------------------------------------------------------------------------
GUI_Handler::~GUI_Handler()
{
  if(m_irrDevice != NULL)
    m_irrDevice = NULL;

  if(m_irrGUIEnv != NULL)
    m_irrGUIEnv = NULL;

  if(m_irrGUISkin != NULL)
    m_irrGUISkin  = NULL;

  if(m_irrGUIFont != NULL)
    m_irrGUIFont  = NULL;

  if(m_irrVideoDriver != NULL)
    m_irrVideoDriver = NULL;

  if(m_irrGUIListBox_logBox != NULL)
    m_irrGUIListBox_logBox = NULL;

  if(m_irrGUIImage_irrLogo != NULL)
    m_irrGUIImage_irrLogo     = NULL;

  if(m_irrGUIImage_particleLogo != NULL)
    m_irrGUIImage_particleLogo = NULL;

  printf("[*] GUI Handler deinitialized.\n");
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
void GUI_Handler::initEnvironment()
{
  if(m_irrDevice != NULL)
    m_irrGUIEnv = m_irrDevice->getGUIEnvironment();
  else
    throw "Tried to initialize GUI handler when device pointer is NULL.";
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
void GUI_Handler::createToolBox()
{
	//! Remove toolbox if it's already there.
	windowExists(IRR_WINDOW_TOOLBOX, true);

  //! Create toolbox.
  m_irrGUIWindow_toolBox = m_irrGUIEnv->addWindow(rect<s32>(625,35,800,550), false, L"Toolbox", 0, IRR_WINDOW_TOOLBOX);
  //! Add tabs to toolbox.
  //IGUITabControl *tab = m_irrGUIEnv->addTabControl(rect<s32>(2,20,640-452,550-7), m_irrGUIWindow_toolBox, true, true);
  IGUITabControl *tab = m_irrGUIEnv->addTabControl(rect<s32>(0,20,175,550-7), m_irrGUIWindow_toolBox, true, true);
  IGUITab *t1 = tab->addTab(L"Emitter");
  IGUITab *t2 = tab->addTab(L"Particles");
  IGUITab *t3 = tab->addTab(L"Presets");

  //! Add controls to Tab 1.
  s32 offset = 16;

  m_irrGUIEnv->addStaticText(L"Emitter Min Start Color", rect<s32>(10,10,165,25), displayDevVersion, false, t1, -1, false);

  m_irrGUIScrollBar_minRColorComponent =
    m_irrGUIEnv->addScrollBar(true, rect<s32>(10,10+offset,165,25+offset), t1, IRR_TOOLBOX_EMITTER_MIN_COLOR_R_COMPONENT);
  m_irrGUIScrollBar_minGColorComponent =
    m_irrGUIEnv->addScrollBar(true, rect<s32>(10,26+offset,165,41+offset), t1, IRR_TOOLBOX_EMITTER_MIN_COLOR_G_COMPONENT);
  m_irrGUIScrollBar_minBColorComponent =
    m_irrGUIEnv->addScrollBar(true, rect<s32>(10,42+offset,165,57+offset), t1, IRR_TOOLBOX_EMITTER_MIN_COLOR_B_COMPONENT);

  m_irrGUIScrollBar_minRColorComponent->setMax(255);
  m_irrGUIScrollBar_minRColorComponent->setPos(255);
  m_irrGUIScrollBar_minGColorComponent->setMax(255);
  m_irrGUIScrollBar_minGColorComponent->setPos(255);
  m_irrGUIScrollBar_minBColorComponent->setMax(255);
  m_irrGUIScrollBar_minBColorComponent->setPos(255);

  offset += 20;

  m_irrGUIEnv->addStaticText(L"Emitter Max Start Color", rect<s32>(10,80+offset-1,165,95+offset-1), displayDevVersion, false, t1, -1, false);

  m_irrGUIScrollBar_maxRColorComponent =
    m_irrGUIEnv->addScrollBar(true, rect<s32>(10, 95+offset,165,110+offset), t1, IRR_TOOLBOX_EMITTER_MAX_COLOR_R_COMPONENT);
  m_irrGUIScrollBar_maxGColorComponent =
    m_irrGUIEnv->addScrollBar(true, rect<s32>(10,111+offset,165,126+offset), t1, IRR_TOOLBOX_EMITTER_MAX_COLOR_G_COMPONENT);
  m_irrGUIScrollBar_maxBColorComponent =
    m_irrGUIEnv->addScrollBar(true, rect<s32>(10,127+offset,165,142+offset), t1, IRR_TOOLBOX_EMITTER_MAX_COLOR_B_COMPONENT);

  m_irrGUIScrollBar_maxRColorComponent->setMax(255);
  m_irrGUIScrollBar_maxRColorComponent->setPos(255);
  m_irrGUIScrollBar_maxGColorComponent->setMax(255);
  m_irrGUIScrollBar_maxGColorComponent->setPos(255);
  m_irrGUIScrollBar_maxBColorComponent->setMax(255);
  m_irrGUIScrollBar_maxBColorComponent->setPos(255);

  //! Create emitter min color image.
  offset -= 20;

  m_emitterMinStartColor_dat =
    updateEmitterColorImage(155,32,
      SColor(0,
        m_irrGUIScrollBar_minRColorComponent->getPos(),
        m_irrGUIScrollBar_minGColorComponent->getPos(),
        m_irrGUIScrollBar_minBColorComponent->getPos()));

  img =
    m_irrVideoDriver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(155,32),
      m_emitterMinStartColor_dat, false);

  m_emitterMinStartColor_tex =
    m_irrVideoDriver->addTexture("EmitterMinStartColor", img);

  m_emitterMinStartColor_img =
    m_irrGUIEnv->addImage(m_emitterMinStartColor_tex, position2d<s32>(10,60+offset), false, t1);

  //! Create emitter max color image.
  offset += 20;

  img = NULL;

  m_emitterMaxStartColor_dat =
    updateEmitterColorImage(155,32,
      SColor(0,
        m_irrGUIScrollBar_maxRColorComponent->getPos(),
        m_irrGUIScrollBar_maxGColorComponent->getPos(),
        m_irrGUIScrollBar_maxBColorComponent->getPos()));

  img =
    m_irrVideoDriver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(155,32),
      m_emitterMaxStartColor_dat, false);

  m_emitterMaxStartColor_tex =
    m_irrVideoDriver->addTexture("EmitterMaxStartColor", img);

  m_emitterMaxStartColor_img =
    m_irrGUIEnv->addImage(m_emitterMaxStartColor_tex, position2d<s32>(10,145+offset), false, t1);

  //! -------------------------------
  //! More controls to tab 1.
  //! -------------------------------
  m_irrGUIEnv->addStaticText(L"Emitter Box Size", rect<s32>(10,145+offset+40,165,160+offset+40), displayDevVersion, false, t1, -1, false);

  s32 x_offset = 165/3;
    m_editBox_EMITTER_BOX_WIDTH =
      m_irrGUIEnv->addEditBox(L"2", rect<s32>(10            ,160+offset+41  ,x_offset*1 ,175+offset+41), true, t1, IRR_TOOLBOX_EMITTER_BOX_WIDTH);
    m_editBox_EMITTER_BOX_HEIGHT =
      m_irrGUIEnv->addEditBox(L"2", rect<s32>(10+x_offset   ,160+offset+41  ,x_offset*2 ,175+offset+41), true, t1, IRR_TOOLBOX_EMITTER_BOX_HEIGHT);
    m_editBox_EMITTER_BOX_LENGTH =
      m_irrGUIEnv->addEditBox(L"2", rect<s32>(10+x_offset*2 ,160+offset+41  ,x_offset*3 ,175+offset+41), true, t1, IRR_TOOLBOX_EMITTER_BOX_LENGTH);

  offset+=10;
  m_irrGUIEnv->addStaticText(L"Direction", rect<s32>(10,175+offset+40,165,185+offset+40), displayDevVersion, false, t1, -1, false);

    m_editBox_EMITTER_DIRECTION_X =
      m_irrGUIEnv->addEditBox(L"0.0"  , rect<s32>(10            ,185+offset+41  ,x_offset*1 ,200+offset+41), true, t1, IRR_TOOLBOX_EMITTER_DIRECTION_X);
    m_editBox_EMITTER_DIRECTION_Y =
      m_irrGUIEnv->addEditBox(L"0.006", rect<s32>(10+x_offset   ,185+offset+41  ,x_offset*2 ,200+offset+41), true, t1, IRR_TOOLBOX_EMITTER_DIRECTION_Y);
    m_editBox_EMITTER_DIRECTION_Z =
      m_irrGUIEnv->addEditBox(L"0.0"  , rect<s32>(10+x_offset*2 ,185+offset+41  ,x_offset*3 ,200+offset+41), true, t1, IRR_TOOLBOX_EMITTER_DIRECTION_Z);

  offset+=10;
  m_irrGUIEnv->addStaticText(L"Particles Per Second Min/Max", rect<s32>(10,200+offset+40,165,210+offset+40), displayDevVersion, false, t1, -1, false);

  x_offset = 165/2;
    m_editBox_EMITTER_PARTICLES_MIN =
      m_irrGUIEnv->addEditBox(L"80"   , rect<s32>(10            ,210+offset+41  ,x_offset*1 ,225+offset+41), true, t1, IRR_TOOLBOX_EMITTER_PARTICLES_MIN);
    m_editBox_EMITTER_PARTICLES_MAX =
      m_irrGUIEnv->addEditBox(L"100"  , rect<s32>(10+x_offset   ,210+offset+41  ,x_offset*2 ,225+offset+41), true, t1, IRR_TOOLBOX_EMITTER_PARTICLES_MAX);

  offset+=10;
  m_irrGUIEnv->addStaticText(L"Particle Life Time Min/Max", rect<s32>(10,225+offset+40,165,235+offset+40), displayDevVersion, false, t1, -1, false);

    m_editBox_EMITTER_PARTICLES_LIFE_MIN =
      m_irrGUIEnv->addEditBox(L"800"   , rect<s32>(10            ,235+offset+41  ,x_offset*1 ,250+offset+41), true, t1, IRR_TOOLBOX_EMITTER_PARTICLES_LIFE_MIN);
    m_editBox_EMITTER_PARTICLES_LIFE_MAX =
      m_irrGUIEnv->addEditBox(L"2000"  , rect<s32>(10+x_offset   ,235+offset+41  ,x_offset*2 ,250+offset+41), true, t1, IRR_TOOLBOX_EMITTER_PARTICLES_LIFE_MAX);

  offset+=10;
  m_irrGUIEnv->addStaticText(L"Max Angle Degrees", rect<s32>(10,250+offset+40,165,260+offset+40), displayDevVersion, false, t1, -1, false);

    m_editBox_EMITTER_PARTICLES_ANGLE =
      m_irrGUIEnv->addEditBox(L"0.0"   , rect<s32>(10            ,265+offset+41  ,x_offset*1 ,280+offset+41), true, t1, IRR_TOOLBOX_EMITTER_PARTICLES_ANGLE);

  offset+=10;
  m_irrGUIEnv->addButton(rect<s32>(30,280+offset+40,150,300+offset+40), t1, IRR_TOOLBOX_EMITTER_CONFIRM_UPDATE_EMITTER, L"Update Emitter");
  offset+=30;
  m_irrGUIEnv->addButton(rect<s32>(30,280+offset+40,150,300+offset+40), t1, IRR_TOOLBOX_EMITTER_CONFIRM_NEW_EMITTER, L"Create Emitter");


  //! -------------------------------
  //! Add controls to Tab 2.
  //! -------------------------------
  m_irrGUIEnv->addButton(rect<s32>(10,10,165,25), t2, IRR_TOOLBOX_PARTICLE_TEXTURE_BTN, L"Set Texture...");

  m_particle_tex = m_irrVideoDriver->getTexture("./textures/particles/ParticleFire.tga");
 // m_particle_tex = m_irrVideoDriver->getTexture("./textures/particles/ParticleFire.tga");
  m_particle_img = m_irrGUIEnv->addImage(m_particle_tex, position2d<s32>(10, 30), false, t2);

  offset = 140;
  x_offset = 165/3;
  m_irrGUIEnv->addStaticText(L"Particle Scale", rect<s32>(10,30+offset,165,40+offset), displayDevVersion, false, t2, -1, false);

    m_editBox_PARTICLE_SCALE_X =
      m_irrGUIEnv->addEditBox(L"1.0"  , rect<s32>(10            ,40+offset  ,x_offset*1 ,55+offset), true, t2, IRR_TOOLBOX_PARTICLE_SCALE_X);
    m_editBox_PARTICLE_SCALE_Y =
      m_irrGUIEnv->addEditBox(L"1.0"  , rect<s32>(10+x_offset   ,40+offset  ,x_offset*2 ,55+offset), true, t2, IRR_TOOLBOX_PARTICLE_SCALE_Y);
    m_editBox_PARTICLE_SCALE_Z =
      m_irrGUIEnv->addEditBox(L"1.0"  , rect<s32>(10+x_offset*2 ,40+offset  ,x_offset*3 ,55+offset), true, t2, IRR_TOOLBOX_PARTICLE_SCALE_Z);

  offset += 10;
  x_offset = 165/2;
  m_irrGUIEnv->addStaticText(L"Particle Size", rect<s32>(10,55+offset,165,65+offset), displayDevVersion, false, t2, -1, false);

    m_editBox_PARTICLE_SIZE_X =
      m_irrGUIEnv->addEditBox(L"2.0"  , rect<s32>(10            ,65+offset  ,x_offset*1 ,80+offset), true, t2, IRR_TOOLBOX_PARTICLE_SIZE_X);
    m_editBox_PARTICLE_SIZE_Y =
      m_irrGUIEnv->addEditBox(L"2.0"  , rect<s32>(10+x_offset   ,65+offset  ,x_offset*2 ,80+offset), true, t2, IRR_TOOLBOX_PARTICLE_SIZE_Y);

  offset += 10;
  x_offset = 165/3;
  m_irrGUIEnv->addStaticText(L"Particle Position", rect<s32>(10,80+offset,165,90+offset), displayDevVersion, false, t2, -1, false);

    m_editBox_PARTICLE_POSITION_X =
      m_irrGUIEnv->addEditBox(L"0.0"  , rect<s32>(10            ,90+offset  ,x_offset*1 ,105+offset), true, t2, IRR_TOOLBOX_PARTICLE_POSITION_X);
    m_editBox_PARTICLE_POSITION_Y =
      m_irrGUIEnv->addEditBox(L"0.0"  , rect<s32>(10+x_offset   ,90+offset  ,x_offset*2 ,105+offset), true, t2, IRR_TOOLBOX_PARTICLE_POSITION_Y);
    m_editBox_PARTICLE_POSITION_Z =
      m_irrGUIEnv->addEditBox(L"0.0"  , rect<s32>(10+x_offset*2 ,90+offset  ,x_offset*3 ,105+offset), true, t2, IRR_TOOLBOX_PARTICLE_POSITION_Z);

  offset+=10;
  m_irrGUIEnv->addStaticText(L"Material Type", rect<s32>(10,105+offset,165,115+offset), displayDevVersion, false, t2, -1, false);

    m_irrGUIComboBox_materialType = m_irrGUIEnv->addComboBox(rect<s32>(10,115+offset,165,130+offset), t2, IRR_TOOLBOX_COMBO_BOX_MATERIAL_TYPE);

  wchar_t *S_MATERIAL_TYPE[17] =
  {
      L"SOLID",
      L"SOLID_2_LAYER",
      L"LIGHTMAP",
      L"LIGHTMAP_ADD",
      L"LIGHTMAP_M2",
      L"LIGHTMAP_M4",
      L"LIGHTMAP_LIGHTING",
      L"LIGHTMAP_LIGHTING_M2",
      L"LIGHTMAP_LIGHTING_M4",
      L"DETAIL_MAP",
      L"SPHERE_MAP",
      L"REFLECTION_2_LAYER",
      L"TRANSPARENT_ADD_COLOR",
      L"TRANSPARENT_ALPHA_CHANNEL",
      L"TRANSPARENT_ALPHA_CHANNEL_REF",
      L"TRANSPARENT_VERTEX_ALPHA",
      L"TRANSPARENT_REFLECTION_2_LAYER"
      /*
      L"NORMAL_MAP_SOLID",
      L"NORMAL_MAP_TRANSPARENT_ADD_COLOR",
      L"NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA",
      L"PARALLAX_MAP_SOLID",
      L"PARALLAX_MAP_TRANSPARENT_ADD_COLOR",
      L"PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA"
      */
  };

  s32 id = -1;
  for(int i = 0; i < 17; i++)
  {
    id = m_irrGUIComboBox_materialType->addItem(S_MATERIAL_TYPE[i]);
    //printf("[%i] %S\n", id, S_MATERIAL_TYPE[i]);
  }

  m_irrGUIComboBox_materialType->setSelected(15);

  //! ---------------------------------
  //! Fade out affector settings.
  //! ---------------------------------
  offset+=40;
  m_irrGUIEnv->addStaticText(L"Fade Out Affector", rect<s32>(10,105+offset,165,115+offset), displayDevVersion, false, t2, -1, false);

    m_irrGUIEnv->addStaticText(L"Target Color", rect<s32>(10,115+offset,165,125+offset), displayDevVersion, false, t2, -2, false);

    m_irrGUIScrollBar_affectorFadeOutTargetColorR =
      m_irrGUIEnv->addScrollBar(true, rect<s32>(10,125+offset,165,135+offset), t2, IRR_TOOLBOX_AFFECTOR_FADEOUT_TARGET_COLOR_R);
    m_irrGUIScrollBar_affectorFadeOutTargetColorG =
      m_irrGUIEnv->addScrollBar(true, rect<s32>(10,136+offset,165,146+offset), t2, IRR_TOOLBOX_AFFECTOR_FADEOUT_TARGET_COLOR_G);
    m_irrGUIScrollBar_affectorFadeOutTargetColorB =
      m_irrGUIEnv->addScrollBar(true, rect<s32>(10,147+offset,165,157+offset), t2, IRR_TOOLBOX_AFFECTOR_FADEOUT_TARGET_COLOR_B);

    m_irrGUIScrollBar_affectorFadeOutTargetColorR->setMax(255);
    m_irrGUIScrollBar_affectorFadeOutTargetColorR->setPos(0);
    m_irrGUIScrollBar_affectorFadeOutTargetColorG->setMax(255);
    m_irrGUIScrollBar_affectorFadeOutTargetColorG->setPos(0);
    m_irrGUIScrollBar_affectorFadeOutTargetColorB->setMax(255);
    m_irrGUIScrollBar_affectorFadeOutTargetColorB->setPos(0);

  //! Create fade to color image.
  img = NULL;

  m_affectorFadeOutTargetColor_dat =
    updateEmitterColorImage(155,10,
      SColor(0,
        m_irrGUIScrollBar_affectorFadeOutTargetColorR->getPos(),
        m_irrGUIScrollBar_affectorFadeOutTargetColorG->getPos(),
        m_irrGUIScrollBar_affectorFadeOutTargetColorB->getPos()));

  img =
    m_irrVideoDriver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(155,10),
      m_affectorFadeOutTargetColor_dat, false);

  m_affectorFadeOutTargetColor_tex =
    m_irrVideoDriver->addTexture("FadeOutAffectorTargetColor", img);

  m_affectorFadeOutTargetColor_img =
    m_irrGUIEnv->addImage(m_affectorFadeOutTargetColor_tex, position2d<s32>(10,158+offset), false, t2);

  //! Fade time settings.
  x_offset = 165/2;
  offset += 10;

    m_irrGUIEnv->addStaticText(L"Fade Time", rect<s32>(10,160+offset,x_offset*1,170+offset), displayDevVersion, false, t2, -2, false);

    m_editBox_AFFECTOR_FADEOUT_TIME =
      m_irrGUIEnv->addEditBox(L"1000"  , rect<s32>(10+x_offset,160+offset,x_offset*2,170+offset), true, t2, IRR_TOOLBOX_AFFECTOR_FADEOUT_TIME);

  //! ---------------------------------
  //! Gravity affector settings.
  //! ---------------------------------
  offset+=10;
  x_offset = 165/3;
  m_irrGUIEnv->addStaticText(L"Gravity Affector", rect<s32>(10,180+offset,165,190+offset), displayDevVersion, false, t2, -1, false);

    m_irrGUIEnv->addStaticText(L"Gravity", rect<s32>(10,190+offset,165,200+offset), displayDevVersion, false, t2, -2, false);

    m_editBox_AFFECTOR_GRAVITY_X =
      m_irrGUIEnv->addEditBox(L"0.0"  , rect<s32>(10            ,200+offset  ,x_offset*1 ,215+offset), true, t2, IRR_TOOLBOX_AFFECTOR_GRAVITY_X);
    m_editBox_AFFECTOR_GRAVITY_Y =
      m_irrGUIEnv->addEditBox(L"-0.03"  , rect<s32>(10+x_offset   ,200+offset  ,x_offset*2 ,215+offset), true, t2, IRR_TOOLBOX_AFFECTOR_GRAVITY_Y);
    m_editBox_AFFECTOR_GRAVITY_Z =
      m_irrGUIEnv->addEditBox(L"0.0"  , rect<s32>(10+x_offset*2 ,200+offset  ,x_offset*3 ,215+offset), true, t2, IRR_TOOLBOX_AFFECTOR_GRAVITY_Z);

  x_offset = 165/2;
  offset += 5;

    m_irrGUIEnv->addStaticText(L"Time Force", rect<s32>(10,215+offset,x_offset*1,225+offset), displayDevVersion, false, t2, -2, false);

    m_editBox_AFFECTOR_TIME_FORCE_LOST =
      m_irrGUIEnv->addEditBox(L"1000"  , rect<s32>(10+x_offset,215+offset,x_offset*2,225+offset), true, t2, IRR_TOOLBOX_AFFECTOR_TIME_FORCE_LOST);

  //! -------------------------------
  //! Add controls to Tab 3.
  //! -------------------------------
  m_irrGUIComboBox_presets = m_irrGUIEnv->addComboBox(rect<s32>(10,10,165,30), t3, IRR_TOOLBOX_COMBO_BOX_PRESETS);

  //m_irrGUIComboBox_presets->addItem(L"Fire");
  //m_irrGUIComboBox_presets->addItem(L"Snow");

  m_irrGUIEnv->addButton(rect<s32>(10,35,165,50), t3, IRR_TOOLBOX_BUTTON_LOAD_PRESETS,  L"Load Presets...");
  m_irrGUIEnv->addButton(rect<s32>(10,55,165,70), t3, IRR_TOOLBOX_BUTTON_SAVE_PRESETS,  L"Save Presets");

  //! For adding a new preset.
  m_irrGUIEnv->addStaticText(L"Preset Name", rect<s32>(10,85,165,95), displayDevVersion, false, t3, -1, false);
  m_irrGUIEditBox_presetName = m_irrGUIEnv->addEditBox(L"Default",rect<s32>(10,95,165,110), true, t3, IRR_TOOLBOX_EDITBOX_PRESET_NAME);
  m_irrGUIEnv->addButton(rect<s32>(10,115,165,130), t3, IRR_TOOLBOX_BUTTON_ADD_PRESET, L"Add to presets");
}
// ------------------------------------------------------------------------
void GUI_Handler::createEmitterList()
{
	//! Remove window if it's already there.
  windowExists(IRR_WINDOW_EMITTER_LIST, true);

  //! Create emitter list window.
  m_irrGUIWindow_toolBox = m_irrGUIEnv->addWindow(rect<s32>(10,250,200,460), false, L"Selection Lists", 0, IRR_WINDOW_EMITTER_LIST);

  m_irrGUIListBox_emitterList = m_irrGUIEnv->addListBox(rect<s32>(0,20,190,135), m_irrGUIWindow_toolBox, IRR_TOOLBOX_LIST_BOX_EMITTER_LIST, false);
  m_irrGUIEnv->addButton(rect<s32>(0,135,190,165), m_irrGUIWindow_toolBox, IRR_EMITTER_LIST_DELETE_EMITTER_BTN, L"Delete Emitter");

  populateEmitterList();
}
// ------------------------------------------------------------------------
void GUI_Handler::addEmitterListItem(stringw text)
{
  m_aEmitterNames.push_back(text);

  populateEmitterList();
}
// ------------------------------------------------------------------------
void GUI_Handler::populateEmitterList(void)
{
  if(windowExists(IRR_WINDOW_EMITTER_LIST, false))
  {
    m_irrGUIListBox_emitterList->clear();

    u32 i = 0;
    for(i = 0; i < m_aEmitterNames.size(); i++)
    {
      m_irrGUIListBox_emitterList->addItem(m_aEmitterNames[i].c_str());
    }

    m_irrGUIListBox_emitterList->setSelected(i-1);
  }
}
// ------------------------------------------------------------------------
void GUI_Handler::createSettingsWindow(void)
{
  // FIXME (kjeiwa-3#1#): The values of the settings windows' editboxes are not updated between instances.

	//! Remove window if it's already there.
  windowExists(IRR_WINDOW_SETTINGS, true);

  s32 offsetY = 0;
  s32 offsetX = 40;
  s32 spacing = 4;  //! X-spacing between editboxes.
  s32 width = 60;   //! Width of editboxes.


  //! Create emitter list window.
  m_irrGUIWindow_settings = m_irrGUIEnv->addWindow(rect<s32>(100,150,400,360), false, L"Settings", 0, IRR_WINDOW_SETTINGS);

  //! Add tabs to window.
  IGUITabControl *tab = m_irrGUIEnv->addTabControl(rect<s32>(0,20,300,210), m_irrGUIWindow_settings, true, true);
  IGUITab *t4 = tab->addTab(L"GUI");
  IGUITab *t3 = tab->addTab(L"Cursor");
  IGUITab *t2 = tab->addTab(L"Camera");
  IGUITab *t1 = tab->addTab(L"Scenery");

  //! Add controls to Tab 1.
  m_irrGUIEnv->addStaticText(L"Position:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t1, -1, false);

    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t1, IRR_TOOLBOX_ENV_POSITION_X);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*2+spacing,10+offsetY,offsetX+width*3,25+offsetY), true, t1, IRR_TOOLBOX_ENV_POSITION_Y);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*3+spacing,10+offsetY,offsetX+width*4,25+offsetY), true, t1, IRR_TOOLBOX_ENV_POSITION_Z);

  offsetY += 20;
  m_irrGUIEnv->addStaticText(L"Scale:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t1, -1, false);

    m_irrGUIEnv->addEditBox(L"1.0", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t1, IRR_TOOLBOX_ENV_SCALE_X);
    m_irrGUIEnv->addEditBox(L"1.0", rect<s32>(offsetX+width*2+spacing,10+offsetY,offsetX+width*3,25+offsetY), true, t1, IRR_TOOLBOX_ENV_SCALE_Y);
    m_irrGUIEnv->addEditBox(L"1.0", rect<s32>(offsetX+width*3+spacing,10+offsetY,offsetX+width*4,25+offsetY), true, t1, IRR_TOOLBOX_ENV_SCALE_Z);

  offsetY += 20;
  m_irrGUIEnv->addStaticText(L"Rotation:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t1, -1, false);

    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t1, IRR_TOOLBOX_ENV_ROTATION_X);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*2+spacing,10+offsetY,offsetX+width*3,25+offsetY), true, t1, IRR_TOOLBOX_ENV_ROTATION_Y);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*3+spacing,10+offsetY,offsetX+width*4,25+offsetY), true, t1, IRR_TOOLBOX_ENV_ROTATION_Z);

  //! Add controls to Tab 2.
  offsetY = 0;
  offsetX = 40;
  m_irrGUIEnv->addStaticText(L"Rotate Speed:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t2, -1, false);

    m_irrGUIEnv->addEditBox(L"-80", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t2, IRR_SETTINGS_CAM_MAYA_SPEED_ROTATION);

  offsetY += 20;
  m_irrGUIEnv->addStaticText(L"Zoom Speed:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t2, -1, false);

    m_irrGUIEnv->addEditBox(L"80", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t2, IRR_SETTINGS_CAM_MAYA_SPEED_ZOOM);

  offsetY += 20;
  m_irrGUIEnv->addStaticText(L"Translate Speed:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t2, -1, false);

    m_irrGUIEnv->addEditBox(L"80", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t2, IRR_SETTINGS_CAM_MAYA_SPEED_TRANSLATE);

  //! Add controls to Tab 3.
  offsetY = 0;
  m_irrGUIEnv->addStaticText(L"Position:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t3, -1, false);

    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_POS_X);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*2+spacing,10+offsetY,offsetX+width*3,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_POS_Y);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*3+spacing,10+offsetY,offsetX+width*4,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_POS_Z);

  offsetY += 20;
  m_irrGUIEnv->addStaticText(L"Scale:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t3, -1, false);

    m_irrGUIEnv->addEditBox(L"0.4", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_SCL_X);
    m_irrGUIEnv->addEditBox(L"0.4", rect<s32>(offsetX+width*2+spacing,10+offsetY,offsetX+width*3,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_SCL_Y);
    m_irrGUIEnv->addEditBox(L"0.4", rect<s32>(offsetX+width*3+spacing,10+offsetY,offsetX+width*4,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_SCL_Z);

  offsetY += 20;
  m_irrGUIEnv->addStaticText(L"Rotation:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t3, -1, false);

    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*1+spacing,10+offsetY,offsetX+width*2,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_ROT_X);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*2+spacing,10+offsetY,offsetX+width*3,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_ROT_Y);
    m_irrGUIEnv->addEditBox(L"0.0", rect<s32>(offsetX+width*3+spacing,10+offsetY,offsetX+width*4,25+offsetY), true, t3, IRR_SETTINGS_CURSOR_ROT_Z);

  offsetY +=20;
  m_irrGUIEnv->addStaticText(L"Offset X:", rect<s32>(10,10+offsetY,80,25+offsetY), displayDevVersion, false, t3, IRR_SETTINGS_CURSOR_OFFSET_X, false);
  m_irrGUIEnv->addStaticText(L"Offset Y:", rect<s32>(10,26+offsetY,80,41+offsetY), displayDevVersion, false, t3, IRR_SETTINGS_CURSOR_OFFSET_Y, false);
  m_irrGUIEnv->addStaticText(L"Offset Z:", rect<s32>(10,42+offsetY,80,57+offsetY), displayDevVersion, false, t3, IRR_SETTINGS_CURSOR_OFFSET_Z, false);

    IGUIScrollBar *e1 = m_irrGUIEnv->addScrollBar(true, rect<s32>(105,10+offsetY,280,25+offsetY), t3, IRR_SETTINGS_CURSOR_OFFSET_X);
    IGUIScrollBar *e2 = m_irrGUIEnv->addScrollBar(true, rect<s32>(105,26+offsetY,280,41+offsetY), t3, IRR_SETTINGS_CURSOR_OFFSET_Y);
    IGUIScrollBar *e3 = m_irrGUIEnv->addScrollBar(true, rect<s32>(105,42+offsetY,280,57+offsetY), t3, IRR_SETTINGS_CURSOR_OFFSET_Z);

    e1->setMax(500);  e1->setPos(0);
    e2->setMax(500);  e2->setPos(0);
    e3->setMax(500);  e3->setPos(0);

  //! Add controls to Tab 4.
  offsetY = 0;
  m_irrGUIEnv->addStaticText(L"Alpha:", rect<s32>(10,10+offsetY,290,25+offsetY), displayDevVersion, false, t4, -1, false);

    IGUIScrollBar *f1 = m_irrGUIEnv->addScrollBar(true, rect<s32>(10, 30+offsetY,290,45+offsetY), t4, IRR_SETTINGS_GUI_ALPHA);
    f1->setMax(255);
    f1->setPos(192);
}
// ------------------------------------------------------------------------
void GUI_Handler::createHelpWindow(void)
{
	//! Remove window if it's already there.
  windowExists(IRR_WINDOW_HELP, true);

  s32 message_size = 120;

  wchar_t *HELP_MESSAGE[124] =
  {
      L"Particle Editor v0.2",
      L"",
      L"",
      L"-----------------------------------------------------------------------------------------------------------------------",
      L"USAGE:",
      L"-----------------------------------------------------------------------------------------------------------------------",
      L"    Keys:",
      L"          PageUp:\tSwitch Camera Mode.",
      L"          F1:\tShow toolbox",
      L"          F2:\tShow settings dialog",
      L"          F3:\tShow emitter list",
      L"          F5:\tGenerate new emitter at cursor location.",
      L"          TAB:\tShow all dialogs",
      L"          ESC:\tQuit editor.",
      L"",
      L"    MiddleMouse: Place mouse cursor in the 3d environment.",
      L"",
      L"-----------------------------------------------------------------------------------------------------------------------",
      L"NOTES:",
      L"-----------------------------------------------------------------------------------------------------------------------",
      L"    Placing the cursor will not work if there's no scenery loaded, use the",
      L"    settings dialog instead.",
      L"",
      L"",
      L"",
      L"",
      L"",
      L"",
      L"",
      L"",
      L"-----------------------------------------------------------------------------------------------------------------------",
      L"Created by:",
      L"-----------------------------------------------------------------------------------------------------------------------",
      L"    Kjell Iwarson",
      L"    deesine@grafikfel.org",
      L"",
      L""
  };

  //! Create help message window.
  IGUIWindow *m_irrGUIWindow_help = m_irrGUIEnv->addWindow(rect<s32>(10,250,400,460), false, L"Help", 0, IRR_WINDOW_HELP);

	IGUIListBox *list = m_irrGUIEnv->addListBox(rect<s32>(0,20,385,210), m_irrGUIWindow_help, IRR_WINDOW_HELP_LIST, false);

  wchar_t t1[MAXSTRING];
  swprintf(t1, MAXSTRING, L"%c", 44);

  for(s32 i = 0; i < message_size; i++)
  {
    //list->addItem(HELP_MESSAGE[i], t1);
    list->addItem(HELP_MESSAGE[i], 0);
  }
}
// ------------------------------------------------------------------------
void GUI_Handler::createGUI()
{
  if(m_irrGUIEnv != NULL)
  {
    m_irrGUISkin = m_irrGUIEnv->getSkin();
    m_irrGUIFont = m_irrGUIEnv->getFont("./textures/gui/fonts/guiFont.bmp");
    m_irrGUIFontFixed = m_irrGUIEnv->getFont("./textures/gui/fonts/guiFontFixed.bmp");
    //m_irrGUISkin = m_irrGUIEnv->createSkin(EGST_WINDOWS_CLASSIC);
    //m_irrGUISkin->setFont(m_irrGUIFont);

    if(m_irrGUIFont)
      m_irrGUISkin->setFont(m_irrGUIFont);
    else
      printf("Failed to load GUI font.\n");

    //! Setup skin.
    m_irrGUISkin->setColor(EGDC_BUTTON_TEXT, SColor(255,240,230,230));
    m_irrGUISkin->setColor(EGDC_3D_FACE, SCOLOR_DARKGRAY);
    m_irrGUISkin->setColor(EGDC_3D_HIGH_LIGHT, SCOLOR_MIDGRAY);
    m_irrGUISkin->setColor(EGDC_3D_LIGHT, SCOLOR_DARKGRAY);

    m_irrGUISkin->setColor(EGDC_WINDOW, SCOLOR_DARKGRAY);
    m_irrGUISkin->setColor(EGDC_3D_DARK_SHADOW, SCOLOR_DARKGRAY);
    m_irrGUISkin->setColor(EGDC_3D_SHADOW, SCOLOR_DARKGRAY);
    m_irrGUISkin->setColor(EGDC_APP_WORKSPACE, SCOLOR_DARKGRAY);
    m_irrGUISkin->setColor(EGDC_GRAY_TEXT, SCOLOR_LIGHTGRAY);

    setAlpha(192);

    //! Create logging listbox.
    //m_irrGUIListBox_logBox = m_irrGUIEnv->addListBox(rect<s32>(0,440,200,600));
    //m_irrGUIListBox_logBox->setIconFont(m_irrGUIFont);

    //! Create menu.
    m_irrGUIContextMenu = m_irrGUIEnv->addMenu(0,-1);
    m_irrGUIContextMenu->addItem(L"File", MENU_FILE, true, true);
    m_irrGUIContextMenu->addItem(L"View", MENU_VIEW, true, true);
    m_irrGUIContextMenu->addItem(L"Help", MENU_HELP, true, true);

    m_irrGUISubMenu = m_irrGUIContextMenu->getSubMenu(0);
    m_irrGUISubMenu->addItem(L"Load Environment...", MENU_LOAD_ENV);
    m_irrGUISubMenu->addSeparator();
    m_irrGUISubMenu->addItem(L"Save Particle System to C++", MENU_FILE_SAVE_CPP);
    m_irrGUISubMenu->addSeparator();
    m_irrGUISubMenu->addItem(L"Quit Editor", MENU_FILE_QUIT);

    m_irrGUISubMenu = m_irrGUIContextMenu->getSubMenu(1);
    m_irrGUISubMenu->addItem(L"Settings...", MENU_EDIT_SHOW_SETTINGS);
    m_irrGUISubMenu->addSeparator();
    m_irrGUISubMenu->addItem(L"Show Toolbox", MENU_EDIT_SHOW_TOOLBOX);
    m_irrGUISubMenu->addItem(L"Show Emitter List", MENU_EDIT_SHOW_EMITTER_LIST);

    m_irrGUISubMenu = m_irrGUIContextMenu->getSubMenu(2);
    m_irrGUISubMenu->addItem(L"Credits & Usage...", MENU_HELP_USAGE);


    /// NOTE (Kjell#9#): This is the only instance outside of WorldManager where we load a mesh,
    /// since this is part of the GUI as a "cursor" display.
    /// Might preferably be moved to load and receive from the WorldManager in the future
    //! Create cursor marker.
    IAnimatedMesh *m_irrAnimatedMesh = m_irrSceneManager->getMesh("./models/ActorMarker.x");
    IAnimatedMeshSceneNode *m_irrAnimatedMeshSceneNode = 0;

    if(m_irrAnimatedMesh)
    {
      //IMeshManipulator *m_irrMeshManipulator = m_irrSceneManager->getMeshManipulator();
      //m_irrMeshManipulator->flipSurfaces(m_irrAnimatedMesh->getMesh(0));
      //m_irrMeshManipulator->recalculateNormals(m_irrAnimatedMesh->getMesh(0), true);

      m_irrAnimatedMeshSceneNode = m_irrSceneManager->addAnimatedMeshSceneNode(m_irrAnimatedMesh);
    }
    if(m_irrAnimatedMeshSceneNode != 0)
    {
      //! Change material properties.
      video::SColor col = video::SColor(255,255,255,255);
      m_irrAnimatedMeshSceneNode->getMaterial(0).Shininess = 20.0f;
      m_irrAnimatedMeshSceneNode->getMaterial(0).DiffuseColor = col;
      m_irrAnimatedMeshSceneNode->getMaterial(0).SpecularColor = col;
      m_irrAnimatedMeshSceneNode->getMaterial(0).AmbientColor = col;
      m_irrAnimatedMeshSceneNode->getMaterial(0).EmissiveColor = col;

      m_irrAnimatedMeshSceneNode->setPosition(vector3df(0,0,0));
      m_irrAnimatedMeshSceneNode->setRotation(vector3df(0,0,0));

      m_irrAnimatedMeshSceneNode->setAnimationSpeed(0.0f);

      // Enable lighting and fog.
      m_irrAnimatedMeshSceneNode->setMaterialFlag(EMF_LIGHTING, true);
      m_irrAnimatedMeshSceneNode->setMaterialFlag(EMF_FOG_ENABLE, false);

      m_irrAnimatedMeshSceneNode->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
      //m_irrAnimatedMeshSceneNode->setMaterialType(EMT_TRANSPARENT_VERTEX_ALPHA);

      m_irrAnimatedMeshSceneNode->setScale(vector3df(0.4,0.4,0.4));
      m_irrAnimatedMeshSceneNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
      //m_irrAnimatedMeshSceneNode->setDebugDataVisible(EDS_BBOX);
      //m_irrAnimatedMeshSceneNode->setDebugDataVisible(EDS_NORMALS);
    }
    m_cursorMarker = m_irrAnimatedMeshSceneNode;

    //! Create windows.
    if(displayDevVersion)
    {
      createToolBox();
      createEmitterList();
      createSettingsWindow();
      createHelpWindow();
      //getUserInputString(L"Title", L"Input a string:");
    }

    //! Load GUI texures.
    if(m_irrVideoDriver != NULL)
    {
      m_irrGUIImage_irrLogo = m_irrGUIEnv->addImage(
        m_irrVideoDriver->getTexture("./textures/gui/irrlichtlogoalpha.tga"),
        position2d<int>(1024-90,20));

      m_irrGUIImage_particleLogo = m_irrGUIEnv->addImage(
        m_irrVideoDriver->getTexture("./textures/gui/particlelogoalpha.tga"),
        position2d<int>(1024-90,52));

      /*
      m_irrGUIImage_crossHair = m_irrGUIEnv->addImage(
        m_irrVideoDriver->getTexture("./utility/crosshair.tga"),
        position2d<int>(400-16, 300-16));
        */
    }
    else
    {
      throw "GUI Handler: Tried to load textures when video driver pointer is NULL.";
    }
  }
  else
  {
    throw "GUI Handler: Tried to create GUI when environment pointer is NULL.";
  }
}
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
void GUI_Handler::updateEmitterColorImage(SColor col, bool min)
{
  if(min)
  {
    //! Update min texture.
    m_emitterMinStartColor_dat =
      updateEmitterColorImage(155,32,col);

    img =
      m_irrVideoDriver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(155,32),
        m_emitterMinStartColor_dat, false);

    m_emitterMinStartColor_tex =
      m_irrVideoDriver->addTexture("EmitterMinStartColor", img);

    m_emitterMinStartColor_img->setImage(m_emitterMinStartColor_tex);
  } else {
    //! Update max texture.
    m_emitterMaxStartColor_dat =
      updateEmitterColorImage(155,32,col);

    img =
      m_irrVideoDriver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(155,32),
        m_emitterMaxStartColor_dat, false);

    m_emitterMaxStartColor_tex =
      m_irrVideoDriver->addTexture("EmitterMaxStartColor", img);

    m_emitterMaxStartColor_img->setImage(m_emitterMaxStartColor_tex);
  }
}
// ------------------------------------------------------------------------
char *GUI_Handler::updateEmitterColorImage(int ih, int iw, SColor col)
{
  long count = 0;
  char *data = new char[iw*ih*3];

  for(int x=0; x<iw; x++)
  for(int y=0; y<ih; y++)
  {
    data[count+0] = (char) col.getRed();
    data[count+1] = (char) col.getGreen();
    data[count+2] = (char) col.getBlue();

    count += 3;
  }

  return data;
}
// ------------------------------------------------------------------------
void GUI_Handler::updateTargetColorImage(SColor col)
{
  m_affectorFadeOutTargetColor_dat =
    updateEmitterColorImage(155,32,col);

  img =
    m_irrVideoDriver->createImageFromData(ECF_R8G8B8, dimension2d<u32>(155,32),
      m_affectorFadeOutTargetColor_dat, false);

  m_affectorFadeOutTargetColor_tex =
    m_irrVideoDriver->addTexture("FadeOutAffectorTargetColor", img);

  m_affectorFadeOutTargetColor_img->setImage(m_affectorFadeOutTargetColor_tex);

}
// ------------------------------------------------------------------------
void GUI_Handler::updateParticleTextureImage(stringc &image)
{
  m_particle_tex = m_irrVideoDriver->getTexture(image.c_str());
  m_particle_img->setImage(m_particle_tex);
  printf("yep");
}
// ------------------------------------------------------------------------
void GUI_Handler::updateGUIElementsFromPreset(ParticleSystem &pParticleSystem, int index)
{
  wchar_t t1[MAXSTRING];
  wchar_t t2[MAXSTRING];
  wchar_t t3[MAXSTRING];

  //!---------------------------
  //! Update emitter color min/max.
  //!---------------------------

  m_irrGUIScrollBar_minRColorComponent->setPos( pParticleSystem.m_aPresets[index].emitter.minStartColor.getRed() );
  m_irrGUIScrollBar_minGColorComponent->setPos( pParticleSystem.m_aPresets[index].emitter.minStartColor.getGreen() );
  m_irrGUIScrollBar_minBColorComponent->setPos( pParticleSystem.m_aPresets[index].emitter.minStartColor.getBlue() );

  m_irrGUIScrollBar_maxRColorComponent->setPos( pParticleSystem.m_aPresets[index].emitter.maxStartColor.getRed() );
  m_irrGUIScrollBar_maxGColorComponent->setPos( pParticleSystem.m_aPresets[index].emitter.maxStartColor.getGreen() );
  m_irrGUIScrollBar_maxBColorComponent->setPos( pParticleSystem.m_aPresets[index].emitter.maxStartColor.getBlue() );

  this->updateEmitterColorImage( pParticleSystem.getEmitterMinStartColor(), true );
  this->updateEmitterColorImage( pParticleSystem.getEmitterMaxStartColor(), false );

  //!---------------------------
  //! Update emitter box.
  //!---------------------------

  vector3df minEdge = pParticleSystem.m_aPresets[index].emitter.emitterBox.MinEdge;
  vector3df maxEdge = pParticleSystem.m_aPresets[index].emitter.emitterBox.MaxEdge;

  swprintf(t1, MAXSTRING, L"%1.2f", (-minEdge.X)+maxEdge.X);
  swprintf(t2, MAXSTRING, L"%1.2f", (-minEdge.X)+maxEdge.Y);
  swprintf(t3, MAXSTRING, L"%1.2f", (-minEdge.X)+maxEdge.Z);

  m_editBox_EMITTER_BOX_WIDTH->setText(t1);
  m_editBox_EMITTER_BOX_HEIGHT->setText(t2);
  m_editBox_EMITTER_BOX_LENGTH->setText(t3);

  //!---------------------------
  //! Update emitter direction.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.5f", pParticleSystem.m_aPresets[index].emitter.direction.X);
  swprintf(t2, MAXSTRING, L"%1.5f", pParticleSystem.m_aPresets[index].emitter.direction.Y);
  swprintf(t3, MAXSTRING, L"%1.5f", pParticleSystem.m_aPresets[index].emitter.direction.Z);

  m_editBox_EMITTER_DIRECTION_X->setText(t1);
  m_editBox_EMITTER_DIRECTION_Y->setText(t2);
  m_editBox_EMITTER_DIRECTION_Z->setText(t3);

  //!---------------------------
  //! Update emitter particles min/max.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.m_aPresets[index].emitter.minParticlesPerSecond);
  swprintf(t2, MAXSTRING, L"%i", pParticleSystem.m_aPresets[index].emitter.maxParticlesPerSecond);

  m_editBox_EMITTER_PARTICLES_MIN->setText(t1);
  m_editBox_EMITTER_PARTICLES_MAX->setText(t2);

  //!---------------------------
  //! Update emitter particles life min/max.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.m_aPresets[index].emitter.lifeTimeMin);
  swprintf(t2, MAXSTRING, L"%i", pParticleSystem.m_aPresets[index].emitter.lifeTimeMax);

  m_editBox_EMITTER_PARTICLES_LIFE_MIN->setText(t1);
  m_editBox_EMITTER_PARTICLES_LIFE_MAX->setText(t2);

  //!---------------------------
  //! Update emitter angle degree.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.3f", pParticleSystem.m_aPresets[index].emitter.maxAngleDegrees);

  m_editBox_EMITTER_PARTICLES_ANGLE->setText(t1);

  //!---------------------------
  //! Update particle scale.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.2f", pParticleSystem.m_aPresets[index].particle.scale.X);
  swprintf(t2, MAXSTRING, L"%1.2f", pParticleSystem.m_aPresets[index].particle.scale.Y);
  swprintf(t3, MAXSTRING, L"%1.2f", pParticleSystem.m_aPresets[index].particle.scale.Z);

  m_editBox_PARTICLE_SCALE_X->setText(t1);
  m_editBox_PARTICLE_SCALE_Y->setText(t2);
  m_editBox_PARTICLE_SCALE_Z->setText(t3);

  //!---------------------------
  //! Update particle size.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.1f", pParticleSystem.m_aPresets[index].particle.size.Width);
  swprintf(t2, MAXSTRING, L"%1.1f", pParticleSystem.m_aPresets[index].particle.size.Height);

  m_editBox_PARTICLE_SIZE_X->setText(t1);
  m_editBox_PARTICLE_SIZE_Y->setText(t2);

  //!---------------------------
  //! Update particle position.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.3f", pParticleSystem.m_aPresets[index].particle.position.X);
  swprintf(t2, MAXSTRING, L"%1.3f", pParticleSystem.m_aPresets[index].particle.position.Y);
  swprintf(t3, MAXSTRING, L"%1.3f", pParticleSystem.m_aPresets[index].particle.position.Z);

  m_editBox_PARTICLE_POSITION_X->setText(t1);
  m_editBox_PARTICLE_POSITION_Y->setText(t2);
  m_editBox_PARTICLE_POSITION_Z->setText(t3);

  //!---------------------------
  //! Update particle material type.
  //!---------------------------

  m_irrGUIComboBox_materialType->setSelected(pParticleSystem.m_aPresets[index].particle.materialType);

  //!---------------------------
  //! Update particle texture image.
  //!---------------------------

  stringc texture = pParticleSystem.m_aPresets[index].texture;
  updateParticleTextureImage(texture);

  //!---------------------------
  //! Update affector target color.
  //!---------------------------

  m_irrGUIScrollBar_affectorFadeOutTargetColorR->setPos( pParticleSystem.m_aPresets[index].affector.targetColor.getRed() );
  m_irrGUIScrollBar_affectorFadeOutTargetColorG->setPos( pParticleSystem.m_aPresets[index].affector.targetColor.getGreen() );
  m_irrGUIScrollBar_affectorFadeOutTargetColorB->setPos( pParticleSystem.m_aPresets[index].affector.targetColor.getBlue() );

  this->updateTargetColorImage( pParticleSystem.m_aPresets[index].affector.targetColor );

  //!---------------------------
  //! Update affector fade out time.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.m_aPresets[index].affector.timeNeededToFadeOut);

  m_editBox_AFFECTOR_FADEOUT_TIME->setText(t1);

  //!---------------------------
  //! Update affector gravity.
  //!---------------------------

  printf("Updating gravity: %f\n", pParticleSystem.m_aPresets[index].affector.gravity.Y);

  swprintf(t1, MAXSTRING, L"%1.3f", pParticleSystem.m_aPresets[index].affector.gravity.X);
  swprintf(t2, MAXSTRING, L"%1.3f", pParticleSystem.m_aPresets[index].affector.gravity.Y);
  swprintf(t3, MAXSTRING, L"%1.3f", pParticleSystem.m_aPresets[index].affector.gravity.Z);

  m_editBox_AFFECTOR_GRAVITY_X->setText(t1);
  m_editBox_AFFECTOR_GRAVITY_Y->setText(t2);
  m_editBox_AFFECTOR_GRAVITY_Z->setText(t3);

  //!---------------------------
  //! Update affector time force lost.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.m_aPresets[index].affector.timeForceLost);

  m_editBox_AFFECTOR_TIME_FORCE_LOST->setText(t1);
}
// ------------------------------------------------------------------------
/*! \brief updateGUIElementsFromCurrent
 *
 *  Updates the gui elements based on current particle system.
 */
void GUI_Handler::updateGUIElementsFromCurrent(ParticleSystem &pParticleSystem)
{
  printf("Updating\n");
  wchar_t t1[MAXSTRING];
  wchar_t t2[MAXSTRING];
  wchar_t t3[MAXSTRING];

  //!---------------------------
  //! Update emitter color min/max.
  //!---------------------------

  m_irrGUIScrollBar_minRColorComponent->setPos( pParticleSystem.getEmitterMinStartColor().getRed() );
  m_irrGUIScrollBar_minGColorComponent->setPos( pParticleSystem.getEmitterMinStartColor().getGreen() );
  m_irrGUIScrollBar_minBColorComponent->setPos( pParticleSystem.getEmitterMinStartColor().getBlue() );

  m_irrGUIScrollBar_maxRColorComponent->setPos( pParticleSystem.getEmitterMaxStartColor().getRed() );
  m_irrGUIScrollBar_maxGColorComponent->setPos( pParticleSystem.getEmitterMaxStartColor().getGreen() );
  m_irrGUIScrollBar_maxBColorComponent->setPos( pParticleSystem.getEmitterMaxStartColor().getBlue() );

  this->updateEmitterColorImage( pParticleSystem.getEmitterMinStartColor(), true );
  this->updateEmitterColorImage( pParticleSystem.getEmitterMaxStartColor(), false );

  //!---------------------------
  //! Update emitter box.
  //!---------------------------

  vector3df minEdge = pParticleSystem.getEmitterBox().MinEdge;
  vector3df maxEdge = pParticleSystem.getEmitterBox().MaxEdge;

  swprintf(t1, MAXSTRING, L"%1.2f", (-minEdge.X)+maxEdge.X);
  swprintf(t2, MAXSTRING, L"%1.2f", (-minEdge.X)+maxEdge.Y);
  swprintf(t3, MAXSTRING, L"%1.2f", (-minEdge.X)+maxEdge.Z);

  m_editBox_EMITTER_BOX_WIDTH->setText(t1);
  m_editBox_EMITTER_BOX_HEIGHT->setText(t2);
  m_editBox_EMITTER_BOX_LENGTH->setText(t3);

  //!---------------------------
  //! Update emitter direction.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.5f", pParticleSystem.getEmitterDirection().X);
  swprintf(t2, MAXSTRING, L"%1.5f", pParticleSystem.getEmitterDirection().Y);
  swprintf(t3, MAXSTRING, L"%1.5f", pParticleSystem.getEmitterDirection().Z);

  m_editBox_EMITTER_DIRECTION_X->setText(t1);
  m_editBox_EMITTER_DIRECTION_Y->setText(t2);
  m_editBox_EMITTER_DIRECTION_Z->setText(t3);

  //!---------------------------
  //! Update emitter particles min/max.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.getEmitterParticleMin());
  swprintf(t2, MAXSTRING, L"%i", pParticleSystem.getEmitterParticleMax());

  m_editBox_EMITTER_PARTICLES_MIN->setText(t1);
  m_editBox_EMITTER_PARTICLES_MAX->setText(t2);

  //!---------------------------
  //! Update emitter particles life min/max.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.getEmitterParticlesLifeMin());
  swprintf(t2, MAXSTRING, L"%i", pParticleSystem.getEmitterParticlesLifeMax());

  m_editBox_EMITTER_PARTICLES_LIFE_MIN->setText(t1);
  m_editBox_EMITTER_PARTICLES_LIFE_MAX->setText(t2);

  //!---------------------------
  //! Update emitter angle degree.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.3f", pParticleSystem.getEmitterMaxAngleDegrees());

  m_editBox_EMITTER_PARTICLES_ANGLE->setText(t1);

  //!---------------------------
  //! Update particle scale.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.2f", pParticleSystem.getParticleSystemScale().X);
  swprintf(t2, MAXSTRING, L"%1.2f", pParticleSystem.getParticleSystemScale().Y);
  swprintf(t3, MAXSTRING, L"%1.2f", pParticleSystem.getParticleSystemScale().Z);

  m_editBox_PARTICLE_SCALE_X->setText(t1);
  m_editBox_PARTICLE_SCALE_Y->setText(t2);
  m_editBox_PARTICLE_SCALE_Z->setText(t3);

  //!---------------------------
  //! Update particle size.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.1f", pParticleSystem.getParticleSizeX());
  swprintf(t2, MAXSTRING, L"%1.1f", pParticleSystem.getParticleSizeY());

  m_editBox_PARTICLE_SIZE_X->setText(t1);
  m_editBox_PARTICLE_SIZE_Y->setText(t2);

  //!---------------------------
  //! Update particle position.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.3f", pParticleSystem.getParticlePosition().X);
  swprintf(t2, MAXSTRING, L"%1.3f", pParticleSystem.getParticlePosition().Y);
  swprintf(t3, MAXSTRING, L"%1.3f", pParticleSystem.getParticlePosition().Z);

  m_editBox_PARTICLE_POSITION_X->setText(t1);
  m_editBox_PARTICLE_POSITION_Y->setText(t2);
  m_editBox_PARTICLE_POSITION_Z->setText(t3);

  //!---------------------------
  //! Update particle material type.
  //!---------------------------

  m_irrGUIComboBox_materialType->setSelected(pParticleSystem.getMaterialType());

  //!---------------------------
  //! Update particle texture image.
  //!---------------------------

  stringc texture = pParticleSystem.getParticleTexture();
  updateParticleTextureImage(texture);

  //!---------------------------
  //! Update affector target color.
  //!---------------------------

  m_irrGUIScrollBar_affectorFadeOutTargetColorR->setPos( pParticleSystem.getAffectorTargetColor().getRed() );
  m_irrGUIScrollBar_affectorFadeOutTargetColorG->setPos( pParticleSystem.getAffectorTargetColor().getGreen() );
  m_irrGUIScrollBar_affectorFadeOutTargetColorB->setPos( pParticleSystem.getAffectorTargetColor().getBlue() );

  this->updateTargetColorImage( pParticleSystem.getAffectorTargetColor() );

  //!---------------------------
  //! Update affector fade out time.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.getAffectorFadeOutTime());

  m_editBox_AFFECTOR_FADEOUT_TIME->setText(t1);

  //!---------------------------
  //! Update affector gravity.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%1.3f", pParticleSystem.getAffectorGravity().X);
  swprintf(t2, MAXSTRING, L"%1.3f", pParticleSystem.getAffectorGravity().Y);
  swprintf(t3, MAXSTRING, L"%1.3f", pParticleSystem.getAffectorGravity().Z);

  m_editBox_AFFECTOR_GRAVITY_X->setText(t1);
  m_editBox_AFFECTOR_GRAVITY_Y->setText(t2);
  m_editBox_AFFECTOR_GRAVITY_Z->setText(t3);

  //!---------------------------
  //! Update affector time force lost.
  //!---------------------------

  swprintf(t1, MAXSTRING, L"%i", pParticleSystem.getAffectorTimeForceLost());

  m_editBox_AFFECTOR_TIME_FORCE_LOST->setText(t1);
}
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
void GUI_Handler::draw()
{
  m_irrGUIEnv->drawAll();
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
void GUI_Handler::logText(wchar_t *text)
{
  s32 id = m_irrGUIListBox_logBox->addItem(text);
  m_irrGUIListBox_logBox->setSelected(id);

  core::list<gui::IGUIElement*>::ConstIterator it = m_irrGUIListBox_logBox->getChildren().getLast();
  gui::IGUIScrollBar* scrollbar = static_cast<gui::IGUIScrollBar*>((*it));
  scrollbar->setPos(0x7FFFFFFF);
}
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
void GUI_Handler::getUserInputString(wchar_t *title, wchar_t *message, int type)
{
  	//! Remove window if it's already there.
  windowExists(IRR_WINDOW_USER_INPUT, true);

  s32 offsetY = 20;
  s32 width = 220;


  //! Create emitter list window.
  m_irrGUIWindow_userInputString = m_irrGUIEnv->addWindow(rect<s32>(800/2-width/2,400/2-60,800/2+width/2,400/2+60), true, title, 0, IRR_WINDOW_USER_INPUT);

  m_irrGUIEnv->addStaticText(message, rect<s32>(10,10+offsetY,width-10,25+offsetY), displayDevVersion, false, m_irrGUIWindow_userInputString, -1, false);

  offsetY += 20;

  IGUIEditBox *e;

  switch(type)
  {
    case USER_INPUT_STRING_TYPE_EMITTER_NAME:
    {
      e = m_irrGUIEnv->addEditBox(L"", rect<s32>(10,10+offsetY,width-10,35+offsetY), true, m_irrGUIWindow_userInputString, IRR_INPUT_USER_STRING_EMITTER_NAME);
    } break;
    case USER_INPUT_STRING_TYPE_SAVE_CPP:
    {
      e = m_irrGUIEnv->addEditBox(L"", rect<s32>(10,10+offsetY,width-10,35+offsetY), true, m_irrGUIWindow_userInputString, IRR_INPUT_USER_STRING_SAVE_CPP_NAME);
    } break;
  }

  m_irrGUIEnv->setFocus(e);
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
IrrlichtDevice *GUI_Handler::getIrrlichtDevice()
{
  return m_irrDevice;
}
// ------------------------------------------------------------------------
void GUI_Handler::setIrrlichtDevice(IrrlichtDevice &device)
{
  m_irrDevice = &device;
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
IVideoDriver *GUI_Handler::getVideoDriver()
{
  return m_irrVideoDriver;
}
// ------------------------------------------------------------------------
void GUI_Handler::setVideoDriver(IVideoDriver &videoDriver)
{
  m_irrVideoDriver = &videoDriver;
}
// ------------------------------------------------------------------------

ISceneManager *GUI_Handler::getSceneManager()
{
  return m_irrSceneManager;
}
// ------------------------------------------------------------------------
void GUI_Handler::setSceneManager(ISceneManager &sceneManager)
{
  m_irrSceneManager = &sceneManager;
}

IGUIEnvironment *GUI_Handler::getGUIEnvironment(void)
{
  return m_irrGUIEnv;
}


// ------------------------------------------------------------------------
//  Functions to hide and show mouse cursor.
// ------------------------------------------------------------------------
void GUI_Handler::showMouseCursor(void)
{
  if(m_irrDevice != NULL)
    m_irrDevice->getCursorControl()->setVisible(true);
}
// ------------------------------------------------------------------------
void GUI_Handler::hideMouseCursor(void)
{
  if(m_irrDevice != NULL)
    m_irrDevice->getCursorControl()->setVisible(false);
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//   END OF FILE.
// ------------------------------------------------------------------------
