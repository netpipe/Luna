/*
  World Manager class implementation.

    The world manager handles everything regarding the world.
    Characters, scenery, lights.
*/

#include "WorldManager.h"


// ------------------------------------------------------------------------
// De- / Constructor
// ------------------------------------------------------------------------
World_Manager::World_Manager()
{
  m_strFilePath = NULL;
  memset(m_strFileName, 0, 128);

  m_irrSceneNode    = NULL;
  m_irrSceneManager = NULL;
  m_irrVideoDriver  = NULL;
  m_irrDevice       = NULL;

  m_irrAnimatedMesh           = NULL;
  m_irrAnimatedMeshSceneNode  = NULL;

  m_lightColor  = SColorf(1.0f, 1.0f, 1.0f, 1.0f);
  m_lightRadius = 2000.0f;
  m_lightID     = 0;

  m_dynamicLight = new SLight();
  m_dynamicLight->AmbientColor  = SColorf(255,255,255);
  m_dynamicLight->DiffuseColor  = SColorf(255,255,255);
  m_dynamicLight->SpecularColor = SColorf(255,255,255);
  m_dynamicLight->Position      = vector3df(0,0,0);
  m_dynamicLight->CastShadows   = false;
  m_dynamicLight->Radius        = m_lightRadius;
  m_dynamicLight->Type          = ELT_DIRECTIONAL;

  printf("[*] World Manager initialized.\n");
}
// ------------------------------------------------------------------------
World_Manager::~World_Manager()
{
  if(m_strFilePath != NULL)
    m_strFilePath = NULL;

  if(m_strFileName != NULL)
    memset(m_strFileName, 0, 128);

  if(m_irrSceneNode != NULL)
    m_irrSceneNode = NULL;

  if(m_irrVideoDriver != NULL)
    m_irrVideoDriver = NULL;

  if(m_irrDevice != NULL)
  m_irrDevice = NULL;

  if(m_irrAnimatedMesh != NULL)
    m_irrAnimatedMesh = NULL;

  if(m_irrAnimatedMeshSceneNode != NULL)
    m_irrAnimatedMeshSceneNode = NULL;

  if(m_irrSceneManager != NULL)
    m_irrSceneManager = NULL;

  if(m_dynamicLight != NULL)
    delete m_dynamicLight;

  printf("[*] World Manager deinitialized.\n");
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//  Functions to get and set the scene node.
// ------------------------------------------------------------------------
ISceneNode *World_Manager::getSceneNode(void)
{
  return m_irrSceneNode;
}
// ------------------------------------------------------------------------
void World_Manager::setSceneNode(ISceneNode &sceneNode)
{
  m_irrSceneNode = &sceneNode;
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
ISceneManager *World_Manager::getSceneManager()
{
  return m_irrSceneManager;
}
// ------------------------------------------------------------------------
void World_Manager::setSceneManager(ISceneManager &sceneManager)
{
  m_irrSceneManager = &sceneManager;
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
IVideoDriver *World_Manager::getVideoDriver()
{
  return m_irrVideoDriver;
}
// ------------------------------------------------------------------------
void World_Manager::setVideoDriver(IVideoDriver &videoDriver)
{
  m_irrVideoDriver = &videoDriver;
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
IrrlichtDevice *World_Manager::getIrrlichtDevice()
{
  return m_irrDevice;
}
// ------------------------------------------------------------------------
void World_Manager::setIrrlichtDevice(IrrlichtDevice &device)
{
  m_irrDevice = &device;
  m_cWorldFile.setIrrlichtDevice(device);
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
void World_Manager::setResourcePath(char *path)
{
  m_strFilePath = path;
  m_iPathLength = strlen(m_strFilePath);
}
// ------------------------------------------------------------------------
void World_Manager::addAnimatedMeshNode(char *file)
{
  strcpy(m_strFileName, m_strFilePath);
  strcpy(&m_strFileName[m_iPathLength], file);

  printf("[WM] Loading mesh node %s\n", m_strFileName);

  if(m_irrSceneManager == NULL)
    throw "Tried adding animated scene mesh node when scene manager pointer is NULL.";

  m_irrAnimatedMesh = m_irrSceneManager->getMesh(m_strFileName);

  if(m_irrAnimatedMesh)
  {
    m_irrAnimatedMeshSceneNode = m_irrSceneManager->addAnimatedMeshSceneNode(m_irrAnimatedMesh);
  }
}
// ------------------------------------------------------------------------
void World_Manager::setAnimatedMeshProperties(
  vector3df position,
  vector3df rotation,
  vector3df scale,
  float animationSpeed,
  bool castShadows,
  E_MATERIAL_TYPE materialType)
{
  if(m_irrAnimatedMeshSceneNode != 0)
  {
    m_irrAnimatedMeshSceneNode->setPosition(position);
    m_irrAnimatedMeshSceneNode->setRotation(rotation);

    m_irrAnimatedMeshSceneNode->setAnimationSpeed(animationSpeed);

    // Enable lighting and fog.
    m_irrAnimatedMeshSceneNode->setMaterialFlag(EMF_LIGHTING, true);
    m_irrAnimatedMeshSceneNode->setMaterialFlag(EMF_FOG_ENABLE, true);

    // FIXME (kjeiwa-3#1#): Default is transparency on for all materials. Fix for non-transparent materials.
    m_irrAnimatedMeshSceneNode->setMaterialType(materialType);

    if(scale != vector3df(1,1,1))
    {
      m_irrAnimatedMeshSceneNode->setScale(scale);
      m_irrAnimatedMeshSceneNode->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
    }

    if(castShadows == true)
    {
      m_irrAnimatedMeshSceneNode->addShadowVolumeSceneNode();
      m_irrSceneManager->setShadowColor(SColor(96,0,0,0));
    }
  }
}
// ------------------------------------------------------------------------
void World_Manager::setAnimatedMeshProperties(vector3df position)
{
  setAnimatedMeshProperties(
    position,
    vector3df(0,0,0),
    vector3df(1,1,1),
    15.0f,
    false);
}
// ------------------------------------------------------------------------
void World_Manager::setAnimatedMeshProperties(void)
{
  setAnimatedMeshProperties(
    vector3df(0,0,0),
    vector3df(0,0,0),
    vector3df(1,1,1),
    15.0f,
    false);
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//  Functions for adding light sources in the world.
// ------------------------------------------------------------------------
void World_Manager::setLightColor(SColorf color)
{
  m_lightColor = color;
}
// ------------------------------------------------------------------------
void World_Manager::setLightRadius(f32 radius)
{
  m_lightRadius = radius;
}
// ------------------------------------------------------------------------
void World_Manager::addLight(ISceneNode *parent, vector3df position, SColorf color, f32 radius, s32 id)
{
  m_irrSceneNode =
    m_irrSceneManager->addLightSceneNode(parent, position, color, radius, id);
}
// ------------------------------------------------------------------------
void World_Manager::addLight(vector3df position)
{
  m_irrSceneNode =
    m_irrSceneManager->addLightSceneNode(0, position, m_lightColor, m_lightRadius, m_lightID++);
}
// ------------------------------------------------------------------------
void World_Manager::addLight(void)
{
  m_irrSceneNode =
    m_irrSceneManager->addLightSceneNode(0, vector3df(0,0,0), m_lightColor, m_lightRadius, m_lightID++);
}
// ------------------------------------------------------------------------
void World_Manager::addDynamicLight(SColorf ambientColor, SColorf diffuseColor, SColorf specularColor, bool castShadows, vector3df &position, f32 radius, E_LIGHT_TYPE lightType)
{
  m_dynamicLight->AmbientColor  = ambientColor;
  m_dynamicLight->DiffuseColor  = diffuseColor;
  m_dynamicLight->SpecularColor = specularColor;
  m_dynamicLight->Position      = position;
  m_dynamicLight->CastShadows   = castShadows;
  m_dynamicLight->Radius        = radius;
  m_dynamicLight->Type          = lightType;

  this->addDynamicLight();
}
// ------------------------------------------------------------------------
void World_Manager::addDynamicLight(vector3df position)
{
  m_dynamicLight->Position  = position;
  m_dynamicLight->Radius    = m_lightRadius;

  this->addDynamicLight();
}
// ------------------------------------------------------------------------
void World_Manager::addDynamicLight(void)
{
  if(m_irrVideoDriver!=NULL)
  {
    m_irrVideoDriver->addDynamicLight(*m_dynamicLight);
  }
  else
  {
    printf("[WM] Warning: Tried to create dynamic light when pointer to video driver is NULL.\n");
  }
}
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//  Functions for adding world environment.
// ------------------------------------------------------------------------
void World_Manager::addEnvironment(char *file, vector3df scale)
{
  //m_irrSceneManager->getParameters()->setParameter(DMF_TEXTURE_PATH, m_strFilePath);
  //m_irrSceneManager->getParameters()->setParameter(DMF_USE_MATERIALS_DIRS, false);
  //m_irrSceneManager->getParameters()->setParameter(DMF_ALPHA_CHANNEL_REF, 0.01f);
  //sceneManager->getParameters()->setParameter(DMF_FLIP_ALPHA_TEXTURES, true);

  strcpy(m_strFileName, m_strFilePath);
  strcpy(&m_strFileName[m_iPathLength], file);

  m_irrAnimatedMesh = m_irrSceneManager->getMesh(m_strFileName);

  if(m_irrAnimatedMesh)
  {
    m_irrSceneNode = m_irrSceneManager->addOctTreeSceneNode(m_irrAnimatedMesh->getMesh(0));
    m_irrSceneNode->setPosition(vector3df(0,0,0));
    m_irrSceneNode->setScale(vector3df(scale));
    m_irrSceneNode->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
    m_irrSceneNode->setMaterialFlag(EMF_LIGHTING, true);
    m_irrSceneNode->setMaterialFlag(EMF_FOG_ENABLE, true);
  }
}
// ------------------------------------------------------------------------
void World_Manager::addSkyBox(void)
{
  if( (m_irrVideoDriver != NULL) && (m_irrSceneManager != NULL) )
  {
    char sbFront[64]  = "";
    char sbBack[64]   = "";
    char sbLeft[64]   = "";
    char sbRight[64]  = "";
    char sbTop[64]    = "";
    char sbBottom[64] = "";

    m_irrVideoDriver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, false);

    strcpy(sbFront, m_strFilePath);
    strcpy(&sbFront[m_iPathLength], "pos_z.bmp");

    strcpy(sbBack, m_strFilePath);
    strcpy(&sbBack[m_iPathLength], "neg_z.bmp");

    strcpy(sbLeft, m_strFilePath);
    strcpy(&sbLeft[m_iPathLength], "pos_x.bmp");

    strcpy(sbRight, m_strFilePath);
    strcpy(&sbRight[m_iPathLength], "neg_x.bmp");

    strcpy(sbTop, m_strFilePath);
    strcpy(&sbTop[m_iPathLength], "pos_y.bmp");

    strcpy(sbBottom, m_strFilePath);
    strcpy(&sbBottom[m_iPathLength], "neg_y.bmp");

    m_irrSceneNode = m_irrSceneManager->addSkyBoxSceneNode(
      m_irrVideoDriver->getTexture(sbTop),
      m_irrVideoDriver->getTexture(sbBottom),

      m_irrVideoDriver->getTexture(sbLeft),
      m_irrVideoDriver->getTexture(sbRight),

      m_irrVideoDriver->getTexture(sbFront),
      m_irrVideoDriver->getTexture(sbBack)
    );

    //m_irrSceneNode->setMaterialFlag(EMF_FOG_ENABLE, true);

    m_irrVideoDriver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS, true);
  }
  else
  {
    printf("[WM] Warning: Tried to create skybox when pointer to video driver is NULL.\n");
  }
}
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
//  END OF FILE.
// ------------------------------------------------------------------------
