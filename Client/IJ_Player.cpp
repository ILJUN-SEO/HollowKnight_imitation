#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Input.h"
#include "IJ_Time.h"
#include "IJ_Animator.h"


namespace IJ
{
	Player::Player()
	{}

	Player::~Player()
	{}

	void Player::Initialize()
	{}

	void Player::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		
		bool myinput = false;
		if (Input::GetKeyPressing(myKeyCode::Up))
		{
			pos.y -= 300.0f * Time::DeltaTime();
			myinput = true;
		}
		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			anim->PlayAnimation(L"Knight_walk", true);

			pos.x -= 300.0f * Time::DeltaTime();
			myinput = true;
		}
		if (Input::GetKeyPressing(myKeyCode::Down))
		{
			pos.y += 300.0f * Time::DeltaTime();
			myinput = true;
		}
		if (Input::GetKeyPressing(myKeyCode::Right))
		{
			anim->PlayAnimation(L"Knight_walk", true);

			pos.x += 300.0f * Time::DeltaTime();
			myinput = true;
		}
		if (myinput == false)
		{
			anim->PlayAnimation(L"Knight_idle", true);
		}

		tr->SetPosition(pos);
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}