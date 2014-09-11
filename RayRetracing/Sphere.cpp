
#include "Structures.h"
#include "Geometry.h"

namespace RayTracingEngine
{
	CSphere::CSphere(CPoint3 center, float radius)
	{
		gmtlSphere.setCenter(gmtl::Point3f(center[0], center[1], center[2]));
		gmtlSphere.setRadius(radius);
	}


	bool CSphere::intersect(Intersection& intersection, const Ray& ray)
	{
		int numhits;
		float t0, t1;
		bool hasIntersection = gmtl::intersect(gmtlSphere, ray.gmtlRay, numhits, t0, t1);

		if (!hasIntersection)
			return false;

		t0 = fminf(t0, t1);

		intersection.fDistance = t0;
		intersection.ray = ray;
		intersection.pPoint = ray.pOrigin + ray.uDirection * t0;
		intersection.uNormal = intersection.pPoint - gmtlSphere.mCenter;
		intersection.rgbColor = RGB_GREEN;

		return true;
	}
}
