#pragma once

#include "Structures.h"
#include "LightSource.h"

namespace RayTracingEngine
{
	class CDirectedSpotLight :
		public ILightSource
	{
	public:
		CDirectedSpotLight();
		~CDirectedSpotLight();

		CPoint3		pPosition;
		CNormal3	uDirection;
		RGBColor	rgbColor;
	};
}

