#ifndef WORLDFILE_H
#define WORLDFILE_H

#include "globals.hxx"
#include "ParticleSystem/ParticleSystem.h"
#include <stdio.h>

/*! \brief  WorldFile class.
 *          Loads and saves world files.
 */
class WorldFile
{
  public:

    WorldFile();

    virtual ~WorldFile();

    void saveParticleSystemToCPP(stringc pFileName,stringc emitterName, ParticleSystem &pParticleSystem, bool append);
    void saveParticleSystemPresetsXMLFile(const stringc pFileName, ParticleSystem &pParticleSystem);
    void loadParticleSystemPresetsXMLFile(const stringc pFileName, ParticleSystem &pParticleSystem);

    __inline void setIrrlichtDevice(IrrlichtDevice &device) { m_irrDevice = &device; }

    void setWorkDir(stringc dir){
      workDir = dir;
      printf("[WF] Workdir: %s\n", workDir.c_str());
    }

  protected:
  private:

    stringc workDir;

    IXMLWriter  *m_irrXMLSaveFile;
    IXMLReader  *m_irrXMLReadFile;
    FILE        *m_irrCPPSaveFile;  //! Would like to change this to something more up-to-date.
    bool        m_bSave;

    int commentCnt,
        commentCntPrev;
    int elementCnt;

    IrrlichtDevice *m_irrDevice;
};

#endif // WORLDFILE_H
