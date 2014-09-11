#include "MarbleTexture.h"

namespace RayTracingEngine
{
	RGBColor CMarbleTexture::getColor(const CVector2& texCoord, const CPoint3& hitPoint)
	{
		float tmp = scale * noice.turbulence(freq * static_cast<CVector3>(hitPoint), octaves);
		float t = 2.0f * fabs(gmtl::Math::sin(freq * hitPoint[0] + tmp));

		if (t < 1.0f)
			return c1 * t + c2 * (1.0f - t);
		else
			return c0 * t + c1 * (2.0f - t);\
	}
}