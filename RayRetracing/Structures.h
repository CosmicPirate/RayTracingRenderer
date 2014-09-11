#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include "Math.h"
#include "ITexture.h"

//	v - ������
//	u - ��������� ������ (������� ������������)
//	p - �����
//	f - float
//	e - float � ��������� [-1, 1]

namespace RayTracingEngine
{
	class Ray
	{
	public:
		void setOrigin(const CPoint3& origin)
		{
			pOrigin = origin;
			gmtlRay.setOrigin(pOrigin);
		}

		void setDir(const CVector3& dir)
		{
			uDirection = dir;
			gmtl::normalize(uDirection);

			gmtlRay.setDir(uDirection);
		}

		CPoint3 pOrigin;
		CVector3 uDirection;

		gmtl::Rayf gmtlRay;
	};

	struct RGBColor
	{
		float eR;
		float eG;
		float eB;

		RGBColor operator*(float f)
		{
			return RGBColor{eR * f, eG * f, eB * f};
		}

		RGBColor operator+(RGBColor c)
		{
			return RGBColor{eR + c.eR, eG + c.eG, eB + c.eB};
		}
	};

	struct Intersection
	{
		float	fDistance;	//	���������� �� ��������� ���� �� ����� �����������
		CPoint3	pPoint;		//	����� �����������
		Ray		ray;		//	���
		CVector3 uNormal;	//	������� � ����� �����������
		ITexture* ptrTexture;
	};

	struct Vertex
	{
		CPoint3 pPostion;
		CVector3 uNormal;
	};

	extern const RGBColor RGB_WHITE;
	extern const RGBColor RGB_BLACK;
	extern const RGBColor RGB_RED;
	extern const RGBColor RGB_GREEN;
	extern const RGBColor RGB_BLUE;

}	//	namespace RayTracingEngine

#endif // _STRUCTURES_H_