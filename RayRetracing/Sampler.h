#pragma once

namespace RayTracingEngine
{
	class CSampler
	{
	public:
		CSampler();

		bool getNext(float& x, float& y);

		void reset();

		int width, height;

		int xCurrent, yCurrent;
	};
}
