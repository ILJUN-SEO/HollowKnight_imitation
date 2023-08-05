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

		// â�� ũ�⸦ ���������ݴϴ�
		RECT myWinSize = { 0, 0, myWidth, myHeight };
		AdjustWindowRect(&myWinSize, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(myHWND
			, nullptr, 0, 0
			, myWinSize.right - myWinSize.left
			, myWinSize.bottom - myWinSize.top
			, 0);
		ShowWindow(myHWND, true);

		// ������۸� ����Ѱ��� ���� ������ ������ �׸����� �ִ� ��Ʈ���� ����ϴ�
		// Render���� �׷����� �͵��� �� �̰��� �׷����ϴ�
		myBackBuffer = CreateCompatibleBitmap(myHDC, myWidth, myHeight);
		myBackHDC = CreateCompatibleDC(myHDC);
		HBITMAP tempBitmap = (HBITMAP)SelectObject(myBackHDC, myBackBuffer);
		DeleteObject(tempBitmap);

		// �ʱ�ȭ�� �ʿ��� Ŭ�������� �ʱ�ȭ�� ���ݴϴ�
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
		// �� ���ۿ� �׷��� �͵��� ���� ���ۿ� �����մϴ�
		BitBlt(myHDC, 0, 0, myWidth, myHeight
			, myBackHDC, 0, 0, SRCCOPY);
	}

	void Application::Release()
	{}
}