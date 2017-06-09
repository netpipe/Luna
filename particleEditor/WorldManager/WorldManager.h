#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include "globals.hxx"
#include "WorldFile.h"

class World_Manager
{
	public:
		World_Manager();
		virtual ~World_Manager();

		// Sets the path to use, so we only have to specify it once before loading models.
		void setResourcePath(char *path);

    // Functions for animated meshes.
		void addAnimatedMeshNode(char *file);
		void setAnimatedMeshProperties(vector3df position, vector3df rotation, vector3df scale, float animationSpeed, bool castShadows, E_MATERIAL_TYPE materialType = EMT_TRANSPARENT_ADD_COLOR);
		void setAnimatedMeshProperties(vector3df position);
		void setAnimatedMeshProperties(void);

    // Functions for adding scene lights.
    void addLight(ISceneNode *parent, vector3df position, SColorf color, f32 radius, s32 id);
    void addLight(vector3df position);
    void addLight(void);
    void addDynamicLight(SColorf ambientColor, SColorf diffuseColor, SColorf specularColor, bool castShadows, vector3df &position, f32 radius, E_LIGHT_TYPE lightType);
    void addDynamicLight(vector3df position);
    void addDynamicLight(void);
    void setLightColor(SColorf color);
    void setLightRadius(f32 radius);

    void addSkyBox(void);

    // Functions for adding the worlds basic environment.
    /*
      Assumptions:
        File format loaded is DMF.
        It will be added as an Octree scene node.
    */
    void addEnvironment(char *file, vector3df scale);

    // Functions for getting and setting pointers.
		ISceneNode *getSceneNode(void);
		void        setSceneNode(ISceneNode &sceneNode);

		ISceneManager  *getSceneManager();
		void            setSceneManager(ISceneManager &sceneManager);

		IVideoDriver   *getVideoDriver();
		void            setVideoDriver(IVideoDriver &driver);

		IrrlichtDevice  *getIrrlichtDevice();
		void            setIrrlichtDevice(IrrlichtDevice &device);

    IAnimatedMeshSceneNode *getAnimatedMeshSceneNode(void){ return m_irrAnimatedMeshSceneNode; }
    IAnimatedMesh *getAnimatedMesh(void) { return m_irrAnimatedMesh; }

    WorldFile m_cWorldFile;

	protected:
	private:

	ISceneNode      *m_irrSceneNode;
	ISceneManager   *m_irrSceneManager;
  IVideoDriver    *m_irrVideoDriver;
  IrrlichtDevice  *m_irrDevice;

	IAnimatedMesh *m_irrAnimatedMesh;
	IAnimatedMeshSceneNode *m_irrAnimatedMeshSceneNode;

  char *m_strFilePath;
  char m_strFileName[128];

  int m_iPathLength;

  // Lighting related variables.
  SLight    *m_dynamicLight;
  SColorf   m_lightColor;
  f32       m_lightRadius;
  s32       m_lightID;
};

#endif // WORLD_MANAGER_H
