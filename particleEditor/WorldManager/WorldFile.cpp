#include "WorldFile.h"
#include <sstream>

/*! \brief  WorldFile constructor.
 */
WorldFile::WorldFile()
{
  m_irrDevice = NULL;
}

/*! \brief  WorldFile destructor.
 */
WorldFile::~WorldFile()
{
  m_irrDevice = NULL;
}

void WorldFile::loadParticleSystemPresetsXMLFile(const stringc pFileName, ParticleSystem &pParticleSystem)
{
  printf("Loading presets\n");

  if(m_irrDevice == NULL)
    throw "WorldFile: m_irrDevice == NULL";

  stringc file = workDir;
  file += pFileName;
  printf("Loading from: %s\n", file.c_str());
  m_irrXMLReadFile = m_irrDevice->getFileSystem()->createXMLReader(file.c_str());

  s32 id = -1;
  commentCnt = -1;
  commentCntPrev = -1;
  elementCnt = -1;

  pParticleSystem.clearPresets();

  PRESET tempPreset;

  stringw nodeName;
  wchar_t *presetName = NULL;

  while(m_irrXMLReadFile->read())
  {
    switch(id = m_irrXMLReadFile->getNodeType())
    {
      case EXN_ELEMENT:
      {
        nodeName  = m_irrXMLReadFile->getNodeName();

        elementCnt++;

        if(elementCnt == 0)
        {
          printf("\nelementCnt == 0\n");
          presetName = (wchar_t*)nodeName.c_str();
          pParticleSystem.setPresetName(presetName);
        }

        float a = m_irrXMLReadFile->getAttributeValueAsFloat(0);
        float b = m_irrXMLReadFile->getAttributeValueAsFloat(1);
        float c = m_irrXMLReadFile->getAttributeValueAsFloat(2);
        float d = m_irrXMLReadFile->getAttributeValueAsFloat(3);

        //!------------------------
        //! Read emitter box dimensions.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"emitterBox")) == 0)
        {
          aabbox3d<f32> box(-a/2, 0, -c/2, a/2, b, c/2);

          tempPreset.emitter.emitterBox = box;
        }

        //!------------------------
        //! Read emitter direction.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"direction")) == 0)
        {
          vector3df direction(a,b,c);

          tempPreset.emitter.direction = direction;
        }

        //!------------------------
        //! Read emitter rate.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"rate")) == 0)
        {
          tempPreset.emitter.minParticlesPerSecond = (u32)a;
          tempPreset.emitter.maxParticlesPerSecond = (u32)b;
        }

        //!------------------------
        //! Read emitter min start color.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"minStartColor")) == 0)
        {
          SColor col((u32)a,(u32)b,(u32)c,(u32)d);

          tempPreset.emitter.minStartColor = col;
        }

        //!------------------------
        //! Read emitter max start color.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"maxStartColor")) == 0)
        {
          SColor col((u32)a,(u32)b,(u32)c,(u32)d);

          tempPreset.emitter.maxStartColor = col;
        }

        //!------------------------
        //! Read emitter life.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"life")) == 0)
        {
          tempPreset.emitter.lifeTimeMin = (u32)a;
          tempPreset.emitter.lifeTimeMax = (u32)b;
        }

        //!------------------------
        //! Read emitter max angle.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"maxAngle")) == 0)
        {
          tempPreset.emitter.maxAngleDegrees = (s32)a;
        }

        //!---------------------------------------------------------
        //! Done reading emitter, begin particles.
        //!---------------------------------------------------------

        //!------------------------
        //! Read particle position.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"position")) == 0)
        {
          vector3df position(a,b,c);

          tempPreset.particle.position = position;
        }

        //!------------------------
        //! Read particle scale.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"scale")) == 0)
        {
          vector3df scale(a,b,c);

          tempPreset.particle.scale = scale;
        }

        //!------------------------
        //! Read particle size.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"size")) == 0)
        {
          dimension2d<f32> size(a,b);

          tempPreset.particle.size = size;
        }

        //!------------------------
        //! Read particle material type.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"material")) == 0)
        {
          int a = m_irrXMLReadFile->getAttributeValueAsInt(0);
          tempPreset.particle.materialType = E_MATERIAL_TYPE(a);
        }

        //!------------------------
        //! Read particle texture name.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"texture")) == 0)
        {
          stringc a = m_irrXMLReadFile->getAttributeValue(0);
          tempPreset.texture = a;
        }

        //!---------------------------------------------------------
        //! Done reading particles, begin affector.
        //!---------------------------------------------------------

        //!------------------------
        //! Read affector target color.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"targetColor")) == 0)
        {
          SColor color((u32)a,(u32)b,(u32)c,(u32)d);

          tempPreset.affector.targetColor = color;
        }

        //!------------------------
        //! Read affector fade time.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"fadeOutTime")) == 0)
        {
          u32 time = m_irrXMLReadFile->getAttributeValueAsInt(0);

          tempPreset.affector.timeNeededToFadeOut = time;
        }

        //!------------------------
        //! Read affector gravity.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"gravity")) == 0)
        {
          vector3df gravity = vector3df(a,b,c);

          tempPreset.affector.gravity = gravity;
        }

        //!------------------------
        //! Read affector time force lost.
        //!------------------------
        if( (wcscmp(nodeName.c_str(), L"timeForceLost")) == 0)
        {
          u32 time = m_irrXMLReadFile->getAttributeValueAsInt(0);

          tempPreset.affector.timeForceLost = time;
        }

      } break;

      case EXN_COMMENT:
      {
        //! Every preset is followed by a comment, so we consider us done with this preset and continue with the next.
        // NOTE (kjeiwa-3#9#): We need to skip the last comment in the file, hence checking if index is the same size.
        if( (commentCnt > -1) && (commentCnt == pParticleSystem.presetNamesIndex) )
        {
          printf("\n(commentCnt > -1) %i index: %i\n", commentCnt, pParticleSystem.presetNamesIndex);
          tempPreset.affector.timeForceLost = 1000;
          tempPreset.affector.timeNeededToFadeOut = 1000;
          pParticleSystem.addPreset(tempPreset);
        }
        commentCnt++;
        elementCnt = -1;
      } break;

      default:
      {
        //printf("%d\n", id);
      } break;
    }
  }

  m_irrXMLReadFile->drop();
}

void WorldFile::saveParticleSystemPresetsXMLFile(const stringc pFileName, ParticleSystem &pParticleSystem)
{
  if(m_irrDevice == NULL)
    throw "WorldFile: m_irrDevice == NULL";

  stringc file = workDir;
  file += pFileName;
  printf("Saving to: %s\n", file.c_str());
  m_irrXMLSaveFile = m_irrDevice->getFileSystem()->createXMLWriter(file.c_str());

  m_irrXMLSaveFile->writeXMLHeader();
  m_irrXMLSaveFile->writeLineBreak();
  m_irrXMLSaveFile->writeComment(L"Irrlicht Particle Editor Presets file");
  m_irrXMLSaveFile->writeLineBreak();
  m_irrXMLSaveFile->writeLineBreak();

  wchar_t t1[MAXSTRING];
  wchar_t t2[MAXSTRING];
  wchar_t t3[MAXSTRING];
  wchar_t t4[MAXSTRING];

  for(u32 i = 0; i < pParticleSystem.m_aPresets.size(); i++)
  {
    printf("Saving preset: %S\n", pParticleSystem.presetNames[i].c_str());

    //! Write start of particle system.
    m_irrXMLSaveFile->writeElement(pParticleSystem.presetNames[i].c_str(), false);
    m_irrXMLSaveFile->writeLineBreak();

      //! Write emitter values.
      m_irrXMLSaveFile->writeText(L"\t");
      m_irrXMLSaveFile->writeElement(L"Emitter", false);
      m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write emitter box dimensions.
        //!------------------------
        vector3df minEdge = pParticleSystem.m_aPresets[i].emitter.emitterBox.MinEdge;
        vector3df maxEdge = pParticleSystem.m_aPresets[i].emitter.emitterBox.MaxEdge;

        wprintf(t1, L"%f", (-minEdge.X)+maxEdge.X);
        wprintf(t2, L"%f", (-minEdge.Y)+maxEdge.Y);
        wprintf(t3, L"%f", (-minEdge.Z)+maxEdge.Z);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"emitterBox", true,
          L"w",   t1,
          L"h",  t2,
          L"l",  t3);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write emitter direction.
        //!------------------------
        wprintf(t1, L"%f", pParticleSystem.m_aPresets[i].emitter.direction.X);
        wprintf(t2, L"%f", pParticleSystem.m_aPresets[i].emitter.direction.Y);
        wprintf(t3, L"%f", pParticleSystem.m_aPresets[i].emitter.direction.Z);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"direction", true,
          L"x", t1,
          L"y", t2,
          L"z", t3);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write emitter rate min max.
        //!------------------------
        wprintf(t1, L"%i", pParticleSystem.m_aPresets[i].emitter.minParticlesPerSecond);
        wprintf(t2, L"%i", pParticleSystem.m_aPresets[i].emitter.maxParticlesPerSecond);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"rate", true,
          L"min", t1,
          L"max", t2);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write emitter min start color.
        //!------------------------
        wprintf(t1, L"%i", pParticleSystem.m_aPresets[i].emitter.minStartColor.getAlpha());
        wprintf(t2, L"%i", pParticleSystem.m_aPresets[i].emitter.minStartColor.getRed());
        wprintf(t3, L"%i", pParticleSystem.m_aPresets[i].emitter.minStartColor.getGreen());
        wprintf(t4, L"%i", pParticleSystem.m_aPresets[i].emitter.minStartColor.getBlue());

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"minStartColor", true,
          L"a", t1,
          L"r", t2,
          L"g", t3,
          L"b", t4
          );

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write emitter max start color.
        //!------------------------
        wprintf(t1, L"%i", pParticleSystem.m_aPresets[i].emitter.maxStartColor.getAlpha());
        wprintf(t2, L"%i", pParticleSystem.m_aPresets[i].emitter.maxStartColor.getRed());
        wprintf(t3, L"%i", pParticleSystem.m_aPresets[i].emitter.maxStartColor.getGreen());
        wprintf(t4, L"%i", pParticleSystem.m_aPresets[i].emitter.maxStartColor.getBlue());

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"maxStartColor", true,
          L"a", t1,
          L"r", t2,
          L"g", t3,
          L"b", t4
          );

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write emitter life min max.
        //!------------------------
        wprintf(t1, L"%i", pParticleSystem.m_aPresets[i].emitter.lifeTimeMin);
        wprintf(t2, L"%i", pParticleSystem.m_aPresets[i].emitter.lifeTimeMax);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"life", true,
          L"min", t1,
          L"max", t2);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write emitter max angle.
        //!------------------------
        wprintf(t1, L"%i", pParticleSystem.m_aPresets[i].emitter.maxAngleDegrees);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"maxAngle", true,
          L"degrees", t1
          );

        m_irrXMLSaveFile->writeLineBreak();

      //! Write emitter closing tag.
      m_irrXMLSaveFile->writeText(L"\t");
      m_irrXMLSaveFile->writeClosingTag(L"Emitter");
      m_irrXMLSaveFile->writeLineBreak();

      //! Write particle values.
      m_irrXMLSaveFile->writeText(L"\t");
      m_irrXMLSaveFile->writeElement(L"Particle", false);
      m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write particle position.
        //!------------------------
        wprintf(t1, L"%f", pParticleSystem.m_aPresets[i].particle.position.X);
        wprintf(t2, L"%f", pParticleSystem.m_aPresets[i].particle.position.Y);
        wprintf(t3, L"%f", pParticleSystem.m_aPresets[i].particle.position.Z);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"position", true,
          L"x", t1,
          L"y", t2,
          L"z", t3);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write particle scale.
        //!------------------------
        wprintf(t1, L"%f", pParticleSystem.m_aPresets[i].particle.scale.X);
        wprintf(t2, L"%f", pParticleSystem.m_aPresets[i].particle.scale.Y);
        wprintf(t3, L"%f", pParticleSystem.m_aPresets[i].particle.scale.Z);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"scale", true,
          L"x", t1,
          L"y", t2,
          L"z", t3);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write particle size.
        //!------------------------
        wprintf(t1, L"%f", pParticleSystem.m_aPresets[i].particle.size.Width);
        wprintf(t2, L"%f", pParticleSystem.m_aPresets[i].particle.size.Height);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"size", true,
          L"width",   t1,
          L"height",  t2
          );

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write particle material type.
        //!------------------------
        wprintf(t1, L"%i", pParticleSystem.m_aPresets[i].particle.materialType);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"material", true,
          L"type",   t1
          );

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write particle texture name.
        //!------------------------
        wprintf(t1, L"%S", pParticleSystem.m_aPresets[i].texture.c_str());

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"texture", true,
          L"name",   t1
          );

        m_irrXMLSaveFile->writeLineBreak();

      //! Write particle closing tag.
      m_irrXMLSaveFile->writeText(L"\t");
      m_irrXMLSaveFile->writeClosingTag(L"Particle");
      m_irrXMLSaveFile->writeLineBreak();

      //! Write affector values.
      m_irrXMLSaveFile->writeText(L"\t");
      m_irrXMLSaveFile->writeElement(L"Affector", false);
      m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write affector target color.
        //!------------------------
        wprintf(t1, L"%i", pParticleSystem.m_aPresets[i].affector.targetColor.getAlpha());
        wprintf(t2, L"%i", pParticleSystem.m_aPresets[i].affector.targetColor.getRed());
        wprintf(t3, L"%i", pParticleSystem.m_aPresets[i].affector.targetColor.getGreen());
        wprintf(t4, L"%i", pParticleSystem.m_aPresets[i].affector.targetColor.getBlue());


        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"targetColor", true,
          L"a", t1,
          L"r", t2,
          L"g", t3,
          L"b", t4);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write affector fade out time.
        //!------------------------
        wprintf(t1, L"%d", pParticleSystem.m_aPresets[i].affector.timeNeededToFadeOut);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"fadeOutTime", true,
          L"time",   t1
          );

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write affector gravity.
        //!------------------------
        wprintf(t1, L"%f", pParticleSystem.m_aPresets[i].affector.gravity.X);
        wprintf(t2, L"%f", pParticleSystem.m_aPresets[i].affector.gravity.Y);
        wprintf(t3, L"%f", pParticleSystem.m_aPresets[i].affector.gravity.Z);


        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"gravity", true,
          L"x", t1,
          L"y", t2,
          L"z", t3);

        m_irrXMLSaveFile->writeLineBreak();

        //!------------------------
        //! Write affector time force lost.
        //!------------------------
        wprintf(t1, L"%d", pParticleSystem.m_aPresets[i].affector.timeForceLost);

        m_irrXMLSaveFile->writeText(L"\t\t");
        m_irrXMLSaveFile->writeElement(L"timeForceLost", true,
          L"time",   t1
          );

        m_irrXMLSaveFile->writeLineBreak();

      //! Write affector closing tag.
      m_irrXMLSaveFile->writeText(L"\t");
      m_irrXMLSaveFile->writeClosingTag(L"Affector");
      m_irrXMLSaveFile->writeLineBreak();

    //! Write end of particle system.
    m_irrXMLSaveFile->writeClosingTag(pParticleSystem.presetNames[i].c_str());
    m_irrXMLSaveFile->writeLineBreak();
    m_irrXMLSaveFile->writeComment(L"End of preset");
    m_irrXMLSaveFile->writeLineBreak();
  }

  m_irrXMLSaveFile->drop();
}

/*! \brief saveParticleSystemToCPP
 *
 *  Saves a particle system to a CPP style document.
 */
void WorldFile::saveParticleSystemToCPP(stringc pFileName, stringc emitterName, ParticleSystem &pParticleSystem, bool append)
{
  stringc file = workDir;
  file += L"save/";
  file += pFileName;
  printf("Saving to: %s\n", file.c_str());

  if(append)
  {
    printf("Appending...\n");
    m_irrCPPSaveFile = fopen(file.c_str(), "a+");
  }
  else
  {
    printf("Not appending...\n");
    m_irrCPPSaveFile = fopen(file.c_str(), "w+");
  }

  if(!m_irrCPPSaveFile){
    printf("Failed to open file: %s\n", pFileName.c_str());
  }

  char *S_MATERIAL_TYPE[17] =
  {
      "SOLID",
      "SOLID_2_LAYER",
      "LIGHTMAP",
      "LIGHTMAP_ADD",
      "LIGHTMAP_M2",
      "LIGHTMAP_M4",
      "LIGHTMAP_LIGHTING",
      "LIGHTMAP_LIGHTING_M2",
      "LIGHTMAP_LIGHTING_M4",
      "DETAIL_MAP",
      "SPHERE_MAP",
      "REFLECTION_2_LAYER",
      "TRANSPARENT_ADD_COLOR",
      "TRANSPARENT_ALPHA_CHANNEL",
      "TRANSPARENT_ALPHA_CHANNEL_REF",
      "TRANSPARENT_VERTEX_ALPHA",
      "TRANSPARENT_REFLECTION_2_LAYER"
      /*
      L"NORMAL_MAP_SOLID",
      L"NORMAL_MAP_TRANSPARENT_ADD_COLOR",
      L"NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA",
      L"PARALLAX_MAP_SOLID",
      L"PARALLAX_MAP_TRANSPARENT_ADD_COLOR",
      L"PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA"
      */
  };

  //printf("Material Type: %s\n", S_MATERIAL_TYPE[pParticleSystem.getMaterialType()]);

  char buffer[2048] = "";

  sprintf(buffer, "\
//! ---------------------------------------------------------------------------------\n\
//! Particle system ID: %i\n\
//! Particle system name: %s\n\n\
\tscene::IParticleSystemSceneNode* p = scenemgr->addParticleSystemSceneNode();\n\
\n\
\tp->setParticleSize(core::dimension2d<f32>(%1.1ff, %1.1ff));\n\
\n\
\tscene::IParticleEmitter* em = p->createBoxEmitter(\n\
\t        core::aabbox3d<f32>(-%i,-%i,-%i,%i,%i,%i),\n\
\t        core::vector3df(%1.3ff,%1.3ff,%1.3ff),\n\
\t        %i,%i, video::SColor(%i, %i, %i, %i),video::SColor(%i, %i, %i, %i), %i, %i);\n\
        \n\
\tp->setEmitter(em); \n\
\tem->drop();\n\
\n\
\tscene::IParticleAffector* paf = p->createFadeOutParticleAffector();\n\
\tp->addAffector(paf);\n\
\tpaf->drop();\n\
\n\
\tps->setMaterialFlag(video::EMF_LIGHTING, false);\n\
\tps->setMaterialTexture(0, driver->getTexture(\"%s\"));\n\
\tps->setMaterialType(video::",
    pParticleSystem.getCurrentID(), emitterName.c_str(),
    pParticleSystem.getParticleSizeX(), pParticleSystem.getParticleSizeY(),
    pParticleSystem.getEmitterBoxWidth()/2, pParticleSystem.getEmitterBoxHeight()/2, pParticleSystem.getEmitterBoxLength()/2,
    pParticleSystem.getEmitterBoxWidth()/2, pParticleSystem.getEmitterBoxHeight()/2, pParticleSystem.getEmitterBoxLength()/2,
    pParticleSystem.getEmitterDirection().X, pParticleSystem.getEmitterDirection().Y, pParticleSystem.getEmitterDirection().Z,
    pParticleSystem.getEmitterParticleMin(), pParticleSystem.getEmitterParticleMax(),
    pParticleSystem.getEmitterMinStartColor().getAlpha(), pParticleSystem.getEmitterMinStartColor().getRed(), pParticleSystem.getEmitterMinStartColor().getGreen(), pParticleSystem.getEmitterMinStartColor().getBlue(),
    pParticleSystem.getEmitterMaxStartColor().getAlpha(), pParticleSystem.getEmitterMaxStartColor().getRed(), pParticleSystem.getEmitterMaxStartColor().getGreen(), pParticleSystem.getEmitterMaxStartColor().getBlue(),
    pParticleSystem.getEmitterParticlesLifeMin(), pParticleSystem.getEmitterParticlesLifeMax(),
    pParticleSystem.getParticleTexture().c_str()
  );

  int size = strlen(buffer);
  sprintf(&buffer[size], "%s);\n\n", S_MATERIAL_TYPE[pParticleSystem.getMaterialType()]);

  fprintf(m_irrCPPSaveFile, buffer);

  fclose(m_irrCPPSaveFile);
}
