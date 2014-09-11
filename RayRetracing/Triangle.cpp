#include "Structures.h"
#include "Geometry.h"

using namespace RayTracingEngine;

CTriangle::CTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	verts[0] = v1;
	verts[1] = v2;
	verts[2] = v3;

	calculateNormalAndOffset();
}

CTriangle::CTriangle(CPoint3 vert1, CPoint3 vert2, CPoint3 vert3, CPoint3 normal1, CPoint3 normal2, CPoint3 normal3)
{
	verts[0].pPostion = vert1;
	verts[0].uNormal = normal1;
	verts[1].pPostion = vert2;
	verts[1].uNormal = normal2;
	verts[2].pPostion = vert3;
	verts[2].uNormal = normal3;

	calculateNormalAndOffset();
}

CTriangle::~CTriangle()
{
}

bool CTriangle::intersect(Intersection& intersection, const Ray& ray)
{
	const float epsilon(0.00001f);

	float t = 0;
	float denom = gmtl::dot(ray.uDirection, normal);

	if (abs(denom) < epsilon)	//	луч параллелен плоскости
	{
		if (dot(normal, static_cast<CVector3>(ray.pOrigin)) - offset >= epsilon)	//	ориджин не на плоскости
			return false;
	}

	t = gmtl::dot(normal, normal * offset - ray.pOrigin) / denom;

	if (t < 0)
		return false;

	CPoint3 pt = ray.pOrigin * t;

	float i1, i2; //	две самые маленькие компоненты нормали
	if ((i1 = fminf(normal[0], normal[1])) == normal[0])
		i2 = fminf(normal[1], normal[2]);
	else
		i2 = fminf(normal[0], normal[2]);
	
	float u0 = pt[i1] - verts[0].pPostion[i1];
	float v0 = pt[i2] - verts[0].pPostion[i2];
	float u1 = verts[1].pPostion[i1] - verts[0].pPostion[i1];
	float u2 = verts[2].pPostion[i1] - verts[0].pPostion[i1];
	float v1 = verts[1].pPostion[i2] - verts[0].pPostion[i2];
	float v2 = verts[2].pPostion[i2] - verts[0].pPostion[i2];
	float a, b;

	if (u1 < epsilon)
	{
		b = u0 / u2;
		if (b >= 0 && b <= 1)
			a = (v0 - b * v2) / v1;
		else
			return false;
	}
	else
	{
		b = (v0 * u1 - u0 * v1) / (v2 * u1 - u2 * v1);
		if (b >= 0 && b <= 1)
			a = (u0 - b * u2) / u1;
		else
			return false;
	}

	if (a < 0 || a + b > 1)
		return false;

	intersection.fDistance = t;
	intersection.ray = ray;
	intersection.pPoint = pt;
	intersection.uNormal = normal;	//	TODO: сделать сумму нормалей вершин
	intersection.rgbColor = RGB_BLUE;

	return true;
}

//	Private Methods

void CTriangle::calculateNormalAndOffset()
{
	gmtl::cross<float>(
		normal,
		verts[1].pPostion - verts[0].pPostion,
		verts[2].pPostion - verts[1].pPostion);

	offset = dot(static_cast<CVector3>(verts[0].pPostion), normal);
}

