/*******************************************************************************
 Copyright (C) 2009 McCauley404@gmail.com
 First Person Weapon - zlib/BSD code by kat104
 ******************************************************************************/
#include "../config.h"
#ifdef FPS
#include "firstPersonWeapon.h"
#include "../Luna.h"

int aniSpeed=25;
int speedSkill=2;

//smgr->addLightSceneNode(NULL, core::vector3df(0,10,0), video::SColorf(5.0f, 255.0f, 255.0f), 2500, -1);

/*==============================================================================
  Constructor  Destructor
==============================================================================*/
firstPersonWeapon::~firstPersonWeapon()
{
  node->remove();
}

firstPersonWeapon::firstPersonWeapon(IrrlichtDevice* device, ICameraSceneNode* cam)
{
  camera = cam;
  device2 = device;
   smgr = device->getSceneManager();
  IAnimatedMesh* mesh = smgr->getMesh("../media/data/models/weapons/M4/1st_person/fpw_M4.b3d");
  node = smgr->addAnimatedMeshSceneNode(mesh);
  if (node)
  {
    //node->setPosition(vector3df(0,-1,0)); // done by artwork!
    node->setAnimationSpeed(25);
    camera->addChild(node);
  }
  mesh->drop();

  // particular values for M4 carbine
  nbshotsPerMagazine = 28;
  nbMagazines = 4;

  // and it is already loaded at the beginning
  ammoLeftInMagazine = nbshotsPerMagazine;

  //init receiver
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
       KeyDown[i] = false;

    LEFTBUTTONCLICKED = RIGHTBUTTONCLICKED = false;

  // show idle animation at startup
  this->idle();
  wasAiming=false;
}


///==============================================================================
///  events
///==============================================================================

bool firstPersonWeapon::OnEvent(const SEvent& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
  {
    KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
  }
  else if (event.EventType == EET_MOUSE_INPUT_EVENT)
  {
    if     (event.MouseInput.Event==EMIE_LMOUSE_PRESSED_DOWN) LEFTBUTTONCLICKED = true;
    else if(event.MouseInput.Event==EMIE_LMOUSE_LEFT_UP     ) LEFTBUTTONCLICKED = false;
    else if(event.MouseInput.Event==EMIE_RMOUSE_PRESSED_DOWN) RIGHTBUTTONCLICKED = true;
    else if(event.MouseInput.Event==EMIE_RMOUSE_LEFT_UP     ) RIGHTBUTTONCLICKED = false;
  }
#ifdef JOYSTICK
  		if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
			&& event.JoystickEvent.Joystick == 0)
		{
		//printf("joystickevent");
			JoystickState = event.JoystickEvent;
		}
#endif
  return false;
}
#ifdef JOYSTICK
	const SEvent::SJoystickEvent & firstPersonWeapon::GetJoystickState(void) const
	{
		return JoystickState;
	}

bool firstPersonWeapon::setjoystick(core::array<SJoystickInfo> *joystickInfo3)
{
joystickInfo2=joystickInfo3;
  return 1;
}
#endif

bool firstPersonWeapon::isKeyDown(EKEY_CODE keyCode) const
{
  return KeyDown[keyCode];
}


//
//	const SEvent::SJoystickEvent & GetJoystickState(void) const
//	{
//		return JoystickState;
//	}

//void firstPersonWeapon::OnRegisterSceneNode()
//    {
////        if (IsVisible)
//            smgr->registerNodeForRendering(this,ESRP_DEFAULT);
//
//        ISceneNode::OnRegisterSceneNode();
//}
//
//void firstPersonWeapon::render()
//{
//  update(device2->getTimer()->getTime());
//}
///==============================================================================
///EVENT LOOP
///==============================================================================
//  those static will screw calculations if there are several instances
void firstPersonWeapon::update(u32 now)
{
  static u32 nextAction = 0;
  static u32 nextShoot = 0;
  #ifdef JOYSTICK
const SEvent::SJoystickEvent & joystickData = this->GetJoystickState();
 #endif
  if (LEFTBUTTONCLICKED  && nextShoot < now) // shoot
  {
    shoot();
    nextShoot = now + 30;
  }

  else if (RIGHTBUTTONCLICKED && nextAction < now) // draw/holster
  {
    if (wasAiming){
        holster();
        wasAiming = false;
    //                    node->setAnimationSpeed(aniSpeed*speedSkill);  // makes gun holseter animation slow
    } else  {
        wasAiming = true;
        draw();
       // node->setAnimationSpeed(aniSpeed/speedSkill); // sets down draw animation
    }
    nextAction = now + 700;
  }

  else if (isKeyDown(KEY_KEY_R) && nextAction < now) // reload
  {
 if (ammoLeftInMagazine<28){
    reload();
    nextAction = now + (3000/speedSkill); // makes it lock the animation for given time
  }
  }


#ifdef JOYSTICK
	bool movedWithJoystick = false;
	const f32 MOVEMENT_SPEED = 5.f;
 const f32 DEAD_ZONE = 0.05f;
 core::vector3df nodePosition = node->getPosition();
//		if(joystickInfo2->size() > 0)
//		{
      		float moveHorizontal =
				(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
			if(fabs(moveHorizontal) > DEAD_ZONE){
				moveHorizontal = 0.f;
			//printf ("%f",moveHorizontal);
			}

			float moveVertical =
				(f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
			if(fabs(moveVertical) > DEAD_ZONE){
				moveVertical = 0.f;

		//printf ("%f",moveVertical);
		}

				if (joystickData.IsButtonPressed(3)){shoot();printf("button3");}
//		if (joystickData.IsButtonPressed(2)){printf("button2");}
//		if (joystickData.IsButtonPressed(1)){printf("button1");}
//		if (joystickData.IsButtonPressed(0)){printf("button0");}
//}

//			if(!core::equals(moveHorizontal, 0.f) || !core::equals(moveVertical, 0.f))
//			{
//				camera->setRotation(vector3df((MOVEMENT_SPEED * moveHorizontal),0,0));
//				camera->setRotation(vector3df(0,(MOVEMENT_SPEED * moveVertical),0));
//				//camera.Y += MOVEMENT_SPEED * moveVertical;
//				//movedWithJoystick = true;
//			}

//					if(!movedWithJoystick)
//		{ printf ("test");
//		core::position2di topScreenPosition(device2->getVideoDriver()->getScreenSize().Width / 2, 0);
//			// Create a ray through the mouse cursor.
//			core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
//				topScreenPosition, camera);
//
//
//			// And intersect the ray with a plane around the node facing towards the camera.
//			core::plane3df plane(nodePosition, core::vector3df(0, 0, -1));
//			core::vector3df mousePosition;
//			if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
//			{
//				// We now have a mouse position in 3d space; move towards it.
//				core::vector3df toMousePosition(mousePosition - nodePosition);
//				const f32 availableMovement = MOVEMENT_SPEED * 110.4;
//
//				if(toMousePosition.getLength() <= availableMovement)
//					nodePosition = mousePosition; // Jump to the final position
//				else
//					nodePosition += toMousePosition.normalize() * availableMovement; // Move towards it
//			}
//		}
//
//		smgr->getActiveCamera()->setPosition(nodePosition);
		#endif



      if (isKeyDown(    KEY_SPACE))
    {    //  m_cPlayer->jump();


            vector3df ha = camera->getAbsolutePosition();
      //  printf("Jump position: %f %f %f \n", pos[0], pos[1], pos[2]);
        camera->setPosition(vector3df( ha.X, ha.Y+40, ha.Z));
    }


}


void firstPersonWeapon::idle()
{
  action = FPW_IDLE;
  node->setFrameLoop(PLAYER_IDLE);
  node->setLoopMode(true);
  node->setAnimationSpeed(aniSpeed/speedSkill);
}


void firstPersonWeapon::draw()
{
  action = FPW_DRAW;
  camera->setFOV(1.f);
  node->setFrameLoop(PLAYER_DRAW);
  node->setLoopMode(false);
  node->setAnimationEndCallback(this);
    node->setAnimationSpeed(aniSpeed*speedSkill);
}


void firstPersonWeapon::holster()
{
  if (action == FPW_HOLSTER) return;
  action = FPW_HOLSTER;
  camera->setFOV(1.256f);
  node->setFrameLoop(PLAYER_HOLSTER);
  node->setLoopMode(false);
  node->setAnimationEndCallback(this);
  node->setAnimationSpeed(aniSpeed*speedSkill); //*scare effect :
}

void firstPersonWeapon::reload()
{
    if (action == FPW_RELOAD || nbMagazines == 0) return;
    //ammoBar->setValue((nbMagazines-1) * NBSHOTSPERMAGAZINE);

    //playSound("sound/M4/reload.wav", false);
    holster();
  if (--nbMagazines > 0)
  {
    action = FPW_RELOAD;
 //   wasAiming = (action==wasAiming);
    node->setFrameLoop(PLAYER_RELOAD);
    node->setLoopMode(false);
    node->setAnimationEndCallback(this);
  }
 // wasAiming=true;
}

bool firstPersonWeapon::shoot()
{
   node->setAnimationSpeed(aniSpeed);
  // if I am already shooting or reloading, dont shoot
  if (action == FPW_SHOOT_SHOULDER ||
      action == FPW_SHOOT_HIP ||
      action == FPW_RELOAD) return false;

  // ok now if there's at least one bullet in magazine,
  if (ammoLeftInMagazine > 0)
  {
    // show correct animation depending on if I am aiming or not
    if (action == FPW_AIM)
    {
      action = FPW_SHOOT_SHOULDER;
      node->setFrameLoop(PLAYER_SHOOT_SHOULDER);
    }
    else
    {
      action = FPW_SHOOT_HIP;
      node->setFrameLoop(PLAYER_SHOOT_HIP);
    }
    node->setLoopMode(false);
    node->setAnimationEndCallback(this);
 //   #define FPSShoot
#ifdef FPSShoot
///start of bullet stuff

//   if(q3levelmesh) q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0));
//    scene::ITriangleSelector* selector = 0;
//    q3node->setMaterialFlag(video::EMF_LIGHTING, true);
//    if(q3node)
//    {
//        q3node->setScale(core::vector3df(1.0, 1.0, 1.0));
//        selector = smgr->createOctTreeTriangleSelector(q3levelmesh->getMesh(0), q3node, 128);
//        q3node->setTriangleSelector(selector);
//        selector->drop();
//    }

        // shootTime = device->getTimer()->getTime() + 100;
         //Find intersection point
         ISceneNode* outNode;
         core::line3d<f32> line;
         core::vector3df intersection;
         core::triangle3df tri;
         line.start = camera->getPosition();
         line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;

         if (smgr->getSceneCollisionManager()->getCollisionPoint(line, selector, intersection, tri,outNode))
         {
            //Setup decal sprite
            decals[nextDecal]->Setup(tri,intersection);
            nextDecal++;
            if (nextDecal >= MAX_DECALS)
               nextDecal = 0;
         }
/// end
#endif

    // playSound("sound/M4/shoot.wav");

    // emit particules

    // throw a bullet

    // remove bullet from chamber
    ammoLeftInMagazine--;

    // create bullet
        //Muzzle Flash
        ISceneNode*bnode;
        vector3df bpos=camera->getAbsolutePosition();
        int randx=rand()%20;
        int randy=rand()%10;
        int randgun=rand()%3;
        u32 time;
        if (!wasAiming)
        {
            bnode = smgr->addBillboardSceneNode(camera,core::dimension2d<f32>(randx,randy),vector3df(1.f,-3,12) );
             time = 333;
        }
        else
        {    bnode = smgr->addBillboardSceneNode(camera,core::dimension2d<f32>(randx,randy),vector3df(0,0,42) );
        time = 333;
        }
            bnode->setMaterialFlag(video::EMF_LIGHTING, false);
            bnode->setMaterialTexture(0, device2->getVideoDriver()->getTexture("data/textures/muzzleflash.tga"));
            bnode->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

            bnode->setRotation(vector3df(90+randgun,10,180+randgun));// was gunnode i changed it to bnode

            scene::ISceneNodeAnimator* anim;
            anim = smgr->createDeleteAnimator(time);
            bnode->addAnimator(anim);
            anim->drop();

//scene::ISceneNode* what = smgr->addLightSceneNode(NULL, core::vector3df(0,10,10), video::SColorf(5.0f, 255.0f, 255.0f), 1000, -1);

    // spawn one empty shell

 //   printf("%d\n", ammoLeftInMagazine);
    return true;
  }
  // no ammo left in magazine!
  else
  {
      reload();
    //playSound("sound/clic.wav");
  }
  return false;
}



void firstPersonWeapon::OnAnimationEnd(IAnimatedMeshSceneNode* node)
{
  if (action == FPW_DRAW)
  {
    action = FPW_AIM;
    node->setFrameLoop(PLAYER_AIMING);
    node->setLoopMode(true);
            node->setAnimationSpeed(aniSpeed/2); // play the gunsights slow
  }

  else if (action == FPW_SHOOT_SHOULDER)
  {
    action = FPW_AIM;
    node->setFrameLoop(PLAYER_AIMING);
    node->setLoopMode(true);
 //   idle(); //unless scared or rushe
  }

  else if (action == FPW_SHOOT_HIP) idle();

  else if (action == FPW_HOLSTER) ;//idle();

  else if (action == FPW_RELOAD)
  {
    //NOW gun is ready
    ammoLeftInMagazine = nbshotsPerMagazine;
    //magazineBar->setValue(ammoLeftInMagazine);

    if (wasAiming)
    {
        draw();
        action = FPW_AIM;
        node->setFrameLoop(PLAYER_AIMING);
        node->setAnimationSpeed(aniSpeed);
    }
    else
    {
        action = FPW_IDLE;
        node->setFrameLoop(PLAYER_IDLE);
        node->setAnimationSpeed(aniSpeed);
    }

    node->setLoopMode(true);
    wasAiming = false;
  }
}



u8 firstPersonWeapon::getAmmo()
{
  return ammoLeftInMagazine;
}





#endif
