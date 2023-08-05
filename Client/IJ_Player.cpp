#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Input.h"
#include "IJ_Time.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"
#include "IJ_ObjectManager.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"

#include "IJ_PlayerSlash.h"


namespace IJ
{
	Player::Player()
		: myCurrentState(myPlayerState::Idle)
		, isLookingLeft(true)
		, isGrounded(false)
		, jumpPressingTime(0.0f)
		, isAttacking(false)
	{}

	Player::~Player()
	{}

	void Player::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		Rigidbody* rb = AddComponent<Rigidbody>();
		Texture* img = ResourceManager::Load<Texture>(L"Knight_atlas"
			, L"..\\Resources\\Extras\\atlas\\knight_atlas_test.png");
		Collider* col = AddComponent<Collider>();
		Animator* at = AddComponent<Animator>();

		col->SetSize(Vector2(64.0f, 128.0f));

		at->CreateAnimationInAnimator(L"Knight_idle_left", img, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_idle_right", img, Vector2(0.0f, 128.0f), Vector2(64.0f, 128.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_walk_left", img, Vector2(0.0f, 256.0f), Vector2(64.0f, 128.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_walk_right", img, Vector2(0.0f, 384.0f), Vector2(64.0f, 128.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_jump_left", img, Vector2(0.0f, 512.0f), Vector2(96.0f, 136.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_jump_right", img, Vector2(0.0f, 646.0f), Vector2(96.0f, 136.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_left", img, Vector2(0.0f, 784.0f), Vector2(96.0f, 144.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_right", img, Vector2(0.0f, 928.0f), Vector2(96.0f, 144.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_falling_left", img, Vector2(288.0f, 784.0f), Vector2(96.0f, 144.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_falling_right", img, Vector2(288.0f, 928.0f), Vector2(96.0f, 144.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_attack_left", img, Vector2(0.0f, 1072.0f), Vector2(128.0f, 128.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_right", img, Vector2(0.0f, 1200.0f), Vector2(128.0f, 128.0f), 5);
	}

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
		case IJ::Player::myPlayerState::Dash:
			Dash();
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

		jumpPressingTime = 0.0f;
		isAttacking = false;

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
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
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
		Rigidbody* rigidbody = GetComponent<Rigidbody>();

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
			if (jumpPressingTime < 0.4f)
			{
				Vector2 velocity = rigidbody->GetVelocity();
				velocity.y = -600.0f;
				rigidbody->SetVelocity(velocity);
				jumpPressingTime += Time::DeltaTime();
			}
			else if (0.4f <= jumpPressingTime && jumpPressingTime < 0.6f)
			{
				Vector2 velocity = rigidbody->GetVelocity();
				velocity.y = -300.0f;
				rigidbody->SetVelocity(velocity);
				jumpPressingTime += Time::DeltaTime();
			}
			else
			{
				Vector2 velocity = rigidbody->GetVelocity();
				velocity.y = 0.0f;
				rigidbody->SetVelocity(velocity);
				//jumpPressingTime = 0.0f;
				myCurrentState = myPlayerState::Fall;
			}
		}
		
		if (Input::GetKeyUp(myKeyCode::D))
		{
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.y = 0.0f;
			rigidbody->SetVelocity(velocity);
			//jumpPressingTime = 0.0f;
			myCurrentState = myPlayerState::Fall;
		}

		tr->SetPosition(position);
		rigidbody->SetGrounded(false);
	}

	void Player::Fall()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();

		jumpPressingTime = 0.0f;

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_fall_left");
		else
			animator->PlayAnimation(L"Knight_fall_right");

		Vector2 velocity = rb->GetVelocity();
		velocity.y = 600.0f;
		rb->SetVelocity(velocity);

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

		if (isGrounded)
			myCurrentState = myPlayerState::Idle;
		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myPlayerState::Falling;

		tr->SetPosition(position);
	}

	void Player::Falling()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rb = GetComponent<Rigidbody>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_falling_left", true);
		else
			animator->PlayAnimation(L"Knight_falling_right", true);

		Vector2 velocity = rb->GetVelocity();
		velocity.y = 600.0f;
		rb->SetVelocity(velocity);

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
		if (isGrounded)
			myCurrentState = myPlayerState::Idle;

		tr->SetPosition(position);
	}

	void Player::Dash()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Rigidbody* rb = GetComponent<Rigidbody>();
	}

	void Player::Attack()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 position = tr->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
			//isLookingLeft = true;
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
			//isLookingLeft = false;
		}

		if (isAttacking == false)
		{
			isAttacking = true;

			if (isLookingLeft)
				animator->PlayAnimation(L"Knight_attack_left");
			else
				animator->PlayAnimation(L"Knight_attack_right");

			Texture* texture = ResourceManager::Load<Texture>(L"SlashEffect"
				, L"..\\Resources\\Extras\\atlas\\SlashEffect.png");
			PlayerSlash* playerslash = InputObject::Instantiate<PlayerSlash>(myLayerType::Player);
			playerslash->SetOwner(this);
			Transform* slash_tr = playerslash->GetComponent<Transform>();
			//slash_tr->SetPosition(tr->GetPosition());
			Animator* slash_at = playerslash->AddComponent<Animator>();
			slash_at->CreateAnimationInAnimator(L"Slash_left", texture, Vector2(0.0f, 0.0f), Vector2(160.0f, 112.0f), 4, Vector2(-100.0f, 0.0f));
			slash_at->CreateAnimationInAnimator(L"Slash_right", texture, Vector2(0.0f, 112.0f), Vector2(160.0f, 112.0f), 4, Vector2(100.0f, 0.0f));
			Collider* slash_col = playerslash->AddComponent<Collider>();
			if (isLookingLeft)
			{
				slash_at->PlayAnimation(L"Slash_left", false);
				slash_col->SetSize(Vector2(160.0f, 112.0f));
				slash_col->SetOffset(Vector2(-100.0f, 0.0f));
			}
			else
			{
				slash_at->PlayAnimation(L"Slash_right", false);
				slash_col->SetSize(Vector2(160.0f, 112.0f));
				slash_col->SetOffset(Vector2(100.0f, 0.0f));
			}

			//InputObject::Instantiate<PlayerSlash>(myLayerType::Player);
		}

		if (animator->IsActavatedAnimationComplete())
		{
			isAttacking = false;
			myCurrentState = myPlayerState::Idle;
		}

		tr->SetPosition(position);
		//slash_tr->SetPosition(position);
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