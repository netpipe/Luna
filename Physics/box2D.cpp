

#ifdef BOX2D2
#include "box2D.h"

//cbox2d test;

cbox2d::cbox2d(){};

cbox2d::~cbox2d(){};

void cbox2d::box2dMain(){
	//device->run();

	//	if (device->isWindowActive())
	//	{
//			u32 time = device->getTimer()->getTime();
//      driver->beginScene(true, true, SColor(255,100,101,140));
		//	driver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, video::SColor(255,120,102,136));

			/*
			First, we draw 3 sprites, using the alpha channel we
			created with makeColorKeyTexture. The last parameter
			specifies that the drawing method should use this alpha
			channel. The last-but-one parameter specifies a
			color, with which the sprite should be colored.
			(255,255,255,255) is full white, so the sprite will
			look like the original. The third sprite is drawn
			with the red channel modulated based on the time.
			*/

		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		position = body->GetPosition();
		float32 angle = body->GetAngle();
//		printf("%i",i);
		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);

//body->SetPosition(position);



	//	IGUIImage* test = env->addImage(driver->getTexture("../../media/irrlichtlogo2.png"),position2d<int>(position.x, position.y));
//		test->setRelativePosition(position2d<int>(position.x, position.y));
	//	test->setRoatation(angle);
			// draw fire & dragons background world
//			driver->draw2DImage(images, core::position2d<s32>(50,50),
//				core::rect<s32>(0,0,342,224), 0,
//				video::SColor(255,255,255,255), true);
//
//			// draw flying imp
//			driver->draw2DImage(images, core::position2d<s32>(164,125),
//				(time/500 % 2) ? imp1 : imp2, 0,
//				video::SColor(255,255,255,255), true);
//
//			// draw second flying imp with color cycle
//			driver->draw2DImage(images, core::position2d<s32>(270,105),
//				(time/500 % 2) ? imp1 : imp2, 0,
//				video::SColor(255,(time) % 255,255,255), true);

			/*
			Drawing text is really simple. The code should be self
			explanatory.
			*/

			// draw some text
//			if (font)
//				font->draw(L"This demo shows that Irrlicht is also capable of drawing 2D graphics.",
//					core::rect<s32>(130,10,300,50),
//					video::SColor(255,255,255,255));
//
//			// draw some other text
//			//if (font2)
//				font2->draw(L"Also mixing with 3d graphics is possible.",
//					core::rect<s32>(130,20,300,60),
//					video::SColor(255,time % 255,time % 255,255));

			/*
			Next, we draw the Irrlicht Engine logo (without
			using a color or an alpha channel). Since we slightly scale
			the image we use the prepared filter mode.
			*/

			driver->enableMaterial2D();
			driver->draw2DImage(images, core::rect<s32>(10,10,108,48),core::rect<s32>(354,87,442,118));
			driver->enableMaterial2D(false);

			/*
			Finally draw a half-transparent rect under the mouse cursor.
			*/
//			core::position2d<s32> m = device->getCursorControl()->getPosition();
//			driver->draw2DRectangle(video::SColor(100,255,255,255),
//				core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));
//
//env->drawAll();
//
//			driver->endScene();
//			//device->sleep(2);
//			usleep(10000);
//		}
	//}

}

//void cbox2d::registerdevice(IrrlichtDevice *device){
//
//}

int cbox2d::init(IrrlichtDevice *device)
{
	driver = device->getVideoDriver();

	const io::path mediaPath = "./" //getExampleMediaPath();



	//box2d init
//		B2_NOT_USED(argc);
//	B2_NOT_USED(argv);

//	// Define the gravity vector.
//	b2Vec2 gravity(0.0f, -10.0f);
//
//	// Construct a world object, which will hold and simulate the rigid bodies.
//	b2World world(gravity,true);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
    body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.1f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	timeStep = 1.0f / 60.0f;
	 velocityIterations = 6;
	 positionIterations = 2;


env = device->getGUIEnvironment();
//
//
//	images = driver->getTexture(mediaPath + "2ddemo.png");
//	driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));
//
//
//	font = device->getGUIEnvironment()->getBuiltInFont();
//	font2 =
//		//device->getGUIEnvironment()->getFont(mediaPath + "SpriteFonts/Font05_70_Normal.txt");
//		device->getGUIEnvironment()->getFont("./media/fonthaettenschweiler.bmp");
//
//
//
//
//	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
//	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;
//
//test = env->addImage(driver->getTexture("./media/irrlichtlogo2.png"),position2d<int>(position.x, position.y));
////test->setRelativePosition(position2d<int>(-20, -400));
//body->SetTransform(b2Vec2(110,-200),body->GetAngle());


//
//box2D();


}

#endif
