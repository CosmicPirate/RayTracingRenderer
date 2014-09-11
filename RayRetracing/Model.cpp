#include "Model.h"
#include <vector>
#include <limits>

namespace RayTracingEngine
{
	CModel::CModel()
	{
		childSurfaces = new std::vector<ISurface*>();
	}


	CModel::~CModel()
	{
		delete childSurfaces;
	}


	bool CModel::intersect(Intersection& intersection, const Ray& ray)
	{
		Intersection minIntersection{std::numeric_limits<float>::max()};
		Intersection currentIntersection;
		bool hasIntersection = false;

		for (std::vector<ISurface*>::iterator sur = childSurfaces->begin(); sur != childSurfaces->end(); ++sur)
		{
			if ((*sur)->intersect(currentIntersection, ray) == false)
				break;

			hasIntersection = true;
			if (currentIntersection.fDistance < minIntersection.fDistance)
			{
				minIntersection = currentIntersection;
			}
		}

		if (!hasIntersection)
			return false;

		intersection = minIntersection;

		return true;
	}

	void CModel::addSurface(ISurface* surface)
	{
		if (surface == nullptr)
			return;

		((std::vector<ISurface*>*)childSurfaces)->push_back(surface);
	}
}
