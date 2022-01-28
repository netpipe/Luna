#include "../config.h"
#ifdef PYTHON
#ifdef VEGETATION
//#define ENVVEG
#ifdef ENVVEG

//todo not working at the moment

#include "../TerrainFactory/Vegetation/IGE_SceneNode_Vegetation.h"
using namespace IGE;


// to use a single model for all of this uncomment this line
 //#define USE_SINGLE_MODEL
//#define MODELNAME "../GAME/media/vegetation/_assets/_Models/_Foliage/Seven/wheat1.obj"
#define MODELNAME "../media/models/wheat1.obj"

//#include <conio.h>


// globals are easier for simple demos
//IrrlichtDevice*				device		= 0;
//video::IVideoDriver*		driver		= 0;
//scene::ISceneManager*		smgr		= 0;
//gui::IGUIEnvironment*		env			= 0;

// a few global variables specific to this demo
ITerrainSceneNode*			terrain = 0;		// the terrain to cover with grass
scene::ICameraSceneNode*	MainCamera = 0;			// the main FPS camera
scene::ICameraSceneNode*	Camera2 = 0;		// a test camera to check grass rendering through
bool						useLight = false;
bool						useFog = false;

// some view distances for each layer of vegetation
float VIEW_DISTANCE_GRASS		= 10000;
float VIEW_DISTANCE_FLOWERS		= 5000;
float VIEW_DISTANCE_SHRUBS		= 7000;
float VIEW_DISTANCE_SMALLTREES	= 8000;
float VIEW_DISTANCE_LARGETREES	= 10000;
float VIEW_DISTANCE_ROCKS		= 10000;

// the terrain scale
#define TERRAIN_SCALE		vector3df(400.f, 4.4f, 400.f)

// the vegetation layers
core::array<IGE_SceneNode_Vegetation*> vegetationLayers;

/// /////////////////////////////////////////////////////////////////////
//  create 6 new scenenodes, each derived from the IGE_SceneNode_Vegetation class
//  this allows us to setup each layer independently
//  I commented the first layer (grass) extensively but the others are the same just used for different scenenodes
/// /////////////////////////////////////////////////////////////////////

class IGE_SceneNode_Vegetation_Grass : public IGE_SceneNode_Vegetation
{
public:
	//! constructor - do nothing constructor
	IGE_SceneNode_Vegetation_Grass(ITerrainSceneNode* parent, stringc layoutimagefilename, float viewdistance, vector3df layoutrandomness, bool uselight, bool usefog, ISceneManager* smgr, s32 id)
		: IGE_SceneNode_Vegetation(parent, layoutimagefilename, viewdistance,layoutrandomness, uselight, usefog, smgr, id)
	{}

	//! destructor - do nothing destructor
	virtual ~IGE_SceneNode_Vegetation_Grass() {}

	// override to provide scenenode with layout values based on pixel colors
	// in this case we are just hard coding the values, but you could use the pizel color to determine each attribute
	virtual int			getDensityFromLayoutImageColor(SColor pixel) { return 200; }

	// override to provide scenenode with layout values based on pixel colors
	// in this case, if the pixel color green attribute is greater that 100 then return one of the grass templates
	// otherwise return -2 which is interpreted as no grass node in this area
	virtual int			getStyleFromLayoutImageColor(SColor pixel, int templatesize, vector3df pos)
	{
		if (pixel.getGreen() > 100) return getRandomInteger(1, templatesize) - 1;
		else return -2;
	}

	// override to provide scenenode with layout values based on pixel colors
	// in this case we are just hard coding the values, but you could use the pizel color to determine each attribute
	virtual vector3df   getRotationFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(0, getRandomFloat(0, 360), 0); }

	// override to provide scenenode with layout values based on pixel colors
	// in this case we are just hard coding the values, but you could use the pizel color to determine each attribute
	virtual vector3df   getScaleFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(3, getRandomInteger(1,10), 3); }
};

class IGE_SceneNode_Vegetation_Flowers : public IGE_SceneNode_Vegetation
{
public:
	//! constructor
	IGE_SceneNode_Vegetation_Flowers(ITerrainSceneNode* parent, stringc layoutimagefilename, float viewdistance, vector3df layoutrandomness, bool uselight, bool usefog, ISceneManager* smgr, s32 id)
		: IGE_SceneNode_Vegetation(parent, layoutimagefilename, viewdistance, layoutrandomness, uselight, usefog, smgr, id)
	{}

	//! destructor
	virtual ~IGE_SceneNode_Vegetation_Flowers() {}

	// override to provide scenenode with layout values based on pixel colors
	virtual int			getDensityFromLayoutImageColor(SColor pixel) { return 2000; }
	virtual int			getStyleFromLayoutImageColor(SColor pixel, int templatesize, vector3df pos) { return (getRandomInteger(1, templatesize)) - 1; }
	virtual vector3df   getRotationFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(0, getRandomFloat(0, 360), 0); }
	virtual vector3df   getScaleFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(3, 8, 3); }
};

class IGE_SceneNode_Vegetation_Shrubs : public IGE_SceneNode_Vegetation
{
public:
	//! constructor
	IGE_SceneNode_Vegetation_Shrubs(ITerrainSceneNode* parent, stringc layoutimagefilename, float viewdistance, vector3df layoutrandomness, bool uselight, bool usefog, ISceneManager* smgr, s32 id)
		: IGE_SceneNode_Vegetation(parent, layoutimagefilename, viewdistance, layoutrandomness, uselight, usefog, smgr, id)
	{}

	//! destructor
	virtual ~IGE_SceneNode_Vegetation_Shrubs() {}

	// override to provide scenenode with layout values based on pixel colors
	virtual int			getDensityFromLayoutImageColor(SColor pixel) { return 1000; }
	virtual int			getStyleFromLayoutImageColor(SColor pixel, int templatesize, vector3df pos) { return (getRandomInteger(1, templatesize)) - 1; }
	virtual vector3df   getRotationFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(0, getRandomFloat(0, 360), 0); }
	virtual vector3df   getScaleFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(5, 5, 5); }
};

class IGE_SceneNode_Vegetation_SmallTrees : public IGE_SceneNode_Vegetation
{
public:
	//! constructor
	IGE_SceneNode_Vegetation_SmallTrees(ITerrainSceneNode* parent, stringc layoutimagefilename, float viewdistance, vector3df layoutrandomness, bool uselight, bool usefog, ISceneManager* smgr, s32 id)
		: IGE_SceneNode_Vegetation(parent, layoutimagefilename, viewdistance, layoutrandomness, uselight, usefog, smgr, id)
	{}

	//! destructor
	virtual ~IGE_SceneNode_Vegetation_SmallTrees() {}

	// override to provide scenenode with layout values based on pixel colors
	virtual int			getDensityFromLayoutImageColor(SColor pixel) { return 3000; }
	virtual int			getStyleFromLayoutImageColor(SColor pixel, int templatesize, vector3df pos) { return (getRandomInteger(1, templatesize)) - 1; }
	virtual vector3df   getRotationFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(0, getRandomFloat(0, 360), 0); }
	virtual vector3df   getScaleFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(8, 8, 8); }
};

class IGE_SceneNode_Vegetation_LargeTrees : public IGE_SceneNode_Vegetation
{
public:
	//! constructor
	IGE_SceneNode_Vegetation_LargeTrees(ITerrainSceneNode* parent, stringc layoutimagefilename, float viewdistance, vector3df layoutrandomness, bool uselight, bool usefog, ISceneManager* smgr, s32 id)
		: IGE_SceneNode_Vegetation(parent, layoutimagefilename, viewdistance, layoutrandomness, uselight, usefog, smgr, id)
	{}

	//! destructor
	virtual ~IGE_SceneNode_Vegetation_LargeTrees() {}

	// override to provide scenenode with layout values based on pixel colors
	virtual int			getDensityFromLayoutImageColor(SColor pixel) { return 4000; }
	virtual int			getStyleFromLayoutImageColor(SColor pixel, int templatesize, vector3df pos) { return (getRandomInteger(1, templatesize)) - 1; }
	virtual vector3df   getRotationFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(0, getRandomFloat(0, 360), 0); }
	virtual vector3df   getScaleFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(14,14,14); }
};

class IGE_SceneNode_Vegetation_Rocks : public IGE_SceneNode_Vegetation
{
public:
	//! constructor
	IGE_SceneNode_Vegetation_Rocks(ITerrainSceneNode* parent, stringc layoutimagefilename, float viewdistance, vector3df layoutrandomness, bool uselight, bool usefog, ISceneManager* smgr, s32 id)
		: IGE_SceneNode_Vegetation(parent, layoutimagefilename, viewdistance, layoutrandomness, uselight, usefog, smgr, id)
	{}

	//! destructor
	virtual ~IGE_SceneNode_Vegetation_Rocks() {}

	// override to provide scenenode with layout values based on pixel colors
	virtual int			getDensityFromLayoutImageColor(SColor pixel) { return 5000; }
	virtual int			getStyleFromLayoutImageColor(SColor pixel, int templatesize, vector3df pos) { return (getRandomInteger(1, templatesize)) - 1; }
	virtual vector3df   getRotationFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(0, getRandomFloat(0, 360), 0); }
	virtual vector3df   getScaleFromLayoutImageColor(SColor pixel, int templatesize, int style, vector3df pos) { return vector3df(2, 2, 2); }
};
#endif
// create all of the vegetation
// in this case, we create 6 different scenenodes and add mesh templates to each
//void createVegetation()
//{
PyObject * Python::PyIrr_vegetation(PyObject * self,PyObject * args) //flag one better for speed less realistic
{
	float x,y,z;
	int t;
	//	char * t;
	PyArg_ParseTuple(args,"i",&t);
#ifdef ENVVEG
	    device->getFileSystem()->addFileArchive("../GAME/media/vegetation/_assets/_models/arteria3d_tropicalpack.zip");

Camera2 = smgr->addCameraSceneNode();
MainCamera = smgr->getActiveCamera() ;
	    	terrain = smgr->addTerrainSceneNode(
		"../GAME/media/vegetation/_assets/_terrain/heightmaps/terrain-plains.jpg",
		0,                  // parent node
		-1,                 // node id
		core::vector3df(0.f, 0.f, 0.f),     // position
		core::vector3df(0.f, 0.f, 0.f),     // rotation
		TERRAIN_SCALE,  // scale
		video::SColor(255, 255, 255, 255),   // vertexColor
		5,                  // maxLOD
		scene::ETPS_17,             // patchSize
		4                   // smoothFactor
	);

		terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain->setMaterialTexture(0, driver->getTexture("../GAMES/media/vegetation/_assets/_terrain/textures/aerial_grass_rock_diff_4k.jpg"));
	terrain->setMaterialTexture(1, driver->getTexture("../GAMES/media/vegetation/_assets/_terrain/textures/aerial_grass_rock_diff_4k.jpg"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
	terrain->scaleTexture(1.0f, 20.0f);

	// if ther is no terrain then bail
	if (!terrain)
	{
		printf("terrain node is not valid!");
		return;
	}

	// clear any existing vegetation layers
	for (u32 i = 0; i < vegetationLayers.size(); i++) vegetationLayers[i]->remove(); vegetationLayers.clear();


	// create the layer and add some templates to it
	IGE_SceneNode_Vegetation_Grass* grass = new IGE_SceneNode_Vegetation_Grass(terrain, "../GAME/media/vegetation/_assets/_Foliage/_LayoutImages/grasslayout.jpg",VIEW_DISTANCE_GRASS, vector3df(5, 0, 5), useLight, useFog, smgr, 0);
#ifdef USE_SINGLE_MODEL
	grass->addMeshTemplate(MODELNAME, 0);
#else
	grass->addMeshTemplate("../GAME/media/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/misc/trop_grass(region).x", 0);
#endif
	vegetationLayers.push_back(grass);

	// create the layer and add some templates to it
	IGE_SceneNode_Vegetation_Flowers* flowers = new IGE_SceneNode_Vegetation_Flowers(terrain, "../GAME/media/vegetation/_assets/_Foliage/_LayoutImages/flowerslayout.jpg",VIEW_DISTANCE_FLOWERS, vector3df(50, 0, 50), useLight, useFog, smgr, 0);
#ifdef USE_SINGLE_MODEL
	grass->addMeshTemplate(MODELNAME, 0);
#else
	flowers->addMeshTemplate("../GAME/media/vegetation/_assets/_Models/_Foliage/tropical/arteria3d_tropicalpack/flowers/flower 1.x", 0);
		flowers->addMeshTemplate("../GAME/media/vegetation/_assets/_Models/_Foliage/tropical/arteria3d_tropicalpack/flowers/flower 2.x", 0);
		flowers->addMeshTemplate("../GAME/media/vegetation/_assets/_Models/_Foliage/tropical/arteria3d_tropicalpack/flowers/flower 3.x", 0);
		flowers->addMeshTemplate("../GAME/media/vegetation/_assets/_Models/_Foliage/tropical/arteria3d_tropicalpack/flowers/flower 4.x", 0);
		flowers->addMeshTemplate("../GAME/media/vegetation/_assets/_Models/_Foliage/tropical/arteria3d_tropicalpack/flowers/flower 5.x", 0);
		flowers->addMeshTemplate("../GAME/media/vegetation/_assets/_Models/_Foliage/tropical/arteria3d_tropicalpack/flowers/flower 6.x", 0);
		flowers->addMeshTemplate("../GAME/media/vegetation/_assets/_Models/_Foliage/tropical/arteria3d_tropicalpack/flowers/flower 7.x", 0);
#endif
		vegetationLayers.push_back(flowers);

	// create the layer and add some templates to it
	IGE_SceneNode_Vegetation_Shrubs* shrubs = new IGE_SceneNode_Vegetation_Shrubs(terrain, "../GAME/media/vegetation/_assets/_Foliage/_LayoutImages/shrubslayout.jpg", VIEW_DISTANCE_SHRUBS, vector3df(500, 0, 500), useLight, useFog, smgr, 0);
#ifdef USE_SINGLE_MODEL
	grass->addMeshTemplate(MODELNAME, 0);
#else
	shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/fan plant.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/fan plant version 2.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/fan plant version 3.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant a.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant b.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant c.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant d.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant e.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant g.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant h.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant k.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant l.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant m.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant n.x", 0);
		shrubs->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/plants/plant n version2.x", 0);
#endif
		vegetationLayers.push_back(shrubs);

	// create the layer and add some templates to it
	IGE_SceneNode_Vegetation_SmallTrees* SmallTrees = new IGE_SceneNode_Vegetation_SmallTrees(terrain, "../GAME/media/vegetation/_assets/_Foliage/_LayoutImages/smalltreeslayout.jpg", VIEW_DISTANCE_SMALLTREES, vector3df(500, 0, 500), useLight, useFog, smgr, 0);
#ifdef USE_SINGLE_MODEL
	grass->addMeshTemplate(MODELNAME, 0);
#else
	SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/bananatree.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/bananatree version2.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/bananatree version2 b.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/floorpalm.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/floorpalm 2.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm1.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm2.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm3.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm3 B.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm3 C.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm4.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm5.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/palm6.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/worn palm.x", 0);
		SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/yuka.x", 0);
		//SmallTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/yuka 2.x", 0);
#endif
		vegetationLayers.push_back(SmallTrees);

	// create the layer and add some templates to it
	IGE_SceneNode_Vegetation_LargeTrees* LargeTrees = new IGE_SceneNode_Vegetation_LargeTrees(terrain, "../GAME/media/vegetation/_assets/_Foliage/_LayoutImages/largetreeslayout.jpg", VIEW_DISTANCE_LARGETREES, vector3df(500, 0, 500), useLight, useFog, smgr, 0);
#ifdef USE_SINGLE_MODEL
		grass->addMeshTemplate(MODELNAME, 0);
#else
		LargeTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/bananatree.x", 0);
		LargeTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/bananatree version2.x", 0);
		LargeTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/bananatree version2 b.x", 0);
		LargeTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/floorpalm.x", 0);
		LargeTrees->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/trees/floorpalm 2.x", 0);
#endif
		vegetationLayers.push_back(LargeTrees);

	// create the layer and add some templates to it
	IGE_SceneNode_Vegetation_Rocks* rocks = new IGE_SceneNode_Vegetation_Rocks(terrain, "../GAME/media/vegetation/_assets/_Foliage/_LayoutImages/rockslayout.jpg", VIEW_DISTANCE_ROCKS, vector3df(500, 0, 500), useLight, useFog, smgr, 0);
#ifdef USE_SINGLE_MODEL
		grass->addMeshTemplate(MODELNAME, 0);
#else
		rocks->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/rocks/LargeCoveRockA.x", 0);
		rocks->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/rocks/rock2.x", 0);
		rocks->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/rocks/LargeCoveRockB.x", 0);
	//	rocks->addMeshTemplate("../GAME/media/vegetation/_assets/_models/_foliage/tropical/arteria3d_tropicalpack/rocks/rock4.x", 0);
#endif
		vegetationLayers.push_back(rocks);

	// now process all of the layers
	// each layer will scan the layout image and create node positions, rotations and scales based on the layout image
	for (u32 i = 0; i < vegetationLayers.size(); i++)
		vegetationLayers[i]->processLayout();
#endif
		return Py_BuildValue("");
}


//	createVegetation();


//	createScene();

//	createGui();


#endif
#endif

