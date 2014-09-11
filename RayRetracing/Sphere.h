#pragma once

namespace RayTracingEngine
{
	class CSphere :
		public ISurface
	{
	public:
		CSphere(CPoint3 center, float radius);
		~CSphere();

		bool intersect(Intersection& intersection, const Ray& ray);

	private:
		gmtl::Spheref gmtlSphere;
	};
}
