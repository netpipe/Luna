#ifdef RECAST
#include "recast_util.h"

//#include <SampleInterfaces.h>

using namespace std;
using namespace irr;

RecastUtil::RecastUtil()
:	verts(0),
	tris(0),

	m_ctx(0),

	m_keepInterResults(true),
	m_totalBuildTimeMs(0),
	m_triareas(0),
	m_solid(0),
	m_chf(0),
	m_cset(0),
	m_pmesh(0),
	m_dmesh(0)
{
	BuildContext ctx;
	this->setContext(&ctx);

	this->resetCommonSettings();
}

RecastUtil::~RecastUtil()
{
	cleanup();
}

void RecastUtil::cleanup()
{

	if (verts) { delete[] verts; verts = 0; }
	if (tris) { delete[] tris; tris = 0; }

	delete [] m_triareas;
	m_triareas = 0;
	rcFreeHeightField(m_solid);
	m_solid = 0;
	rcFreeCompactHeightfield(m_chf);
	m_chf = 0;
	rcFreeContourSet(m_cset);
	m_cset = 0;
	rcFreePolyMesh(m_pmesh);
	m_pmesh = 0;
	rcFreePolyMeshDetail(m_dmesh);
	m_dmesh = 0;

}


bool RecastUtil::handleBuild(scene::IMeshBuffer* buffer)
{
	cleanup();

	std::vector<float> vs;
	std::vector<int> ts;
	int nverts;
	int ntris;

	if (!this->getMeshBufferData(buffer, vs, nverts, ts, ntris))
	{
		printf("getMeshBufferData() failed!\n");
		return false;
	}

	// populate verts and tris:

	verts = new float[nverts];
	for (int n = 0; n < nverts; ++n)
	{
		verts[n] = vs[n];
		//printf("verts[%i]=%g\n", n, verts[n]);
	}

	tris = new int[ntris * 3];
	for (int n = 0; n < ntris; ++n)
	{
		tris[n*3] = ts[n*3];
		tris[n*3+1] = ts[n*3+1];
		tris[n*3+2] = ts[n*3+2];
		//printf("tris[%i]=(%i,%i,%i)\n", n, tris[n*3], tris[n*3+1], tris[n*3+2]);
	}
	printf("vs.size()=%i,nverts=%i\n", vs.size(), nverts);
	printf("ts.size()=%i,ntris=%i\n", ts.size(), ntris);
	float bmin[3];
	float bmax[3];

	//rcCalcBounds(const float* verts, int nv, float* bmin, float* bmax)
	rcCalcBounds(verts, nverts/3, bmin, bmax);





	//
	// Step 1. Initialize build config.
	//

	// Init build configuration from GUI
	memset(&m_cfg, 0, sizeof(m_cfg));
	m_cfg.cs = m_cellSize;
	m_cfg.ch = m_cellHeight;
	m_cfg.walkableSlopeAngle = m_agentMaxSlope;
	m_cfg.walkableHeight = (int)ceilf(m_agentHeight / m_cfg.ch);
	m_cfg.walkableClimb = (int)floorf(m_agentMaxClimb / m_cfg.ch);
	m_cfg.walkableRadius = (int)ceilf(m_agentRadius / m_cfg.cs);
	m_cfg.maxEdgeLen = (int)(m_edgeMaxLen / m_cellSize);
	m_cfg.maxSimplificationError = m_edgeMaxError;
	m_cfg.minRegionArea = (int)rcSqr(m_regionMinSize);		// Note: area = size*size
	m_cfg.mergeRegionArea = (int)rcSqr(m_regionMergeSize);	// Note: area = size*size
	m_cfg.maxVertsPerPoly = (int)m_vertsPerPoly;
	m_cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
	m_cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;

	// Set the area where the navigation will be build.
	// Here the bounds of the input mesh are used, but the
	// area could be specified by an user defined box, etc.
	rcVcopy(m_cfg.bmin, bmin);
	rcVcopy(m_cfg.bmax, bmax);
	rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);

	// Reset build times gathering.
	m_ctx->resetTimers();

	// Start the build process.
	m_ctx->startTimer(RC_TIMER_TOTAL);

	m_ctx->log(RC_LOG_PROGRESS, "Building navigation:");
	m_ctx->log(RC_LOG_PROGRESS, " - %d x %d cells", m_cfg.width, m_cfg.height);
	m_ctx->log(RC_LOG_PROGRESS, " - %.1fK verts, %.1fK tris", nverts/1000.0f, ntris/1000.0f);

	//
	// Step 2. Rasterize input polygon soup.
	//

	// Allocate voxel heightfield where we rasterize our input data to.
	m_solid = rcAllocHeightfield();
	if (!m_solid)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
		return false;
	}
	if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create solid heightfield.");
		return false;
	}

	// Allocate array that can hold triangle area types.
	// If you have multiple meshes you need to process, allocate
	// and array which can hold the max number of triangles you need to process.
	m_triareas = new unsigned char[ntris];
	if (!m_triareas)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", ntris);
		return false;
	}

	// Find triangles which are walkable based on their slope and rasterize them.
	// If your input data is multiple meshes, you can transform them here, calculate
	// the are type for each of the meshes and rasterize them.
	memset(m_triareas, 0, ntris*sizeof(unsigned char));
	rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, verts, nverts, tris, ntris, m_triareas);
	rcRasterizeTriangles(m_ctx, verts, nverts, tris, m_triareas, ntris, *m_solid, m_cfg.walkableClimb);

	this->showHeightFieldInfo(*m_solid); //<-----------------------------------------------------------------------------------------

	if (!m_keepInterResults)
	{
		delete [] m_triareas;
		m_triareas = 0;
	}

	//
	// Step 3. Filter walkables surfaces.
	//

	// Once all geoemtry is rasterized, we do initial pass of filtering to
	// remove unwanted overhangs caused by the conservative rasterization
	// as well as filter spans where the character cannot possibly stand.
	rcFilterLowHangingWalkableObstacles(m_ctx, m_cfg.walkableClimb, *m_solid);
	rcFilterLedgeSpans(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
	rcFilterWalkableLowHeightSpans(m_ctx, m_cfg.walkableHeight, *m_solid);


	//
	// Step 4. Partition walkable surface to simple regions.
	//

	// Compact the heightfield so that it is faster to handle from now on.
	// This will result more cache coherent data as well as the neighbours
	// between walkable cells will be calculated.
	m_chf = rcAllocCompactHeightfield();
	if (!m_chf)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'chf'.");
		return false;
	}
	if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build compact data.");
		return false;
	}

	if (!m_keepInterResults)
	{
		rcFreeHeightField(m_solid);
		m_solid = 0;
	}

	// Erode the walkable area by agent radius.
	if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not erode.");
		return false;
	}

	// (Optional) Mark areas.
	//const ConvexVolume* vols = m_geom->getConvexVolumes();
	//for (int i  = 0; i < m_geom->getConvexVolumeCount(); ++i)
		//rcMarkConvexPolyArea(m_ctx, vols[i].verts, vols[i].nverts, vols[i].hmin, vols[i].hmax, (unsigned char)vols[i].area, *m_chf);

	if (m_monotonePartitioning)
	{
		// Partition the walkable surface into simple regions without holes.
		// Monotone partitioning does not need distancefield.
		if (!rcBuildRegionsMonotone(m_ctx, *m_chf, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
		{
			m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
			return false;
		}
	}
	else
	{
		// Prepare for region partitioning, by calculating distance field along the walkable surface.
		if (!rcBuildDistanceField(m_ctx, *m_chf))
		{
			m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build distance field.");
			return false;
		}

		// Partition the walkable surface into simple regions without holes.
		if (!rcBuildRegions(m_ctx, *m_chf, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
		{
			m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
			return false;
		}
	}

	//
	// Step 5. Trace and simplify region contours.
	//

	// Create contours.
	m_cset = rcAllocContourSet();
	if (!m_cset)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'cset'.");
		return false;
	}
	if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create contours.");
		return false;
	}
	printf("m_cset->nconts=%i\n", m_cset->nconts);
	//
	// Step 6. Build polygons mesh from contours.
	//

	// Build polygon navmesh from the contours.
	m_pmesh = rcAllocPolyMesh();
	if (!m_pmesh)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmesh'.");
		return false;
	}
	if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not triangulate contours.");
		return false;
	}

	//
	// Step 7. Create detail mesh which allows to access approximate height on each polygon.
	//

	m_dmesh = rcAllocPolyMeshDetail();
	if (!m_dmesh)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmdtl'.");
		return false;
	}

	if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build detail mesh.");
		return false;
	}

	if (!m_keepInterResults)
	{
		rcFreeCompactHeightfield(m_chf);
		m_chf = 0;
		rcFreeContourSet(m_cset);
		m_cset = 0;
	}

	// At this point the navigation mesh data is ready, you can access it from m_pmesh.
	// See duDebugDrawPolyMesh or dtCreateNavMeshData as examples how to access the data.

	//
	// (Optional) Step 8. Create Detour data from Recast poly mesh.
	//
	// ...

	m_ctx->stopTimer(RC_TIMER_TOTAL);

	// Show performance stats.
	duLogBuildTimes(*m_ctx, m_ctx->getAccumulatedTime(RC_TIMER_TOTAL));
	m_ctx->log(RC_LOG_PROGRESS, ">> Polymesh: %d vertices  %d polygons", m_pmesh->nverts, m_pmesh->npolys);

	m_totalBuildTimeMs = m_ctx->getAccumulatedTime(RC_TIMER_TOTAL)/1000.0f;

	// irr part:
	printf("RC_LOG_PROGRESS >> Polymesh: %d vertices  %d polygons\n", m_pmesh->nverts, m_pmesh->npolys);
	return true;
}


void RecastUtil::resetCommonSettings()
{
	m_cellSize = 0.3f;
	m_cellHeight = 0.2f;
	m_agentHeight = 2.0f;
	m_agentRadius = 0.6f;
	m_agentMaxClimb = 0.9f;
	m_agentMaxSlope = 45.0f;
	m_regionMinSize = 8;
	m_regionMergeSize = 20;
	m_monotonePartitioning = false;
	m_edgeMaxLen = 12.0f;
	m_edgeMaxError = 1.3f;
	m_vertsPerPoly = 6.0f;
	m_detailSampleDist = 6.0f;
	m_detailSampleMaxError = 1.0f;
}


bool RecastUtil::getMeshBufferData
(
	scene::IMeshBuffer* buffer,
	std::vector<float>& verts, int& nverts,
	std::vector<int>& tris, int& ntris
)
{
	nverts = buffer->getVertexCount() * 3;
	printf("nverts=%i\n", nverts);

	ntris = buffer->getIndexCount() / 3;
	printf("ntris=%i\n", ntris);

	if ((nverts <= 0) || (ntris <= 0))
	{
		printf("(nverts <= 0) || (ntris <= 0)\n");
		return false;
	}

	for (int i = 0; i < int(buffer->getVertexCount()); ++i)
	{
		core::vector3df pos = buffer->getPosition(i);
		verts.push_back(pos.X);
		verts.push_back(pos.Y);
		verts.push_back(pos.Z);
	}

	u16* indices = buffer->getIndices();
	//for (int i = 0; i < int(buffer.Indices.size()); ++i)
	for (int i = 0; i < ntris; ++i)
	{
		// some verts may contain nan (invalid values)??:
		/***
		bool ok = true;
		for (int j = 0; j < 3; ++j)
		{
			if (isnan(verts[buffer.Indices[i*3+j]]))
			{
				ok = false;
				break;
			}
		}
		if (!ok)
			continue;
		***/

		tris.push_back(indices[i*3]);
		tris.push_back(indices[i*3+1]);
		tris.push_back(indices[i*3+2]);
	}
	ntris = int(tris.size() / 3);

	// replace nan with 0 in verts:
	//for (int n = 0; n < int(verts.size()); ++n)
		//if (isnan(verts[n]))
			//verts[n] = 0.0f;
	return true;
}


bool RecastUtil::setupIrrSMeshFromRecastDetailMesh(scene::SMesh* smesh)
{
	rcPolyMeshDetail* dmesh = m_dmesh;

	if ((!smesh) || (!dmesh))
		return false;

	scene::SMeshBuffer* buffer = new scene::SMeshBuffer();

	std::vector<float> vertsOut;
	int nvertsOut = 0;

	std::vector<int> trisOut;
	int ntrisOut = 0;

	bool ok = getMeshDataFromPolyMeshDetail
	(
		dmesh,
		vertsOut, nvertsOut,
		trisOut, ntrisOut
	);

	if (!ok)
	{
		printf("setupSMesh(): getMeshDataFromPolyMeshDetail() failed!\n");
		buffer->drop();
		return false;
	}

	printf("setupSMesh(): vertsOut.size()=%i\n", vertsOut.size());

	ok = setMeshBufferData// std::vector version!
	(
		*buffer, vertsOut, nvertsOut, trisOut, ntrisOut
	);
	if (!ok)
	{
		printf("setupSMesh(): setMeshBufferData() failed!\n");

		buffer->drop();
		return false;
	}
	// this is important:
	// if not done, scene may disappear sometimes!
	// recalculate bounding box
	for (u32 n=0; n<buffer->getVertexCount(); ++n)
	{
		buffer->BoundingBox.addInternalPoint(buffer->Vertices[n].Pos);
	}

	smesh->addMeshBuffer(buffer);
	smesh->setHardwareMappingHint(scene::EHM_STATIC, scene::EBT_VERTEX_AND_INDEX);
	smesh->recalculateBoundingBox();

	buffer->drop();
	return true;

}

void RecastUtil::showHeightFieldInfo(const rcHeightfield& hf)
{
	int w = hf.width;
	int h = hf.height;
	const float* bmin = hf.bmin;
	const float* bmax = hf.bmax;
	float cs = hf.cs;
	float ch = hf.ch;

	printf
	(
		"rcHeightfield hf: w=%i,h=%i,bmin=(%f,%f,%f),bmax=(%f,%f,%f),cs=%f,ch=%f\n",
		w,h,bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2],cs,ch
	);
}

bool RecastUtil::getMeshDataFromPolyMeshDetail
(
	rcPolyMeshDetail* dmesh,
	std::vector<float>& vertsOut, int& nvertsOut,
	std::vector<int>& trisOut, int& ntrisOut
)
{
	printf("getMeshDataFromPolyMeshDetail(): dmesh->nmeshes=%i\n", dmesh->nmeshes);
	if (dmesh->nmeshes == 0)
	{
		printf("getMeshDataFromPolyMeshDetail(): dmesh->nmeshes == 0\n");
		return false;
	}

	nvertsOut = dmesh->nverts * 3;
	printf("getMeshDataFromPolyMeshDetail: nvertsOut=%i\n", nvertsOut);

	ntrisOut = dmesh->ntris;
	printf("getMeshDataFromPolyMeshDetail: ntrisOut=%i\n", ntrisOut);

	//const unsigned char* tris = dmesh->tris;
	const float* verts = dmesh->verts;

	for (int n = 0; n < nvertsOut; ++n)
	{
		//printf("getMeshDataFromPolyMeshDetail: tris[n*4+k]=%i\n", tris[n*4+k]);
		vertsOut.push_back(verts[n]);
	}


	//FIXME:
	int tri_offset = 0;
	int old_nverts = 0;
	for (int p = 0; p < dmesh->nmeshes; ++p)
	{
		unsigned int* m = &(dmesh->meshes[p*4]);
		const unsigned short bverts = m[0]; // `b' means "beginning of"!!
		const unsigned short nverts = m[1];
		const unsigned short btris = m[2];
		const unsigned short ntris = m[3];
		//const float* verts = &(dmesh->verts[bverts*3]);
		const unsigned char* tris = &(dmesh->tris[btris*4]);
		//printf("meshnum=%i, bverts=%i, btris=%i\n", p, bverts, btris);
		//ntrisOut += int(ntris);


		tri_offset += old_nverts;

		for (int n = 0; n < ntris; ++n)
		{
			for (int k = 0; k < 3; ++k)
			{
				int tri = tris[n*4+k] + tri_offset;
				trisOut.push_back(tri);
				//printf("getMeshDataFromPolyMeshDetail: tri=%i, index=%i\n", n, tri);
				//vertsOut.push_back(verts[tri*3 + 0]);
				//vertsOut.push_back(verts[tri*3 + 1]);
				//vertsOut.push_back(verts[tri*3 + 2]);
			}
		}
		old_nverts = nverts;
	}
	printf("getMeshDataFromPolyMeshDetail(): vertsOut.size()=%i\n", vertsOut.size());

	return true;

}


bool RecastUtil::setMeshBufferData
(
	scene::SMeshBuffer& buffer,
	const std::vector<float>& verts, int& nverts,
	const std::vector<int>& tris, int& ntris
)
{
	//TODO:
	// err handling:
	if (verts.empty() || tris.empty())
	{
		return false;
	}

	buffer.Vertices.set_used(nverts / 3);
	buffer.Indices.set_used(ntris * 3); // ntris triangles!


	//video::SColor color(255, 255, 255, 255);
	//video::SColor color(128, 255, 255, 255);

	//S3DVertex => pos, normal, color, texcoords

	for (int i = 0; i < nverts; i += 3)
	{
		float x = verts[i];
		float y = verts[i + 1];
		float z = verts[i + 2];

		buffer.Vertices[i / 3] = video::S3DVertex
		(
			x, y, z,
			0.0f, 1.0f, 0.0f,
			//0.0f, 0.0f, 0.0f,
			0x80FF0000,
			//0xFFFFFFFF,
			0.0f, 0.0f
		);
	}


	for (int i = 0; i < ntris * 3; ++i)
	{
		int index = tris[i];
		buffer.Indices[i] = index;
	}


	buffer.getMaterial().Lighting = false;
	buffer.getMaterial().BackfaceCulling = false;
	buffer.getMaterial().Wireframe = true;
	buffer.getMaterial().Thickness = 2.0f;
	//buffer.getMaterial().MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;
	buffer.getMaterial().MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
	//buffer.getMaterial().MaterialType = video::EMT_SOLID;
	buffer.recalculateBoundingBox();

	return true;
}
/*
   //Detour stuff
    vector<irr::core::vector3df>  RecastUtilM::returnPath(core::vector3df pStart, core::vector3df pEnd)
    {
        std::vector<irr::core::vector3df> lstPoints;
        if (m_navQuery)
        {
            if (m_navMesh == 0)
            {
                return  lstPoints;
            }
        ./
            dtQueryFilter m_filter;
            dtPolyRef m_startRef;
            dtPolyRef m_endRef;

            const int MAX_POLYS = 256;
            dtPolyRef m_polys[MAX_POLYS];
            dtPolyRef returnedPath[MAX_POLYS];
            float m_straightPath[MAX_POLYS * 3];
            int numStraightPaths;
            float  m_spos[3] = { pStart.X, pStart.Y, pStart.Z };
            float  m_epos[3] = { pEnd.X, pEnd.Y, pEnd.Z };
            float m_polyPickExt[3];
            m_polyPickExt[0] = 2;
            m_polyPickExt[1] = 4;
            m_polyPickExt[2] = 2;


            m_navQuery->findNearestPoly(m_spos, m_polyPickExt, &m_filter, &m_startRef, 0);

            if (m_startRef == 0)
            {
                return lstPoints;

            }
            m_navQuery->findNearestPoly(m_epos, m_polyPickExt, &m_filter, &m_endRef, 0);

            if (m_endRef == 0)
            {
                return lstPoints;

            }
            dtStatus findStatus = DT_FAILURE;
            int pathCount;

            findStatus = m_navQuery->findPath(m_startRef, m_endRef, m_spos, m_epos, &m_filter, returnedPath, &pathCount, MAX_POLYS);



            if (pathCount > 0)
            {
                findStatus = m_navQuery->findStraightPath(m_spos, m_epos, returnedPath,
                    pathCount, m_straightPath, 0, 0, &numStraightPaths, MAX_POLYS);

                for (int i = 0; i < numStraightPaths; ++i)
                {
                    vector3df cpos(m_straightPath[i * 3], m_straightPath[i * 3 + 1] + 0.25,
                        m_straightPath[i * 3 + 2]);

                    lstPoints.push_back(cpos);
                    //path->AddNode(node);
                }


            }

        }
        return lstPoints;
    }

*/
#endif

