#ifndef _MARBLE_TEXTURE_H_
#define _MARBLE_TEXTURE_H_

#include "Math.h"
#include "ITexture.h"
#include "Structures.h"
#include "SolidNoice.h"

namespace RayTracingEngine
{
	class CMarbleTexture :
		public ITexture
	{
	public:
		CMarbleTexture(float stripesPerUnit, float scale = 5.0, int octaves = 8)
		{
			freq = gmtl::Math::PI * stripesPerUnit;
			this->scale = scale;
			this->octaves = octaves;
			c0 = RGBColor{ 0.8, 0.8, 0.8 };
			c1 = RGBColor{ 0.4, 0.2, 0.1 };
			c2 = RGBColor{ 0.06, 0.04, 0.02 };
		}

		CMarbleTexture(const RGBColor& _c0, const RGBColor& _c1, const RGBColor& _c2, float stripesPerUnit, float scale = 5.0, int octaves = 8)
			: c0(_c0), c1(_c1), c2(_c2)
		{
			freq = gmtl::Math::PI * stripesPerUnit;
			this->scale = scale;
			this->octaves = octaves;
		}

		virtual RGBColor getColor(const CVector2& texCoord, const CPoint3& hitPoint);

		float freq, scale;
		int octaves;
		RGBColor c0, c1, c2;
		CSolidNoice noice;
	};
}

#endif	//	_MARBLE_TEXTURE_H_