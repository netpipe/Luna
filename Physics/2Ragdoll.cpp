/* Written by: Marten Svanfeldt */
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btIDebugDraw.h"
#include "Ragdoll.h"

#ifndef M_PI// Enrico: Shouldn't these three variables be real constants and not defines?
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif


class RagDoll
{
	enum
	{
		BODYPART_PELVIS = 0,
		BODYPART_SPINE,BODYPART_HEAD,
		BODYPART_LEFT_UPPER_LEG,BODYPART_LEFT_LOWER_LEG,
		BODYPART_RIGHT_UPPER_LEG,BODYPART_RIGHT_LOWER_LEG,
		BODYPART_LEFT_UPPER_ARM,BODYPART_LEFT_LOWER_ARM,
		BODYPART_RIGHT_UPPER_ARM,BODYPART_RIGHT_LOWER_ARM,
		BODYPART_COUNT
	};

	enum
	{
		JOINT_PELVIS_SPINE = 0,     JOINT_SPINE_HEAD,
		JOINT_LEFT_HIP,             JOINT_LEFT_KNEE,
		JOINT_RIGHT_HIP,            JOINT_RIGHT_KNEE,
		JOINT_LEFT_SHOULDER,        JOINT_LEFT_ELBOW,
		JOINT_RIGHT_SHOULDER,       JOINT_RIGHT_ELBOW,
		JOINT_COUNT
	};

	btDynamicsWorld* m_ownerWorld;
	btCollisionShape* m_shapes[BODYPART_COUNT];
	btRigidBody* m_bodies[BODYPART_COUNT];
	btTypedConstraint* m_joints[JOINT_COUNT];
    btDiscreteDynamicsWorld* ownerWorld;


/* OLD ONE
	btRigidBody* localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
	{

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			shape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		m_ownerWorld->addRigidBody(body);

		return body;
	}
*/
btRigidBody*  localCreateRigidBody(float mass, const btTransform& startTransform,btCollisionShape* shape, ISceneNode *node)
{
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

    m_ownerWorld->addRigidBody(body);
   // m_cPhysics->push_back(body);
    return body;
}

public:
    Physics *m_cPhysics;

	RagDoll (btDiscreteDynamicsWorld* ownerWorld, const btVector3& positionOffset, IrrlichtDevice *m_irrDevice)
		: m_ownerWorld (ownerWorld)
	{

        IAnimatedMesh *mesh = m_irrDevice->getSceneManager()->getMesh("./data/sydney.md2");

       // m_irrDevice->getSceneManager()->getMeshManipulator()->scaleMesh(mesh,trackScale);

        IAnimatedMeshSceneNode *node = m_irrDevice->getSceneManager()->addAnimatedMeshSceneNode(mesh);


		//! Setup the geometry
		m_shapes[BODYPART_PELVIS] = new btCapsuleShape(btScalar(0.15), btScalar(0.20));
		m_shapes[BODYPART_SPINE] = new btCapsuleShape(btScalar(0.15), btScalar(0.28));
		m_shapes[BODYPART_HEAD] = new btCapsuleShape(btScalar(0.10), btScalar(0.05));
		m_shapes[BODYPART_LEFT_UPPER_LEG] = new btCapsuleShape(btScalar(0.07), btScalar(0.45));
		m_shapes[BODYPART_LEFT_LOWER_LEG] = new btCapsuleShape(btScalar(0.05), btScalar(0.37));
		m_shapes[BODYPART_RIGHT_UPPER_LEG] = new btCapsuleShape(btScalar(0.07), btScalar(0.45));
		m_shapes[BODYPART_RIGHT_LOWER_LEG] = new btCapsuleShape(btScalar(0.05), btScalar(0.37));
		m_shapes[BODYPART_LEFT_UPPER_ARM] = new btCapsuleShape(btScalar(0.05), btScalar(0.33));
		m_shapes[BODYPART_LEFT_LOWER_ARM] = new btCapsuleShape(btScalar(0.04), btScalar(0.25));
		m_shapes[BODYPART_RIGHT_UPPER_ARM] = new btCapsuleShape(btScalar(0.05), btScalar(0.33));
		m_shapes[BODYPART_RIGHT_LOWER_ARM] = new btCapsuleShape(btScalar(0.04), btScalar(0.25));

		// Setup all the rigid bodies
		btTransform offset; offset.setIdentity();
		offset.setOrigin(positionOffset);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(1.), btScalar(0.)));
    m_bodies[BODYPART_PELVIS] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_PELVIS],node);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(1.2), btScalar(0.)));
    m_bodies[BODYPART_SPINE] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_SPINE],node);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(1.6), btScalar(0.)));
    m_bodies[BODYPART_HEAD] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_HEAD],node);
    //!Legs
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.65), btScalar(0.)));
    m_bodies[BODYPART_LEFT_UPPER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_LEG],node);
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.2), btScalar(0.)));
    m_bodies[BODYPART_LEFT_LOWER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_LEG],node);
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.65), btScalar(0.)));
    m_bodies[BODYPART_RIGHT_UPPER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_LEG],node);
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.2), btScalar(0.)));
    m_bodies[BODYPART_RIGHT_LOWER_LEG] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_LEG],node);
    //!arms
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.35), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,M_PI_2);
    m_bodies[BODYPART_LEFT_UPPER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_ARM],node);
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(-0.7), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,M_PI_2);
    m_bodies[BODYPART_LEFT_LOWER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_ARM],node);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.35), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,-M_PI_2);
		m_bodies[BODYPART_RIGHT_UPPER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_ARM],node);

		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.7), btScalar(1.45), btScalar(0.)));
		transform.getBasis().setEulerZYX(0,0,-M_PI_2);
		m_bodies[BODYPART_RIGHT_LOWER_ARM] = localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_ARM],node);

		//! Setup some damping on the m_bodies
		for (int i = 0; i < BODYPART_COUNT; ++i)
		{
			m_bodies[i]->setDamping(0.05, 0.85);
			m_bodies[i]->setDeactivationTime(0.8);
			m_bodies[i]->setSleepingThresholds(1.6, 2.5);
		}

		//! Now setup the constraints
		btHingeConstraint* hingeC;
		btConeTwistConstraint* coneC;

		btTransform localA, localB;

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.15), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.15), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_SPINE], localA, localB);
		hingeC->setLimit(btScalar(-M_PI_4), btScalar(M_PI_2));
		m_joints[JOINT_PELVIS_SPINE] = hingeC;
		m_ownerWorld->addConstraint(m_joints[JOINT_PELVIS_SPINE], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,M_PI_2); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.30), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,-M_PI_2); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_HEAD], localA, localB);
		coneC->setLimit(M_PI_4, M_PI_4, M_PI_2);
		m_joints[JOINT_SPINE_HEAD] = coneC;
		m_ownerWorld->addConstraint(m_joints[JOINT_SPINE_HEAD], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,-M_PI_4*5); localA.setOrigin(btVector3(btScalar(-0.18), btScalar(-0.10), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,M_PI_4*5); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_LEFT_UPPER_LEG], localA, localB);
		coneC->setLimit(M_PI_4, M_PI_4, 0);
		m_joints[JOINT_LEFT_HIP] = coneC;
		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_HIP], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_LEG], *m_bodies[BODYPART_LEFT_LOWER_LEG], localA, localB);
		hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
		m_joints[JOINT_LEFT_KNEE] = hingeC;
		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_KNEE], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,M_PI_4); localA.setOrigin(btVector3(btScalar(0.18), btScalar(-0.10), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,-M_PI_4); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_RIGHT_UPPER_LEG], localA, localB);
		coneC->setLimit(M_PI_4, M_PI_4, 0);
		m_joints[JOINT_RIGHT_HIP] = coneC;
		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_HIP], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_LEG], *m_bodies[BODYPART_RIGHT_LOWER_LEG], localA, localB);
		hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
		m_joints[JOINT_RIGHT_KNEE] = hingeC;
		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_KNEE], true);


		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,M_PI); localA.setOrigin(btVector3(btScalar(-0.2), btScalar(0.15), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,-M_PI_2); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_LEFT_UPPER_ARM], localA, localB);
		coneC->setLimit(M_PI_2, M_PI_2, 0);
		m_joints[JOINT_LEFT_SHOULDER] = coneC;
		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_SHOULDER], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_ARM], *m_bodies[BODYPART_LEFT_LOWER_ARM], localA, localB);
		hingeC->setLimit(btScalar(-M_PI_2), btScalar(0));
		m_joints[JOINT_LEFT_ELBOW] = hingeC;
		m_ownerWorld->addConstraint(m_joints[JOINT_LEFT_ELBOW], true);



		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,0,0); localA.setOrigin(btVector3(btScalar(0.2), btScalar(0.15), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,0,-M_PI_2); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));
		coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_RIGHT_UPPER_ARM], localA, localB);
		coneC->setLimit(M_PI_2, M_PI_2, 0);
		m_joints[JOINT_RIGHT_SHOULDER] = coneC;
		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_SHOULDER], true);

		localA.setIdentity(); localB.setIdentity();
		localA.getBasis().setEulerZYX(0,M_PI_2,0); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));
		localB.getBasis().setEulerZYX(0,M_PI_2,0); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));
		hingeC =  new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_ARM], *m_bodies[BODYPART_RIGHT_LOWER_ARM], localA, localB);
		hingeC->setLimit(btScalar(-M_PI_2), btScalar(0));
		m_joints[JOINT_RIGHT_ELBOW] = hingeC;
		m_ownerWorld->addConstraint(m_joints[JOINT_RIGHT_ELBOW], true);
	}

	virtual	~RagDoll () {
		int i;
		//! Remove all constraints
		for ( i = 0; i < JOINT_COUNT; ++i)
		{
			m_ownerWorld->removeConstraint(m_joints[i]);
			delete m_joints[i]; m_joints[i] = 0;
		}
		//! Remove all bodies and shapes
		for ( i = 0; i < BODYPART_COUNT; ++i)
		{
			m_ownerWorld->removeRigidBody(m_bodies[i]);
			delete m_bodies[i]->getMotionState();
			delete m_bodies[i]; m_bodies[i] = 0;
			delete m_shapes[i]; m_shapes[i] = 0;
		}
	}
};

void RagdollDemo::registerIrrDevice(IrrlichtDevice &device) {    m_irrDevice = &device;}

void RagdollDemo::registerPhysics(Physics &physics)         {    m_cPhysics = &physics;  }

//void RagdollDemo::registerScene(Scene &scene)               {   m_cScene = &scene;  }


void RagdollDemo::initPhysics()
{
	//! Setup the basic world
    //setCameraDistance(btScalar(5.));
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	btVector3 worldAabbMin(-10000,-10000,-10000);
	btVector3 worldAabbMax(10000,10000,10000);
	m_broadphase = new btAxisSweep3 (worldAabbMin, worldAabbMax);

	m_solver = new btSequentialImpulseConstraintSolver;
//	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);

	//! Spawn one ragdoll
	btVector3 startOffset(1,20.5,-10);
	spawnRagdoll(startOffset);
//	startOffset.setValue(-1,-20.5,0);
//	spawnRagdoll(startOffset);
//	clientResetScene();
}

void RagdollDemo::spawnRagdoll(const btVector3& startOffset)
{
	RagDoll* ragDoll = new RagDoll (m_cPhysics->getDynamicsWorld(), startOffset,m_irrDevice);
	ragDoll->m_cPhysics = m_cPhysics;
	m_ragdolls.push_back(ragDoll);
}

void RagdollDemo::clientMoveAndDisplay()
{
	//!simple dynamics world doesn't handle fixed-time-stepping
//	float ms = getDeltaTimeMicroseconds();

//	float minFPS = 1000000.f/60.f;
//	if (ms > minFPS)
//		ms = minFPS;

//	if (m_cPhysics->getDynamicsWorld()) {
	//	m_cPhysics->getDynamicsWorld()->stepSimulation(ms / 1000000.f);
		//optional but useful: debug drawing
		m_cPhysics->getDynamicsWorld()->debugDrawWorld();
//	}
//	renderme();
}

void RagdollDemo::displayCallback() {
}

void RagdollDemo::keyboardCallback(unsigned char key, int x, int y) {
}

void	RagdollDemo::exitPhysics()
{
    int i;

  for (i=0;i<m_ragdolls.size();i++)
    {
		RagDoll* doll = m_ragdolls[i];
		delete doll;
	}
	//!cleanup in the reverse order of creation/initialization
	//!remove the rigidbodies from the dynamics world and delete them

  for (i=m_cPhysics->getDynamicsWorld()->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_cPhysics->getDynamicsWorld()->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
      if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_cPhysics->getDynamicsWorld()->removeCollisionObject( obj );
		delete obj;
	}

	//!delete collision shapes
  for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		delete shape;
	}
	//delete dynamics world
//	delete m_dynamicsWorld;
	//delete solver
	delete m_solver;
	//delete broadphase
	delete m_broadphase;
	//delete dispatcher
	delete m_dispatcher;
	delete m_collisionConfiguration;
}




