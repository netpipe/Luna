#ifndef PYMAIN_H_INCLUDED
#define PYMAIN_H_INCLUDED
#ifdef PYTHON
//device->sleep(5,0); python delay for mainloop possibly use timers

#ifdef POLYVOX
	#include <PolyVoxCore/MaterialDensityPair.h>
	#include <PolyVoxCore/Material.h>
	#include <PolyVoxCore/CubicSurfaceExtractorWithNormals.h>
	#include <PolyVoxCore/SurfaceMesh.h>
	#include <PolyVoxCore/SimpleVolume.h>

//#include "..//include/MaterialDensityPair.h"

//#include "../Input/Model/PolyVox/PolyVoxCore/include/MaterialDensityPair.h"

#endif

PyMethodDef irr_Input[] =
{
    {"getKey",Python::PyIrr_getKey,METH_VARARGS,"get key state"},
    {"wii",Python::PyIrr_wii,METH_VARARGS,"wiimote access"},
    {"gamepad",Python::PyIrr_gamePad,METH_VARARGS,"gamepad"},
	{"mouse",Python::PyIrr_Mouse,METH_VARARGS,"mouse"},
	{"sqlconnect",Python::PyIrr_sqlconnect,METH_VARARGS,"sqlconnect"},
	{"sqlcommand",Python::PyIrr_sqlcommand,METH_VARARGS,"sqlcommand"},
	{"voxelLoad",Python::PyIrr_voxelLoad,METH_VARARGS,"voxelLoad"},
    {NULL,NULL,0,NULL}
};


bool Python::CheckKeyState(int key){
//EKEY_CODE akey;
//printf("checking key state \n");
//printf("value is %i \n",key);
bool keystate = mEvent.getKeyState( irr::EKEY_CODE(key) );
//if ( keystate == true  ){printf("pyKeyE pressed")};
//irr::EKEY_CODE(KEY_KEY_P)
//return irr::EKEY_CODE( keyValue );
return (keystate);
//return 1;
}

PyObject * Python::PyIrr_getKey(PyObject * self,PyObject * args){
//irr::EKEY_CODE StringToEKey_Code( std::string tempString )
	s32 key;
	 int keyValue,secondary;
    std::string tempString;
	char * tempString2;
	//	EKEY_CODE ekey;
	PyArg_ParseTuple(args,"s",&tempString2);
	tempString = tempString2;
//  parse key_key from tempString  // use primary and secondary key checking for common keys

/// tip from bobbo
//Wouldn't it be quicker/better/easier to just use std::map<std::string, EKEY_CODE> or similar container?
//Bobbo You'd basically have to setup your container, and then just do like `return keyMap.find(stringCode)->second;`

//switch ( EKEY_CODE(tempString)){//    case  KEY_KEY_P: 'KEY_KEY_E'
//    //mouse
//    case KEY_KEY_E://
//          keyValue = 0x45;
//          break;
//    case KEY_LBUTTON:
//         keyValue = 0x01;
//        break;
//}

// if joystick event may aswell check hat positions aswell
//const SEvent::SJoystickEvent & joystickData = receiver.GetJoystickState();
//
//			moveHorizontal =
//				(f32)joystickData.Axis[2] / 32767.f; //4 is the z 4 is
//			if(fabs(moveHorizontal) < DEAD_ZONE)
//				moveHorizontal = 0.f;
//
//			moveVertical =
//				(f32)joystickData.Axis[3] / 32767.f;
//			if(fabs(moveVertical) < DEAD_ZONE)
//				moveVertical = 0.f;

//		if (event.JoystickEvent.IsButtonPressed(0)){
//                         std::cout << "B0" << std::endl;
//		}




    bool keystate ;
	//   printf ("%s",tempString2);
	if (tempString2 > ""){   //not sure why but it seemed to speed things up a bit

	keyValue=-1;
    if          ( tempString == "KEY_LBUTTON" )    {  keyValue = 0x01; }
//    else if( tempString == "KEY_RBUTTON" )    {        keyValue = 0x02;}
//    else if( tempString == "KEY_CANCEL" )    {        keyValue = 0x03;}
//    else if( tempString == "KEY_MBUTTON" )    {        keyValue = 0x04;}
//    else if( tempString == "KEY_XBUTTON1" )    {        keyValue = 0x05;}
//    else if( tempString == "KEY_XBUTTON2" )    {        keyValue = 0x06;}
//    else if( tempString == "KEY_BACK" )    {        keyValue = 0x08;}
//    else if( tempString == "KEY_TAB" )    {        keyValue = 0x09;}
//    else if( tempString == "KEY_CLEAR" )    {        keyValue = 0x0C;}
       else if( tempString == "KEY_RETURN" )    {        keyValue = 0x0D;}
//    else if( tempString == "KEY_SHIFT" )    {        keyValue = 0x10;}
//    else if( tempString == "KEY_CONTROL" )    {        keyValue = 0x08;}
//    else if( tempString == "KEY_MENU" )    {        keyValue = 0x12;}
//    else if( tempString == "KEY_PAUSE" )    {        keyValue = 0x13;}
//    else if( tempString == "KEY_CAPITAL" )    {        keyValue = 0x14;}
//    else if( tempString == "KEY_KANA" )    {        keyValue = 0x15}
//    else if( tempString == "KEY_HANGUEL" )    {        keyValue = 0x15;}
//    else if( tempString == "KEY_HANGUL" )    {        keyValue = 0x15;}
//    else if( tempString == "KEY_JUNJA" )    {        keyValue = 0x17;}
//    else if( tempString == "KEY_FINAL" )    {        keyValue = 0x18;}
//    else if( tempString == "KEY_HANJA" )    {        keyValue = 0x19;}
//    else if( tempString == "KEY_KANJI" )    {        keyValue = 0x19;}
    else if( tempString == "KEY_ESCAPE" )    {        keyValue = 0x1B;}
//    else if( tempString == "KEY_CONVERT" )    {        keyValue = 0x1C;}
//    else if( tempString == "KEY_NONCONVERT" )    {        keyValue = 0x1D;}
//    else if( tempString == "KEY_ACCEPT" )    {        keyValue = 0x1E;}
//    else if( tempString == "KEY_MODECHANGE" )    {        keyValue = 0x1F;}
//
//
    else if( tempString == "KEY_SPACE" )    {        keyValue = 0x20;    }
//    else if( tempString == "KEY_PRIOR" )    {        keyValue = 0x21;    }
//    else if( tempString == "KEY_NEXT" )    {        keyValue = 0x22;    }
//    else if( tempString == "KEY_END" )    {        keyValue = 0x23;    }
//    else if( tempString == "KEY_HOME" )    {        keyValue = 0x24;    }
    else if( tempString == "KEY_LEFT" )    {        keyValue = 0x25;    }
    else if( tempString == "KEY_UP" )    {        keyValue = 0x26;    }
    else if( tempString == "KEY_RIGHT" )    {        keyValue = 0x27;    }
    else if( tempString == "KEY_DOWN" )    {        keyValue = 0x28;    }
//    else if( tempString == "KEY_SELECT" )    {        keyValue = 0x29;    }
//    else if( tempString == "KEY_PRINT" )    {        keyValue = 0x2A;    }
//    else if( tempString == "KEY_EXECUT" )    {        keyValue = 0x2B;    }
//    else if( tempString == "KEY_SNAPSHOT" )    {        keyValue = 0x2C;    }
//    else if( tempString == "KEY_INSERT" )    {        keyValue = 0x2D;    }
//    else if( tempString == "KEY_DELETE" )    {        keyValue = 0x2E;    }
//    else if( tempString == "KEY_HELP" )    {        keyValue = 0x2F;    }

//
//    //numbers
//    else if( tempString == "KEY_KEY_1" )    {        keyValue = 0x30;    }
//    else if( tempString == "KEY_KEY_2" )    {        keyValue = 0x31;    }
//    else if( tempString == "KEY_KEY_3" )    {        keyValue = 0x32;    }
//    else if( tempString == "KEY_KEY_4" )    {        keyValue = 0x33;    }
//    else if( tempString == "KEY_KEY_5" )    {        keyValue = 0x34;    }
//    else if( tempString == "KEY_KEY_6" )    {        keyValue = 0x35;    }
//    else if( tempString == "KEY_KEY_7" )    {        keyValue = 0x36;    }
//    else if( tempString == "KEY_KEY_8" )    {        keyValue = 0x37;    }
//    else if( tempString == "KEY_KEY_8" )    {        keyValue = 0x38;    }

    //letters
//    else if( tempString == "KEY_KEY_A" )    {        keyValue = 0x41;    }
//    else if( tempString == "KEY_KEY_B" )    {        keyValue = 0x42;    }
//    else if( tempString == "KEY_KEY_C" )    {        keyValue = 0x43;}
//    else if( tempString == "KEY_KEY_D" )    {        keyValue = 0x44;}
    else if( tempString == "KEY_KEY_E" )    {        keyValue = 0x45;}
//    else if( tempString == "KEY_KEY_F" )    {        keyValue = 0x46;}
//    else if( tempString == "KEY_KEY_G" )    {        keyValue = 0x47;}
//    else if( tempString == "KEY_KEY_H" )    {        keyValue = 0x48;}
//    else if( tempString == "KEY_KEY_I" )    {        keyValue = 0x49;}
//    else if( tempString == "KEY_KEY_J" )    {        keyValue = 0x4A;}
    else if( tempString == "KEY_KEY_A" )    {        keyValue = 0x41;    }
//    else if( tempString == "KEY_KEY_B" )    {        keyValue = 0x42;    }
//    else if( tempString == "KEY_KEY_C" )    {        keyValue = 0x43;}
    else if( tempString == "KEY_KEY_D" )    {        keyValue = 0x44;}
//    else if( tempString == "KEY_KEY_E" )    {        keyValue = 0x45;}
//    else if( tempString == "KEY_KEY_F" )    {        keyValue = 0x46;}
//    else if( tempString == "KEY_KEY_G" )    {        keyValue = 0x47;}
//    else if( tempString == "KEY_KEY_H" )    {        keyValue = 0x48;}
//    else if( tempString == "KEY_KEY_I" )    {        keyValue = 0x49;}
//    else if( tempString == "KEY_KEY_J" )    {        keyValue = 0x4A;}
//     else if( tempString == "KEY_KEY_K" )    {        keyValue = 0x43;}
//    else if( tempString == "KEY_KEY_L" )    {        keyValue = 0x44;}
//    else if( tempString == "KEY_KEY_M" )    {        keyValue = 0x45;}
//    else if( tempString == "KEY_KEY_N" )    {        keyValue = 0x46;}
//    else if( tempString == "KEY_KEY_O" )    {        keyValue = 0x47;}
//    else if( tempString == "KEY_KEY_P" )    {        keyValue = 0x48;}
//    else if( tempString == "KEY_KEY_Q" )    {        keyValue = 0x49;}
       else if( tempString == "KEY_KEY_R" )    {        keyValue = 0x52;}
       else if( tempString == "KEY_KEY_S" )    {        keyValue = 0x53;}
//    else if( tempString == "KEY_KEY_T" )    {        keyValue = 0x54;}
//    else if( tempString == "KEY_KEY_U" )    {        keyValue = 0x55;}
//    else if( tempString == "KEY_KEY_V" )    {        keyValue = 0x56;}
    else if( tempString == "KEY_KEY_W" )    {        keyValue = 0x57;}
//    else if( tempString == "KEY_KEY_X" )    {        keyValue = 0x58;}
//    else if( tempString == "KEY_KEY_Y" )    {        keyValue = 0x59;}
//    else if( tempString == "KEY_KEY_Z" )    {        keyValue = 0x5A;}
//
//    //fkeys
    else if( tempString == "KEY_F1" )    {        keyValue = 0x70;}
    else if( tempString == "KEY_F2" )    {        keyValue = 0x71;}
    else if( tempString == "KEY_F3" )    {        keyValue = 0x72;}
    else if( tempString == "KEY_F4" )    {        keyValue = 0x73;}
    else if( tempString == "KEY_F5" )    {        keyValue = 0x74;}
//    else if( tempString == "KEY_F6" )    {        keyValue = 0x75;}
//    else if( tempString == "KEY_F7" )    {        keyValue = 0x76;}
//    else if( tempString == "KEY_F8" )    {        keyValue = 0x77;}
//    else if( tempString == "KEY_F9" )    {        keyValue = 0x78;}
//    else if( tempString == "KEY_F10" )    {        keyValue = 0x79;}
//    else if( tempString == "KEY_F11" )    {        keyValue = 0x7A;}
//    else if( tempString == "KEY_F12" )    {        keyValue = 0x7B;}


//    else if( tempString == "KEY_F13" )    {        keyValue = 0x7C;}
//    else if( tempString == "KEY_F14" )    {        keyValue = 0x7D;}
//    else if( tempString == "KEY_F15" )    {        keyValue = 0x7E;}
//    else if( tempString == "KEY_F16" )    {        keyValue = 0x7F;}
//KEY_F16
//KEY_F17
//KEY_F18
//KEY_F19
//KEY_F20
//KEY_F21
//KEY_F22
//KEY_F23
//KEY_F24

    //numberpad

//    else if( tempString == "KEY_LWIN" )    {        keyValue = 0x7E;}
//    else if( tempString == "KEY_RWIN" )    {        keyValue = 0x7F;}
//    else if( tempString == "KEY_APPS" )    {        keyValue = 0x7E;}
//    else if( tempString == "KEY_SLEEP" )    {        keyValue = 0x7F;}
//
//    else if( tempString == "KEY_NUMPAD0" )    {        keyValue = 0x60;}
//    else if( tempString == "KEY_NUMPAD1" )    {        keyValue = 0x61;}
//    else if( tempString == "KEY_NUMPAD2" )    {        keyValue = 0x62;}
//    else if( tempString == "KEY_NUMPAD3" )    {        keyValue = 0x63;}
//    else if( tempString == "KEY_NUMPAD4" )    {        keyValue = 0x64;}
//    else if( tempString == "KEY_NUMPAD5" )    {        keyValue = 0x65;}
//    else if( tempString == "KEY_NUMPAD6" )    {        keyValue = 0x66;}
//    else if( tempString == "KEY_NUMPAD7" )    {        keyValue = 0x67;}
//    else if( tempString == "KEY_NUMPAD8" )    {        keyValue = 0x68;}
//    else if( tempString == "KEY_NUMPAD9" )    {        keyValue = 0x69;}
//    else if( tempString == "KEY_MULTIPLY" )    {        keyValue = 0x6A;}
//    else if( tempString == "KEY_ADD" )    {        keyValue = 0x6B;}
//    else if( tempString == "KEY_SEPARATOR" )    {        keyValue = 0x6C;}
//    else if( tempString == "KEY_SUBTRACT" )    {        keyValue = 0x6D;}
//    else if( tempString == "KEY_DECIMAL" )    {        keyValue = 0x6E;}
//    else if( tempString == "KEY_DIVIDE" )    {        keyValue = 0x6F;}
//
//    else if( tempString == " KEY_NUMLOCK" )    {        keyValue = 0x90;}
//    else if( tempString == "KEY_SCROLL" )    {        keyValue = 0x91;}
//    else if( tempString == " KEY_LSHIFT" )    {        keyValue = 0xA0;}
//    else if( tempString == "KEY_RSHIFT" )    {        keyValue = 0xA1;}
//    else if( tempString == " KEY_LCONTROL" )    {        keyValue = 0xA2;}
//    else if( tempString == "KEY_RCONTROL" )    {        keyValue = 0xA3;}
//    else if( tempString == " KEY_LMENU" )    {        keyValue = 0xA4;}
//    else if( tempString == "KEY_RMENU" )    {        keyValue = 0xA5;}
//
//    else if( tempString == " KEY_OEM_1" )    {        keyValue = 0xBA;}
//    else if( tempString == "KEY_PLUS" )    {        keyValue = 0xBB;}
//    else if( tempString == " KEY_COMMA" )    {        keyValue = 0xBC;}
//    else if( tempString == "KEY_MINUS" )    {        keyValue = 0xBD;}
//
//    else if( tempString == " KEY_PERIOD" )    {        keyValue = 0xBE;}
//    else if( tempString == "KEY_OEM_2" )    {        keyValue = 0xBF;}
//    else if( tempString == " KEY_OEM_3" )    {        keyValue = 0xC0;}
//    else if( tempString == "KEY_OEM_4" )    {        keyValue = 0xDB;}
//    else if( tempString == " KEY_OEM_5" )    {        keyValue = 0xDC;}
//    else if( tempString == "KEY_OEM_6" )    {        keyValue = 0xDD;}
//    else if( tempString == " KEY_OEM_7" )    {        keyValue = 0xDE;}
//    else if( tempString == "KEY_OEM_8" )    {        keyValue = 0xDF;}
//    else if( tempString == "KEY_OEM_9" )    {        keyValue = 0xE0;}// NOT SURE ABOUT THIS KEYVALUE
//
//    else if( tempString == "KEY_OEM_AX" )    {        keyValue = 0xE1;}
//    else if( tempString == " KEY_OEM_102" )    {        keyValue = 0xE2;}
//    else if( tempString == "KEY_ATTN" )    {        keyValue = 0xF6;}
//    else if( tempString == " KEY_CRSEL" )    {        keyValue = 0xF7;}
//    else if( tempString == "KEY_EXSEL" )    {        keyValue = 0xF8;}
//    else if( tempString == " KEY_EREOF" )    {        keyValue = 0xF9;}
//    else if( tempString == "KEY_PLAY" )    {        keyValue = 0xFA;}
//    else if( tempString == "KEY_ZOOM" )    {        keyValue = 0xFB;}
//
//    else if( tempString == "KEY_PA1" )    {        keyValue = 0xFC;}
//    else if( tempString == " KEY_OEM_CLEAR" )    {        keyValue = 0xFE;}
//    else if( tempString == "KEY_KEY_CODES_COUNT" )    {        keyValue = 0xFF;}
    //extras

    else
    {
          return Py_BuildValue("b",0);
    // No keycode match for string.
    }
//keyValue=0;
	if (keyValue >= -1){
   keystate = CheckKeyState( keyValue );
	}
}

	// bool keystate = mEvent.getKeyState(irr::EKEY_CODE(keyValue));

 //  if (keystate == true ){printf("the key was pressed");}
  return Py_BuildValue("b",keystate);
}




PyObject * Python::PyIrr_voxelLoad(PyObject * self,PyObject * args){

	int type;
//	char * gui,*driver,*smgr;
	char * device;
		char * path;
	PyArg_ParseTuple(args,"ss",&device,&path);
#ifdef POLYVOX
   wchar_t cBuffer[100];
    int move;

//    gui::IGUIEnvironment* device = device->getGUIEnvironment();

//    gui::IGUIEnvironment* gui = device->getGUIEnvironment();
//    video::IVideoDriver* driver = device->getVideoDriver();
//    irr::scene::ISceneManager* smgr = device->getSceneManager();

//    createMandelbulb(volData);



    //Extract the surface
//    PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal> polyvoxmesh;
//    PolyVox::CubicSurfaceExtractorWithNormals<PolyVox::SimpleVolume< uint8_t >> surfaceExtractor(&volData, volData.getEnclosingRegion(), &polyvoxmesh);
//    surfaceExtractor.execute();
//
//SMesh * testmesh = new SMesh();
//
//
//    irr::scene::IMeshBuffer * testbuffer = ConvertMesh(polyvoxmesh);
//    printf("%i ",testbuffer->getVertexCount());
//    printf("%i ",testbuffer->getIndexCount());
//    testmesh->addMeshBuffer(testbuffer);
//    testmesh->recalculateBoundingBox();
//
//
//    scene::ISceneNode * testnode = smgr->addMeshSceneNode(testmesh); //, core::vector3df(2000, 1000, 2000),core::vector3df(0, 100, 0),core::vector3df(20.0F, 20.0F, 20.0F));
//
//
//    testnode->setMaterialFlag(EMF_LIGHTING, true);
//
//    testnode->setMaterialType( video::EMT_SOLID );
//
//    testnode->setMaterialTexture(0, driver->getTexture("textureatlas.bmp"));
//    testnode->getMaterial(0).getTextureMatrix(0).setRotationDegrees(
//                        core::vector3d<f32>(0.0f, 0.0f, 180 ));
//    testnode->getMaterial(0).getTextureMatrix(0).setTextureTranslate(0.5f,0.5f);
//    testnode->setRotation(core::vector3df(0.0f, 180.0f, 0.0f));
//
//    gui::IGUIFont* font =
//        device->getGUIEnvironment()->getFont("arialbold.bmp");






//irr::scene::IMeshBuffer* ConvertMesh(const PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal>& mesh) {
//
//
//   const std::vector<uint32_t>& indices = mesh.getIndices();
//   const std::vector<PolyVox::PositionMaterialNormal>& vertices = mesh.getVertices();
//
//   irr::scene::IDynamicMeshBuffer *mb = new irr::scene::CDynamicMeshBuffer(irr::video::EVT_STANDARD, irr::video::EIT_32BIT);
//
//   mb->getVertexBuffer().set_used(vertices.size());
//   for (size_t i = 0; i < vertices.size(); ++i) {
//       const PolyVox::Vector3DFloat& position = vertices[i].getPosition();
//       const PolyVox::Vector3DFloat& normal = vertices[i].getNormal();
//       mb->getVertexBuffer()[i].Pos.X = position.getX();
//       mb->getVertexBuffer()[i].Pos.Y = position.getY();
//       mb->getVertexBuffer()[i].Pos.Z = position.getZ();
//       mb->getVertexBuffer()[i].Normal.X = normal.getX();
//       mb->getVertexBuffer()[i].Normal.Y = normal.getY();
//       mb->getVertexBuffer()[i].Normal.Z = normal.getZ();
//       mb->getVertexBuffer()[i].Color = irr::video::SColor(255,0,200,200);
//   }
//
//   mb->getIndexBuffer().set_used(indices.size());
//   for (size_t i = 0; i < indices.size(); ++i) {
//       mb->getIndexBuffer().setValue(i, indices[i]);
//   }
//   mb->recalculateBoundingBox();
//   return mb;
//}

//
// //http://irrlicht.sourceforge.net/forum/viewtopic.php?f=9&t=45175&p=284526&hilit=polyvox#p284526
//
//        //Transform voxel into mesh
//PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal> mesh;
//PolyVox::CubicSurfaceExtractorWithNormals< PolyVox::SimpleVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
////PolyVox::MarchingCubesSurfaceExtractor< PolyVox::SimpleVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);
//surfaceExtractor.execute();
//
////Transform mesh into irrlicht mesh
//irr::scene::IMeshSceneNode* levelMesh=sceneManager->addMeshSceneNode(convertPolyMesh(mesh));
#endif

}
#ifdef POLYVOX
irr::scene::SMesh* convertPolyMesh(const PolyVox::SurfaceMesh<PolyVox::PositionMaterialNormal>& meshPoly) {
   //irr::scene::SMeshBuffer* buffer =new irr::scene::SMeshBuffer();
   irr::scene::IDynamicMeshBuffer* buffer =new irr::scene::CDynamicMeshBuffer(irr::video::EVT_STANDARD, irr::video::EIT_32BIT);
   irr::video::SColor clr(255,255,255,255);

   const std::vector<uint32_t>& indices = meshPoly.getIndices();
   const std::vector<PolyVox::PositionMaterialNormal>& vertices = meshPoly.getVertices();

   // Create indices
   //buffer->Indices.set_used(indices.size());
//    for (size_t i=0; i<indices.size(); ++i) {
//        buffer->Indices[i] = indices[i];
//    }
   buffer->getIndexBuffer().set_used(indices.size());
   for (size_t i = 0; i < indices.size(); ++i) {
       buffer->getIndexBuffer().setValue(i, indices[i]);
   }

   // Create vertices
//    buffer->Vertices.reallocate(vertices.size());
//    for (size_t i = 0; i < vertices.size(); ++i) {
//        const PolyVox::Vector3DFloat& position = vertices[i].getPosition();
//        const PolyVox::Vector3DFloat& normal = vertices[i].getNormal();
//        buffer->Vertices.push_back(irr::video::S3DVertex(position.getX(),position.getY(),position.getZ(),normal.getX(),normal.getY(),normal.getZ(), clr, 0, 0));
//    }
   buffer->getVertexBuffer().set_used(vertices.size());
   for (size_t i = 0; i < vertices.size(); ++i) {
       const PolyVox::Vector3DFloat& position = vertices[i].getPosition();
       const PolyVox::Vector3DFloat& normal = vertices[i].getNormal();
       buffer->getVertexBuffer()[i].Pos.X = position.getX();
       buffer->getVertexBuffer()[i].Pos.Y = position.getY();
       buffer->getVertexBuffer()[i].Pos.Z = position.getZ();
       buffer->getVertexBuffer()[i].Normal.X = normal.getX();
       buffer->getVertexBuffer()[i].Normal.Y = normal.getY();
       buffer->getVertexBuffer()[i].Normal.Z = normal.getZ();
       buffer->getVertexBuffer()[i].Color = irr::video::SColor(255,255,255,255);
   }

   // Recalculate bounding box
   buffer->recalculateBoundingBox();
//    buffer->BoundingBox.reset(0,0,0);
//    for (u32 i=0; i<vertices.size(); ++i) {
//        buffer->BoundingBox.addInternalPoint(buffer->Vertices[i].Pos);
//    }
   //Create mesh
   irr::scene::SMesh* mesh =new irr::scene::SMesh;
   //irr::video::SMaterial mat;
   //buffer->Material=mat;
   mesh->addMeshBuffer(buffer);
   buffer->drop();

   mesh->recalculateBoundingBox();
   return mesh;
}

#endif

PyObject * Python::PyIrr_wii(PyObject * self,PyObject * args){
// wii device accessor keystate return
	char * btaddr;
	char * type;
	//	EKEY_CODE ekey;
	PyArg_ParseTuple(args,"ss",&type,&btaddr);


//	if (type = "wii"){
//		Wii_init();
//	cwiid_wiimote_t *wiimote;	/* wiimote handle */
//	struct cwiid_state state;	/* wiimote state */
//	bdaddr_t bdaddr;	/* bluetooth device address */
//	unsigned char mesg = 0;
//	unsigned char led_state = 0;
//	unsigned char rpt_mode = 0;
//	unsigned char rumble = 0;
//	int exit = 0;
//
//	cwiid_set_err(err);


//	}
//	if (type = "wii-led1"){
////		();
//	}



	return Py_BuildValue("");
}

PyObject * Python::PyIrr_gamePad(PyObject * self,PyObject * args){

	s32 key;
	int udev;
	char * type;
	//	EKEY_CODE ekey;
	PyArg_ParseTuple(args,"ss",&type,&udev);



	return Py_BuildValue("");
}

PyObject * Python::PyIrr_Mouse(PyObject * self,PyObject * args){
int type;
	PyArg_ParseTuple(args,"i",&type);

	//setcursor position
	//get cursor position
	//visible

device->getCursorControl()->setVisible(type);
  return Py_BuildValue("");
}

PyObject * Python::PyIrr_sqlconnect(PyObject * self,PyObject * args){
int type;
char * cstring;
	PyArg_ParseTuple(args,"is",&type,&cstring);
#ifdef SQLITE
	  sqlite3 *db;
   fprintf(stderr, "Opening DB \n");
    rc = sqlite3_open( cstring, &db);
    if( rc ){
        fprintf(stderr,"Can't open database: %s\n", sqlite3_errmsg(db));
  }
     fprintf(stderr, "DB READY \n");

//	    sqlCon *sq =new sqlCon(cstring);
//    //  sq->execute(".dump");
//     // needs error management if table exists it crashse
//      sq->execute("CREATE TABLE learnss (y string,a integer, b string);");
//    //  sq->execute("insert into learnss (y,a,b) VALUES('ssssnipples',33 , 34);");
//    //  sq->execute("INSERT INTO learn (a,b) VALUES(33 , 34);");
//        sq->execute("SELECT * FROM learnss where b like '34%';");
//    //  sq->execute("SELECT * FROM learn");
//    //  sq->execute("PRAGMA table_info(learnss)");
//    //  sq->execute("SELECT * FROM sqlite_master WHERE tbl_name = 'learnss' AND type = 'table'");

//  return Py_BuildValue("l",sq);
return Py_BuildValue("l",db);
#endif
}

PyObject * Python::PyIrr_sqlcommand(PyObject * self,PyObject * args){
int type;
char * command;
long sqlconn2;
	PyArg_ParseTuple(args,"lis",&sqlconn2,&type,&command);
	#ifdef SQLITE
//	sqlCon *sq=sqlconn2;
//	sq->execute(cstring);
sqlite3 *db=(sqlite3 *)sqlconn2;
  int nrow;
  int ncol;
   fprintf(stderr, "Executing Command \n");

    rc = sqlite3_prepare(db, "PRAGMA table_info(learnss)", strlen(command), &stmt, 0);
    int col_cnt = sqlite3_column_count(stmt);
    printf("do tokanizing on  #%i Cols\n",col_cnt);



            sqlite3_reset(stmt);
            int result;

            for ( int i=0; i < col_cnt/2  ;i++){
                    rc = sqlite3_step(stmt);

                const  unsigned char* vp = sqlite3_column_text(stmt, i);
                printf( "%s ", vp);
            };
            printf("   =-=");
       //     sqlite3_finalize(stmt);


   rc = sqlite3_prepare(db, command, strlen(command), &stmt, 0); // -1 for the string length seems to work too.
    //  rc = sqlite3_exec(db, command, sqlCon::callback, 0, &zErrMsg);



/*  <<they should make coment folding into CB for certain things
      rc = sqlite3_get_table(
			db,              // An open database
			command,        //SQL to be executed
			&result,        //Result written to a char *[]  that this points to
			&nrow,          //    Number of result rows written here
			&ncol,           //Number of result columns written here
			&zErrMsg          // Error msg written here
			);

	  printf("nrow=%d ncol=%d\n",nrow,ncol);
	 // printf("PRINTING 2 ROWS ONLY \n");
        for(int i=0 ; i < nrow+ncol; ++i){
            printf("#%i ",i);
            printf("%s ",result[i]);
            //++i;
            //printf("#%i ",i);
            //printf("%s \n",result[i]);
        }
*/

printf("   =-=");
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

    int rowcount;
   col_cnt = sqlite3_column_count(stmt);
printf("there is #%i columns \n",col_cnt);
bool  finished = false;
  while (!finished) {
      if(col_cnt !=0){
    rc = sqlite3_step(stmt);
    switch (rc) {
      case SQLITE_DONE:     //Execution finished.
        finished = true;
        sqlite3_reset(stmt);  //Resets the compiled statement for re-use.
        //Execute logic for end of data set.
        break;
      case SQLITE_ROW:      //We have a row.
        if (rowcount == 0) {
         // Execute code for start of data set

        }

        //Scan all the columns.  Return value in "strg"
        for (int a = 0; a < col_cnt; a++) {
          //Get actual type.
          switch (sqlite3_column_type(stmt, a)) {
            case SQLITE_INTEGER:
              result = sqlite3_column_int(stmt, a);
              printf( "%d ", result);
              break;
            case SQLITE_FLOAT:
              {
                //Float to string.
                double  dub;
                dub = sqlite3_column_double(stmt, a);
                printf( "%f", dub);
              }
              break;
            case SQLITE_TEXT:
             {
                const  unsigned char* vp = sqlite3_column_text(stmt, a);
                //  sqlite3_stmt *p = stmt;
                printf( "%s ", vp);
                //  while (*vp > 0)            //        { *p++ = *vp++;}
              break;
              }
            case SQLITE_BLOB:
              //Write to a file, dynamic memory ...
              break;
            case SQLITE_NULL:
             {
        //   stmt[0] = 0;
              break;
             }
          }  //switch
        }    //for
 printf( "\n");
       rowcount++;
        break;
             default:
             {
        sqlite3_finalize(stmt);
        break;
             }
    };
  } else {
      printf( "EXECUTED A COMMAND WITH NULL RESULTS\n");
     finished = true;};

  }
    #endif
  return Py_BuildValue("");
}

void Python::CheckKeyStates(){

//obsolete moving this to python ni

    #ifdef BITCLOUD
            clouds->render();
            #endif

#ifdef CHOPPER
if (chopperEnabled){

        //  printf("Jump position: %f %f %f \n", pos[0], pos[1], pos[2]);
     //   camera->setPosition(vector3df( ha.X, ha.Y+40, ha.Z));
        chopperControl->checkKey();
        chopperControl->update();
        chopperControl->updateAbsolutePosition();

//       vector3df ha = chopperControl->RootEmpty->getPosition();
//        camera->bindTargetAndRotation(1);
//        camera->setParent(chopperControl->RootEmpty);

//
//        irr::core::matrix4 m;
//        m.setRotationDegrees(chopperControl->RootEmpty->getRotation());
//   //     irr::core::vector3df upv = irr::core::vector3df (0.0f, 1.0f, 0.0f);    m.transformVect(upv);
//        irr::core::vector3df frv = irr::core::vector3df (0.0f, 0.0f, 10.0f);    m.transformVect(frv);
//
//        camera->setTarget( ha+frv);
//        //camera->setPosition(ha);
////        camera->setUpVector(upv); //set up vector of camera.
//        camera->setRotation(chopperControl->YawEmpty->getRotation());
//        camera->updateAbsolutePosition();
    }
#endif

            #ifdef occlusion
                if (bOcclusion){
                RenderMan->updateCulling();
                }
            #endif

//    if (mEvent.getKeyState(    KEY_ESCAPE))
//                    {mEvent.Quit = true;}


//    if (mEvent.getKeyState(    KEY_SPACE))    //SPACEBAR
//    {    //  m_cPlayer->jump();
//            vector3df ha = camera->getAbsolutePosition();
//      //  printf("Jump position: %f %f %f \n", pos[0], pos[1], pos[2]);
//        camera->setPosition(vector3df( ha.X, ha.Y+40, ha.Z));
//     //   camera->setTarget(vector3df(1000,1000,1000));
//    }

//#define BULLETCAR  // needtofix global defines should not be here
//    #ifdef BULLETCAR // send print to console saying engine not compiled with bullet support
//    if (bCar){
//    if (mEvent.getKeyState(    irr::EKEY_CODE(KEY_KEY_P)))
//    {
//        btVector3 pos = m_cVehicle->getVehiclePosition();
//        vector3df ha = vector3df(pos[0], pos[1]+10, pos[2]);
//        printf("Vehicle position: %f %f %f \n", pos[0], pos[1], pos[2]);
//        camera->setPosition(vector3df( ha.X, ha.Y, ha.Z));
//    }
//
//    if (mEvent.getKeyState(    KEY_KEY_8))
//    {
//        vector3df ha = camera->getPosition();
//        m_cVehicle->setPosition(vector3df( ha.X, ha.Y, ha.Z));
//    }
//
//    if (mEvent.getKeyState(    KEY_KEY_1))
//    {
//        vector3df pos = camera->getPosition();
//        vector3df scl = vector3df(1,1,1);
//        luna->m_cPhysics->createBox( btVector3(pos.X, pos.Y, pos.Z), btVector3(scl.X, scl.Y, scl.Z), 10); //weight
//    }


#ifdef DECALS
  if(bDecals){
        btVector3 Normal;
//      vector3df pos = camera->getPosition();
        vector3df upvect = camera->getUpVector();
        vector3df target = camera->getTarget();

        core::line3d<f32> line;
		line.start = camera->getPosition();
		line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;


#ifdef PHYSICS
        btVector3 rayHit = luna->m_cPhysics->RaycastWorld(btVector3(line.start.X, line.start.Y, line.start.Z),btVector3(line.end.X, line.end.Y, line.end.Z),Normal);
        printf("ray position position: %f %f %f \n", rayHit[0], rayHit[1], rayHit[2]);
        printf("hit normal vector: %f %f %f \n", Normal[0], Normal[1], Normal[2]);
#endif

#ifdef DECALS2s

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
#ifdef DECALSs
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
//}
//device->sleep(5,0);
#endif //decals

//    if (mEvent.getKeyState(    KEY_KEY_4))    //SPACEBAR
//    {
//        vector3df pos = camera->getPosition();
//        vector3df scl = vector3df(1,1,1);
//        btRigidBody *had = luna->m_cPhysics->createBox( btVector3(pos.X, pos.Y, pos.Z),
//                                                                btVector3(scl.X, scl.Y, scl.Z), 10); //weight
//                                                                had->setLinearVelocity(btVector3(8000,0,1));
//    }

//    if (mEvent.getKeyState(    KEY_SPACE))    //SPACEBAR
//                    {m_cVehicle->brake();   }

//    if (mEvent.getKeyState(    KEY_KEY_2))
//    {
//        //if ( icount > 15){ //sphere limiter
//            vector3df pos = camera->getPosition();
//            vector3df rot = camera->getRotation();
//            bingo=1;
//            if (bingo) { // suposed to only create 1 sphere then transport you to it if its made already
//                ha2 = luna->m_cPhysics->createSphere( btVector3(pos.X, pos.Y, pos.Z),2,5);
//                //ha2->setAngularVelocity(btVector3(400,400,400));
//                bingo= false;
//            } else {
//                btVector3 pos2 = ha2->getCenterOfMassPosition();
//                camera->setPosition(vector3df(pos2[0],pos2[1],pos2[2]));
//            }
//        //  ha2->clearForces();
//        // ha2->applyDamping(100);
//        // ha2->applyForce(btVector3(50,8000,50),btVector3(110,111,110));
//        // icount=0;
//        //m_cPhysics->clearBodies(); crashes
//    // }
////         icount++;
//    }

//    if (bCar) {
//    if (mEvent.getKeyState(    KEY_KEY_R))
//                    {m_cVehicle->resetVehicle();
                            // Park camera where the vehicle is.


       //   m_cVehicle->setPosition(camera->getPosition());
//           }
//    if (bCarFollow) {
//    // this is for putting the camera above the car
//        btVector3 point = m_cVehicle->getVehiclePosition();
//        camera->setPosition(vector3df(
//          (f32)point[0],
//          (f32)point[1]+10,
//          (f32)point[2]-50));
//    }
//    if (mEvent.getKeyState(    irr::EKEY_CODE( 0x26 ) ))//KEY_UP)  ) ///| getkey.keyUP
//                    {m_cVehicle->accelerate(1);}// need gears or something haha
//  //  else if (!mEvent.getKeyState(  KEY_UP) && (m_cVehicle->getState() != EVEHICLE_REVERSING))
//      //              {m_cVehicle->accelerate(-1);}   //wind resistance
//// not working just keeps accelerating moved to speed incs
//
//    if (mEvent.getKeyState(    KEY_DOWN))
//                    {m_cVehicle->reverse(1);    }
////    else if (!mEvent.getKeyState(  KEY_DOWN) && (m_cVehicle->getState() != EVEHICLE_ACCELERATING))
////                    {m_cVehicle->reverse(0.3);}      // wind resistance
//    if (mEvent.getKeyState(    KEY_LEFT))
//                    {m_cVehicle->steer_left(); }
//    if (mEvent.getKeyState(    KEY_RIGHT))
//                    {m_cVehicle->steer_right(); }
//    if (!mEvent.getKeyState(   KEY_LEFT) && !mEvent.getKeyState(KEY_RIGHT))
//                    {m_cVehicle->steer_reset(); }
//    }
//#endif

//#define bskeleton
#ifdef SKELETON
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



//        if (mEvent.getKeyState(KEY_ESCAPE )) {
//		luna->m_cInGameEvents.Quit=true;
//		return;
//		}



//vector3df ha = camera->getAbsolutePosition();
 //   camera->setPosition(vector3df( ha.X, ha.Y-11, ha.Z));
//device->sleep(5,0);
}



#endif // PYMAIN_H_INCLUDED
#endif
