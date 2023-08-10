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

#include "IJ_HUDHealth.h"
#include "IJ_PlayerSlash.h"


namespace IJ
{
	Player::Player()
		: myCurrentState(myPlayerState::Idle)
		, isLookingLeft(true)
		, isGrounded(false)
		, jumpPressingTime(0.0f)
		, damageStunTime(0.0f)
		, isAttacking(false)
		, playerHealth(5)
		, playerMana(0)
	{}

	Player::~Player()
	{}

	void Player::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		Texture* img = ResourceManager::Load<Texture>(L"Knight_atlas"
			, L"..\\Resources\\Extras\\atlas\\knight_atlas_test.png");
		Collider* col = AddComponent<Collider>();
		Animator* at = AddComponent<Animator>();

		col->SetSize(Vector2(64.0f, 128.0f));

		//at->SetScale(Vector2(0.6f, 0.6f));
		//col->SetScale(0.6f);

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

		HUDHealth* hp1 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		HUDHealth* hp2 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		HUDHealth* hp3 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		HUDHealth* hp4 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		HUDHealth* hp5 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);

		myHealth.push_back(hp1);
		myHealth.push_back(hp2);
		myHealth.push_back(hp3);
		myHealth.push_back(hp4);
		myHealth.push_back(hp5);

		hp1->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 80.0f));
		hp2->GetComponent<Transform>()->SetPosition(Vector2(300.0f, 80.0f));
		hp3->GetComponent<Transform>()->SetPosition(Vector2(400.0f, 80.0f));
		hp4->GetComponent<Transform>()->SetPosition(Vector2(500.0f, 80.0f));
		hp5->GetComponent<Transform>()->SetPosition(Vector2(600.0f, 80.0f));
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
		case IJ::Player::myPlayerState::JumpAttack:
			JumpAttack();
			break;
		case IJ::Player::myPlayerState::FallAttack:
			FallAttack();
			break;
		case IJ::Player::myPlayerState::Focus:
			Focus();
			break;
		case IJ::Player::myPlayerState::Spell:
			Spell();
			break;
		case IJ::Player::myPlayerState::Death:
			Death();
			break;
		case IJ::Player::myPlayerState::Damaged:
			Damaged();
			break;
		case IJ::Player::myPlayerState::END:
			break;
		default:
			break;
		}

		for (size_t i = 0; i < myHealth.size(); i++)
		{
			if (i + 1 > playerHealth)
				myHealth[i]->SetActivated(false);
		}

		if (Input::GetKeyDown(myKeyCode::I))
		{
			// 디버그용 위치 초기화
			GetComponent<Transform>()->SetPosition(Vector2(2300.0f, 4600.0f));
			myCurrentState = myPlayerState::Fall;
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
		damageStunTime = 0.0f;
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
		//Rigidbody* rigidbody = GetComponent<Rigidbody>();
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
		transform->SetPosition(position);

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

	}

	void Player::Jump()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();
		//Rigidbody* rigidbody = GetComponent<Rigidbody>();

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
				position.y -= 600.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else if (0.4f <= jumpPressingTime && jumpPressingTime < 0.6f)
			{
				position.y -= 300.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else
				myCurrentState = myPlayerState::Fall;
		}
		transform->SetPosition(position);
		isGrounded = false;

		if (Input::GetKeyUp(myKeyCode::D))
			myCurrentState = myPlayerState::Fall;

		if (Input::GetKeyDown(myKeyCode::S))
			myCurrentState = myPlayerState::JumpAttack;
	}

	void Player::Fall()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();
		//Rigidbody* rb = GetComponent<Rigidbody>();

		jumpPressingTime = 0.0f;
		isAttacking = false;

		position.y += 600.0f * Time::DeltaTime();

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
		transform->SetPosition(position);

		if (isGrounded)
			myCurrentState = myPlayerState::Idle;
		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myPlayerState::Falling;

		if (Input::GetKeyDown(myKeyCode::S))
			myCurrentState = myPlayerState::FallAttack;
	}

	void Player::Falling()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();
		//Rigidbody* rb = GetComponent<Rigidbody>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_falling_left", true);
		else
			animator->PlayAnimation(L"Knight_falling_right", true);

		position.y += 600.0f * Time::DeltaTime();

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
		transform->SetPosition(position);

		if (isGrounded)
			myCurrentState = myPlayerState::Idle;

		if (Input::GetKeyDown(myKeyCode::S))
			myCurrentState = myPlayerState::FallAttack;
	}

	void Player::Dash()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
	}

	void Player::Attack()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		//Rigidbody* rigidbody = GetComponent<Rigidbody>();
		Animator* animator = GetComponent<Animator>();

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
		}

		if (isAttacking == false)
		{
			isAttacking = true;

			if (isLookingLeft)
				animator->PlayAnimation(L"Knight_attack_left");
			else
				animator->PlayAnimation(L"Knight_attack_right");

			PlayerSlash* playerslash = InputObject::Instantiate<PlayerSlash>(myLayerType::PlayerSlash);
			playerslash->SetOwner(this);
			if (isLookingLeft)
			{
				playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_left", false);
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 112.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(-100.0f, 0.0f));
			}
			else
			{
				playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_right", false);
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 112.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(100.0f, 0.0f));
			}
		}

		if (animator->IsActavatedAnimationComplete())
		{
			isAttacking = false;
			myCurrentState = myPlayerState::Idle;
		}

		transform->SetPosition(position);
	}

	void Player::JumpAttack()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();
		//Rigidbody* rigidbody = GetComponent<Rigidbody>();

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
		}

		if (Input::GetKeyPressing(myKeyCode::D))
		{
			if (jumpPressingTime < 0.4f)
			{
				position.y -= 600.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else if (0.4f <= jumpPressingTime && jumpPressingTime < 0.6f)
			{
				position.y -= 300.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else
			{
				myCurrentState = myPlayerState::Fall;
			}
		}
		if (Input::GetKeyUp(myKeyCode::D))
		{
			myCurrentState = myPlayerState::Fall;
		}
		transform->SetPosition(position);

		if (isAttacking == false)
		{
			isAttacking = true;

			if (isLookingLeft)
				animator->PlayAnimation(L"Knight_attack_left");
			else
				animator->PlayAnimation(L"Knight_attack_right");

			PlayerSlash* playerslash = InputObject::Instantiate<PlayerSlash>(myLayerType::PlayerSlash);
			playerslash->SetOwner(this);
			if (isLookingLeft)
			{
				playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_left", false);
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 112.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(-100.0f, 0.0f));
			}
			else
			{
				playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_right", false);
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 112.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(100.0f, 0.0f));
			}
		}

		if (animator->IsActavatedAnimationComplete())
		{
			isAttacking = false;
			myCurrentState = myPlayerState::Fall;
		}
	}

	void Player::FallAttack()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();
		//Rigidbody* rigidbody = GetComponent<Rigidbody>();

		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			position.x -= 300.0f * Time::DeltaTime();
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			position.x += 300.0f * Time::DeltaTime();
		}

		position.y += 600.0f * Time::DeltaTime();

		transform->SetPosition(position);

		if (isAttacking == false)
		{
			isAttacking = true;

			if (isLookingLeft)
				animator->PlayAnimation(L"Knight_attack_left");
			else
				animator->PlayAnimation(L"Knight_attack_right");

			PlayerSlash* playerslash = InputObject::Instantiate<PlayerSlash>(myLayerType::PlayerSlash);
			playerslash->SetOwner(this);
			if (isLookingLeft)
			{
				playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_left", false);
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 112.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(-100.0f, 0.0f));
			}
			else
			{
				playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_right", false);
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 112.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(100.0f, 0.0f));
			}
		}

		if (animator->IsActavatedAnimationComplete())
		{
			isAttacking = false;
			myCurrentState = myPlayerState::Falling;
		}

		if (isGrounded)
			myCurrentState = myPlayerState::Idle;
	}

	void Player::Focus()
	{}

	void Player::Spell()
	{}

	void Player::Damaged()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (damageStunTime == 0.0f)
		{
			playerHealth--;
			isGrounded = false;
		}
		

		if (isLookingLeft)
			pos.x += 300.0f * Time::DeltaTime();
		else
			pos.x -= 300.0f * Time::DeltaTime();
		pos.y -= 150.0f * Time::DeltaTime();
		tr->SetPosition(pos);

		damageStunTime += Time::DeltaTime();
		if (damageStunTime > 0.25f)
			myCurrentState = Player::myPlayerState::Fall;
	}

	void Player::Death()
	{}
}