#ifdef _WIN32
#pragma once
#endif

//********************************************************************************************
// File:   CWindGen.h
// Purpose:*sniggers* generate some wind *sniggers*, should be renamed CRoganJosh :)
// Started: 26th May 2011
// Last ed: 26th May 2011
// History:
//********************************************************************************************

#ifndef __CWINDGEN_H__
#define __CWINDGEN_H__


#include <irrlicht.h>
//#include "perlin.h"
#include "../../TerrainFactory/open-simplex-noise.h"

using namespace irr;
using namespace core;

class CWindGen
{
	vector3df	mindir;		// min direction
	vector3df	maxdir;		// max direction
	float		strength;	// strength of the wind
	float		variation;	// magnitude of the variation
//	Perlin1D*	dir_pNoise;	// 1d perlin noise control for direction interpolation
//	Perlin1D*	str_pNoise;	// 1d perlin noise for modulating the strength variation
	struct osn_context *dir_pNoise;
	struct osn_context *str_pNoise;


public:

	CWindGen(vector3df dir, float var, osn_context* dir_pN, float strngth, float strvar, osn_context* str_pN)
		: mindir(dir), maxdir(dir), dir_pNoise(dir_pN), strength(strngth), variation(strvar), str_pNoise(str_pN)
	{
		mindir.rotateXZBy(-var * 0.5);
		maxdir.rotateXZBy(var * 0.5);
	}
	void get(double f,vector3df& windv)
	{
		float mag = strength + open_simplex_noise2(str_pNoise,f * variation,1);
		VectorLerp(mindir, maxdir, open_simplex_noise2(dir_pNoise ,f + 0.5f,1),windv);
		windv = windv * mag;
	}
	void get(float f,vector3df& windv, vector3df& winddir)
	{
		float mag = strength + open_simplex_noise2(str_pNoise,(f * variation),1);
		VectorLerp(mindir, maxdir, open_simplex_noise2(dir_pNoise, (f + 0.5f),1),winddir);
		windv = winddir * mag;
	}
	void VectorLerp(const vector3df& src1, const vector3df& src2, float t, vector3df& dest )
	{
		dest.X = src1.X + (src2.X - src1.X) * t;
		dest.Y = src1.Y + (src2.Y - src1.Y) * t;
		dest.Z = src1.Z + (src2.Z - src1.Z) * t;
	}

//	float noise(struct osn_context * ctx,float f){
//    float persistance =1;
//    int scale=3;  // noise scaler, not the same as patch scaler
//    float total = 0;
//    int octaves=5;
//
//    int x,y = f;
//
//    //amplify?
//    int ax=0;
//    int az=0;
//
//    for (int i=3; i < octaves; i++)
//    {
//        float frequency = pow(2.0f, i);
//        float amplitude = pow(persistance, i);
//        total += open_simplex_noise2(ctx, (((x+ax)/scale)/frequency),
//                               (((y+az)/scale)/ frequency), 0.0, 0.0) *amplitude;
//    }
//    return total;
//}

};


#endif
