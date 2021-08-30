#ifdef BOX2DLITE

#include <string.h>
//#include <GL/glut.h>
#include <stdio.h>

#include "./Box2D_Lite/World.h"
#include "./Box2D_Lite/Body.h"
#include "./Box2D_Lite/Joint.h"

namespace
{
	Body bodies[200];
	Joint joints[100];

	float timeStep = 1.0f / 60.0f;
	int iterations = 10;

	Vec2 gravity(0.0f, 1000.0f);

	int numBodies = 0;
	int numJoints = 0;
	int demoIndex = 0;
	World world(gravity, iterations);
}

		Body* b1;


void InitDemo(int index)
{
	world.Clear();
	numBodies = 0;
	numJoints = 0;
printf("box2ddemo initializer\n");
}

#endif









#ifdef BOX2D
#include <irrlicht.h>

#include "Box2D/Box2D.h"
#include <stdio.h>
#include <unistd.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class cbox2d
{

box2d();
~box2d();
public:
void init(IrrlichtDevice *device);
void box2dMain();

IrrlichtDevice *device;
video::IVideoDriver* driver;
video::ITexture* images;
IGUIEnvironment* env;

IGUIImage* test;
b2Vec2 position;

	float32 timeStep ;
	int32 velocityIterations ;
	int32 positionIterations ;
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 40.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);
	b2Body* body ;
	core::rect<s32> imp1(349,15,385,78);
	core::rect<s32> imp2(387,15,423,78);
		gui::IGUIFont* font ;
	gui::IGUIFont* font2;

}

/*
That's all. I hope it was not too difficult.
**/

#endif
