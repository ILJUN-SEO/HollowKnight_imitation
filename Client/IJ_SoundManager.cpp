#include "IJ_SoundManager.h"
#include "IJ_Application.h"


extern IJ::Application application;

namespace IJ
{
	LPDIRECTSOUND8 SoundManager::mySoundDevice;

	bool SoundManager::Initialize()
	{
		if (FAILED(DirectSoundCreate8(NULL, &mySoundDevice, NULL)))
		{
			MessageBox(NULL, L"사운드 디바이스 생성 실패", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		// 사운드 디바이스 협조레벨 설정
		HWND hWnd = application.GetHWND();
		if (FAILED(mySoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag 값 정리
		{
			MessageBox(NULL, L"사운드 디바이스 협조레벨 설정", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		return true;
	}
}