#pragma once

#include "Structures.h"
#include "Geometry.h"

namespace RayTracingEngine
{
	//	Набор серфейсов
	class CModel :
		public ISurface
	{
	public:
		CModel();
		CModel(ISurface* surfaces);
		~CModel();

		void addSurface(ISurface* surface);

		bool intersect(Intersection& intersection, const Ray& ray);

	private:
		std::vector<ISurface*>* childSurfaces;	//	(std::vector<ISurface*>*)
	};
}
