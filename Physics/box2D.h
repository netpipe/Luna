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

	Vec2 gravity(0.0f, -10.0f);

	int numBodies = 0;
	int numJoints = 0;

	World world(gravity, iterations);
}

void Demo1(Body* b, Joint* j)
{
	b->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b->position.Set(0.0f, -0.5f * b->width.y);
	world.Add(b);
	++b; ++numBodies;

	b->Set(Vec2(1.0f, 1.0f), 200.0f);
	b->position.Set(0.0f, 4.0f);
	world.Add(b);
	++b; ++numBodies;
}

// A simple pendulum
void Demo2(Body* b, Joint* j)
{
	Body* b1 = b + 0;
	b1->Set(Vec2(100.0f, 20.0f), FLT_MAX);
	b1->friction = 0.2f;
	b1->position.Set(0.0f, -0.5f * b1->width.y);
	b1->rotation = 0.0f;
	world.Add(b1);

	Body* b2 = b + 1;
	b2->Set(Vec2(1.0f, 1.0f), 100.0f);
	b2->friction = 0.2f;
	b2->position.Set(9.0f, 11.0f);
	b2->rotation = 0.0f;
	world.Add(b2);

	numBodies += 2;

	j->Set(b1, b2, Vec2(0.0f, 11.0f));
	world.Add(j);

	numJoints += 1;
}

//void (*demos[])(Body* b, Joint* j) = {Demo1, Demo2, Demo3, Demo4, Demo5, Demo6, Demo7, Demo8, Demo9};
//char* demoStrings[] = {
//	"Demo 1: A Single Box",
//	"Demo 2: Simple Pendulum",
//	"Demo 3: Varying Friction Coefficients",
//	"Demo 4: Randomized Stacking",
//	"Demo 5: Pyramid Stacking",
//	"Demo 6: A Teeter",
//	"Demo 7: A Suspension Bridge",
//	"Demo 8: Dominos",
//	"Demo 9: Multi-pendulum"};

void InitDemo(int index)
{
	world.Clear();
	numBodies = 0;
	numJoints = 0;

//    demoIndex = index;
//	demos[index](bodies, joints);
}

void SimulationLoop()
{


    world.Step(timeStep);
    printf("test32");
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
