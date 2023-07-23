#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Input.h"
#include "IJ_Time.h"
#include "IJ_Animator.h"


namespace IJ
{
	Player::Player()
		: myCurrentState(myPlayerState::Idle)
		, isLookingLeft(true)
		, isGrounded(true)
	{}

	Player::~Player()
	{}

	void Player::Initialize()
	{}

	void Player::Update()
	{
		GameObject::Update();

		switch (myCurrentState)
		{
		case IJ::Player::myPlayerState::Idle:
			Idle();
			break;
		case IJ::Player::myPlayerState::Move:
			Move();
			break;
		case IJ::Player::myPlayerState::Jump:
			Jump();
			break;
		case IJ::Player::myPlayerState::Fall:
			Fall();
			break;
		case IJ::Player::myPlayerState::Falling:
			Falling();
			break;
		case IJ::Player::myPlayerState::Attack:
			Attack();
			break;
		case IJ::Player::myPlayerState::Spell:
			break;
		case IJ::Player::myPlayerState::SpellUp:
			break;
		case IJ::Player::myPlayerState::SpellDown:
			break;
		case IJ::Player::myPlayerState::Death:
			break;
		case IJ::Player::myPlayerState::END:
			break;
		default:
			break;
		}
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{}

	void Player::OnCollisionStay(Collider* other)
	{}

	void Player::OnCollisionExit(Collider* other)
	{}

	void Player::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_idle_left", true);
		else
			animator->PlayAnimation(L"Knight_idle_right", true);

		if (Input::GetKeyDown(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Left))
		{
			isLookingLeft = true;
			myCurrentState = myPlayerState::Move;
		}
		else if (Input::GetKeyDown(myKeyCode::Right) || Input::GetKeyPressing(myKeyCode::Right))
		{
			isLookingLeft = false;
			myCurrentState = myPlayerState::Move;
		}

		if (Input::GetKeyDown(myKeyCode::D))
			myCurrentState = myPlayerState::Jump;

		if (Input::GetKeyDown(myKeyCode::S))
			myCurrentState = myPlayerState::Attack;
	}

	void Player::Move()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_walk_left", true);
		else
			animator->PlayAnimation(L"Knight_walk_right", true);

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
			isLookingLeft = true;
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
			isLookingLeft = false;
		}

		if (Input::GetKeyDown(myKeyCode::Down))
			position = Vector2(800.0f, 600.0f);

		if (Input::GetKeyDown(myKeyCode::D))
			myCurrentState = myPlayerState::Jump;

		if (Input::GetKeyDown(myKeyCode::S))
			myCurrentState = myPlayerState::Attack;

		if (Input::GetKeyUp(myKeyCode::Left))
		{
			myCurrentState = myPlayerState::Idle;
		}
		else if (Input::GetKeyUp(myKeyCode::Right))
		{
			myCurrentState = myPlayerState::Idle;
		}

		transform->SetPosition(position);
	}

	void Player::Jump()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_jump_left");
		else
			animator->PlayAnimation(L"Knight_jump_right");

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
			isLookingLeft = true;
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
			isLookingLeft = false;
		}

		if (Input::GetKeyPressing(myKeyCode::D))
		{
			if (jumpPressingTime < 1.0f)
			{
				position.y -= 500.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else
			{
				jumpPressingTime = 0.0f;
				myCurrentState = myPlayerState::Fall;
			}
		}
		
		if (Input::GetKeyUp(myKeyCode::D))
		{
			jumpPressingTime = 0.0f;
			myCurrentState = myPlayerState::Fall;
		}

		tr->SetPosition(position);
	}

	void Player::Fall()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_fall_left");
		else
			animator->PlayAnimation(L"Knight_fall_right");

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
			isLookingLeft = true;
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
			isLookingLeft = false;
		}

		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myPlayerState::Falling;

		tr->SetPosition(position);
	}

	void Player::Falling()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_falling_left", true);
		else
			animator->PlayAnimation(L"Knight_falling_right", true);

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
			isLookingLeft = true;
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
			isLookingLeft = false;
		}

		if (Input::GetKeyDown(myKeyCode::I))
		{
			position = Vector2(800.0f, 600.0f);
			myCurrentState = myPlayerState::Idle;
		}

		tr->SetPosition(position);
	}

	void Player::Attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_attack_left");
		else
			animator->PlayAnimation(L"Knight_attack_right");

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
			isLookingLeft = true;
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
			isLookingLeft = false;
		}

		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myPlayerState::Idle;

		tr->SetPosition(position);
	}

	void Player::Spell()
	{}

	void Player::SpellUp()
	{}

	void Player::SpellDown()
	{}

	void Player::Death()
	{}
}