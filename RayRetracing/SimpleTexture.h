#pragma once

#include "Structures.h"
#include "ITexture.h"

namespace RayTracingEngine
{
	class CSimpleTexture :
		public ITexture
	{
	public:
		CSimpleTexture(RGBColor color);

		virtual RGBColor getColor(const CVector2& texCoord, const CPoint3& hitPoint)
		{
			return color;
		}

		RGBColor color;
	};
}
