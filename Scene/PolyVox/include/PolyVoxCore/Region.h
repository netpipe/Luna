/*******************************************************************************
Copyright (c) 2005-2009 David Williams

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution. 	
*******************************************************************************/

#ifndef __PolyVox_Region_H__
#define __PolyVox_Region_H__

#include "Impl/TypeDef.h"

#include "PolyVoxCore/Vector.h"

namespace PolyVox
{
	/**
	Represents a part of a Volume.

	Many operations in PolyVox are constrained to only part of a volume. For example, when running the surface extractors 
	it is unlikely that you will want to run it on the whole volume at once, as this will give a very large mesh which may 
	be too much to render. Instead you will probably want to run a surface extractor a number of times on different parts 
	of the volume, there by giving a number of meshes which can be culled and rendered seperately.

	The Region class is used to define these parts (regions) of the volume. Essentially it consists of an upper and lower 
	bound which specify the range of voxels positions considered to be part of the region. Note that these bounds are 
	<em>inclusive</em>. The class also provides functions for modifying the regions in a variety of ways.

	\Note The dimensions of a region can be measured either in voxels or in cells. See the manual for more information 
	about these definitions.
	*/
#ifdef SWIG
	class Region
#else
	class POLYVOX_API Region
#endif
	{
	public:

		static const Region MaxRegion;

		Region();
		Region(const Vector3DInt32& v3dLowerCorner, const Vector3DInt32& v3dUpperCorner);
		Region(int32_t iLowerX, int32_t iLowerY, int32_t iLowerZ, int32_t iUpperX, int32_t iUpperY, int32_t iUpperZ);

		///Equality Operator.
        bool operator==(const Region& rhs) const;
		///Inequality Operator.
        bool operator!=(const Region& rhs) const;

		const Vector3DInt32& getLowerCorner(void) const;
		const Vector3DInt32& getUpperCorner(void) const;

		/// Gets the width of the region measured in voxels
		int32_t getWidthInVoxels(void) const;
		/// Gets the height of the region measured in voxels
		int32_t getHeightInVoxels(void) const;
		/// Gets the depth of the region measured in voxels
		int32_t getDepthInVoxels(void) const;
		/// Gets the dimensions of the region measured in voxels
		Vector3DInt32 getDimensionsInVoxels(void) const;

		/// Gets the width of the region measured in cells
		int32_t getWidthInCells(void) const;
		/// Gets the height of the region measured in cells
		int32_t getHeightInCells(void) const;
		/// Gets the depth of the region measured in cells
		int32_t getDepthInCells(void) const;
		/// Gets the dimensions of the region measured in cells
		Vector3DInt32 getDimensionsInCells(void) const;

		void setLowerCorner(const Vector3DInt32& v3dLowerCorner);
		void setUpperCorner(const Vector3DInt32& v3dUpperCorner);

		bool containsPoint(const Vector3DFloat& pos, float boundary = 0.0f) const;
		bool containsPoint(const Vector3DInt32& pos, uint8_t boundary = 0) const;
		//FIXME - Don't like these. Make containsPoint take flags indicating which axes to check?
		bool containsPointInX(float pos, float boundary = 0.0f) const;
		bool containsPointInX(int32_t pos, uint8_t boundary = 0) const;
		bool containsPointInY(float pos, float boundary = 0.0f) const;
		bool containsPointInY(int32_t pos, uint8_t boundary = 0) const;
		bool containsPointInZ(float pos, float boundary = 0.0f) const;
		bool containsPointInZ(int32_t pos, uint8_t boundary = 0) const;
		void cropTo(const Region& other);
		/// Deprecated and misleading
		POLYVOX_DEPRECATED int32_t depth(void) const;
		/// Deprecated and misleading
		POLYVOX_DEPRECATED int32_t height(void) const;
		void shift(const Vector3DInt32& amount);
		void shiftLowerCorner(const Vector3DInt32& amount);
		void shiftUpperCorner(const Vector3DInt32& amount);
		//FIXME - Add dilate and erode functions?
		/// Deprecated and misleading
		POLYVOX_DEPRECATED Vector3DInt32 dimensions(void);
		/// Deprecated and misleading
		POLYVOX_DEPRECATED int32_t width(void) const;

	private:
		Vector3DInt32 m_v3dLowerCorner;
		Vector3DInt32 m_v3dUpperCorner;

		//FIXME - This variable is unused, but without it the OpenGL example crashes in release mode
		//when the volume size is 128^3 and the level of detail is 2. Very strange, but consistant.
		//Presubablly some kind of alignment issue? It started after this class was changed to use
		//int16's rather than int32's. To be investigated.
		uint8_t dummy; 
	};
}

#endif
