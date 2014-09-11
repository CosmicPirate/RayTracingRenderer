#ifndef _ITEXTURE_H_
#define _ITEXTURE_H_

#include "Structures.h"

namespace RayTracingEngine
{
	class ITexture
	{
	public:
		virtual RGBColor getColor(const CVector2& texCoord, const CPoint3& hitPoint) const = 0;
	};
}

#endif	//	_ITEXTURE_H_