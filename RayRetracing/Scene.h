#pragma once

#include "Geometry.h"
#include "Material.h"
#include <vector>

namespace RayTracingEngine
{
	class CScene
	{
	public:
		CScene();
		~CScene();

		std::vector<CModel*> models;
		int numOfModels;

		std::vector<CMaterial*> materials;
		int numOfMaterials;
	};
}
