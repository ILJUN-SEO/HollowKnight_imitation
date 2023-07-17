#include "IJ_Camera.h"
#include "IJ_Application.h"
#include "IJ_Transform.h"
#include "IJ_Input.h"
#include "IJ_Time.h"


extern IJ::Application application;

namespace IJ
{
	Vector2 Camera::myResolution = Vector2::Zero;
	Vector2 Camera::myCameraPosition = Vector2::Zero;
	Vector2 Camera::myWinPosition = Vector2::Zero;
	GameObject* Camera::myTarget = nullptr;

	void Camera::Initialize()
	{
		myResolution.x = application.GetWidth();
		myResolution.y = application.GetHeight();
		myCameraPosition = myResolution / 2.0f;
	}

	void Camera::Update()
	{
		if (Input::GetKeyPressing(myKeyCode::H))
			myCameraPosition.y -= 300.0f * Time::DeltaTime();
		if (Input::GetKeyPressing(myKeyCode::N))
			myCameraPosition.y += 300.0f * Time::DeltaTime();
		if (Input::GetKeyPressing(myKeyCode::B))
			myCameraPosition.x -= 300.0f * Time::DeltaTime();
		if (Input::GetKeyPressing(myKeyCode::M))
			myCameraPosition.x += 300.0f * Time::DeltaTime();

		if (myTarget)
		{
			Transform* tr = myTarget->GetComponent<Transform>();
			myCameraPosition = tr->GetPosition();
		}

		myWinPosition = myCameraPosition - (myResolution / 2.0f);
	}
}