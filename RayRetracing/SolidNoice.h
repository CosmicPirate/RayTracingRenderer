#ifndef _SOLID_NOICE_H_
#define _SOLID_NOICE_H_

#include "Math.h"

namespace RayTracingEngine
{
	class CSolidNoice
	{
	public:
		CSolidNoice();

		//	Perlin noice
		float noice(const CVector3& vec) const;
		float turbulence(const CVector3& vec, int depth) const;
		float dturbulence(const CVector3& vec, int depth, float d) const;

		float omega(float t) const;
		CVector3 gamma(int i, int j, int k) const;
		int intGamma(int i, int j) const;
		float knot(int i, int j, int k, CVector3& vec) const;

		CVector3 grad[16];	//	12 вершин куба
		int phi[16];		//	перемешаные числа из [0, 15]
	};

}

#endif	//	_SOLID_NOICE_H_