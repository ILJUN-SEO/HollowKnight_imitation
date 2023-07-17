#include "IJ_Time.h"


namespace IJ
{
	LARGE_INTEGER Time::myCpuFrequency = {};
	LARGE_INTEGER Time::myPrevFrequency = {};
	LARGE_INTEGER Time::myCurrentFrequency = {};
	float Time::myDeltaTime = 0.0f;
	float Time::fps = 0.0f;

	void Time::Initialize()
	{
		// CPU 고유 진동수를 가져옵니다
		QueryPerformanceFrequency(&myCpuFrequency);

		// 프로그램이 시작되었을 당시의 진동수를 가져옵니다
		QueryPerformanceCounter(&myPrevFrequency);
	}

	void Time::Update()
	{
		// 전 프레임과의 진동수 차를 구하고 CPU 고유 진동수로 나누어 현재 작업이 얼마나 오래 걸렸는지 알 수 있습니다
		QueryPerformanceCounter(&myCurrentFrequency);
		float FrequencyDifference = static_cast<float>(myCurrentFrequency.QuadPart - myPrevFrequency.QuadPart);

		myDeltaTime = FrequencyDifference / static_cast<float>(myCpuFrequency.QuadPart);
		myPrevFrequency.QuadPart = myCurrentFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		// 화면에 현제 프레임레이트를 표시합니다
		// 연산량이 많으므로 사용할 때엔 주의합시다
		static float timeCount = 0.0f;

		timeCount += myDeltaTime;
		if (timeCount >= 1.0f)
		{
			Time::fps = 1.0f / myDeltaTime;
			
			timeCount = 0.0f;
		}
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"FPS : %f", Time::fps);
		int strLength = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 10, szFloat, strLength);
	}
}