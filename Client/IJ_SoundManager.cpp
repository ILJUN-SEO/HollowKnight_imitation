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
			MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		// ���� ����̽� �������� ����
		HWND hWnd = application.GetHWND();
		if (FAILED(mySoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag �� ����
		{
			MessageBox(NULL, L"���� ����̽� �������� ����", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		return true;
	}
}