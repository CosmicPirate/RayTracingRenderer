#pragma once

#include "Structures.h"
#include "LightSource.h"

namespace RayTracingEngine
{
	class CSpotLight :
		public ILightSource
	{
	public:
		CSpotLight();

		CPoint3 pPosition;
		RGBColor rgbColor;
	};

}