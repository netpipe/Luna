#include "../config.h"
#ifdef PHYSICS
#include "Physics.h"
/*testing
#include "../FileSystem/BulletBlendReader.h"
//#include "btBulletDynamicsCommon.h"
#include "../FileSystem/readblend/readblend.h"
#include "../FileSystem/readblend/blendtype.h"
#include "../FileSystem/blenderUp.h"
*/
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Physics* Physics::instance = NULL;


int debug_draw_bullet = 0;

class DebugDraw : public btIDebugDraw
{

    public:DebugDraw(irr::IrrlichtDevice* const device) :
    mode(DBG_NoDebug), driver(device->getVideoDriver()), logger(device->getLogger())
    {}

    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
    {
    //workaround to bullet's inconsistentdebug colors which are either from 0.0 - 1.0 or from 0.0 - 255.0
    irr::video::SColor newColor(255,(irr::u32)color[0], (irr::u32)color[1],(irr::u32)color[2]);

    if (color[0] <= 1.0 && color[0] > 0.0) newColor.setRed((irr::u32)(color[0]*255.0));

    if (color[1] <= 1.0 && color[1] > 0.0) newColor.setGreen((irr::u32)(color[1]*255.0));

    if (color[2] <= 1.0 && color[2] > 0.0) newColor.setBlue((irr::u32)(color[2]*255.0));

    this->driver->draw3DLine(irr::core::vector3df(from[0],from[1], from[2]),irr::core::vector3df(to[0], to[1],to[2]),newColor);
    }
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar
    distance, int lifeTime, const btVector3&  color)
    {
    static const irr::video::SColor
    CONTACTPOINT_COLOR2(255, 255, 255, 0);
    const btVector3 CONTACTPOINT_COLOR = btVector3(255, 255, 255);
    //bullet's are black :(
    //
    this->drawLine(PointOnB, PointOnB +normalOnB*distance, CONTACTPOINT_COLOR);
    const btVector3 to(PointOnB +normalOnB*distance);
    this->driver->draw3DLine(irr::core::vector3df(PointOnB[0],
    PointOnB[1], PointOnB[2]),irr::core::vector3df(to[0], to[1],to[2]),CONTACTPOINT_COLOR2);
    }
    void reportErrorWarning(const char* text){
    this->logger->log(text, irr::ELL_ERROR);
    }
    void draw3dText(const btVector3& location,const char* text) { }
    void setDebugMode(int mode) { this->mode =mode; }
    int getDebugMode() const { return this->mode; }
    private:
    int mode;
    irr::video::IVideoDriver* const driver;
    irr::ILogger* logger;
};



Physics::Physics() {
	m_irrDevice = NULL;

	instance = this;
	refId = 0;

	btVector3 worldAabbMin ( -2000,-2000,-2000 );// set the world min/max
	btVector3 worldAabbMax ( 2000,2000,2000 );
	int maxProxies = 32766;

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher ( collisionConfiguration );
	solver = new btSequentialImpulseConstraintSolver();
	broadphase = new btAxisSweep3 ( worldAabbMin, worldAabbMax, maxProxies );
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

//	dynamicsWorld->getDispatchInfo().m_enableSPU = true;
//	dynamicsWorld->setGravity ( btVector3 ( 0, -3.14, -0 ) ); //LHS y up

	simulationSpeed = (15); //15
	firstTick = true ;

//	DebugDraw debugDraw(m_irrDevice);
//debugDraw.setDebugMode(
//btIDebugDraw::DBG_DrawWireframe |
//	btIDebugDraw::DBG_DrawAabb |
//btIDebugDraw::DBG_DrawContactPoints |
////btIDebugDraw::DBG_DrawText |
////btIDebugDraw::DBG_DrawConstraintLimits |
//btIDebugDraw::DBG_DrawConstraints //|
//);
//dynamicsWorld->setDebugDrawer(&debugDraw);
//irr::video::SMaterial debugMat;
//debugMat.Lighting = false;
//const bool debug_draw_bullet = true;

}

Physics::~Physics() {
	clearBodies();
	delete dynamicsWorld;
	delete broadphase;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
}

btDiscreteDynamicsWorld *Physics::getDynamicsWorld(void)
{
  return dynamicsWorld;
}

btDefaultCollisionConfiguration *Physics::getCollisionConfiguration(void)
{
  return collisionConfiguration;
}

btCollisionDispatcher *Physics::getCollisionDispatcher(void)
{
  return dispatcher;
}

btSequentialImpulseConstraintSolver *Physics::getConstraintSolver(void)
{
  return solver;
}

void Physics::push_back(btRigidBody *body)
{
  m_rigidBodies.push_back(body);
}

void Physics::unregisterObject ( const unsigned long int &objectID ) { }

void Physics::tick() { }

void Physics::clearBodies(void) {
   /* taken from bullet vehicle physics
    	int i;
    	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--){
    		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
    		btRigidBody* body = btRigidBody::upcast(obj);
    		if (body && body->getMotionState())
    		{
    			delete body->getMotionState();
    		}
    		m_dynamicsWorld->removeCollisionObject( obj );
    		delete obj;
    	}
    */
	for(list<btRigidBody *>::Iterator iter = m_rigidBodies.begin(); iter != m_rigidBodies.end(); ++iter){

		btRigidBody *body = *iter;
		// Delete irrlicht node.
		ISceneNode *node = static_cast<ISceneNode *>(body->getUserPointer());
		node->remove();

		dynamicsWorld->removeRigidBody(body);

		delete body->getMotionState();
		delete body->getCollisionShape();
		delete body;
	}
	m_rigidBodies.clear();
}

void Physics::updatePhysics(u32 deltaTime) {

    float minFPS = 1000000.f/60.f;
	if (deltaTime * 0.001f > minFPS)
		deltaTime = minFPS;


	dynamicsWorld->stepSimulation(deltaTime* 0.001f * simulationSpeed );//deltaTime * 0.001f * simulationSpeed,2

	for(list<btRigidBody*>::Iterator iter = m_rigidBodies.begin(); iter !=  m_rigidBodies.end(); ++iter)
		updateRender(*iter);

//smgr drawall first
if (debug_draw_bullet)
{
//m_irrDevice->setMaterial(debugMat);
//driver->setTransform(irr::video::ETS_WORLD,irr::core::IdentityMatrix);
dynamicsWorld->debugDrawWorld();
}


}

void Physics::updateRender(btRigidBody *body) {
	ISceneNode *node = static_cast<ISceneNode *>(body->getUserPointer());

	// Set position.
	btVector3 point = body->getCenterOfMassPosition();
	node->setPosition(vector3df(
		(f32)point[0],
		(f32)point[1],
		(f32)point[2]));

	// Set rotation.
	btVector3 eulerRot;
	quaternionToEuler(body->getOrientation(), eulerRot);
	node->setRotation(vector3df(
		eulerRot[0],
		eulerRot[1],
		eulerRot[2]));
}


btVector3 Physics::RaycastWorld(const btVector3 Start, btVector3 End, btVector3 &Normal) {

                btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
//                RayCallback.m_collisionFilterMask = FILTER_CAMERA;

                // Perform raycast
                dynamicsWorld->rayTest(Start, End, RayCallback);
                if(RayCallback.hasHit()) {
                        End = RayCallback.m_hitPointWorld;
                        Normal = RayCallback.m_hitNormalWorld;
                        return RayCallback.m_hitPointWorld;
                }
    //    }

      //  return ;
}

btRigidBody *Physics::createBox(const btVector3 &pos, const btVector3 &scale, btScalar mass) {
	ISceneNode *node = m_irrDevice->getSceneManager()->addCubeSceneNode(1.0f);
	node->setScale(vector3df(
		(f32)scale[0],
		(f32)scale[1],
		(f32)scale[2]));
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	node->setMaterialTexture(0, m_irrDevice->getVideoDriver()->getTexture("data/textures/material/wood1_512.png"));

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(pos);

	btDefaultMotionState *motionState = new btDefaultMotionState(transform);

	// Create the shape.
	btVector3 halfExtents(scale[0] * 0.5f, scale[1] * 0.5f, scale[2] * 0.5f);
	btCollisionShape *shape = new btBoxShape(halfExtents);

	// Add mass.
	btVector3 localInertia;
	shape->calculateLocalInertia(mass, localInertia);

	// Create the rigid body object.
	btRigidBody *body = new btRigidBody(mass, motionState, shape, localInertia);

	// Store pointer to object.
	body->setUserPointer((void *)(node));

	// Add the object to the world.
	dynamicsWorld->addRigidBody(body);
	//m_rigidBodies.push_back(body);
	push_back(body);
}

 btRigidBody *Physics::createSphere(char *texture ,const btVector3 &pos, btScalar radius, btScalar mass) {
	ISceneNode *node = m_irrDevice->getSceneManager()->addSphereSceneNode(radius, 32);

	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	node->setMaterialTexture(0, m_irrDevice->getVideoDriver()->getTexture(texture));

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(pos);

	btDefaultMotionState *motionState = new btDefaultMotionState(transform);

	// Create the shape.
	btCollisionShape *shape = new btSphereShape(radius);

	// Add mass.
	btVector3 localInertia;
	shape->calculateLocalInertia(mass, localInertia);

	// Create the rigid body object.
	btRigidBody *body = new btRigidBody(mass, motionState, shape, localInertia);

	// Store pointer to object.
	body->setUserPointer((void *)(node));

	// Add the object to the world.
	dynamicsWorld->addRigidBody(body);
	//m_rigidBodies.push_back(body);
	push_back(body);

	return body;

}

void Physics::quaternionToEuler(const btQuaternion &quat, btVector3 &euler) {
	btScalar 	w = quat.getW(),
						x = quat.getX(),
						y = quat.getY(),
						z = quat.getZ();

	float wSquared = w * w,
				xSquared = x * x,
				ySquared = y * y,
				zSquared = z * z;

	euler.setX(atan2f(2.0f * (y * z + x * w), -xSquared - ySquared + zSquared + wSquared));
	euler.setY(asinf(-2.0f * (x * z - y * w)));
	euler.setZ(atan2f(2.0f * (x * y + z * w), xSquared - ySquared - zSquared + wSquared));

	euler *= RADTODEG;
}

void Physics::convertIrrMeshBufferBtTriangleMesh(IMeshBuffer *meshBuffer, btTriangleMesh *collisionMesh, vector3df scale)
{
  btVector3 triVerts[3];
  u16 *indices = meshBuffer->getIndices();

  if(meshBuffer->getVertexType() == EVT_STANDARD)
  {
    S3DVertex *verts = (S3DVertex *)meshBuffer->getVertices();
    for(u32 i = 0; i < meshBuffer->getIndexCount(); i+= 3)
    {
      triVerts[0] = btVector3(
        verts[indices[i]].Pos.X * scale.X,
        verts[indices[i]].Pos.Y * scale.Y,
        verts[indices[i]].Pos.Z * scale.Z);

      triVerts[1] = btVector3(
        verts[indices[i+1]].Pos.X * scale.X,
        verts[indices[i+1]].Pos.Y * scale.Y,
        verts[indices[i+1]].Pos.Z * scale.Z);

      triVerts[2] = btVector3(
        verts[indices[i+2]].Pos.X * scale.X,
        verts[indices[i+2]].Pos.Y * scale.Y,
        verts[indices[i+2]].Pos.Z * scale.Z);

      collisionMesh->addTriangle(triVerts[0], triVerts[1], triVerts[2]);
    }
  }
  else
  {
    S3DVertex2TCoords *verts = (S3DVertex2TCoords *)meshBuffer->getVertices();
    for(u32 i = 0; i < meshBuffer->getIndexCount(); i+= 3)
    {
      triVerts[0] = btVector3(
        verts[indices[i]].Pos.X * scale.X,
        verts[indices[i]].Pos.Y * scale.Y,
        verts[indices[i]].Pos.Z * scale.Z);

      triVerts[1] = btVector3(
        verts[indices[i+1]].Pos.X * scale.X,
        verts[indices[i+1]].Pos.Y * scale.Y,
        verts[indices[i+1]].Pos.Z * scale.Z);

      triVerts[2] = btVector3(
        verts[indices[i+2]].Pos.X * scale.X,
        verts[indices[i+2]].Pos.Y * scale.Y,
        verts[indices[i+2]].Pos.Z * scale.Z);

      collisionMesh->addTriangle(triVerts[0], triVerts[1], triVerts[2]);
    }
  }
  //printf("Converted Irrlicht mesh buffer to Bullet triangle mesh, numTriangles = %i\n", collisionMesh->getNumTriangles());
}

btRigidBody*	Physics::localCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape, ISceneNode *node)
{
// need to have a offset in here for the car gravity's
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0,0,0);
    btRigidBody* body = NULL;

   btTransform localTrans;
    localTrans.setIdentity();
    localTrans.setRotation( btQuaternion(btVector3(0,1,0), PI));
  //  localTrans.setOrigin(btVector3(0,0,0)); // moves chassi around and center of mass
     //   tr.setIdentity();
     //  tr.setRotation(btQuaternion(0,0,180)); // moves the buggy
      //  tr.setOrigin(btVector3(pos[0]+20,pos[1],pos[1]));
// localTrans.setOrigin(btVector3(pos.X,pos.Y,pos.Z-100));

  // m_carChassis->setCenterOfMassTransform(localTrans);
    //    localTrans.setOrigin(btVector3(pos.X+20,pos.Y,pos.Z)); // moves chassi around and center of mass
    //btVector3 pos= m_carChassis->getCenterOfMassPosition();
//        tr.setOrigin(btVector3(pos[0]+20,pos[1],pos[1]));
    //    shape->setCenterOfMassTransform(tr);



    if (isDynamic)
    {
        shape->calculateLocalInertia(mass,localInertia);  // move the shape around for center of gravity ?
        btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
        body = new btRigidBody(mass, myMotionState, shape, localInertia);
    }
    else
    {
        body = new btRigidBody(mass,0,shape,localInertia);
    }

    body->setWorldTransform(localTrans*startTransform);
    body->setUserPointer((void *)(node));

    getDynamicsWorld()->addRigidBody(body);
    push_back(body);
    return body;
}

void Physics::registerIrrDevice(IrrlichtDevice *device) {
	m_irrDevice = device;

}
#endif
