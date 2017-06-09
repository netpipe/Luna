#include "LoadingScreen.h"

/*! \brief  LoadingScreen constructor.
 *
 */
LoadingScreen::LoadingScreen(IVideoDriver &driver, IGUIEnvironment &GUIEnv, char *progressBarImage)
: m_irrVideoDriver (&driver), m_irrGUIEnv (&GUIEnv)
{
  if(!m_irrGUIEnv && !m_irrVideoDriver)
    throw "Need to pass video driver and gui environment pointers to LoadingScreen constructor.";

  m_irrVideoDriver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY, true);
  m_irrVideoDriver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, false);
  m_irrVideoDriver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT, true);

  m_irrTexture_progressBar = m_irrVideoDriver->getTexture(progressBarImage);
  m_irrTexture_splash      = m_irrVideoDriver->getTexture("./textures/splash/03.tga");

  m_irrVideoDriver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY, false);
  m_irrVideoDriver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, true);
  m_irrVideoDriver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT, false);

  m_irrGUIFont_loadingFont = m_irrGUIEnv->getBuiltInFont();
}

/*! \brief  LoadingScreen destructor.
 *
 */
LoadingScreen::~LoadingScreen()
{
  m_irrVideoDriver = NULL;
  m_irrGUIEnv = NULL;
  m_irrGUIFont_loadingFont = NULL;
  m_irrTexture_progressBar = NULL;
}

/*! \brief  Updates the progress bar.
 */
void LoadingScreen::updateProgressBar(s32 percent, wchar_t *string)
{
  m_irrVideoDriver->beginScene(true, false, SColor(0,0,0,0));

  if(m_irrTexture_splash)
  {
    /*
    m_irrVideoDriver->draw2DImage(
      m_irrTexture_splash,
      position2d<s32>(0,0),
      rect<s32>(0,0,800,600),
      0,
      SColor(SCOLOR_WHITE),
      false);
      */
    m_irrVideoDriver->draw2DImage(
      m_irrTexture_splash,
      rect<s32>(0,0,800,600),
      rect<s32>(0,0,512,512));
  }

  rect<s32> clip(0,516,(800*percent)/100,516+16);

  if(m_irrTexture_progressBar)
  {
    m_irrVideoDriver->draw2DImage(
      m_irrTexture_progressBar,
      rect<s32>(0,516,800,516+16),
      rect<s32>(0,0,256,16),
      &clip);
  }

  m_irrGUIFont_loadingFont->draw(
    string,
    rect<s32>(50,516,50+200,516+150),
    SColor(255,255,255,255));

  m_irrVideoDriver->endScene();
}
