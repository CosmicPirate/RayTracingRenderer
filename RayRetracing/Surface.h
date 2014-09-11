#pragma once

namespace RayTracingEngine
{
	class ISurface
	{
	public:
		virtual bool intersect(Intersection& intersection, const Ray& ray) = 0;
		//virtual ~ISurface() = 0;
	};
}