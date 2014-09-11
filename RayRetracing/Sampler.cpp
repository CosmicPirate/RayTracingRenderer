#include "Structures.h"
#include "Sampler.h"

namespace RayTracingEngine
{
	CSampler::CSampler()
	{
		xCurrent = 0;
		yCurrent = 0;
	}


	bool CSampler::getNext(float& x, float& y)
	{
		++xCurrent;

		if (xCurrent >= width)
		{
			xCurrent = 0;
			++yCurrent;
		}

		if (yCurrent >= height)
			return false;

		x = xCurrent + 0.5;// gmtl::Math::unitRandom();
		y = yCurrent + 0.5;// gmtl::Math::unitRandom();

		return true;
	}

	void CSampler::reset()
	{
		xCurrent = 0;
		yCurrent = 0;
	}
}
