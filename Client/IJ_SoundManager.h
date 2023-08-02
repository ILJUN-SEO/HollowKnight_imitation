#pragma once
#include "CommonInclude.h"


namespace IJ
{
	class SoundManager
	{
	public:
		static bool Initialize();
		static LPDIRECTSOUND8 GetDevice() { return mySoundDevice; }

	private:
		static LPDIRECTSOUND8 mySoundDevice;
	};
}
