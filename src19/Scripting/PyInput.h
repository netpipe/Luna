#ifndef PYMAIN_H_INCLUDED
#define PYMAIN_H_INCLUDED




void Python::CheckKeyStates(){
    #ifdef BITCLOUD
            clouds->render();
            #endif

#ifdef CHOPPER
if (chopperEnabled){
        vector3df ha = chopperControl->Node->getAbsolutePosition();
        //  printf("Jump position: %f %f %f \n", pos[0], pos[1], pos[2]);
        camera->setPosition(vector3df( ha.X, ha.Y+40, ha.Z));
       chopperControl->checkKey();
        chopperControl->update();
    }
#endif

            #ifdef occlusion
                if (bOcclusion){
                RenderMan->updateCulling();
                }
            #endif

    if (mEvent.getKeyState(    KEY_ESCAPE))
                    {mEvent.Quit = true;}


    if (mEvent.getKeyState(    KEY_SPACE))    //SPACEBAR
    {    //  m_cPlayer->jump();
            vector3df ha = camera->getAbsolutePosition();
      //  printf("Jump position: %f %f %f \n", pos[0], pos[1], pos[2]);
        camera->setPosition(vector3df( ha.X, ha.Y+40, ha.Z));
     //   camera->setTarget(vector3df(1000,1000,1000));
    }

#define BULLETCAR  // needtofix global defines should not be here
    #ifdef BULLETCAR
    if (bCar){
    if (mEvent.getKeyState(    KEY_KEY_P))
    {
        btVector3 pos = m_cVehicle->getVehiclePosition();
        vector3df ha = vector3df(pos[0], pos[1]+10, pos[2]);
        printf("Vehicle position: %f %f %f \n", pos[0], pos[1], pos[2]);
        camera->setPosition(vector3df( ha.X, ha.Y, ha.Z));
    }

    if (mEvent.getKeyState(    KEY_KEY_8))
    {
        vector3df ha = camera->getPosition();
        m_cVehicle->setPosition(vector3df( ha.X, ha.Y, ha.Z));
    }

    if (mEvent.getKeyState(    KEY_KEY_1))
    {
        vector3df pos = camera->getPosition();
        vector3df scl = vector3df(1,1,1);
        luna->m_cPhysics->createBox( btVector3(pos.X, pos.Y, pos.Z), btVector3(scl.X, scl.Y, scl.Z), 10); //weight
    }



  if(bDecals){
        btVector3 Normal;
//      vector3df pos = camera->getPosition();
        vector3df upvect = camera->getUpVector();
        vector3df target = camera->getTarget();

        core::line3d<f32> line;
		line.start = camera->getPosition();
		line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;



        btVector3 rayHit = luna->m_cPhysics->RaycastWorld(btVector3(line.start.X, line.start.Y, line.start.Z),btVector3(line.end.X, line.end.Y, line.end.Z),Normal);
        printf("ray position position: %f %f %f \n", rayHit[0], rayHit[1], rayHit[2]);
        printf("hit normal vector: %f %f %f \n", Normal[0], Normal[1], Normal[2]);

#ifdef DECALS2

///just testing
//        if (yesim)
//        {
//             bill = smgr->addBillboardSceneNode();
//             yesim = false;
//        }
//        bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
//        bill->setMaterialTexture(0, driver->getTexture("./media/particle.bmp"));
//        bill->setMaterialFlag(video::EMF_LIGHTING, false);
//        bill->setMaterialFlag(video::EMF_ZBUFFER, false);
//        bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
////        bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it
//        bill->setPosition(vector3df(rayHit[0], rayHit[1], rayHit[2]));
     //    if (smgr->getSceneCollisionManager()->getCollisionPoint(line, selector, intersection, tri,outNode))
     //    {
            //Setup decal sprite


         if ( rayHit[0] != 0)
         {
             vector3df hitsend = vector3df(rayHit[0], rayHit[1], rayHit[2]);
             vector3df norm = vector3df(Normal[0], Normal[1], Normal[2]);

            decals[nextDecal]->VNSetup(norm,hitsend);
            nextDecal++;
            if (nextDecal >= MAX_DECALS)
               nextDecal = 0;
         }
#endif

//!Decal Manager
#ifdef DECALS
                 // Create a decal
        irr::core::vector3df position = irr::core::vector3df(80, 80, 80);
        irr::core::vector3df dimension = irr::core::vector3df(10, 10, 10);
        irr::core::vector3df normal = irr::core::vector3df(0, 1, 0);
        irr::f32 textureRotation = 40;
        //irr::scene::ISceneNode* parent = 0;
        irr::f32 lifeTime = 40;
        irr::f32 distance = 1111;
        //Position to place the decal        //Dimension of decal        //Orientation of the decal        //Rotation in degrees        //Parent        //Time to life        //Max viewing distance


            scene::IMeshSceneNode* sphere = smgr->addSphereSceneNode(5.f, 100);
            sphere->setPosition(core::vector3df(0, 10, 0));
            sphere->setScale(core::vector3df(20, 20, 20));
            decalManager->addMesh(sphere);
            //sphere->setMaterialFlag(video::EMF_LIGHTING, true);

    bool useCameraNormal=1;
        irr::core::vector3df sizes = irr::core::vector3df(10, 10, 10);
        #ifdef irrlicht17
   				 const irr::scene::ISceneNode* outNode; // Change to 'const scene::ISceneNode* outNode;' for Irrlicht 1.7.2
        #else
                        irr::scene::ISceneNode* outNode; // Change to 'const scene::ISceneNode* outNode;' for Irrlicht 1.7.2
        #endif
				  irr::core::line3d<f32> line3;
				core::vector3df collisionPoint;
				core::triangle3df triangle;
				line3.start = smgr->getActiveCamera()->getAbsolutePosition();
				line3.end = smgr->getActiveCamera()->getTarget();
				scene::ITriangleSelector* selector = decalManager->getMetaTriangleSelector();

				if (smgr->getSceneCollisionManager()->getCollisionPoint(line3, selector, collisionPoint, triangle, outNode)) {
					core::vector3df normal = triangle.getNormal();
					if (useCameraNormal) {
						normal = line3.start - line3.end;
					}
					irr::scene::ISceneNode* parent = 0;


					if(1) {
						parent = sphere;
					}

//					decalManager->addDecal("media/decal.png", collisionPoint, irr::core::vector3df(sizes, sizes, sizes), normal, rotation, parent, lifetime, distance);
                decalManager->addDecal("./data/textures/bullet.png", collisionPoint, dimension, normal, textureRotation, sphere, lifeTime, distance);
      #endif
  }
}
//device->sleep(5,0);


    if (mEvent.getKeyState(    KEY_KEY_4))    //SPACEBAR
    {
        vector3df pos = camera->getPosition();
        vector3df scl = vector3df(1,1,1);
        btRigidBody *had = luna->m_cPhysics->createBox( btVector3(pos.X, pos.Y, pos.Z),
                                                                btVector3(scl.X, scl.Y, scl.Z), 10); //weight
                                                                had->setLinearVelocity(btVector3(8000,0,1));
    }

    if (mEvent.getKeyState(    KEY_SPACE))    //SPACEBAR
                    {m_cVehicle->brake();   }

    if (mEvent.getKeyState(    KEY_KEY_2))
    {
        //if ( icount > 15){ //sphere limiter
            vector3df pos = camera->getPosition();
            vector3df rot = camera->getRotation();
            bingo=1;
            if (bingo) { // suposed to only create 1 sphere then transport you to it if its made already
                ha2 = luna->m_cPhysics->createSphere( btVector3(pos.X, pos.Y, pos.Z),2,5);
                //ha2->setAngularVelocity(btVector3(400,400,400));
                bingo= false;
            } else {
                btVector3 pos2 = ha2->getCenterOfMassPosition();
                camera->setPosition(vector3df(pos2[0],pos2[1],pos2[2]));
            }
        //  ha2->clearForces();
        // ha2->applyDamping(100);
        // ha2->applyForce(btVector3(50,8000,50),btVector3(110,111,110));
        // icount=0;
        //m_cPhysics->clearBodies(); crashes
    // }
//         icount++;
    }

    if (bCar) {
    if (mEvent.getKeyState(    KEY_KEY_R))
                    {m_cVehicle->resetVehicle();
                            // Park camera where the vehicle is.


       //   m_cVehicle->setPosition(camera->getPosition());
           }
    if (bCarFollow) {
    // this is for putting the camera above the car
        btVector3 point = m_cVehicle->getVehiclePosition();
        camera->setPosition(vector3df(
          (f32)point[0],
          (f32)point[1]+10,
          (f32)point[2]-50));
    }
    if (mEvent.getKeyState(    KEY_UP))
                    {m_cVehicle->accelerate(1);}// need gears or something haha
  //  else if (!mEvent.getKeyState(  KEY_UP) && (m_cVehicle->getState() != EVEHICLE_REVERSING))
      //              {m_cVehicle->accelerate(-1);}   //wind resistance
// not working just keeps accelerating moved to speed incs

    if (mEvent.getKeyState(    KEY_DOWN))
                    {m_cVehicle->reverse(1);    }
//    else if (!mEvent.getKeyState(  KEY_DOWN) && (m_cVehicle->getState() != EVEHICLE_ACCELERATING))
//                    {m_cVehicle->reverse(0.3);}      // wind resistance
    if (mEvent.getKeyState(    KEY_LEFT))
                    {m_cVehicle->steer_left(); }
    if (mEvent.getKeyState(    KEY_RIGHT))
                    {m_cVehicle->steer_right(); }
    if (!mEvent.getKeyState(   KEY_LEFT) && !mEvent.getKeyState(KEY_RIGHT))
                    {m_cVehicle->steer_reset(); }
    }
#endif

//#define bskeleton
#ifdef bskeleton
/**/
	if (mEvent.getKeyState(KEY_KEY_S)) {
		skeleton.setAnimType(CSK_ANIM_BACKWARD);
		return;
	}

	if (mEvent.getKeyState(KEY_KEY_A)) {
		skeleton.setAnimType(CSK_ANIM_STRAFELEFT);
		return;
	}

	if (mEvent.getKeyState(KEY_KEY_D)) {
		skeleton.setAnimType(CSK_ANIM_STRAFERIGHT);
		return;
	}

	if (mEvent.getKeyState(KEY_KEY_W))
		if (mEvent.getKeyState(KEY_SHIFT)) {
			skeleton.setAnimType(CSK_ANIM_WALK);
		} else {
			skeleton.setAnimType(CSK_ANIM_RUN);
		}
	else
		skeleton.setAnimType(CSK_ANIM_STAND);

	if (mEvent.getKeyState(   KEY_SPACE))
		skeleton.setAnimType(CSK_ANIM_JUMP);

		// this routine animates the skeleton
		core::position2di pos2d = core::position2di(mEvent.mouseX,mEvent.mouseY);
		core::line3df line = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(pos2d,camera);
		skeleton.animSkeleton(pos2d);



		// setting player -----------------------------------------------------
		scene::ISceneNode *player = skeleton.getSkeletonSceneNode();
		player->setRotation(core::vector3df(0,.5f*mEvent.mouseX,0));

		core::vector3df playerLook = core::vector3df(1,0,0);
		playerLook.rotateXZBy(-player->getRotation().Y+90,core::vector3df(0,0,0));

		// rotate skeleton
		if (skeleton.getSkeletonVelocity().X != 0) {

			core::vector3df vec = playerLook;
			if (skeleton.getSkeletonVelocity().Y != 0)
				vec.rotateXZBy(skeleton.getSkeletonVelocity().Y,core::vector3df(0,0,0));
			player->setPosition( player->getPosition() + .5f * skeleton.getSkeletonVelocity().X * vec);

		}

		// jump
		if (skeleton.getAnimType() == CSK_ANIM_JUMP && skeleton.getSecondMotionVariable() < 340) {
			f32 wert = pow( 2.f/340.f*skeleton.getSecondMotionVariable()-1 , 2);
			core::vector3df pos = player->getPosition();
			pos.Y = 10.f * (-wert + 1);
			player->setPosition(pos);

		}



		// setting player -----------------------------------------------------
/*
		// setting camera -----------------------------------------------------
		core::vector3df playerPos = player->getPosition();
		core::vector3df distancePlayerCam = playerPos - camera->getPosition();

		f32 distanceMult=15.f;
		f32 distanceTopMult=10.f;
		f32 playerVelo = 1.f;

		if (playerVelo > 1.f) {
			distanceMult /= 1.f*playerVelo;
			distanceTopMult /= 1.f*playerVelo;
		}

		playerLook.normalize();
		playerLook *= distanceMult;

		vector3df camPosZero = playerPos - 1.5f * playerLook;
		camPosZero.Y += distanceTopMult;

		core::vector3df camPos = camera->getPosition();

		// cam - drift
		if (camPos != camPosZero) {
			vector3df delta = camPos - camPosZero;

			camPos = camPos - (.065f * delta);

			camera->setPosition(camPos);
		}

		camera->setTarget(playerPos);
*/

#endif //skeleton



        if (mEvent.getKeyState(KEY_ESCAPE )) {
		luna->m_cInGameEvents.Quit=true;
		return;
		}



//vector3df ha = camera->getAbsolutePosition();
 //   camera->setPosition(vector3df( ha.X, ha.Y-11, ha.Z));
device->sleep(5,0);
}

#endif // PYMAIN_H_INCLUDED
