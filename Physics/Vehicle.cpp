#include "Vehicle.h"
#include "../TerrainFactory/Terrain.h"
#include <string.h>
#include "../Scene/Elevator.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// sets defaults on init
Vehicle::Vehicle()  :    m_carChassis(0),m_cameraHeight(4.f),m_minCameraDistance(3.f),
        m_maxCameraDistance(10.f),m_indexVertexArrays(0),m_vertices(0){
    int scaleT  = 1; // minimum 2 Vehicle Size test scale
    int scaleE  = 1;// engine/weight scale for friction
    printf("Vehicle constructor.\n");
    rightIndex          = 0;
    upIndex             = 1;
    forwardIndex        = 2;
    wheelDirectionCS0   = btVector3(0,-1,0);    // seems to change the length of shocks too
    wheelAxleCS         = btVector3(-1,0,0);       //sey y for dancing effect // makes the car go forward vector
    btCarScale          = btVector3( 1.3f*scaleT, .4f*scaleT, 2*scaleT );//COMeffected -  Collision Box   default 1,2,2
    btModelscale        = btVector3( 1.5f*scaleT, 1.5f*scaleT, 2.f*scaleT );// sides,y,FB     Model Specific
    m_vehiclePosition   = btVector3(0,0,0);         // sets the position initially

    vehicleWeight       = 600         *scaleE*scaleT;      //weight of a typical vehicle 1 vehicle weight
    maxBreakingForce    = 100.0f        *scaleE*scaleT;
    maxEngineForce      = 2200.0f       *scaleE*scaleT;  //this should be engine/velocity dependent
    SpeedINC            = 20            *scaleE*scaleT; // Speed Increasement scale factor  TEST FACTOR ONLY -UNIT

    driveType           =4;               //  0=2RWD  3=2FWD  1=4wd  2=4wd+4wsteer 4=Trike 5=Bike

    connectionHeight    = -0.03f         *scaleT;    //0.03 // surface -> connection to chassy height changes COM
    suspensionStiffness = 20.0f   *scaleE*scaleT; // bigger the number the stiffer it getS
    //! there is a fucked up ratio between the suspension dampners
    suspensionDamping   = 0.0f        ;// bounce time       x<1  -bigger means less bounces for some reason slower
    suspensionCompression= .7f       ;// shock absorber    x<1  -bigger the number the more is absorbed
    suspensionRestLength= btScalar(01.6f *scaleT);   // combined height of .6 to clear the ground
    rollInfluence       = -0.001f;

    wheelFriction       = 1e30f;  //1e30f;
    wheelRadius         = 0.8f          *scaleT;
    wheelWidth          = 0.60f          *scaleT; // only textures at the moment use the scaler then this to fit the tire
    steeringIncrement   = 0.01f;
    steeringClamp       = 0.45f;        // .90 max

    CUBE_HALF_EXTENTS   = 2            *scaleT;    //Wheel SpreadScale
    wheelSpacingX       = 0.3f;       //subtracted  wheel spacing width   .3 default
    wheelSpacingZ       = 2.f;       // back wheel from center of car     2 default
    wheelSpacingZ2      = 2.f;      // Front wheels z-shift               2 default
    wheelScaleFactor    = 1.f;       //wheel model specific
    //! Dont Touch \/ these
    //   m_numWheels         = 4;// dont need used m_vehicle->getNumWheels instead // unless maybe for damage
    m_vehicle           = 0;
    maxProxies          = 32766;
    maxOverlap          = 65535;
    state               = EVEHICLE_STALLED;
    m_vehicle           = NULL;
    gEngineForce        = 0.0f;
    gBreakingForce      = 0.0f;
    gVehicleSteering    = 10.f;
}


void Vehicle::setEventRec(IEventReceiver* m_event){

 //  m_cInGameEvents = m_event;
}

void Vehicle::renderme(){  //deltatime ?
    if(!m_vehicle) return;
    btScalar m[16];
    int i;
            //btCylinderShapeX wheelShape(btVector3(wheelWidth,wheelRadius,wheelRadius));
            //btVector3 wheelColor(1,0,0);
    //! Wheel tranform variables.
    btTransform wheelTransform;
    btVector3 wheelPosition;
    btQuaternion wheelRotation;
    btVector3 wheelRotationEuler;
    f32 wheelOffsetX = 0,
        wheelOffsetY = 0,
        wheelOffsetZ = 0;

// Draw wheels (cylinders)   set rotation according to acceleration and deltatime ?
    for (i=0;i<m_vehicle->getNumWheels();i++)
    {
        //wheelTransform = m_vehicle->getWheelTransformWS(i);
        wheelTransform = m_vehicle->getWheelInfo(i).m_worldTransform;

        wheelPosition = wheelTransform.getOrigin();

        wheelRotation = wheelTransform.getRotation();

        m_cPhysics->quaternionToEuler(wheelRotation, wheelRotationEuler);

        wheelNode[i]->setPosition(vector3df(    (f32)wheelPosition[0] ,
                                                (f32)wheelPosition[1] ,
                                                (f32)wheelPosition[2]));
        wheelNode[i]->setRotation(vector3df(    (f32)wheelRotationEuler[0],
                                                (f32)wheelRotationEuler[1],
                                                (f32)wheelRotationEuler[2]));
                                                        // Synchronize the wheels with the (interpolated) chassis worldtransform
        m_vehicle->updateWheelTransform(i,true);
    }



//		 vector3df wheels node->getAbsolutePosition();
//		node->setPosition(wheels);


      ///IAnimatedMesh* CharMesh = smgr->getMesh("dwarf.x");


//		jointSystem(IAnimatedMeshSceneNode wheelNode){
//		   // Animate character manually
//		         CharNode->setAnimationSpeed(10);
//		   //      CharNode->setJointMode(EJUOR_CONTROL); //To write positions to
//      //CharNode->animateJoints();
//
//
//   // Get the Joint you want to MANIPULATE, and its Parent
//
//   // for loop load wheel positions
//      IBoneSceneNode* thisJoint = wheelNode->getJointNode("wheels.00");
//
//      if( thisJoint )
//      {
//         ISceneNode* parentJoint = thisJoint->getParent();
//
//         if( parentJoint )
//         {
//         // Get the default (animated) Joint's position and rotation
//            vector3df jointPos = thisJoint->getAbsolutePosition();
//            vector3df jointRot = thisJoint->getAbsoluteTransformation().getRotationDegrees();
//
//         // Get the absolute INVERSE Transformation matrix of the parent
//            matrix4 iparentTransform = parentJoint->getAbsoluteTransformation();
//               iparentTransform.makeInverse();
//
//         // Set the Absolute Position or Rotation of the Joint without fear!
//            vector3df newJointPos = jointPos + vector3df( 0, 1+(sin(headPosition)*2), 0 );
//            vector3df newJointRot = vector3df( 0, headRotation, 0 );
//
//         // Transform the Position by the Parent's Inverse matrix before applying it
//            iparentTransform.transformVect( newJointPos );
//
//         // APPLY
//            thisJoint->setPosition( newJointPos );
//            thisJoint->setRotation( newJointRot );
//         }
//      }
//}




//tecan try to add down force on wheel thats not connected{ taken from bullet forums}
//           for (i=0;i<m_numWheels;i++)
//        {
                btWheelInfo &wheel_info = m_vehicle->getWheelInfo(i);
//wheel_info.m_raycastInfo.m_suspensionLength
//                if ( wheel_info.m_raycastInfo.m_isInContact ){}
//               else
//                {
//                gEngineForce -= 50;
//            // A very unphysical thing to handle slopes that are a bit too steep
//            // or uneven (resulting in only one wheel on the ground)
//            // If only the front or only the rear wheels are on the ground, add
//            // a force pulling the axis down (towards the ground). Note that it
//            // is already guaranteed that either both or no wheels on one axis
//            // are on the ground, so we have to test only one of the wheels
//        //    wheel_info.m_wheelsSuspensionForce = 0.001;//-m_track_connect_accel*chassisMass ;
//        //    wheel_info.
//                }
//                }
    updateVehicleMovement();
    gEngineForce -= 0.1;  //wind resistance
}


btVector3 Vehicle::getVehiclePosition(void){
  if(!m_vehicle)
    return m_vehiclePosition;
  else
    return m_vehicle->getRigidBody()->getCenterOfMassPosition();
}


void Vehicle::setPosition( core::vector3df vect ){
   // if(!m_vehicle)
   btVector3 pos = btVector3(vect.X,vect.Y,vect.Z);
  //  m_carChassis->setCenterOfMassTransform(tr);
   m_carChassis->translate(btVector3 (vect.X,vect.Y,vect.Z));
  // m_carChassis->s
   // m_vehicle->set;
}


btQuaternion Vehicle::getVehicleOrientation(void){
    return m_vehicle->getRigidBody()->getOrientation();
}


void Vehicle::setState(EVEHICLE_STATE _state)           {    state = _state;}

EVEHICLE_STATE Vehicle::getState(void)                  {    return state;}

void Vehicle::registerIrrDevice(IrrlichtDevice &device) { m_irrDevice = &device;}

void Vehicle::registerPhysics(Physics &physics)  {  m_cPhysics = &physics;
    printf("Init vehicle physics.\n");
    btVector3 worldMin(-1000,-1000,-1000);
    btVector3 worldMax(1000,1000,1000);
    m_overlappingPairCache = new btAxisSweep3(worldMin,worldMax);
}


void Vehicle::registerScene(Scene &scene)    {   m_cScene = &scene;  }


void Vehicle::accelerate(f32 speed){
    setState(EVEHICLE_ACCELERATING);
    gEngineForce += speed*SpeedINC;

    if (gEngineForce > maxEngineForce) gEngineForce = maxEngineForce;

    //need to figure out these vars (borrowed from sr3)
//float	fGearRatio[33]; // Allow for up to 32 gears plus neutral
    //    	float watt_per_hp = 745.0f;
    //	float seconds_per_minute = 60.0f;
    //
    //	float HorsePower = 10;
    //	float AxleRatio = 1.0f;
    //	float MaxRPM = 7000;
    //	float WheelRadius = psCar->sWheels[0].fRadius;

    //wheelforce =Acceleration *HorsePower * (watt_per_hp * seconds_per_minute) *
	//gearRatio  * AxleRatio /(MaxRPM * WheelRadius * (2.0f * (float)PI));
	//		float Torque = wheel_force_by_throttle * psCar->sWheels[i].fRadius;
	//	*pForce += psCar->Y*Torque;
	//	*pTorque += CrossProduct(psCar->sWheels[i].cRelPos, CVec(0,0,-Torque));
	//    float	diffRatio = 3.6f;
	//float	gearEfficiency = 0.7f;
//EngineForce = t * gearRatio * diffRatio * gearEfficiency * psCar->fAcceleration;

 // gear shifting in here , rpm to engine force ?
//     if (gEngineForce < 0)
//    {
//        gEngineForce = 0;
//        setState(EVEHICLE_STALLED);
//    }

    if (gEngineForce < 0)
    {
        gEngineForce = 0;
        setState(EVEHICLE_STALLED);
    }
    gBreakingForce = 0.f;
}


void Vehicle::reverse(f32 speed){
 setState(EVEHICLE_REVERSING);
 gEngineForce -= speed*SpeedINC;
    if (gEngineForce < -maxEngineForce)
        gEngineForce = -maxEngineForce;

    if (gEngineForce > 0)
    {
        gEngineForce = 0;
        setState(EVEHICLE_STALLED);
    }
    gBreakingForce = 0.f;
}


void Vehicle::steer_right(void){
    if (	(gVehicleSteering+steeringIncrement) < steeringClamp)
    gVehicleSteering += steeringIncrement;
}


void Vehicle::steer_left(void){
    if (	(gVehicleSteering-steeringIncrement) > -steeringClamp)
    gVehicleSteering -= steeringIncrement;
}


void Vehicle::brake(void){
    gBreakingForce = maxBreakingForce;
    gEngineForce = 0.1f;
}


void Vehicle::registerCamera( ICameraSceneNode *camera2){
  camera= camera2;
}


void Vehicle::steer_reset(void){
    gVehicleSteering *= 0.80f;  // auto straighten the wheel out
 //   gVehicleSteering = 0;
}


void Vehicle::resetVehicle(void){
  gVehicleSteering = 0.0f;
  m_carChassis->setCenterOfMassTransform(btTransform::getIdentity());
	m_carChassis->setLinearVelocity(btVector3(0,0,0));
	m_carChassis->setAngularVelocity(btVector3(0,0,0));
	//m_dynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(m_carChassis->getBroadphaseHandle(),getDynamicsWorld()->getDispatcher());
	if (m_vehicle)
	{
		m_vehicle->resetSuspension();
		for (int i=0;i<m_vehicle->getNumWheels();i++)
		{
			//synchronize the wheels with the (interpolated) chassis worldtransform
			m_vehicle->updateWheelTransform(i,true);
		}
	}
}


Vehicle::~Vehicle(){
  if(!m_vehicle) return;
    for (int j=0;j<m_collisionShapes.size();j++)
    {
        btCollisionShape* shape = m_collisionShapes[j];
        delete shape;
    }
    delete m_indexVertexArrays;
    delete m_vertices;
    delete m_vehicleRayCaster;
    delete m_vehicle;
}


void Vehicle::initPhysics(stringc carMesh, stringc texture ) {  tr.setOrigin(m_vehiclePosition);  //pythonize model loading
    IAnimatedMesh *l_node;
    IAnimatedMeshSceneNode *l_node_chassi;
 // const stringc carMesh = "data/models/vehicles/CarBlends/DOHcaddy-car.x";
//    const stringc carMesh = "data/models/vehicles/CarBlends/oldChevy-Truck.x";
  //  const stringc carMesh = "data/models/vehicles/oldChevy-Truck.3ds";

   // const stringc carMesh = "data/models/vehicles/body.irrmesh";
// //                 carMesh = "data/models/vehicles/C.obj";
//
    l_node = m_irrDevice->getSceneManager()->getMesh(carMesh.c_str());

#ifdef upsidedown
//    l_node->rotation(btQuaternion( btVector3(0,1,0), PI ));
    irr::core::quaternion *carModelRotation;
    carModelRotation->set(0.0f,-1.f,0.f, 0.0f) ;  //

        m_irrDevice->getSceneManager()->getMeshManipulator()->
                        transform(l_node, carModelRotation->getMatrix());
            //getMeshManipulator createMeshWithTangents    createMeshCopy
#endif
    if(!l_node) return;
    l_node_chassi = m_irrDevice->getSceneManager()->addAnimatedMeshSceneNode(l_node);

    //old code for loading car
  //  IMeshBuffer *meshBuffer = l_node->getMeshBuffer(0);
  //  btTriangleMesh *collisionMesh = new btTriangleMesh();
  //  m_cPhysics->convertIrrMeshBufferBtTriangleMesh(meshBuffer, collisionMesh, vector3df(0,0,0));
  //  btBvhTriangleMeshShape *chassisShape = new btBvhTriangleMeshShape(collisionMesh, true);

    l_node_chassi->setScale(vector3df(btModelscale[0], btModelscale[1], btModelscale[2]));
 //   l_node_chassi->setPosition(vector3df(0,100,0));
     l_node_chassi->setRotation(vector3df(0,1,0));
    l_node_chassi->setMaterialTexture(0,
    m_irrDevice->getVideoDriver()->getTexture(texture));
    m_cScene->setGenericMaterial(l_node_chassi, 0);
  //        l_node_chassi->getMaterial(0).ZWriteEnable=1;
  //    l_node_chassi->getMaterial(0).BackfaceCulling = true;

    if (!l_node_chassi) printf("Chassi node was not created.\n");

    l_node_chassi->addShadowVolumeSceneNode(l_node,false, 100.f);

    btCollisionShape* chassisShape = new btBoxShape(btCarScale); //! << BULLET BODY SCALE

    btCompoundShape* compound = new btCompoundShape();
    //tr.btTransform(localTrans);
    //
    ////   btModelrotation =  vector3df(0,0,0);
    btTransform localTrans;
    localTrans.setIdentity();
   // localTrans.setRotation(btQuaternion( btVector3(0,1,0), PI ));
    localTrans.setOrigin(btVector3(0,0,0)); // moves chassi around and center of mass
      //  tr.setIdentity();
      // tr.setRotation(btQuaternion( btVector3(0,1,0), 2*PI )); // moves the buggy
      //  tr.setOrigin(btVector3(pos[0]+20,pos[1],pos[1]));


 compound->addChildShape(localTrans,chassisShape);
// localTrans.setOrigin(btVector3(pos.X,pos.Y,pos.Z-100));
    m_carChassis = m_cPhysics->localCreateRigidBody(vehicleWeight,tr,compound, l_node_chassi);//chassisShape);
  // m_carChassis->setCenterOfMassTransform(localTrans);
    //    localTrans.setOrigin(btVector3(pos.X+20,pos.Y,pos.Z)); // moves chassi around and center of mass
    //btVector3 pos= m_carChassis->getCenterOfMassPosition();
//        tr.setOrigin(btVector3(pos[0]+20,pos[1],pos[1]));
    //    m_carChassis->setCenterOfMassTransform(tr);


//m_carChassis->translate
    m_vehicleRayCaster = new btDefaultVehicleRaycaster(m_cPhysics->getDynamicsWorld());
    m_vehicle = new btRaycastVehicle(m_tuning,m_carChassis,m_vehicleRayCaster);

    m_carChassis->setDamping(suspensionDamping,suspensionDamping);
    m_carChassis->setActivationState(DISABLE_DEACTIVATION);         // never deactivate the vehicle

    m_cPhysics->getDynamicsWorld()->addVehicle(m_vehicle);
    m_vehicle->setCoordinateSystem(rightIndex,upIndex,forwardIndex);//choose coordinate system

if(driveType<4){ // draw only 4 wheel vehicles
    // Create Vehicle Wheels
    bool isFrontWheel=true;
    btVector3 connectionPointCS0(CUBE_HALF_EXTENTS-(wheelSpacingX*wheelWidth),connectionHeight,wheelSpacingZ2*CUBE_HALF_EXTENTS-wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

    connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(wheelSpacingX*wheelWidth),connectionHeight,wheelSpacingZ2*CUBE_HALF_EXTENTS-wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

    isFrontWheel = false;
    connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(wheelSpacingX*wheelWidth),connectionHeight,-wheelSpacingZ*CUBE_HALF_EXTENTS+wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

    connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS-(wheelSpacingX*wheelWidth),connectionHeight,-wheelSpacingZ*CUBE_HALF_EXTENTS+wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
}
else if(driveType==4){ // Trikes
    bool isFrontWheel=true;
    btVector3 connectionPointCS0(0,connectionHeight,wheelSpacingZ2*CUBE_HALF_EXTENTS-wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

    isFrontWheel = false;
    connectionPointCS0 = btVector3(-CUBE_HALF_EXTENTS+(wheelSpacingX*wheelWidth),connectionHeight,-wheelSpacingZ*CUBE_HALF_EXTENTS+wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);

    connectionPointCS0 = btVector3(CUBE_HALF_EXTENTS-(wheelSpacingX*wheelWidth),connectionHeight,-wheelSpacingZ*CUBE_HALF_EXTENTS+wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
}
else if(driveType==5){ // Bikes
    bool isFrontWheel=true;
    btVector3 connectionPointCS0(0,connectionHeight,wheelSpacingZ*CUBE_HALF_EXTENTS-wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
   isFrontWheel = false;
    connectionPointCS0 = btVector3(0,connectionHeight,-wheelSpacingZ*CUBE_HALF_EXTENTS-wheelRadius);
    m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
}

///pythonize this to add wheels and shocks

/// add shocks
//connection point from wheelpos and axel
//use 2 cylenders of opposing bottom with y axis spring and scaling for shock model later

/// add dirt tracks ribbon node

    //Set Wheel Property's
    for (int i = 0; i < m_vehicle->getNumWheels(); i++)    {
        btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
        wheel.m_suspensionStiffness = suspensionStiffness;
        wheel.m_wheelsDampingRelaxation = suspensionDamping;
        wheel.m_wheelsDampingCompression = suspensionCompression;
        wheel.m_suspensionRestLength1 = suspensionRestLength;
        wheel.m_wheelsRadius = wheelRadius;
        wheel.m_frictionSlip = wheelFriction;
        wheel.m_rollInfluence = rollInfluence;
        //wheel.m_wheelsRadius
        //wheel.m_wheelsSuspensionForce = -1000;
    }



    printf("Adding wheels.\n");
    IAnimatedMeshSceneNode *tempNode;

    // IAnimatedMesh *l_nodessss;
    //    l_nodessss =  m_irrDevice->getSceneManager()->getMesh("data/models/vehicles/wheel.3ds") ;

    for (int i = 0; i < m_vehicle->getNumWheels(); i++)    {
        tempNode = m_irrDevice->getSceneManager()->addAnimatedMeshSceneNode(
        m_irrDevice->getSceneManager()->getMesh("data/models/vehicles/wheel.x") );
   //     if (i=0){
        tempNode->setMaterialTexture(0, m_irrDevice->getVideoDriver()->getTexture("data/models/vehicles/TIRE_TEX.TGA"));
    //    };
        tempNode->setScale(vector3df(   (wheelWidth*   wheelScaleFactor),
                                        (wheelRadius*  wheelScaleFactor),
                                        (wheelRadius*  wheelScaleFactor)));
        m_cScene->setGenericMaterial(tempNode, 0);
       // tempNode->getMaterial(0).Shininess = 100.0f;
        wheelNode.push_back(tempNode);
        //tempNode->addShadowVolumeSceneNode(l_nodessss,true, 100.f);
        //tempNode->getMaterial(0).Lighting=false;
        tempNode->addShadowVolumeSceneNode();
        tempNode->getMaterial(0).ZWriteEnable=1;
        //tempNode->getMaterial(0).ZWriteEnable=0;
        tempNode->getMaterial(0).BackfaceCulling = false;
    }
    m_numWheels = m_vehicle->getNumWheels();
//pushback (m_vehicle); // ?? untested
}

void Vehicle::updateVehicleMovement(void){
    gBreakingForce=0;
        int wheelIndex = 0; //! RWD
        if (driveType==0){
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                m_vehicle->setBrake(gBreakingForce,wheelIndex);
        wheelIndex = 1;
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                m_vehicle->setBrake(gBreakingForce,wheelIndex);
        wheelIndex = 2;
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                m_vehicle->setBrake(gBreakingForce,wheelIndex);
        wheelIndex = 3;
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                m_vehicle->setBrake(gBreakingForce,wheelIndex);
}
    else if (driveType==1) { //! 4x4 Wheel Drive
            wheelIndex = 0;
                            m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                            m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                            m_vehicle->setBrake(gBreakingForce,wheelIndex);
            wheelIndex = 1;
                            m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                            m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                            m_vehicle->setBrake(gBreakingForce,wheelIndex);
            wheelIndex = 2;
                            m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                            m_vehicle->setBrake(gBreakingForce,wheelIndex);
            wheelIndex = 3;
                            m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                            m_vehicle->setBrake(gBreakingForce,wheelIndex);
        }
    else if (driveType==2) { //! 4 wheel steering (gta monstertruck style)
            wheelIndex = 0;
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
            wheelIndex = 1;
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
            wheelIndex = 2;
                m_vehicle->setSteeringValue(-gVehicleSteering,wheelIndex);
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
            wheelIndex = 3;
                m_vehicle->setSteeringValue(-gVehicleSteering,wheelIndex);
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
        }
    else if (driveType==3) {
            int wheelIndex = 0; //!FWD
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
            wheelIndex = 1;
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
            wheelIndex = 2;
            wheelIndex = 3;
        }
       else if(driveType==4){
        int wheelIndex = 0; //!trike
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
            wheelIndex = 1;
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
            wheelIndex = 2;
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
        }
        else if(driveType==5){
        int wheelIndex = 0; //!BIKE
                m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                m_vehicle->setBrake(gBreakingForce,wheelIndex);
               // m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
            wheelIndex = 1;
             //   m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
                m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
      //      wheelIndex = 2;
       //     wheelIndex = 3;}
       //btVector3 angularfactor( 0, 1, 0 );
        //_bt_rigid_body->setAngularFactor( angularfactor );
        }
}

void Vehicle::recursiveFillMetaSelector(scene::ISceneNode* node, scene::IMetaTriangleSelector* meta ){
  //
  // the following if is basically the same as ISceneNode_assignTriangleSelector
  // adds the models in the node to physics mesh
  printf ("Node name is: %s \n",node->getName());
  printf ("Node id is: %d \n",node->getID());
  printf ("Node type:");
  //  printf ("Node type: %s=",smgr->getSceneNodeTypeName());
  if (node->getType() ==   ESNT_UNKNOWN) printf("Unknown mesh type \n\n");
  if (node->getType() ==   ESNT_MESH)
  {
      io::IAttributes* attribs = m_irrDevice->getFileSystem()->createEmptyAttributes();
      if (attribs)
        {// get the mesh name out
         node->serializeAttributes(attribs);
         core::stringc name = attribs->getAttributeAsString("Mesh");
         attribs->drop();
         // get the animated mesh for the object
         scene::IAnimatedMesh* mesh = m_irrDevice->getSceneManager()->getMesh(name.c_str());
         if (mesh)
         {
            printf("\tAdding triangle selector for mesh\n");
            scene::ITriangleSelector* selector =
            m_irrDevice->getSceneManager()->createTriangleSelector(mesh->getMesh(0), node);
            node->setTriangleSelector(selector);
            metaSelector->addTriangleSelector(selector);
            selector->drop();
/*
            node->setMaterialFlag(video::EMF_LIGHTING, true);
            node->getMaterial(0).Shininess = 100.0f;
            node->getMaterial(0).DiffuseColor = SColor(255,255,255,255);
            node->getMaterial(0).EmissiveColor = SColor(255,255,255,255);
            node->getMaterial(0).AmbientColor = SColor(255,255,255,255);
            node->getMaterial(0).SpecularColor = SColor(255,255,255,255);
            node->getMaterial(0).MaterialTypeParam = 0.01;
*/
            //node->getMaterial(0).MaterialType = EMT_ONETEXTURE_BLEND;
            //node->setFlag(EMF_TRILINEAR_FILTER, true);
         }
     }
  }

  if(strcmp(node->getName(), "elevator") == 0)  {
        node->setMaterialType(EMT_LIGHTMAP_M4);
        node->setMaterialFlag(EMF_LIGHTING, false);
        Elevator::Instance()->Add(node);
        Elevator::Instance()->elevatorStart = node->getAbsolutePosition();
        printf("elevator added");
        //    Elevator::Instance()->Clear();
  }

  if(strcmp(node->getName(), "obstacle") == 0)  {
	//	Obstacle::Instance()->Add(node);
  }

  if (node->getType() ==   ESNT_ANIMATED_MESH) printf("Animated Mesh! \n\n");
  if (node->getType() ==   ESNT_SKY_BOX) printf("SkyBox! \n\n");
  if (node->getType() ==   ESNT_CAMERA_FPS) printf("Fps Camera! \n\n");
  if (node->getType() ==   ESNT_CAMERA_MAYA ) printf("Maya Camera! \n\n");
  if (node->getType() ==   ESNT_CAMERA )
  { printf("STD Camera! \n");
   printf ("The current position of this camera is: %f,%f,%f\n\n",node->getPosition().X,node->getPosition().Y,node->getPosition().Z);
   camera->setPosition(node->getPosition());
  }
  if (node->getType() ==   ESNT_PARTICLE_SYSTEM ) printf("Particles! \n\n");
  if (node->getType() ==   ESNT_LIGHT  ) printf("Light! \n\n");
  if (node->getType() ==   ESNT_OCTREE)  { // occlusion trees
      // OccTrees are for land/surface/scene models
      printf("Occtree! \n");
      io::IAttributes* attribs = m_irrDevice->getFileSystem()->createEmptyAttributes();

      if (attribs)        {// get the mesh name out
         node->serializeAttributes(attribs);
         core::stringc name = attribs->getAttributeAsString("Mesh");
         attribs->drop();
         // get the animated mesh for the object
         scene::IAnimatedMesh* mesh = m_irrDevice->getSceneManager()->getMesh(name.c_str());

         if (mesh)         {
            scene::ITriangleSelector* selector =
            m_irrDevice->getSceneManager()->createOctTreeTriangleSelector(mesh->getMesh(0), node, 128);
            node->setTriangleSelector(selector);
            metaSelector->addTriangleSelector(selector);
            selector->drop();
         }
     }
  }
  // now recurse on children...
  core::list<scene::ISceneNode*>::ConstIterator begin = node->getChildren().begin();
  core::list<scene::ISceneNode*>::ConstIterator end   = node->getChildren().end();

  for (; begin != end; ++begin)
    recursiveFillMetaSelector(*begin, meta);
}


// time to serialize all this
void Vehicle::SetParams(
        float scaleT2,
        float scaleE2,
        btVector3 btCarScale2,
        btVector3 btModelscale2,
        btVector3 m_vehiclePosition2,
        int vehicleWeight2,
        float maxBreakingForce2,
        float maxEngineForce2,
        float SpeedINC2,
        int driveType2,
        float connectionHeight2,
        float suspensionStiffness2,
        float suspensionDamping2,
        float suspensionCompression2,
        //float suspensionRestLength2,
        float rollInfluence2,
        float wheelFriction2,
        float wheelRadius2,
        float wheelWidth2,
        float steeringIncrement2,
        float steeringClamp2,
        float CUBE_HALF_EXTENTS2 ,
        float wheelSpacingX2,
        //float wheelSpacingZ2,
        //float wheelSpacingZ22,
        float wheelScaleFactor2)
{
    int scaleT  = 1; // minimum 2 Vehicle Size test scale
    int scaleE  = 1;// engine/weight scale for friction
scaleT = scaleT2;
scaleE = scaleE2;
 btCarScale = btCarScale2*scaleT;
 btModelscale = btModelscale2*scaleT;
 m_vehiclePosition =m_vehiclePosition2*scaleT;
 vehicleWeight = vehicleWeight2;
 maxBreakingForce =maxBreakingForce2;
 maxEngineForce =maxEngineForce2;
 SpeedINC = SpeedINC2;
 driveType = driveType2;
 connectionHeight =connectionHeight2;
 suspensionStiffness =suspensionStiffness2;
 suspensionDamping = suspensionDamping2;
 suspensionCompression = suspensionCompression2;
// suspensionRestLength = suspensionRestLength2;
 rollInfluence = rollInfluence2;
 wheelFriction = wheelFriction2;
 wheelRadius =wheelRadius2;
 wheelWidth = wheelWidth2;
 steeringIncrement = steeringIncrement2;
 steeringClamp =steeringClamp2;
 CUBE_HALF_EXTENTS = CUBE_HALF_EXTENTS2;
 wheelSpacingX = wheelSpacingX2;
// wheelSpacingZ =wheelSpacingZ2;
 wheelScaleFactor =wheelScaleFactor2;
}


