#include "Structures.h"
#include "Camera.h"

namespace RayTracingEngine
{
	CCamera::CCamera(uint width, uint height,
		const CPoint3& position, const CVector3& direction, const CVector3& up,
		float viewportWidth, float viewportHeight, float focalLength)
	{
		if (width <= 0 || height <= 0)
			throw "width and height must not be zero or negative";

		this->width = width;
		this->height = height;

		sampler.width = width;
		sampler.height = height;

		initialize(position, direction, up, viewportWidth, viewportHeight, focalLength);
	}

	void CCamera::initialize(const CPoint3& position, const CVector3& direction, const CVector3& up,
		float viewportWidth, float viewportHeight, float focalLength)
	{
		pPosition = position;
		uFwDirection = direction;
		uUpDirection = up;

		if (viewportHeight <= 0.0f || viewportWidth <= 0.0f || focalLength <= 0.0f)
			throw "viewportWidth, viewportHeight or focalLength <= 0";

		if (gmtl::normalize(uFwDirection) == 0.0f || gmtl::length(uUpDirection) == 0.0f)
			throw "direction or upVector are zero";

		gmtl::cross(uRightDirection, uFwDirection, uUpDirection);

		if (gmtl::normalize(uRightDirection) == 0.0f)
			throw "uRightDirection is zero";

		gmtl::cross(uUpDirection, uRightDirection, uFwDirection);
		gmtl::normalize(uUpDirection);

		pixelWidth = viewportWidth / width;
		pixelHeight = viewportHeight / height;
		this->focalLength = focalLength;

		pLeftUpCorner = pPosition + focalLength * uFwDirection - viewportWidth / 2 * uRightDirection + viewportHeight / 2 * uUpDirection;
	}

	bool CCamera::getNextRay(Ray& ray)
	{
		float u, v;

		if (!sampler.getNext(u, v))
			return false;

		ray.setOrigin(pPosition);
		ray.setDir(getPixelPt(u, v));

		return true;
	}

	void CCamera::reset()
	{
		sampler.reset();
	}


	//	точка пикселя в 3Д координатах
	CPoint3 CCamera::getPixelPt(float x, float y)
	{
		return pLeftUpCorner + x * pixelWidth * uRightDirection - y * pixelHeight * uUpDirection;
	}
}
