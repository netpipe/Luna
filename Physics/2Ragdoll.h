#ifndef RAGDOLLDEMO_H
#define RAGDOLL_H

//#include "DemoApplication.h"
#include "LinearMath/btAlignedObjectArray.h"
#include "Physics.h"

#include <irrlicht.h>
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;
class	btDynamicsWorld;
class RagdollDemo
{
    IrrlichtDevice *m_irrDevice;


	btAlignedObjectArray<class RagDoll*>    m_ragdolls;
	//!keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;
	btBroadphaseInterface*      	        m_broadphase;
	btCollisionDispatcher*      	        m_dispatcher;
	btConstraintSolver*	                    m_solver;
	btDefaultCollisionConfiguration*        m_collisionConfiguration;

public:
	void initPhysics();
	void exitPhysics();

	virtual ~RagdollDemo() {    exitPhysics();  };
	void spawnRagdoll(const btVector3&      startOffset);
	virtual void clientMoveAndDisplay();
	virtual void displayCallback();
	virtual void keyboardCallback(unsigned char key, int x, int y);
    void registerIrrDevice(IrrlichtDevice &device);
    void registerPhysics(Physics &physics);
//    Scene *m_cScene;
//    void registerScene(Scene &scene);
    void registerCamera(ICameraSceneNode *camera2);
    ICameraSceneNode* camera;
    Physics *m_cPhysics;


};

#endif
