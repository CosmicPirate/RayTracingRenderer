#pragma once

#include "ITexture.h"

namespace RayTracingEngine
{
	class CMaterial
	{
	public:
		CMaterial();
		~CMaterial();

		ITexture* pTexture;
	};
}
