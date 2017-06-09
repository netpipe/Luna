#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "globals.hxx"

/*! \brief  LoadingScreen class.
 *
 */
class LoadingScreen
{
  public:

    LoadingScreen(
      IVideoDriver &driver,
      IGUIEnvironment &GUIEnv,
      char *progressBarImage = "./textures/gui/ProgressBar.tga"
    );

    virtual ~LoadingScreen();

    void updateProgressBar(s32 percent, wchar_t *string);

  protected:
  private:

    ITexture  *m_irrTexture_progressBar;
    ITexture  *m_irrTexture_splash;
    IGUIFont  *m_irrGUIFont_loadingFont;

    IVideoDriver    *m_irrVideoDriver;
    IGUIEnvironment *m_irrGUIEnv;
};

#endif // LOADINGSCREEN_H
