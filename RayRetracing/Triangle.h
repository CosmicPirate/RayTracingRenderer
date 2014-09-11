#pragma once

namespace RayTracingEngine
{
	class CTriangle :
		public ISurface
	{
	public:
		CTriangle(Vertex v1, Vertex v2, Vertex v3);
		CTriangle(CPoint3 vert1, CPoint3 vert2, CPoint3 vert3, CPoint3 normal1, CPoint3 normal2, CPoint3 normal3);
		~CTriangle();

		bool intersect(Intersection& intersection, const Ray& ray);

	private:
		Vertex		verts[3];
		CVector3	normal;
		float		offset;

		void calculateNormalAndOffset();
	};
}
