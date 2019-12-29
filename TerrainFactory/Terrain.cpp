#include "../config.h"
#ifdef TERRAIN

/// todo make some random trees for terrain
// patch grid for larger terrain or go procedural
// impliment planet handler with sphere mapping.
/// TODO aha

#include "irrlicht.h"
#include <math.h>
#include <sstream>
using namespace irr;
using namespace scene;
using namespace core;
#include "open-simplex-noise.h"

#ifdef TREES
    #include "./ProceduralTrees/kornJungle/Jungle.h"
#endif

#define LEAF_TYPE 0
#define NODE_TYPE 1
#define TILETHRESHOLD 10.0f


#include "Terrain.h"


using namespace std;

   SMeshBuffer* pNode1 = new SMeshBuffer();
   SMeshBuffer* glvertex = new SMeshBuffer();

Terrain::Terrain(){};

void Terrain::Init(){

     driver = m_irrDevice->getVideoDriver();
    smgr = m_irrDevice->getSceneManager();
    scene::ICameraSceneNode* camera = smgr->getActiveCamera();

};


Terrain::~Terrain(){
    //   for ( s32 i=0; i<NUM_TREE_DESIGNS; i++ )
    // {
    //   treeDesigns[i].Generator->drop();
    //}
 };


float Terrain::getHeight(float x, float y){
// 	int x, y;
	double value;
	double v0, v1, v2; /* values from different octaves. */
	#define FEATURE_SIZE 1
//	uint32_t rgb;
//	uint32_t image2d[HEIGHT][WIDTH];
//	uint32_t image3d[HEIGHT][WIDTH];
//	uint32_t image4d[HEIGHT][WIDTH];
	struct osn_context *ctx;

	open_simplex_noise(77374, &ctx);

//	for (y = 0; y < HEIGHT; y++) {
//		for (x = 0; x < WIDTH; x++) {
////#if defined(SINGLE_OCTAVE)
//			value = open_simplex_noise4(ctx, (double) x / FEATURE_SIZE,
//                                (double) y / FEATURE_SIZE, 0.0, 0.0)*800;
//#else
			/* Use three octaves: frequency N, N/2 and N/4 with relative amplitudes 4:2:1. */
			v0 = open_simplex_noise4(ctx, (double) x / FEATURE_SIZE / 4,
						(double) y / FEATURE_SIZE / 4, 0.0, 0.0);
			v1 = open_simplex_noise4(ctx, (double) x / FEATURE_SIZE / 2,
						(double) y / FEATURE_SIZE / 2, 0.0, 0.0);
			v2 = open_simplex_noise4(ctx, (double) x / FEATURE_SIZE / 1,
						(double) y / FEATURE_SIZE / 1, 0.0, 0.0);
			value = (v0 * 4 / 7.0 + v1 * 2 / 7.0 + v2 * 1 / 7.0) *5;
//#endif

//    int octaves=5;
//    float persistance =1;
//    int scale=3;  // noise scaler, not the same as patch scaler
//    float total = 0;
//
//    //amplify?
//    int ax=0;
//    int az=0;
//
//    for (int i=3; i < octaves; i++)
//    {
//        float frequency = pow(2.0f, i);
//        float amplitude = pow(persistance, i);
//        total += open_simplex_noise4(ctx, (((x+ax)/scale)/frequency),
//                               (((y+az)/scale)/ frequency), 0.0, 0.0) *amplitude;
//    }

//			rgb = 0x010101 * (uint32_t) ((value + 1) * 127.5);
//			image2d[y][x] = (0x0ff << 24) | (rgb);

//			value = open_simplex_noise2(ctx, (double) x / FEATURE_SIZE, (double) y / FEATURE_SIZE);
//			rgb = 0x010101 * (uint32_t) ((value + 1) * 127.5);
//			image3d[y][x] = (0x0ff << 24) | (rgb);
//
//			value = open_simplex_noise3(ctx, (double) x / FEATURE_SIZE, (double) y / FEATURE_SIZE, 0.0);
//			rgb = 0x010101 * (uint32_t) ((value + 1) * 127.5);
//			image4d[y][x] = (0x0ff << 24) | (rgb);
//		}
//	}
//	write_png_image("test2d.png", (unsigned char *) image2d, WIDTH, HEIGHT, 1);
//	write_png_image("test3d.png", (unsigned char *) image3d, WIDTH, HEIGHT, 1);
//	write_png_image("test4d.png", (unsigned char *) image4d, WIDTH, HEIGHT, 1);
	open_simplex_noise_free(ctx);
	return value;
 }


float Terrain::getHeight2(float x, float z){


//    int octaves=5;
//    float persistance =1;
//    int scale=3;  // noise scaler, not the same as patch scaler
//    float total = 0;
//
//    //amplify?
//    int ax=0;
//    int az=0;
//
//    for (int i=3; i < octaves; i++)
//    {
//        float frequency = pow(2.0f, i);
//        float amplitude = pow(persistance, i);
//        total += SimplexNoise1234::noise(((x+ax)/scale)/ frequency, ((z+az)/scale)/ frequency) * amplitude;
//    }
//
//    return (total);
};

ITerrainSceneNode* Terrain::Terrain2(vector3df t_position,vector3df t_scale,char *hmap,char *tex,char* dmap){

    vector3df t_rotation = vector3df(0,0,0);
		//scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(

		terrain = smgr->addTerrainSceneNode(
		hmap,
		0,					// parent node
		-1,					// node id
		t_position,		// position
		t_rotation,		// rotation
		t_scale,	// scale
		video::SColor ( 255, 255, 255, 255 ),	// vertexColor
		4,					// maxLOD
		scene::ETPS_17,				// patchSize
		4					// smoothFactor
		);

	terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	terrain->setMaterialTexture(0,
			driver->getTexture(tex));
	terrain->setMaterialTexture(1,
			driver->getTexture(dmap));

	terrain->setMaterialType(video::EMT_DETAIL_MAP);

	scene::CDynamicMeshBuffer* mesh = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);

	 terrain->getMeshBufferForLOD (*mesh ,2);

#ifdef PHYSICS
   btVector3 vertices[3];
   s32 j,k;
   btTriangleMesh *  mTriMesh = new btTriangleMesh();

   const irr::u32 vertexCount = mesh->getVertexCount();
   const irr::u32 indexCount = mesh->getIndexCount();

            irr::video::S3DVertex2TCoords* mb_vertices = (irr::video::S3DVertex2TCoords*)mesh->getVertexBuffer().getData();

   u16* mb_indices = mesh->getIndices();

   for(j=0;j<indexCount;j+=3)
   {
      for (k=0;k<3;k++)
      {
         s32 index = mb_indices[j+k];
         vertices[k] = btVector3(
            mb_vertices[index].Pos.X*terrain->getScale().X,
            mb_vertices[index].Pos.Y*terrain->getScale().Y,
            mb_vertices[index].Pos.Z*terrain->getScale().Z);
      }
      mTriMesh->addTriangle(vertices[0], vertices[1], vertices[2]);
   }
	mesh->drop();

   btCollisionShape* mShape = new btBvhTriangleMeshShape(mTriMesh, true);

   btDefaultMotionState* state =   new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
      btVector3(terrain->getPosition().X,terrain->getPosition().Y,terrain->getPosition().Z)));

   mRigidBody = new btRigidBody(0, state, mShape, btVector3(0, 0, 0));
   mRigidBody->setCollisionFlags(mRigidBody->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
   m_cPhysics->getDynamicsWorld()->addRigidBody(mRigidBody);
   #endif
return terrain;
}

void Terrain::Render( char *tex,vector3df terrainPosition,vector3df terrainRotation,vector3df terrainScale,int LOD){


    //INIT VARS
  //  vector3df terrainScale = terrainScale2; // vector3df(.1,.1,.1);
   // vector3df terrainPosition = vector3df(0,-1.0f,0);


 //       camera->setFarValue(5200);
        //camera->setPosition(core::vector3df(-500,100,-500));
 //   smgr->addLightSceneNode(NULL, core::vector3df(0,50,0), video::SColorf(255.0f, 255.0f, 255.0f), 500, -1);


    CreateGrid ( 65,65 ); // width and height + 1
    unsigned int Temp = ( 64/4 ) * ( 64/4 ); // devided into 4 sections ??
    unsigned int Temp2 = CalcNodeNum ( Temp,4 ); // max , min
    //!	{0,GridWidth,(GridHeight*(GridWidth+1)),((GridHeight)*(GridWidth+1))+GridWidth};
    unsigned int uiBoundingCoordinates[] = {0,64, ( 64* ( 65 ) ), ( ( 64 ) * ( 65 ) ) +64};

    // 		pNodeList = new NODE[Temp2];
    pNodeList = ( NODE* ) malloc ( sizeof ( NODE ) *Temp2 );
    CreateNode ( uiBoundingCoordinates,0,0 );
    free ( fVerts );
    generateLod ( LOD, pNodeList , 1, -10, -10 );
    f32 cubeSize = 5.f;

    // video::SColor cubeColour(255,255,255,255);
    glvertex->BoundingBox.reset(0,0,0);

    for (int i=0; i<glvertex->getVertexCount(); ++i)
    {
        glvertex->Vertices[i].Pos -= core::vector3df(0.5f, 0.5f, 0.5f);
        glvertex->Vertices[i].Pos *= cubeSize;
        glvertex->BoundingBox.addInternalPoint(glvertex->Vertices[i].Pos);
    }

    cubeMesh = new SMesh();
    cubeMesh->addMeshBuffer(glvertex);
    cubeMesh->recalculateBoundingBox();
    cubeSceneNode = smgr->addMeshSceneNode(cubeMesh);
    cubeSceneNode->setMaterialTexture(0, driver->getTexture(tex));

  //  free(uiList);  // causes crashing


//not working because i split terrain from vehicle tr identity in relation to car ?
#ifdef PHYSICS
    tr.setIdentity();
    tr.setOrigin(btVector3( terrainPosition.X,  terrainPosition.Y,  terrainPosition.Z));

    cubeSceneNode->setMaterialType(EMT_DETAIL_MAP);
    cubeSceneNode->setMaterialFlag(EMF_LIGHTING, true);
    //! POSITION
    cubeSceneNode->setScale(terrainScale);
    cubeSceneNode->setPosition(terrainPosition);
    //m_cScene->setGenericMaterial(cubeSceneNode, 0);

    IMeshBuffer *meshBuffer = cubeMesh->getMeshBuffer(0);
    btTriangleMesh *collisionMesh = new btTriangleMesh();
    m_cPhysics->convertIrrMeshBufferBtTriangleMesh(meshBuffer, collisionMesh, terrainScale);
    btBvhTriangleMeshShape *trackShape = new btBvhTriangleMeshShape(collisionMesh, true);

    mRigidBody = localCreateRigidBody(0, tr, trackShape, cubeSceneNode);
#endif
    //return cubeSceneNode;
   // return cubeSceneNode;
}


void Terrain::CreateNode(unsigned int Bounding[4],unsigned int ParentID,unsigned int NodeID){


    static unsigned int TotalTreeID = 0;
    unsigned int uiNodeType;
    float uiWidth,uiHeight;

    uiWidth = fVerts[(Bounding[1]*3)] - fVerts[(Bounding[0]*3)];
    uiHeight = fVerts[(Bounding[2]*3)+2] - fVerts[(Bounding[0]*3)+2];

    if ( 0.5*uiWidth==2 ){ uiNodeType = LEAF_TYPE; }else{ uiNodeType = NODE_TYPE; }

    NODE *pNode = &pNodeList[NodeID];
    pNode->uiID = NodeID;
    pNode->uiParentID = ParentID;

    for (int i=0; i < 4; i++)   		//!parrent NODE uiBounding aka texture coords
    {
        pNode->vBoundingCoordinates[i].X = fVerts[(Bounding[i]*3)];
        pNode->vBoundingCoordinates[i].Y = fVerts[(Bounding[i]*3)+1];
        pNode->vBoundingCoordinates[i].Z = fVerts[(Bounding[i]*3)+2];
    }

    pNode->bType = uiNodeType;
    if (uiNodeType == LEAF_TYPE){return;}
    else {
        unsigned int BoundingBox[4];
        TotalTreeID++;
        pNode->uiBranches[0] = TotalTreeID;
        BoundingBox[0] = Bounding[0]; //Top-Left i.e. b[0]
        BoundingBox[1] = Bounding[0]+((Bounding[1]-Bounding[0])/2); //Between b[0] and b[1]
        BoundingBox[2] = Bounding[0]+((Bounding[2]-Bounding[0])/2); //[between b[0] and b[2]
        BoundingBox[3] = Bounding[0]+((Bounding[2]-Bounding[0])/2)+((Bounding[1]-Bounding[0])/2); //middle of node
        CreateNode(BoundingBox,NodeID,TotalTreeID);
//************************************************************************************************************
        TotalTreeID++;
        pNode->uiBranches[1] = TotalTreeID;
        BoundingBox[0] = Bounding[0]+((Bounding[1]-Bounding[0])/2); // Between b[0] and b[1]
        BoundingBox[1] = Bounding[1]; //Top-Right i.e.  b[1]
        BoundingBox[2] = Bounding[0]+((Bounding[2]-Bounding[0])/2)+((Bounding[1]-Bounding[0])/2); //middle of node
        BoundingBox[3] = Bounding[0]+((Bounding[2]-Bounding[0])/2)+((Bounding[1]-Bounding[0])); //between b[1] & b[3]
        CreateNode(BoundingBox,NodeID,TotalTreeID);
//************************************************************************************************************
        TotalTreeID++;
        pNode->uiBranches[2] = TotalTreeID;
        BoundingBox[0] = Bounding[0]+((Bounding[2]-Bounding[0])/2); //between b[0] and b[2]
        BoundingBox[1] = Bounding[0]+((Bounding[2]-Bounding[0])/2)+((Bounding[1]-Bounding[0])/2); //middle of node
        BoundingBox[2] = Bounding[2]; //Bottom-Left i.e. b[2]
        BoundingBox[3] = Bounding[2]+((Bounding[3]-Bounding[2])/2); //between b[2] and b[3]
        CreateNode(BoundingBox,NodeID,TotalTreeID);
//************************************************************************************************************
        TotalTreeID++;
        pNode->uiBranches[3] = TotalTreeID;
        BoundingBox[0] = Bounding[0]+((Bounding[2]-Bounding[0])/2)+((Bounding[1]-Bounding[0])/2); //middle of node
        BoundingBox[1] = Bounding[0]+((Bounding[2]-Bounding[0])/2) + int(uiWidth); //between b[1] and b[3]
        BoundingBox[2] = Bounding[2]+((Bounding[3]-Bounding[2])/2); //between b[2] and b[3]
        BoundingBox[3] = Bounding[3]; //Bottom-Right i.e. b[3]
        CreateNode(BoundingBox,NodeID,TotalTreeID);
    }
}


void Terrain::generateLod(unsigned int LOD, NODE* pNode, const int TN ,const int XT, const int TZ){

    unsigned int count=1;
    unsigned int element=0;
   // LOD=3;
 if (LOD==0){
    for (unsigned int x=0; x < 4 ; x++)
    {
        //get the bounding coords
        unsigned int z=pNode[0].uiBranches[x];
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[1].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[1].X+XT,
                                                   pNode[z].vBoundingCoordinates[1].Z+TZ),
                                         pNode[z].vBoundingCoordinates[1].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[2].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[2].X+XT,
                                                   pNode[z].vBoundingCoordinates[2].Z+TZ),
                                         pNode[z].vBoundingCoordinates[2].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
    }
       return;
 }else if (LOD==1){
	count=1;

		for (unsigned int n=0; n < 4; n++){ // Unit this is dangerous, N is uninitialized

		 for (unsigned int x=0; x < 4; x++) {
			unsigned int z=pNode[count].uiBranches[x];

        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[1].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[1].X+XT,
                                                   pNode[z].vBoundingCoordinates[1].Z+TZ),
                                         pNode[z].vBoundingCoordinates[1].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[2].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[2].X+XT,
                                                   pNode[z].vBoundingCoordinates[2].Z+TZ),
                                         pNode[z].vBoundingCoordinates[2].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;

		 }
		 count+=85;
		}
	return;
 }else if (LOD==2){
		count=2;
		for (unsigned int n=0; n < 4; n++){
		 for (unsigned int g=0; g < 4; g++){
		  for (unsigned int x=0; x < 4 ; x++) {
			unsigned int z=pNode[(count+n)].uiBranches[x];
	        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[1].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[1].X+XT,
                                                   pNode[z].vBoundingCoordinates[1].Z+TZ),
                                         pNode[z].vBoundingCoordinates[1].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(255,33,33,255),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[2].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[2].X+XT,
                                                   pNode[z].vBoundingCoordinates[2].Z+TZ),
                                         pNode[z].vBoundingCoordinates[2].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f
                                         , video::SColor(0xffffffff),

                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
		   }
		   count+=21;
		  }
		}
	return;
 }else if(LOD==3){
		count=3;
		for (unsigned int n=0; n < 4; n++){
		 for (unsigned int d=0; d < 4; d++){
		  for (unsigned int g=0; g < 4; g++){
		   for (unsigned int x=0; x < 4 ; x++){
			unsigned int z=pNode[(count+d)].uiBranches[x];

	        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[1].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[1].X+XT,
                                                   pNode[z].vBoundingCoordinates[1].Z+TZ),
                                         pNode[z].vBoundingCoordinates[1].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(255,33,33,255),
                                         1.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[2].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[2].X+XT,
                                                   pNode[z].vBoundingCoordinates[2].Z+TZ),
                                         pNode[z].vBoundingCoordinates[2].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 1.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[3].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[3].X+XT,
                                                   pNode[z].vBoundingCoordinates[3].Z+TZ),
                                         pNode[z].vBoundingCoordinates[3].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         0.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;
        glvertex->Vertices.push_back(video::S3DVertex(
                                         pNode[z].vBoundingCoordinates[0].X+XT,
                                         getHeight(pNode[z].vBoundingCoordinates[0].X+XT,
                                                   pNode[z].vBoundingCoordinates[0].Z+TZ),
                                         pNode[z].vBoundingCoordinates[0].Z+TZ,
                                         0.0f, 1.0f, 0.0f, video::SColor(0xffffffff),
                                         1.0f, 0.0f));
        glvertex->Indices.push_back(element);
        element++;

		    };
		    count+=5;
		   };
		  };
		 count+=5;
		};

 }; // end of if
}


void Terrain::GenerateNode ( NODE *pNode, const int &TN,const int &XT,const int &TZ, const unsigned int &LOD ){

    generateLod ( 1, pNode, TN, XT, TZ );
}


void Terrain::CreateGrid(unsigned int w,unsigned int h){

    unsigned int total=0;

    unsigned int width = w;
    unsigned int height = h;

    fVerts = (float*)malloc((sizeof(float))*width*height*3); /* Allocate space for 											 vertices with an x,y and z*/

    for (unsigned int ctr=0;ctr<height;ctr++)
    {
        for (unsigned int ctr2=0;ctr2<width;ctr2++)
        {
            // Vertex number is total
            fVerts[total] =  ctr2;	// Vertex X component is ctr2
            fVerts[total+1] = 0;	// Vertex Y component is height field (0)
            fVerts[total+2] =  ctr;  // Vertex Z component is ctr
            total+=3;		// Increase total to be next vertex number
        }
    }
    total=0;

}


unsigned int Terrain::CalcNodeNum(unsigned int max,unsigned int min){


    int ctr=0;
    int var = 0;
    while (var==0)
    {
        ctr+=max;
        max=max/min;

        if (max==1)
        {
            var=1;
        }
    }
    ctr++;
    return ctr;
}

#ifdef PHYSICS
btRigidBody*	Terrain::localCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape, ISceneNode *node){

    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    btRigidBody* body = NULL;

    if (isDynamic)
    {
        shape->calculateLocalInertia(mass,localInertia);
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        body = new btRigidBody(mass, myMotionState, shape, localInertia);
    }
    else
    {
        body = new btRigidBody(mass,0,shape,localInertia);
    }

    body->setWorldTransform(startTransform);
    body->setUserPointer((void *)(node));

    m_cPhysics->getDynamicsWorld()->addRigidBody(body);
    m_cPhysics->push_back(body);
    return body;

}

void Terrain::registerPhysics(Physics &physics){

    m_cPhysics = &physics;
}
    #endif

void Terrain::registerIrrDevice(IrrlichtDevice &device){

    m_irrDevice = &device;
}





void Terrain::registerScene(Scene &scene){

    m_cScene = &scene;
}


/* for continious terrain
void Terrain::tick(const float &CamX, const float &CamY, const float &CamZ)
{
    SceneGraphNodes::BaseNode *activeNode = Azadi::getInstance()->getActiveNode();
    if (CamX > (extentX - TILETHRESHOLD))
    {
        for (std::deque<std::deque<SceneGraphNodes::TerrainNode*> >::iterator it = tNodes.begin(); it != tNodes.end(); ++it)
        {
            delete it->front();
            it->pop_front();
            // Generate a new Node relative to what's already here
            // SceneGraphNodes::TerrainNode *newNode = new SceneGraphNodes::TerrainNode(VBO, EBO, size);
            // Register the node with the scene graph
            // activeNode->addChild(newNode);
            // Push the new node into the back of the matrix
            // it->push_back(newNode);
        }
    }
    else if (CamX < (nextentX + TILETHRESHOLD))
    {
        for (std::deque<std::deque<SceneGraphNodes::TerrainNode*> >::iterator it = tNodes.begin(); it != tNodes.end(); ++it)
        {
            delete it->back();
            it->pop_back();
            // Generate a new Node relative to what's already here
            // SceneGraphNodes::TerrainNode *newNode = new SceneGraphNodes::TerrainNode(VBO, EBO, size);
            // Register the node with the scene graph
            // activeNode->addChild(newNode);
            // Push the new node into the front of the matrix
            // it->push_front(newNode);
        }
    }

    if (CamY > (extentY - TILETHRESHOLD))
    {
        std::deque<std::deque<SceneGraphNodes::TerrainNode*> >::iterator it = tNodes.begin();
        for (std::deque<SceneGraphNodes::TerrainNode*>::iterator ti = it->begin(); ti != it->end(); ++ti)
        {
            delete *ti;
        }
        tNodes.pop_front();
        std::deque<SceneGraphNodes::TerrainNode*> temp;
        for (unsigned long int i = 0; i < 4; ++i)
        {
            // Generate a new Node relative to what's already here
            // SceneGraphNodes::TerrainNode *newNode = new SceneGraphNodes::TerrainNode(VBO, EBO, size);
            // Register the node with the scene graph
            // activeNode->addChild(newNode);
            // Push the new node into the back of the matrix
            // temp.push_back(newNode);
        }
        tNodes.push_back(temp);
    }
    else if (CamY < (nextentY + TILETHRESHOLD))
    {
        std::deque<std::deque<SceneGraphNodes::TerrainNode*> >::iterator it = tNodes.end();
        --it;
        for (std::deque<SceneGraphNodes::TerrainNode*>::iterator ti = it->begin(); ti != it->end(); ++ti)
        {
            delete *ti;
        }
        tNodes.pop_back();
        std::deque<SceneGraphNodes::TerrainNode*> temp;
        for (unsigned long int i = 0; i < 4; ++i)
        {
            // Generate a new Node relative to what's already here
            // SceneGraphNodes::TerrainNode *newNode = new SceneGraphNodes::TerrainNode(VBO, EBO, size);
            // Register the node with the scene graph
            // activeNode->addChild(newNode);
            // Push the new node into the back of the matrix
            // temp.push_back(newNode);
        }
        tNodes.push_front(temp);
    }
}
*/

#ifdef TREES
CTreeSceneNode* Terrain::MakeTrees(vector3df aha,int treetype,char * action){
    // type of tree
    //make the treestack more global ?


if (treetype == 1 ){
//if (action == "Tree"){
CTreeGenerator* generator = 0;
//vector <CTreeSceneNode*> tree2;
CTreeSceneNode* tree2;

    video::ITexture* billTexture = 0;
    video::ITexture* leafTexture = 0;

struct STreeDesignFiles
{
    const c8* DesignFile;
    const c8* TreeTextureFile;
    const c8* LeafTextureFile;
    const c8* BillTextureFile;
};

struct STreeDesign
{
    CTreeGenerator* Generator;
    video::ITexture* TreeTexture;
    video::ITexture* LeafTexture;
    video::ITexture* BillTexture;
};

    const s32 NUM_TREE_DESIGNS = 4;

const STreeDesignFiles treeDesignFiles[NUM_TREE_DESIGNS] = {
        { "./data/trees/Oak.xml", "./data/textures/trees/OakBark.png", "./data/textures/trees/OakLeaf.png", "./data/textures/trees/OakBillboard.png" },
        { "./data/trees/Aspen.xml", "./data/textures/trees/AspenBark.png", "./data/textures/trees/AspenLeaf.png", "./data/textures/trees/AspenBillboard.png" },
        { "./data/trees/Pine.xml", "./data/textures/trees/PineBark.png", "./data/textures/trees/PineLeaf.png", "./data/textures/trees/PineBillboard.png" },
        { "./data/trees/Willow.xml", "./data/textures/trees/WillowBark.png", "./data/textures/trees/WillowLeaf.png", "./data/textures/trees/WillowBillboard.png" }
    };


STreeDesign treeDesigns [NUM_TREE_DESIGNS];
s32 currentTreeDesign = 0;
core::vector3df lightDir=vector3df(-100.0f,-10.0f,-100.0f);
s32 seed = 0;



        for ( s32 i=0; i<NUM_TREE_DESIGNS; i++ )
    {
        treeDesigns[i].Generator = new CTreeGenerator( smgr );
        io::IXMLReader* xml = m_irrDevice->getFileSystem()->createXMLReader( treeDesignFiles[i].DesignFile );
        treeDesigns[i].Generator->loadFromXML( xml );
        xml->drop();
        treeDesigns[i].TreeTexture = driver->getTexture( treeDesignFiles[i].TreeTextureFile );
        treeDesigns[i].LeafTexture = driver->getTexture( treeDesignFiles[i].LeafTextureFile );
        treeDesigns[i].BillTexture = driver->getTexture( treeDesignFiles[i].BillTextureFile );
    }
    video::E_MATERIAL_TYPE leafMaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
    leafMaterialType = (video::E_MATERIAL_TYPE) driver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles(
        "shaders/trees/leaves.vert",
        "main",
        EVST_VS_2_0,
        "shaders/trees/leaves.frag",
        "main", EPST_PS_2_0 , 0 , EMT_TRANSPARENT_ALPHA_CHANNEL_REF , 0 );

        //int treeType = treetype;
   // for(int i=0; i < 12; i++){
        tree2 = new CTreeSceneNode( smgr->getRootSceneNode(), smgr );
        seed = treetype; //rand()%4;
        tree2->setup( treeDesigns[seed].Generator, seed, treeDesigns[seed].BillTexture );
        tree2->getLeafNode()->setMaterialTexture( 0, treeDesigns[seed].LeafTexture );
        tree2->setMaterialTexture( 0, treeDesigns[seed].TreeTexture );

        bool lightsEnabled = 1;
        if ( lightsEnabled )
        tree2->getLeafNode()->applyVertexShadows( lightDir, 1.0f, 0.25f );

        tree2->getLeafNode()->setMaterialType( leafMaterialType );
        tree2->setMaterialFlag( video::EMF_LIGHTING, 0 );
        tree2->setScale(core::vector3df(0.5f,0.5f,0.5f));
        tree2->setPosition(core::vector3df(aha.X,aha.Y,aha.Z));
        tree2->setMaterialType(video::EMT_NORMAL_MAP_SOLID);
        tree2->drop(); //this was disabled not sure why
    //}
    //return pointer to treenode
    return (tree2);





//if (action = "jungle"){
// 	    jungleScene::Jungle *jungle =
//        new jungleScene::Jungle(
//                10240, // world size
//                8,// chunk size. "chunk size" * "chunk size" = "tree count per chunk"
//                16,// max tree dimension diameter
//                4,// tree circular detail
//                terr,
//                smgr,
//                -1);
//
//    smgr->getRootSceneNode()->addChild(jungle);
//    jungle->getMaterial(0).setTexture(0, driver->getTexture("./media/bark.png"));
//    jungle->getMaterial(0).setTexture(1, driver->getTexture("./media/bark_normal.png"));
//    jungle->getMaterial(0).MaterialType = EMT_NORMAL_MAP_SOLID;
//    jungle->getMaterial(0).Shininess = 0.0f;
//
//    jungle->getMaterial(1).setFlag(EMF_BACK_FACE_CULLING, false);
//    jungle->getMaterial(1).setTexture(0,driver->getTexture("./media/leaf.png"));
//    jungle->getMaterial(1).MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
//    // start growing trees
//
//    for(u32 i = 0 ; i < 1000 ; i++)
//    {
//        f32 cx = 100.0f + rand()%10040;
//        f32 cy = 100.0f + rand()%10040;
//        int type = rand()%8+1;
//        int seed = rand();
//        //trees
//        switch(type)
//        {
//            case(1):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                    16,// segment
//                    5,// min rot
//                    30,// max rot
//                    800.0f, // length
//                    8, // branching count
//                    7.5f, // max radius;
//                    3, // ground root
//                    200.0f, // leaf_width
//                    200.0f, // leaf height
//                    2, // leaf segments
//                    1.0, // leaf stiffness
//                    0, //leaf type
//                    0, // bark type
//                    seed, // seed
//                    true
//                    );
//                break;
//            }
//            case(2):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                    25,// segment
//                    0,// min rot
//                    15,// max rot
//                    800.0f, // length
//                    4, // branching count
//                    25.0f, // max radius;
//                    4, // ground root
//                    400.0f, // leaf_width
//                    400.0f, // leaf height
//                    2, // leaf segments
//                    1.0, // leaf stiffness
//                    1, //leaf type
//                    1, // bark type
//                    seed, // seed
//                    true
//                    );
//                break;
//            }
//            case(3):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                    32,// segment
//                    0,// min rot
//                    15,// max rot
//                    400.0f, // length
//                    4, // branching count
//                    5.0f, // max radius;
//                    3, // ground root
//                    100.0f, // leaf_width
//                    100.0f, // leaf height
//                    2, // leaf segments
//                    1.0, // leaf stiffness
//                    2, //leaf type
//                    2, // bark type
//                    seed, // seed
//                    true
//                    );
//                break;
//            }
//            case(4):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                    32,// segment
//                    5,// min rot
//                    20,// max rot
//                    400.0f, // length
//                    4, // branching count
//                    20.0f, // max radius;
//                    4, // ground root
//                    100.0f, // leaf_width
//                    100.0f, // leaf height
//                    2, // leaf segments
//                    1.0, // leaf stiffness
//                    3, //leaf type
//                    3, // bark type
//                    seed, // seed
//                    true
//                    );
//                break;
//            }
//            case(5):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                    12,// segment
//                    10,// min rot
//                    20,// max rot
//                    400.0f, // length
//                    4, // branching count
//                    7.5f, // max radius;
//                    3, // ground root
//                    100.0f, // leaf_width
//                    100.0f, // leaf height
//                    2, // leaf segments
//                    1.0, // leaf stiffness
//                    4, //leaf type
//                    4, // bark type
//                    seed, // seed
//                    true
//                    );
//                break;
//            }
//            case(6):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                    12,// segment
//                    15,// min rot
//                    20,// max rot
//                    400.0f, // length
//                    4, // branching count
//                    5.0f, // max radius;
//                    3, // ground root
//                    100.0f, // leaf_width
//                    100.0f, // leaf height
//                    2, // leaf segments
//                    1.0, // leaf stiffness
//                    5, //leaf type
//                    5, // bark type
//                    seed, // seed
//                    true
//                   );
//                break;
//            }
//            case(7):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                    14,// segment
//                    4,// min rot
//                    20,// max rot
//                    400.0f, // length
//                    4, // branching count
//                    10.0f, // max radius;
//                    3, // ground root
//                    100.0f, // leaf_width
//                    100.0f, // leaf height
//                    2, // leaf segments
//                    1.0, // leaf stiffness
//                    6, //leaf type
//                    6, // bark type
//                    seed, // seed
//                    true
//                   );
//                break;
//            }
//            case(8):
//            {
//                jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//                   20,// segment
//                   0,// min rot
//                   30,// max rot
//                   400.0f, // length
//                   6, // branching count
//                   10.0f, // max radius;
//                   3, // ground root
//                   200.0f, // leaf_width
//                   200.0f, // leaf height
//                   2, // leaf segments
//                   1.0, // leaf stiffness
//                   7, //leaf type
//                   7, // bark type
//                   seed, // seed
//                    true
//                   );
//                    break;
//            }
//        }
//    }
//    return Py_BuildValue("l",jungle);
//	}
//
//	if (action = "JTree"){
//		switch(type){
//				case(1):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//						16,// segment
//						5,// min rot
//						30,// max rot
//						800.0f, // length
//						8, // branching count
//						7.5f, // max radius;
//						3, // ground root
//						200.0f, // leaf_width
//						200.0f, // leaf height
//						2, // leaf segments
//						1.0, // leaf stiffness
//						0, //leaf type
//						0, // bark type
//						seed, // seed
//						true
//						);
//					break;
//				}
//				case(2):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//						25,// segment
//						0,// min rot
//						15,// max rot
//						800.0f, // length
//						4, // branching count
//						25.0f, // max radius;
//						4, // ground root
//						400.0f, // leaf_width
//						400.0f, // leaf height
//						2, // leaf segments
//						1.0, // leaf stiffness
//						1, //leaf type
//						1, // bark type
//						seed, // seed
//						true
//						);
//					break;
//				}
//				case(3):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//						32,// segment
//						0,// min rot
//						15,// max rot
//						400.0f, // length
//						4, // branching count
//						5.0f, // max radius;
//						3, // ground root
//						100.0f, // leaf_width
//						100.0f, // leaf height
//						2, // leaf segments
//						1.0, // leaf stiffness
//						2, //leaf type
//						2, // bark type
//						seed, // seed
//						true
//						);
//					break;
//				}
//				case(4):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//						32,// segment
//						5,// min rot
//						20,// max rot
//						400.0f, // length
//						4, // branching count
//						20.0f, // max radius;
//						4, // ground root
//						100.0f, // leaf_width
//						100.0f, // leaf height
//						2, // leaf segments
//						1.0, // leaf stiffness
//						3, //leaf type
//						3, // bark type
//						seed, // seed
//						true
//						);
//					break;
//				}
//				case(5):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//						12,// segment
//						10,// min rot
//						20,// max rot
//						400.0f, // length
//						4, // branching count
//						7.5f, // max radius;
//						3, // ground root
//						100.0f, // leaf_width
//						100.0f, // leaf height
//						2, // leaf segments
//						1.0, // leaf stiffness
//						4, //leaf type
//						4, // bark type
//						seed, // seed
//						true
//						);
//					break;
//				}
//				case(6):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//						12,// segment
//						15,// min rot
//						20,// max rot
//						400.0f, // length
//						4, // branching count
//						5.0f, // max radius;
//						3, // ground root
//						100.0f, // leaf_width
//						100.0f, // leaf height
//						2, // leaf segments
//						1.0, // leaf stiffness
//						5, //leaf type
//						5, // bark type
//						seed, // seed
//						true
//					   );
//					break;
//				}
//				case(7):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//						14,// segment
//						4,// min rot
//						20,// max rot
//						400.0f, // length
//						4, // branching count
//						10.0f, // max radius;
//						3, // ground root
//						100.0f, // leaf_width
//						100.0f, // leaf height
//						2, // leaf segments
//						1.0, // leaf stiffness
//						6, //leaf type
//						6, // bark type
//						seed, // seed
//						true
//					   );
//					break;
//				}
//				case(8):
//				{
//					jungle->addTreeAt(core::vector3df(cx, terrain->getHeight(cx,cy), cy),
//					   20,// segment
//					   0,// min rot
//					   30,// max rot
//					   400.0f, // length
//					   6, // branching count
//					   10.0f, // max radius;
//					   3, // ground root
//					   200.0f, // leaf_width
//					   200.0f, // leaf height
//					   2, // leaf segments
//					   1.0, // leaf stiffness
//					   7, //leaf type
//					   7, // bark type
//					   seed, // seed
//						true
//					   );
//						break;
//				}
//			}
//		}



}
  #endif
#endif















