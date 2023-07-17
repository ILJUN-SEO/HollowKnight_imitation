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
		// CPU ���� �������� �����ɴϴ�
		QueryPerformanceFrequency(&myCpuFrequency);

		// ���α׷��� ���۵Ǿ��� ����� �������� �����ɴϴ�
		QueryPerformanceCounter(&myPrevFrequency);
	}

	void Time::Update()
	{
		// �� �����Ӱ��� ������ ���� ���ϰ� CPU ���� �������� ������ ���� �۾��� �󸶳� ���� �ɷȴ��� �� �� �ֽ��ϴ�
		QueryPerformanceCounter(&myCurrentFrequency);
		float FrequencyDifference = static_cast<float>(myCurrentFrequency.QuadPart - myPrevFrequency.QuadPart);

		myDeltaTime = FrequencyDifference / static_cast<float>(myCpuFrequency.QuadPart);
		myPrevFrequency.QuadPart = myCurrentFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		// ȭ�鿡 ���� �����ӷ���Ʈ�� ǥ���մϴ�
		// ���귮�� �����Ƿ� ����� ���� �����սô�
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