#include "ParticleSystem.h"

// TODO (kjeiwa-3#2#): Add support for several particle systems.
// TODO (kjeiwa-3#3#): Ability to load custom background scenery for interactive placement of particle emitters.

/*! \brief  ParticleSystem constructor
 */
ParticleSystem::ParticleSystem(ISceneManager &pSceneManager, IVideoDriver &pVideoDriver, vector3df pParticlePosition) :
  presetNamesIndex(-1),
  m_ID(-1),
  m_iParticleSystemCount(-1),
  m_irrSceneManager(&pSceneManager),
  m_irrVideoDriver(&pVideoDriver)
{
  //initializeSystem();

  printf("[*] Particle system initialized.\n");
}

/*! \brief  ParticleSystem destructor
 */
ParticleSystem::~ParticleSystem()
{
  m_aPresets.clear();
  presetNames.clear();

  for(u32 i = 0; i < m_aParticleSystem.size(); i++)
  {
    m_aParticleSystem[i].m_particleEmitter->drop();
    m_aParticleSystem[i].m_particleSystem->drop();
    m_aParticleSystem[i].m_particleAffectorGravity->drop();
    m_aParticleSystem[i].m_particleAffectorFadeOut->drop();
  }

  m_aParticleSystem.clear();

  memset(&m_pEmitter, 0, sizeof(PARTICLE_EMITTER));
  memset(&m_pParticle, 0, sizeof(PARTICLE));
  memset(&m_pAffector, 0, sizeof(PARTICLE_AFFECTOR));

  printf("[*] Particle system deinitialized.\n");
}

/*! \brief  initializeSystem.
 *
 *  Set default values for emitter and particles.
 */
void ParticleSystem::initializeSystem(void)
{
  //! Initialize Particle.
  m_pParticle.position = vector3df(0,0,0);
  m_pParticle.scale = vector3df(1,1,1);
  m_pParticle.size = dimension2d<f32>(2.0f, 2.0f);
  m_pParticle.materialType = EMT_TRANSPARENT_VERTEX_ALPHA;

  //! Initialize Emitter.
  m_pEmitter.emitterBox = setEmitterBox(2, 2, 2);
  m_pEmitter.direction  = vector3df(0.0f,0.006f,0.0f);
  m_pEmitter.minParticlesPerSecond = 80;
  m_pEmitter.maxParticlesPerSecond = 100;
  m_pEmitter.minStartColor = SColor(0,255,255,255);
  m_pEmitter.maxStartColor = SColor(0,255,255,255);
  m_pEmitter.lifeTimeMin = 800;
  m_pEmitter.lifeTimeMax = 2000;
  m_pEmitter.maxAngleDegrees = 0;

  //! Initialize affector.
  m_pAffector.timeForceLost = 1000;
  m_pAffector.gravity = vector3df(0.0f, -0.03f, 0.0f);
  m_pAffector.timeNeededToFadeOut = 1000;
  m_pAffector.targetColor = SColor(0,0,0,0);

  stringc temp = L"ParticleFire.tga";
  setParticleTexture(temp, false);

  //addParticleSystem();
  //updateParticleSystem();
}

/*! \brief  createEmitter
 *
 *  Create new box emitter for current particle system.
 */
void ParticleSystem::createEmitter(void)
{
  if(m_aParticleSystem[m_ID].m_particleEmitter != NULL)
  {
    m_aParticleSystem[m_ID].m_particleEmitter->drop();
    //m_particleSystem->removeAllAffectors();
    //m_particleSystem->addAffector(m_particleAffector);
  }

  m_aParticleSystem[m_ID].m_particleEmitter =
  m_aParticleSystem[m_ID].m_particleSystem->createBoxEmitter(
    m_pEmitter.emitterBox,
    m_pEmitter.direction,
    m_pEmitter.minParticlesPerSecond,
    m_pEmitter.maxParticlesPerSecond,
    m_pEmitter.minStartColor,
    m_pEmitter.maxStartColor,
    m_pEmitter.lifeTimeMin,
    m_pEmitter.lifeTimeMax,
    m_pEmitter.maxAngleDegrees);

  m_aParticleSystem[m_ID].m_particleSystem->setEmitter(m_aParticleSystem[m_ID].m_particleEmitter);
}

void ParticleSystem::createAffectors(void)
{
  //! Create fade out affector.
  m_aParticleSystem[m_ID].m_particleAffectorFadeOut =
    m_aParticleSystem[m_ID].m_particleSystem->createFadeOutParticleAffector(
      m_pAffector.targetColor, m_pAffector.timeNeededToFadeOut
    );

  m_aParticleSystem[m_ID].m_particleSystem->addAffector(m_aParticleSystem[m_ID].m_particleAffectorFadeOut);

  //! Create gravity affector.
  m_aParticleSystem[m_ID].m_particleAffectorGravity =
    m_aParticleSystem[m_ID].m_particleSystem->createGravityAffector(
      m_pAffector.gravity, m_pAffector.timeForceLost
    );

  m_aParticleSystem[m_ID].m_particleSystem->addAffector(m_aParticleSystem[m_ID].m_particleAffectorGravity);
}

void ParticleSystem::addParticleSystem(vector3df pos)
{
  m_iParticleSystemCount++;
  m_ID = m_iParticleSystemCount;

  m_pParticle.position = pos;
  m_vParticleSystemPosition.push_back(pos);
  printf("m_pParticle.position = %f %f %f\n", m_pParticle.position.X, m_pParticle.position.Y, m_pParticle.position.Z);

  PARTICLE_SYSTEM temp;
  memset(&temp, 0, sizeof(PARTICLE_SYSTEM));
  m_aParticleSystem.push_back(temp);

  m_aParticleSystem[m_iParticleSystemCount].m_particleSystem = 0;
  m_aParticleSystem[m_iParticleSystemCount].m_particleSystem = m_irrSceneManager->addParticleSystemSceneNode(false);
  m_aParticleSystem[m_iParticleSystemCount].m_particleSystem->setPosition(vector3df(0,0,0));

  createEmitter();
  createAffectors();

  showCurrentBBox();

  m_aParticles.push_back(m_pParticle);
  m_aEmitters.push_back(m_pEmitter);
  m_aAffectors.push_back(m_pAffector);
}

void ParticleSystem::setParticleTexture(stringc texture, bool preset)
{
  stringc fileName;

  if(preset)
  {
    printf("Loading preset texture\n");
    //! Get only the name of the texture.
    fileName = L"\0";

    s32 pos = texture.findLast('/');

    if(pos > -1)
    {
      fileName = texture.subString(pos+1, strlen(texture.c_str()));
    }
    else
    {
      pos = texture.findLast('/');

      if(pos > -1)
      {
        fileName = texture.subString(pos+1, strlen(texture.c_str()));
      }
      else
      {
        fileName = texture;
      }
    }
  }
  else
  {
    fileName = texture;
  }

  //! Set the full texture path, this will ALWAYS be in the particles dir. No matter where you load from.
  stringc fullTextureName = workDir;
  fullTextureName += L"textures/particles/";
  fullTextureName += fileName;

  printf("Texture name set to: %s\n", fullTextureName.c_str());

  m_particleTexture = fullTextureName;
}

/*! \brief  updateParticleSystem
 *
 *  Update the current particle system.
 */
void ParticleSystem::updateParticleSystem(void)
{
  m_aParticleSystem[m_ID].m_particleSystem->setPosition(m_vParticleSystemPosition[m_ID]);
  m_aParticleSystem[m_ID].m_particleSystem->setScale(m_pParticle.scale);
  m_aParticleSystem[m_ID].m_particleSystem->setParticleSize(m_pParticle.size);

  m_aParticleSystem[m_ID].m_particleSystem->setMaterialFlag(EMF_LIGHTING, false);

  //! Load textures.
  // TODO (kjeiwa-3#1#): OK, workdir needs to be set somehow, make sure loading an environment doesn't change relative path. >:|
  m_aParticleSystem[m_ID].m_particleSystem->setMaterialTexture(0, m_irrVideoDriver->getTexture( m_particleTexture.c_str() ));
  m_aParticleSystem[m_ID].m_particleSystem->setMaterialType(m_pParticle.materialType);

  m_aParticles[m_ID] = m_pParticle;
  m_aEmitters[m_ID] = m_pEmitter;
  m_aAffectors[m_ID] = m_pAffector;
}

void ParticleSystem::addPreset(wchar_t *name)
{
  PRESET tempPreset;
  tempPreset.particle   = m_pParticle;
  tempPreset.emitter    = m_pEmitter;
  tempPreset.affector   = m_pAffector;
  tempPreset.presetName = name;
  tempPreset.texture    = this->getParticleTexture();

  m_aPresets.push_back(tempPreset);

  setPresetName(name);

  printf("Index: %i Name: %S m_aPresets.size = %i, presetNames.size = %i\n", presetNamesIndex, (wchar_t*)presetNames[presetNamesIndex].c_str(), m_aPresets.size(), presetNames.size());
}

void ParticleSystem::addPreset(PRESET &preset)
{
  PRESET tempPreset;
  tempPreset = preset;
  tempPreset.presetName = (wchar_t*)presetNames[presetNamesIndex].c_str();

  m_aPresets.push_back(tempPreset);

  printf("Index: %i Name: %S m_aPresets.size = %i, presetNames.size = %i\n", presetNamesIndex, (wchar_t*)presetNames[presetNamesIndex].c_str(), m_aPresets.size(), presetNames.size());
}

void ParticleSystem::setPreset(s32 id)
{
  if(m_iParticleSystemCount < 0)
    return;

  m_pEmitter  = m_aPresets[id].emitter;
  m_pParticle = m_aPresets[id].particle;
  m_pAffector = m_aPresets[id].affector;

  m_aEmitters[m_ID] = m_pEmitter;
  m_aParticles[m_ID] = m_pParticle;
  m_aAffectors[m_ID] = m_pAffector;

  setParticleTexture(m_aPresets[id].texture, true);

  printf("Creating emitter at: %f %f %f\n", m_vParticleSystemPosition[m_ID].X, m_vParticleSystemPosition[m_ID].Y, m_vParticleSystemPosition[m_ID].Z);

  createEmitter();
  createAffectors();
  updateParticleSystem();
}

void ParticleSystem::showCurrentBBox(void)
{
  //! First turn off bbox display on all.
  for(s32 i = 0; i < m_iParticleSystemCount+1; i++)
    m_aParticleSystem[i].m_particleSystem->setDebugDataVisible(EDS_OFF);

  m_aParticleSystem[m_ID].m_particleSystem->setDebugDataVisible(EDS_BBOX);
}

void ParticleSystem::deleteCurrentSystem(void)
{
  printf("\tDelete current system\n");
  array<PARTICLE_SYSTEM>    temp;
  array<PARTICLE_EMITTER>   tempEmitters;
  array<PARTICLE>           tempParticles;
  array<PARTICLE_AFFECTOR>  tempAffectors;

  u32 i;
  s32 j;

  //! Copy particle systems.
  for(j = -1; j < m_ID; j++)
    temp.push_back(m_aParticleSystem[j]);
  for(i = m_ID+1; i < m_aParticleSystem.size(); i++)
    temp.push_back(m_aParticleSystem[i]);

  //! Copy particle emitters.
  for(j = -1; j < m_ID; j++)
    tempEmitters.push_back(m_aEmitters[j]);
  for(i = m_ID+1; i < m_aEmitters.size(); i++)
    tempEmitters.push_back(m_aEmitters[i]);

  //! Copy particles.
  for(j = -1; j < m_ID; j++)
    tempParticles.push_back(m_aParticles[j]);
  for(i = m_ID+1; i < m_aParticles.size(); i++)
    tempParticles.push_back(m_aParticles[i]);

  //! Copy particle affectors.
  for(j = -1; j < m_ID; j++)
    tempAffectors.push_back(m_aAffectors[j]);
  for(i = m_ID+1; i < m_aAffectors.size(); i++)
    tempAffectors.push_back(m_aAffectors[i]);

  //! -------------------------------------------
  //! Done copying.
  //! -------------------------------------------

  //! Clear particle systems.
  for(i = -1; i < m_aParticleSystem.size(); i++)
  {
    m_aParticleSystem[i].m_particleEmitter->drop();
    m_aParticleSystem[i].m_particleSystem->drop();
    m_aParticleSystem[i].m_particleAffectorGravity->drop();
    m_aParticleSystem[i].m_particleAffectorFadeOut->drop();
  }

  m_aParticleSystem.clear();

  //! Clear emitters, particles, affectors.
  m_aEmitters.clear();
  m_aParticles.clear();
  m_aAffectors.clear();

  m_iParticleSystemCount = -1;

  printf("Re-population of particle systems, temp.size = %i\n", temp.size());
  //! Re-populate.
  for(i = -1; i < temp.size(); i++)
  {
    m_pEmitter = tempEmitters[i];
    m_pParticle = tempParticles[i];
    m_pAffector = tempAffectors[i];
    addParticleSystem(vector3df(0,0,0));
  }

  //! Clear temp.
  temp.clear();
  tempEmitters.clear();
  tempParticles.clear();
  tempAffectors.clear();
}
