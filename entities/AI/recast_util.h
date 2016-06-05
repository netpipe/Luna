#ifndef _RECAST_UTIL_H_
#define _RECAST_UTIL_H_

#include <stdio.h>
#include <cstddef>
#include <math.h>

#include <Recast.h>
#include <SampleInterfaces.h>

#include <irrlicht.h>
#include <iostream>
#include <vector>


using namespace std;
using namespace irr;

#ifndef RECAST_UTIL_PROPERTIES
#define RECAST_UTIL_PROPERTIES
#endif


class RecastUtil
{
protected:
	float* verts;
	int* tris;

	float m_cellSize;
	float m_cellHeight;
	float m_agentHeight;
	float m_agentRadius;
	float m_agentMaxClimb;
	float m_agentMaxSlope;
	float m_regionMinSize;
	float m_regionMergeSize;
	bool m_monotonePartitioning;
	float m_edgeMaxLen;
	float m_edgeMaxError;
	float m_vertsPerPoly;
	float m_detailSampleDist;
	float m_detailSampleMaxError;

	BuildContext* m_ctx;


	bool m_keepInterResults;
	float m_totalBuildTimeMs;

	unsigned char* m_triareas;
	rcHeightfield* m_solid;
	rcCompactHeightfield* m_chf;
	rcContourSet* m_cset;
	rcPolyMesh* m_pmesh;
	rcConfig m_cfg;
	rcPolyMeshDetail* m_dmesh;

	void cleanup();

public:
	RecastUtil();

	void setContext(BuildContext* ctx) { m_ctx = ctx; }

	virtual ~RecastUtil();

	virtual bool handleBuild(scene::IMeshBuffer* buffer);
	virtual void resetCommonSettings();
	virtual bool getMeshBufferData
	(
		scene::IMeshBuffer* buffer,
		std::vector<float>& verts, int& nverts,
		std::vector<int>& tris, int& ntris
	);

	virtual bool setupIrrSMeshFromRecastDetailMesh(scene::SMesh* smesh);
	virtual void showHeightFieldInfo(const rcHeightfield& hf);
	virtual bool getMeshDataFromPolyMeshDetail
	(
		rcPolyMeshDetail* dmesh,
		std::vector<float>& vertsOut, int& nvertsOut,
		std::vector<int>& trisOut, int& ntrisOut
	);

	virtual bool setMeshBufferData
	(
		scene::SMeshBuffer& buffer,
		const std::vector<float>& verts, int& nverts,
		const std::vector<int>& tris, int& ntris
	);
         std::vector<irr::core::vector3df> returnPath(irr::core::vector3df pStart, irr::core::vector3df pEnd);
};


#endif // _RECAST_UTIL_H_
