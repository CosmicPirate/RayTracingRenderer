#include "SolidNoice.h"
#include <ctime>

namespace RayTracingEngine
{

	inline float CSolidNoice::omega(float eT) const
	{
		eT = (eT >= 0.0f) ? eT : -eT;	//	|eT|

		return -6.0f * eT * eT * eT * eT * eT * eT + 15.0f * eT * eT * eT * eT - 10.0f * eT * eT * eT + 1;
	}

	//	gamma(i,j,k) = grad(phi(i + phi(j + phi(k))))
	inline CVector3 CSolidNoice::gamma(int i, int j, int k) const
	{
		int idx;
		idx = phi[abs(k) % 16];
		idx = phi[abs(j + idx) % 16];
		idx = phi[abs(i + idx) % 16];

		return grad[idx];
	}

	//	заглавная омега
	inline float CSolidNoice::knot(int i, int j, int k, CVector3& vec) const
	{
		return omega(vec[0]) * omega(vec[1]) * omega(vec[2]) * gmtl::dot(gamma(i, j, k), vec);
	}

	inline int CSolidNoice::intGamma(int i, int j) const
	{
		int idx = phi[abs(j) % 16];
		idx = phi[abs(i + idx) % 16];
		return idx;
	}


	CSolidNoice::CSolidNoice()
	{
		srand(time(0));

		grad[0] = CVector3( 1, 1, 0);
		grad[1] = CVector3(-1, 1, 0);
		grad[2] = CVector3( 1, -1, 0);
		grad[3] = CVector3(-1, -1, 0);
		
		grad[4] = CVector3( 1, 0, 1);
		grad[5] = CVector3(-1, 0, 1);
		grad[6] = CVector3( 1, 0, -1);
		grad[7] = CVector3(-1, 0, -1);

		grad[8]  = CVector3(0, 1, 1);
		grad[9]  = CVector3(0, -1, 1);
		grad[10] = CVector3(0, 1, -1);
		grad[11] = CVector3(0, -1, -1);

		grad[12] = CVector3(1, 1, 0);
		grad[13] = CVector3(-1, 1, 0);
		grad[14] = CVector3(0, -1, 1);
		grad[15] = CVector3(0, -1, -1);

		int i = 0;
		for (; i < 16; ++i)
			phi[i] = i;

		//	перемешать
		for (i = 14; i >= 0; --i)
		{
			int target = int(rand() * i);
			int temp = phi[i + 1];
			phi[i + 1] = phi[target];
			phi[target] = temp;
		}
	}

	float CSolidNoice::turbulence(const CVector3& vec, int depthM) const
	{
		float sum = 0.0f;
		float weight = 1.0f;
		CVector3 tempVec(vec);

		sum = fabs(noice(tempVec));

		for (int i = 1; i < depthM; ++i)
		{
			weight *= 2;
			tempVec *= weight;

			sum += fabs(noice(tempVec));
		}

		return sum;
	}

	float CSolidNoice::dturbulence(const CVector3& vec, int depth, float d) const
	{
		float weight = 1.0f;
		CVector3 tempVec(vec);

		float sum = fabs(noice(tempVec)) / d;

		for (int i = 0; i < depth; ++i)
		{
			weight = weight * d;
			tempVec *= weight;

			sum += fabs(noice(tempVec)) / d;
		}

		return sum;
	}

	float CSolidNoice::noice(const CVector3& vec) const
	{
		//	целые части
		int xi = int(floor(vec[0]));
		int yi = int(floor(vec[1]));
		int zi = int(floor(vec[2]));

		//	дробные
		float xf = vec[0] - float(xi);
		float yf = vec[1] - float(yi);
		float zf = vec[2] - float(zi);

		float sum = 0.0f;

		sum += knot(xi, yi, zi, CVector3(xf, yf, zf));

		sum += knot(xi, yi, zi + 1, CVector3(xf, yf, zf - 1));


		sum += knot(xi, yi + 1, zi, CVector3(xf, yf - 1, zf));

		sum += knot(xi, yi + 1, zi + 1, CVector3(xf, yf - 1, zf - 1));


		sum += knot(xi + 1, yi, zi, CVector3(xf - 1, yf, zf));

		sum += knot(xi + 1, yi, zi + 1, CVector3(xf - 1, yf, zf - 1));

		sum += knot(xi + 1, yi + 1, zi, CVector3(xf - 1, yf - 1, zf));

		sum += knot(xi + 1, yi + 1, zi + 1, CVector3(xf - 1, yf - 1, zf - 1));

		return sum;
	}
}