#pragma once

#include "Sampler.h"

namespace RayTracingEngine
{

	class CCamera
	{
	public:
		CCamera(uint width, uint height,
				const CPoint3& position, const CVector3& direction, const CVector3& up,
				float viewportWidth, float viewportHeight, float focalLength);

		void initialize(const CPoint3& position, const CVector3& direction, const CVector3& up,
						float viewportWidth, float viewportHeight, float focalLength);

		bool getNextRay(Ray& ray);

		void reset();

		uint		width = 1;
		uint		height = 1;

	public:
		CPoint3		pPosition;
		CVector3	uFwDirection;		//	-w
		CVector3	uUpDirection;		//	v
		CVector3	uRightDirection;	//	u
		float		pixelWidth;
		float		pixelHeight;
		float		focalLength;

		CPoint3		pLeftUpCorner;

		CSampler sampler;

		CPoint3		getPixelPt(float x, float y);
	};

}