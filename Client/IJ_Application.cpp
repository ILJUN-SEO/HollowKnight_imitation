#include "IJ_Application.h"
#include "IJ_Time.h"
#include "IJ_Input.h"
#include "IJ_SceneManager.h"
#include "IJ_Camera.h"
#include "IJ_CollisionManager.h"
#include "IJ_SoundManager.h"


namespace IJ
{
	Application::Application()
		: myHWND(NULL)
		, myHDC(NULL)
		, myBackHDC(NULL)
		, myBackBuffer(NULL)
		, myWidth(0)
		, myHeight(0)
	{}
	Application::~Application()
	{}

	void Application::Initialize(HWND hwnd)
	{
		myHWND = hwnd;
		myHDC = GetDC(myHWND);

		myWidth = 1600;
		myHeight = 900;

		// 창의 크기를 재조정해줍니다
		RECT myWinSize = { 0, 0, myWidth, myHeight };
		AdjustWindowRect(&myWinSize, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(myHWND
			, nullptr, 0, 0
			, myWinSize.right - myWinSize.left
			, myWinSize.bottom - myWinSize.top
			, 0);
		ShowWindow(myHWND, true);

		// 더블버퍼링 비슷한것을 위해 보이진 않지만 그릴수는 있는 비트맵을 만듭니다
		// Render에서 그려지는 것들은 다 이곳에 그려집니다
		myBackBuffer = CreateCompatibleBitmap(myHDC, myWidth, myHeight);
		myBackHDC = CreateCompatibleDC(myHDC);
		HBITMAP tempBitmap = (HBITMAP)SelectObject(myBackHDC, myBackBuffer);
		DeleteObject(tempBitmap);

		// 초기화가 필요한 클래스들의 초기화를 해줍니다
		Time::Initialize();
		Input::Initialize();
		SoundManager::Initialize();
		Camera::Initialize();

		CollisionManager::Initialize();
		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		Camera::Update();

		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(myBackHDC, brush);
		Rectangle(myBackHDC, -1, -1, myWidth + 1, myHeight + 1);
		SelectObject(myBackHDC, oldBrush);
		DeleteObject(brush);
		//Time::Render(myBackHDC);

		CollisionManager::Render(myBackHDC);
		SceneManager::Render(myBackHDC);
		// 백 버퍼에 그려진 것들을 메인 버퍼에 복사합니다
		BitBlt(myHDC, 0, 0, myWidth, myHeight
			, myBackHDC, 0, 0, SRCCOPY);
	}

	void Application::Release()
	{}
}