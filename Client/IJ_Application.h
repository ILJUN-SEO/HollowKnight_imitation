#pragma once
#include "CommonInclude.h"

namespace IJ
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();
		void Release();

		HWND GetHWND() { return myHWND; }
		HDC GetHDC() { return myHDC; }

		UINT GetWidth() { return myWidth; }
		UINT GetHeight() { return myHeight; }

	private:
		HWND myHWND;
		HDC myHDC;
		HDC myBackHDC;
		HBITMAP myBackBuffer;

		UINT myWidth;
		UINT myHeight;
	};
}
