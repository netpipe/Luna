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
