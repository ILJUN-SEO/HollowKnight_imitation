#pragma once
#include "CommonInclude.h"

namespace IJ
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		__forceinline static float DeltaTime() { return myDeltaTime; }

	private:
		static LARGE_INTEGER myCpuFrequency;
		static LARGE_INTEGER myPrevFrequency;
		static LARGE_INTEGER myCurrentFrequency;
		static float myDeltaTime;

		static float fps;
	};
}
