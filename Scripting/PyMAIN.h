#ifndef PYSCENE_H_INCLUDED
#define PYSCENE_H_INCLUDED

#include "../config.h"
#ifdef PYTHON
namespace Python {
    void ExecuteScript(irr::core::string<char> scriptname);
    IrrlichtDevice * device;
    IVideoDriver * driver;
    ISceneManager * smgr;
    IGUIEnvironment * guienv;
    InGameEventReceiver mEvent;
    IGUIFont * default_font;
            SKeyMap keyMap[8]; // KEYMAP

    vector<ITexture *> texture_array; //Our array of textures
    void registerIrrDevice(Luna *luna2, IrrlichtDevice &device,InGameEventReceiver event);

    void initkeys();

    #ifdef CHOPPER
    ChopperControl *chopperControl;
    #endif

    Luna *luna;

  //  cAudio::IAudioManager* manager;
  //  cAudio::IAudioSource* mysound;
    #ifdef SOUND
        cAudio::IAudioManager* managerID = cAudio::createAudioManager(true);  // broken has to be done from main
        cAudio::IAudioSource* mysound;
    #endif

    ICameraSceneNode* camera;  //maybe put in vector for a cameraManager or do it in python


    int test();
    void preEnd();  //declared in PyFunctions2 for some reason... ?
    void CheckKeyStates();
    //Player *m_cPlayer;
    void render();
    void rfm(irr::scene::ISceneNode*);


    #ifdef PHYSICS
        int VehicleParam(Vehicle *vehicle,int param,float state,float ammount,float y,float z);
        Vehicle   *m_cVehicle;
        btRigidBody *ha;
    #endif
    bool CheckKeyState(int key);

//IrrAssimp assimp(ISceneManager* );
//            IrrAssimp assimp(ISceneManager);
 // put into a vector or array


    #ifdef EXTRAS
        gui::CGUIChatBox* chat;
    #endif

    bool bPProcess, opensteer, chopperEnabled, HUDENABLED=0;
    bool rmouse1,lmouse1,mmouse1;

    #ifdef FPS
        firstPersonWeapon* M4;
        bool bFPS;
    #endif

    #ifdef CODEEDITOR
        int bCodeEditor;
    #endif

    #ifdef FLAG
    	SimpleFlagNode	*irrFlagNode;
    #endif

    #ifdef HUD
        CHUD* CHUD2 = new CHUD();
    #endif

    #ifdef ATMOSPHERE
        ATMOsphere *atmo;
    #endif

    #ifdef VIDEO
        CVideoMaster    *vidmaster;
    #endif

    #ifdef TESSELATE
        TesselatedImage *tesImage;
        bool btesimage=0;
    #endif
    #ifdef WATER
    #ifdef ReflectiveWater
        #include "../TerrainFactory/WaterNode/CReflectedWater.h"
        CReflectedWater *water;
    #endif

    #ifdef RealisticWater
        RealisticWaterSceneNode* water2;
    #endif
    #endif
    #ifdef occlusion
        Renderer22 *RenderMan;
    #endif


    //todo bugfix need a way to get set the string in either luna.h or here
   // irr::core::stringc returnString="../media/gameloader.pys";
    irr::core::stringc returnString="../media/main.pys";
//       char * returnString="";

    //Scene
    // would be sweet to have this done automatically somehow lol pita making 2 tables and a function
    PyObject * PyIrr_GetString(PyObject * self,PyObject * args);
    PyObject * PyIrr_addCamera(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadTexture(PyObject * self,PyObject * args);
    PyObject * PyIrr_SetTexture(PyObject * self,PyObject * args);
    PyObject * PyIrr_DrawText(PyObject * self,PyObject * args);
    PyObject * PyIrr_AddCubeSceneNode(PyObject * self,PyObject * args);
    PyObject * PyIrr_FormationDemo(PyObject * self,PyObject * args);
    PyObject * PyIrr_SetCamera(PyObject * self,PyObject * args);
    PyObject * PyIrr_GetCamera(PyObject * self,PyObject * args);
    PyObject * PyIrr_BindCamera(PyObject * self,PyObject * args);
    PyObject * PyIrr_Reset(PyObject * self,PyObject * args);

    PyObject * PyIrr_fpsWeapon(PyObject * self,PyObject * args);
    PyObject * PyIrr_atmosphere(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadShape(PyObject * self,PyObject * args);
    PyObject * PyIrr_addAnimatedMesh(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadMesh(PyObject * self,PyObject * args);
    PyObject * PyIrr_tesselateImage(PyObject * self,PyObject * args);
    PyObject * PyIrr_addHelicopter(PyObject * self,PyObject * args);
    PyObject * PyIrr_setPosition(PyObject * self,PyObject * args);
    PyObject * PyIrr_getPosition(PyObject * self,PyObject * args);
    PyObject * PyIrr_motionTrail(PyObject * self,PyObject * args);

    PyObject * PyIrr_Event(PyObject * self,PyObject * args);
    PyObject * PyIrr_gamePad(PyObject * self,PyObject * args);

    //Functions
    PyObject * PyIrr_WayPoint(PyObject * self,PyObject * args);
    PyObject * PyIrr_exec(PyObject * self,PyObject * args);

    ///Physics
    PyObject * PyIrr_Bullet(PyObject * self,PyObject * args); // try to seperate
    PyObject * PyIrr_RagMan(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadTrack(PyObject * self,PyObject * args);
    PyObject * PyIrr_BulletBlend(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadVehicle(PyObject * self,PyObject * args);
    PyObject * PyIrr_setVelocity(PyObject * self,PyObject * args);
    PyObject * PyIrr_DecalManager(PyObject * self,PyObject * args);
    PyObject * PyIrr_addPlayer(PyObject * self,PyObject * args);
    PyObject * PyIrr_OpenSteer(PyObject * self,PyObject * args);
    PyObject * PyIrr_VehicleParams(PyObject * self,PyObject * args);
    PyObject * PyIrr_addCar(PyObject * self,PyObject * args);
    PyObject * PyIrr_b2Dphysics(PyObject * self,PyObject * args);
    PyObject * PyIrr_MeshManipulator(PyObject * self,PyObject * args);
    PyObject * PyIrr_voxelLoad(PyObject * self,PyObject * args);
    PyObject * PyIrr_CSG(PyObject * self,PyObject * args);
    PyObject * PyIrr_FileArchive(PyObject * self,PyObject * args);
    PyObject * PyIrr_Animators(PyObject * self,PyObject * args);
    PyObject * PyIrr_irrbulletBox(PyObject * self,PyObject * args);
    PyObject * PyIrr_irrbulletliquiddemo(PyObject * self,PyObject * args);
    PyObject * PyIrr_physicspause(PyObject * self,PyObject * args);


    //GUI
    PyObject * PyIrr_addHUD(PyObject * self,PyObject * args);
    PyObject * PyIrr_addVideo(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUIWindow(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUIPanel(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUITabs(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUIButton(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUIText(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUITree(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUIEditBox(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUIBar(PyObject * self,PyObject * args);
    PyObject * PyIrr_sineGraph2d(PyObject * self,PyObject * args);
    PyObject * PyIrr_GUIslider(PyObject * self,PyObject * args);
    PyObject * PyIrr_rTexture(PyObject * self,PyObject * args);

    //Terrain
    PyObject * PyIrr_Trees(PyObject * self,PyObject * args);
    PyObject * PyIrr_addTerrain(PyObject * self,PyObject * args);

    //Scene
    PyObject * PyIrr_addSphereNode(PyObject * self,PyObject * args);
    PyObject * PyIrr_loadModel(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadTrack(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadLevel(PyObject * self,PyObject * args);
    PyObject * PyIrr_Light(PyObject * self,PyObject * args);
    PyObject * PyIrr_Flashlight(PyObject * self,PyObject * args);
    PyObject * PyIrr_ExportScene(PyObject * self,PyObject * args);
    PyObject * PyIrr_FWGrass(PyObject * self,PyObject * args);
    PyObject * PyIrr_PostProcess(PyObject * self,PyObject * args);
    PyObject * PyIrr_getScreen(PyObject * self,PyObject * args);

    //Extras
    PyObject * PyIrr_realCloud(PyObject * self,PyObject * args);
    PyObject * PyIrr_calcMath(PyObject * self,PyObject * args);
    PyObject * PyIrr_bitCloud(PyObject * self,PyObject * args);
    PyObject * PyIrr_WaterPlane(PyObject * self,PyObject * args);

    PyObject * PyIrr_lightning(PyObject * self,PyObject * args);
    PyObject * PyIrr_beam(PyObject * self,PyObject * args);
    PyObject * PyIrr_omareClouds(PyObject * self,PyObject * args);
    PyObject * PyIrr_skyDome(PyObject * self,PyObject * args);
    PyObject * PyIrr_RelayChat(PyObject * self,PyObject * args);

    PyObject * PyIrr_Occlusion(PyObject * self,PyObject * args);
    PyObject * PyIrr_Compass(PyObject * self,PyObject * args);
    PyObject * PyIrr_2Dimage(PyObject * self,PyObject * args);
    PyObject * PyIrr_BlindBoids(PyObject * self,PyObject * args);
    PyObject * PyIrr_omareDemo(PyObject * self,PyObject * args);
    PyObject * PyIrr_CodeEditor(PyObject * self,PyObject * args);
    PyObject * PyIrr_ChatBox(PyObject * self,PyObject * args);

    PyObject * PyIrr_Flag1(PyObject * self,PyObject * args);
    PyObject * PyIrr_Flag2(PyObject * self,PyObject * args);
    PyObject * PyIrr_Flare2(PyObject * self,PyObject * args);
    PyObject * PyIrr_lensFlare(PyObject * self,PyObject * args);
    PyObject * PyIrr_SPARKA(PyObject * self,PyObject * args);
    PyObject * PyIrr_vegetation(PyObject * self,PyObject * args);

    //input
    PyObject * PyIrr_getKey(PyObject * self,PyObject * args);
    PyObject * PyIrr_wii(PyObject * self,PyObject * args);
    PyObject * PyIrr_recast(PyObject * self,PyObject * args);
    PyObject * PyIrr_media(PyObject * self,PyObject * args);
    PyObject * PyIrr_Mouse(PyObject * self,PyObject * args);
    PyObject * PyIrr_Tiled(PyObject * self,PyObject * args);
    PyObject * PyIrr_OIS(PyObject * self,PyObject * args);


    //media
    PyObject * PyIrr_FluidSynth(PyObject * self,PyObject * args);
    PyObject * PyIrr_zistream(PyObject * self,PyObject * args);
    PyObject * PyIrr_zostream(PyObject * self,PyObject * args);

    //SOUND
    PyObject * PyIrr_SoundMan(PyObject * self,PyObject * args);

    //Math
    PyObject * PyIrr_Rand(PyObject * self,PyObject * args);

	// MESH Tools
    PyObject * PyIrr_aBillBoard(PyObject * self,PyObject * args);
    PyObject * PyIrr_addAnimatedMesh(PyObject * self,PyObject * args);
    PyObject * PyIrr_addMesh(PyObject * self,PyObject * args);
    PyObject * PyIrr_pauseGame(PyObject * self,PyObject * args);
    PyObject * PyIrr_exit(PyObject * self,PyObject * args);
    PyObject * PyIrr_using(PyObject * self,PyObject * args);
    PyObject * PyIrr_motionTrail(PyObject * self,PyObject * args);
    PyObject * PyIrr_Delete(PyObject * self,PyObject * args);
    PyObject * PyIrr_setRotation(PyObject * self,PyObject * args);

    //Timers
    PyObject * PyIrr_Delay(PyObject * self,PyObject * args);
    PyObject * PyIrr_Sleep(PyObject * self,PyObject * args);
    PyObject * PyIrr_setTime(PyObject * self,PyObject * args);
    PyObject * PyIrr_getTime(PyObject * self,PyObject * args);

    //network
    PyObject * PyIrr_Connect(PyObject * self,PyObject * args);
    PyObject * PyIrr_Disconnect(PyObject * self,PyObject * args);
    PyObject * PyIrr_Ping(PyObject * self,PyObject * args);
    PyObject * PyIrr_sendFile(PyObject * self,PyObject * args);
    PyObject * PyIrr_Send(PyObject * self,PyObject * args);
    PyObject * PyIrr_Receive(PyObject * self,PyObject * args);
    PyObject * PyIrr_Encrypt(PyObject * self,PyObject * args);
    PyObject * PyIrr_Decrypt(PyObject * self,PyObject * args);
    PyObject * PyIrr_Server(PyObject * self,PyObject * args);
    PyObject * PyIrr_restartServer(PyObject * self,PyObject * args);
    PyObject * PyIrr_Update(PyObject * self,PyObject * args);
    PyObject * PyIrr_irc(PyObject * self,PyObject * args);

    PyObject * PyIrr_sqlconnect(PyObject * self,PyObject * args);
    PyObject * PyIrr_sqlcommand(PyObject * self,PyObject * args);


    //Image
    PyObject * PyIrr_iRotate(PyObject * self,PyObject * args);
    PyObject * PyIrr_iScale(PyObject * self,PyObject * args);
    PyObject * PyIrr_iPosition(PyObject * self,PyObject * args);
    PyObject * PyIrr_iAdd(PyObject * self,PyObject * args);
    PyObject * PyIrr_iDraw(PyObject * self,PyObject * args);
    PyObject * PyIrr_iAlpha(PyObject * self,PyObject * args);
    PyObject * PyIrr_iTexture(PyObject * self,PyObject * args);
    PyObject * PyIrr_icheckBounds(PyObject * self,PyObject * args);
    PyObject * PyIrr_igetBounds(PyObject * self,PyObject * args);
    PyObject * PyIrr_LoadSpriteFont(PyObject * self,PyObject * args);

    PyObject * PyIrr_iGetOHeight(PyObject * self,PyObject * args);
    PyObject * PyIrr_iGetOWidth(PyObject * self,PyObject * args);
    PyObject * PyIrr_iGetHeight(PyObject * self,PyObject * args);
    PyObject * PyIrr_iGetWidth(PyObject * self,PyObject * args);
    PyObject * PyIrr_isetColor(PyObject * self,PyObject * args);
    PyObject * PyIrr_igetColor(PyObject * self,PyObject * args);
    PyObject * PyIrr_iTransparent(PyObject * self,PyObject * args);
    PyObject * PyIrr_iFilter(PyObject * self,PyObject * args);

    PyMODINIT_FUNC init_irr(void);

    //subsystem
    bool LPHYS;
    bool LSOUND;
    // try to use managers asmuch as possible

    u32 timeStamp,deltaTime ;

    #ifdef Image2D
        cImage* image;
    #endif


    void PreRender();
    scene::IMeshBuffer* buff;
    Scene *m_cScene;

    #ifdef PHYSICS
        btRigidBody* ha2;
    #endif

    bool bingo = true;
    bool yesim = true;
    scene::IBillboardSceneNode * bill;
    int nextDecal = 0;

    #ifdef IRRc
        Application *app;
    #endif

    bool flag1,flag2,bImage2d,bCompass,formationDemo,bAtmosphere,bWater,blensFlare,bBlindBoids=0;
    bool bOcclusion,bCar,bCarFollow,bSPARK,bDecals,bPhysics;

#ifdef FORMATION
    WrapperClass::Formation * formation;
    f32 SpeedMultiplier;// = 1.1f;
#endif

    #ifdef COMPASS
        Compass * Compass1;
    #endif
    #ifdef BOIDS
        Flock* flock;
    #endif
    #ifdef TERRAIN
        Terrain *terr;
    #endif
    #ifdef DECALS
        DecalManager* decalManager;
    #endif
    #ifdef DECALS2
       ArmDecalSceneNode* decals[MAX_DECALS];
    #endif

    #ifdef SPARK
        Group* fireGroup = NULL;
        Group* smokeGroup = NULL;
        Emitter* smokeEmitter = NULL;
        System* particleSystem = NULL;
    #endif
//	if (cloudLayer1)		cloudLayer1->drop();
//	if (cloudLayer2)		cloudLayer2->drop();
//	if (cloudLayer3)		cloudLayer3->drop();
};

int Python::test(){};

void Python::PreRender(){   // prerender
        #ifdef SPARK //rain
        if (bSPARK){
		// lightmap effect
        // if(deltaTime >= 0.05f)
        //{
            float decal = SPK::random(0.95f,1.05f);
            for(int y=0; y<2; y++)
                for(int x=0; x<2; x++)
                    ((video::S3DVertex2TCoords*)(buff->getVertices()))[x+2*y].TCoords2 = core::vector2df((x-0.5f)*decal+0.5f,(y-0.5f)*decal+0.5f);
        //lastLightTime = time;
        //}
      //  particleMngr->updatePosition(luna->camera->getAbsolutePosition());
	//	particleMngr->render();
        }
        #endif
};

void Python::preEnd(){                                                 //used to be in pyfunct2 for
    #ifdef FLARE
        if (bFlare2){
        // run occlusion query
        driver->runAllOcclusionQueries(false);
        driver->updateAllOcclusionQueries(false);
        u32 occlusionQueryResult = driver->getOcclusionQueryResult(sunMeshNode);
            if(occlusionQueryResult!= 0xffffffff)
                lensFlareNode->setStrength(f32(occlusionQueryResult)/8000.f);
        }
    #endif
    #ifdef FLARE2
        if (blensFlare){
            driver->runAllOcclusionQueries(false);
            driver->updateAllOcclusionQueries(false);
            lensFlareNode2->render();
            //lensFlareNode2->setPosition(flare->getStartPosition() + camera->getPosition());
        }
    #endif

        #ifdef PostProcess
        if ( bPProcess ){
          //  ppBlurDOF->render( NULL );
          //  ppBlur->render( NULL );
            ppMine->render( NULL );
        //     ppDOF->render( NULL );
      //      ppInvert->render( NULL );
        }
        #endif

}

void Python::render() {//active camera

        deltaTime = device->getTimer()->getRealTime() - timeStamp;
        timeStamp = device->getTimer()->getRealTime();
#ifdef BOIDS
         if (bBlindBoids){flock->update(selecta,deltaTime,0);};
#endif
        #ifdef TESSELATE
            if (btesimage){ tesImage->render(deltaTime); }
        #endif


        #ifdef IRRBULLET
        if (bPhysics==1){
         luna->world->stepSimulation(deltaTime*0.001f, 120);
        }else{
        luna->world->simulationPaused();
       // luna->world->pauseSimulation();
        }//world->pauseSimulation(!world->simulationPaused());

        //        world->debugDrawWorld(debugDraw);

        // This call will draw the technical properties of the physics simulation
        // to the GUI environment.
        luna->world->debugDrawProperties(true);
        #endif

        #ifdef PHYSICS
         //    if (bPhysics){  // fix later should
        luna->m_cPhysics->updatePhysics(deltaTime);

        #ifdef BULLETCAR
        if (bCar){

//            for (std::vector<Vehicle*>::iterator it = m_cVehicle.begin(); it != m_cVehicle.end(); ++it)
//            (*it)->renderme();

            ///  btVector3 pos = m_cVehicle->getVehiclePosition();
            // m_cVehicle2->renderme(); // no need to update unless running 2 players from same computer
    //m_cVehicle->renderme();
//            #ifdef CAR2
//                m_cVehicle2->renderme();
//            #endif
            // m_cVehicle2->setVehiclePosition(vector3df(pos[0]+20,pos[1],pos[2])); //ghostCar
            // camera->setPosition( vector3df(pos[0],pos[1]+4,pos[2]));  //sticking the camera to the car
            }
        #endif
        #ifdef BULLETBLEND
            logicManager->processLogicBricks(deltaTime);
        #endif
        #ifdef RAGDOLL
            for (std::vector<RagDoll*>::iterator it = v_RagDolls.begin(); it != v_RagDolls.end(); ++it)
            (*it)->Update();
        #endif


        //      }
        #endif

        #ifdef FPS
        if (bFPS){    M4->update(device->getTimer()->getTime());}
        #endif
//irr::ITimer* timer = device->getTimer();
// irr::u32 timeThisFrame = timer->getTime();
// timeThisFrame = timer->getTime();
//
//while( (timer->getTime() - timeThisFrame) <= 16 )
//{    timer->tick();  };

//skipper so that its not updated as often
//nexttime = deltaTime - device->getTimer()->getRealTime()+200;
#ifdef WATER
        #ifdef ReflectiveWater
            if (bWater){  water->updateRendertarget(smgr);  }
        #endif
        #ifdef RealisticWater
            if (bWater){  water2->OnAnimate(device->getTimer()->getTime()/1000);
            water2->render();

             }
        #endif
        #endif

        #ifdef COMPASS
        if (bCompass){
            //Compass --BRJ correct way to get heading posted by Vitek
            core::vector3df fore(0, 0, 1);
            smgr->getActiveCamera()->getAbsoluteTransformation().rotateVect(fore);
            core::vector3df rot1 = fore.getHorizontalAngle();
            Compass1->SetCompassHeading( rot1.Y );
        }
        #endif

       //   luna->m_cPlayer->CheckFalling();  // less often per loop
      //    Obstacle::Instance()->CheckCollisionWithPlayer();
      //    Elevator::Instance()->CheckCollisionWithPlayer();
      //    Elevator::Instance()->UpdatePlayerPosition();

        #ifdef SOUND // weird works without this
//            if(managerID){
//                if(mysound && !mysound->isPlaying())
//                {
//                    mysound->setVolume(0.5);
//                    //Set the IAudio Sound to play2d and loop
//                    mysound->play2d(true);
//                }
//            }
        #endif


        #ifdef occlusion
            if (bOcclusion){
                RenderMan->drawGUI();
            }
        #endif

        #ifdef Image2D
            if (bImage2d){
                image->Draw(smgr);
            }
        #endif

        #ifdef OPENSTEER
        if (opensteer){ //OpenSteer::runGraphics();
            OpenSteer::OpenSteerDemo::updateSimulationAndRedraw();
         }
         #endif

        #ifdef HUD
            if (HUDENABLED){
                CHUD2->DisplayHUD(); // for displaying text
            }
        #endif

        #ifdef VIDEO
            if (vidmaster){
                //  videoPlayer->refresh();
                //  videoPlayer->drawVideoTexture();
              ITexture* temp = vidmaster->getTextureByName("Titan");
              temp = vidmaster->getTextureByName("YUV");
                if (temp)
              {
                driver->draw2DImage(temp, vector2di(driver->getScreenSize().Width - 128, driver->getScreenSize().Height - 128));
              }
              vidmaster->update();
              }
        #endif

        #ifdef BITCLOUD
            rot-= 0.02f;
            // silly way to do rotation, depends on speed
            clouds->setRotation(vector3df(0,rot,0));
        #endif

        #ifdef PostProcess
        if ( bPProcess ){
            ppMine->setParameters( min_( 1.0f, device->getTimer( )->getTime( ) * 0.0002f ) );

            f32 p = sinf( device->getTimer( )->getTime( ) * 0.0005f ) * 0.5f - 0.2f;
            ppBlurDOF->setParameters( p * 100.0f + 80.0f, p * 100.0f + 110.0f, p * 100.0f + 160.0f, p * 100.0f + 240.0f, 0.01f );
        }
        #endif

        // rt->render(); //ribbon trail scenenode
//        device->sleep(5);
}



#endif // PYSCENE_H_INCLUDED
#endif
