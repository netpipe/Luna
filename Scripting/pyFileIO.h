PyMethodDef irr_FileIO[] = {
{"tiled",Python::PyIrr_Tiled,METH_VARARGS,"tiled"},
//{"zistream",Python::PyIrr_zistream,METH_VARARGS,"sets camera vector"},
    {"zistream",Python::PyIrr_zistream,METH_VARARGS,"sets camera vector"},
    {"zostream",Python::PyIrr_zostream,METH_VARARGS,"sets camera vector"},
	{"files",Python::PyIrr_FileArchive,METH_VARARGS,"file archive manager"},
	{NULL,NULL,0,NULL}
};


ITimer* timer ;
	s32 currentFrameIndex = 0;
	f32 currentFrameTime = 0;
	f32 deltaTime, oldTime = 0;

PyObject * Python::PyIrr_Tiled(PyObject * self,PyObject * args){
	char * t;
	int test=0;
	PyArg_ParseTuple(args,"si",&t, &test);

		timer = device->getTimer();
#ifdef TILED2D
switch (test){

    case 0:{
        tld = new irrTiled(t,device);
        //tld = new irrTiled("../media/tiled2d/2dbasic.tmx",device);
    }break;

    case 1:{
        // Extracts data from all tile sets.
		for (u32 i = 0; i < tld->tileset.size(); ++i)
		{
			TILESET ts = tld->tileset[i];

			// Extracts data from all layers.
			for (u32 j = 0; j < tld->layer.size(); ++j)
			{
				LAYER lyr = tld->layer[j];

				for (u32 d = 0; d < lyr.data.size(); ++d)
				{
					s32 id = lyr.data[d] - ts.firstgid;
					if (id >= 0)
					{
						// Tile position.
						s32 x = (d % lyr.width) * tld->tileWidth;
						s32 y = (d / lyr.width) * tld->tileHeight;

						// Draw the tile.
						driver->draw2DImage(ts.img.tex, vector2di(x, y), ts.subRects[id], 0, lyr.tintColor, true);
					}
				}
			}
		}
 }break;
 case 2:{
 		// For the animations I use a "delta time".
		deltaTime = timer->getTime() - oldTime;

		// Extracts data from all tile sets.
		for (u32 i = 0; i < tld->tileset.size(); ++i)
		{
			TILESET ts = tld->tileset[i];

			// Extracts data from all layers.
			for (u32 j = 0; j < tld->layer.size(); ++j)
			{
				LAYER lyr = tld->layer[j];

				// The array "lyr.data" contains all the ids of the tiles, in this way it can be used to identify
				// in an image the position of the section to be drawn.
				for (u32 d = 0; d < lyr.data.size(); ++d)
				{
					s32 id = lyr.data[d] - ts.firstgid;
					if (id >= 0)
					{
						// Tile position.
						s32 x = (d % lyr.width) * tld->tileWidth;
						s32 y = (d / lyr.width) * tld->tileHeight;

						// Draw the tile.
						driver->draw2DImage(ts.img.tex, vector2di(x, y), ts.subRects[id], 0, lyr.tintColor, true);

						// This zone corresponds to the tiles extracted when using an external tileset.
						// In this case, the animation data they contain will be used.
						for (u32 j = 0; j < ts.tile.size(); ++j)
						{
							TILE tl = ts.tile[j];

							// In this way it is possible to make some tiles animated.
							// Sure there are other ways, this is just an example.
							if (tl.id == id && !tl.animation.empty())
							{
								currentFrameTime += 1.0f / deltaTime;

								s32 tileID = tl.animation[currentFrameIndex].tileid;
								s32 duration = tl.animation[currentFrameIndex].duration;

								if (currentFrameTime >= duration)
								{
									currentFrameTime = 0.f;

									if (currentFrameIndex == (tl.animation.size() - 1))
										currentFrameIndex = 0;
									else
										++currentFrameIndex;
								}

								// Draw the animation.
								driver->draw2DImage(ts.img.tex, vector2di(x, y), ts.subRects[tileID], 0, lyr.tintColor, true);
							}
						}

					}
				}
			}
		}

		oldTime = timer->getTime();
}break;
case 3:{
    //=======================================================
   // irrTiled* tld = new irrTiled("media/3dbasic.tmx",device);
	//=======================================================

	// Extracts data from all tile sets.
	for (u32 i = 0; i < tld->tileset.size(); ++i)
	{
		TILESET ts = tld->tileset[i];

		// Height and width of the texture.
		s32 texW = ts.img.imageWidth;
		s32 texH = ts.img.imageHeight;

		// Extracts data from all layers.
		for (u32 j = 0; j < tld->layer.size(); ++j)
		{
			LAYER lyr = tld->layer[j];

			// The array "lyr.data" contains all the ids of the tiles, in this way it can be used to identify
			// in an image the position of the section to be drawn.
			for (u32 d = 0; d < lyr.data.size(); ++d)
			{
				s32 id = lyr.data[d] - ts.firstgid;
				if (id >= 0)
				{
					// Tile position.
					s32 x = (d % lyr.width) * ts.tileWidth;
					s32 y = (d / lyr.width) * ts.tileHeight;

					// As you will see, I add a negative sign at the "x" coordinate.This is because if you position
					// anything in a 3D space with the coordinates taken directly from the map, it would be positioned
					// in reverse.In 2D environments it does not happen but in 3D ¿?.
					IMeshSceneNode* mesh = smgr->addCubeSceneNode(ts.tileWidth, 0, -1, vector3df(-x, 0.0f, y));
					mesh->setMaterialTexture(0, ts.img.tex);
					mesh->setMaterialFlag(EMF_BILINEAR_FILTER, false);
					mesh->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL_REF);

					// Modify the position and size of the texture to fit a 3D environment.
					f32 tx = float(id % (texW /ts.tileWidth)) / (texW / ts.tileWidth);
					f32 ty = float(id / (texW / ts.tileWidth)) / (texH / ts.tileHeight);
					f32 sx = float(ts.tileWidth) / float(texW);
					f32 sy = float(ts.tileHeight) / float(texH);

					// Apply a matrix with all the texture data to the mesh.
					matrix4 mat;
					mat.setTextureTranslate(tx, ty);
					mat.setTextureScale(sx, sy);
					mesh->getMaterial(0).TextureLayer[0].setTextureMatrix(mat);
				}
			}
		}
	}

	// Create the floor and ceiling.
    IMesh* plane = smgr->addHillPlaneMesh("", dimension2df(1000, 1000), dimension2du(10,10),0,1);

    IMeshSceneNode* floor = smgr->addMeshSceneNode(plane);
    floor->setPosition(vector3df(0, -64, 0));
    floor->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
    floor->getMaterial(0).AmbientColor = SColor(255, 130, 130, 130);

    IMeshSceneNode* ceiling = smgr->addMeshSceneNode(plane);
    ceiling->setPosition(vector3df(0, 64, 0));
    ceiling->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
    ceiling->getMaterial(0).AmbientColor = SColor(255, 195, 195, 195);
   // };
    }break;
}

   // return Py_BuildValue("%l",tld);
   return Py_BuildValue("");
#else
    return Py_BuildValue("");
    #endif
}


PyObject * Python::PyIrr_FileArchive(PyObject * self,PyObject * args){
	char * t;
	PyArg_ParseTuple(args,"s",&t);
	device->getFileSystem()->addFileArchive( t );
	printf ("archive %s added to archive \n",t);
return Py_BuildValue("");
}

PyObject * Python::PyIrr_zistream(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
	PyArg_ParseTuple(args,"s",&t,&x,&y,&z);
	#ifdef COMPRESS
	//def(stdin, stdout, Z_DEFAULT_COMPRESSION); //for compression
		inf(stdin, stdout);	//zpipe decompression
    #endif
    return Py_BuildValue("");
}


PyObject * Python::PyIrr_zostream(PyObject * self,PyObject * args){
	float x,y,z;
	int t;
	PyArg_ParseTuple(args,"ifff",&t,&x,&y,&z);
return Py_BuildValue("");
}
