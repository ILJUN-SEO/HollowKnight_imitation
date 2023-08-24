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

#include "IJ_HUDFrame.h"
#include "IJ_HUDHealth.h"
#include "IJ_HUDMana.h"

#include "IJ_PlayerSlash.h"


namespace IJ
{
	Player::Player()
		: myCurrentState(myPlayerState::Idle)
		, isLookingLeft(true)
		, isGrounded(false)
		, jumpPressingTime(0.0f)
		, damageStunTime(0.0f)
		, damageInvincibleTime(0.0f)
		, isAttacking(false)
		, attackCooldown(0.5f)
		, altSlashTrigger(false)
		, playerMaxHealth(5)
		, playerHealth(5)
		, playerMaxMana(12)
		, playerMana(0)
	{}

	Player::~Player()
	{}

	void Player::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		Texture* img = ResourceManager::Load<Texture>(L"Knight_atlas"
			, L"..\\Resources\\Extras\\atlas\\knight_atlas.png");
		Collider* col = AddComponent<Collider>();
		Animator* at = AddComponent<Animator>();

		col->SetSize(Vector2(60.0f, 130.0f));

		at->CreateAnimationInAnimator(L"Knight_idle_left", img, Vector2(0.0f, 0.0f), Vector2(70.0f, 140.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_idle_right", img, Vector2(0.0f, 140.0f), Vector2(70.0f, 140.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_walk_left", img, Vector2(0.0f, 280.0f), Vector2(70.0f, 140.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_walk_right", img, Vector2(0.0f, 420.0f), Vector2(70.0f, 140.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_jump_left", img, Vector2(0.0f, 560.0f), Vector2(100.0f, 150.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_jump_right", img, Vector2(0.0f, 710.0f), Vector2(100.0f, 150.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_left", img, Vector2(0.0f, 860.0f), Vector2(100.0f, 150.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_right", img, Vector2(0.0f, 1010.0f), Vector2(100.0f, 150.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_falling_left", img, Vector2(300.0f, 860.0f), Vector2(100.0f, 150.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_falling_right", img, Vector2(300.0f, 1010.0f), Vector2(100.0f, 150.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_attack_left", img, Vector2(0.0f, 1160.0f), Vector2(120.0f, 140.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_right", img, Vector2(0.0f, 1300.0f), Vector2(120.0f, 140.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_alt_left", img, Vector2(0.0f, 1440.0f), Vector2(170.0f, 140.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_alt_right", img, Vector2(0.0f, 1580.0f), Vector2(170.0f, 140.0f), 5);

		HUDFrame* hudFrame = InputObject::Instantiate<HUDFrame>(myLayerType::UI);

		HUDHealth* hp1 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		hp1->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 80.0f));
		myHealth.push_back(hp1);
		HUDHealth* hp2 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		hp2->GetComponent<Transform>()->SetPosition(Vector2(300.0f, 80.0f));
		myHealth.push_back(hp2);
		HUDHealth* hp3 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		hp3->GetComponent<Transform>()->SetPosition(Vector2(400.0f, 80.0f));
		myHealth.push_back(hp3);
		HUDHealth* hp4 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		hp4->GetComponent<Transform>()->SetPosition(Vector2(500.0f, 80.0f));
		myHealth.push_back(hp4);
		HUDHealth* hp5 = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		hp5->GetComponent<Transform>()->SetPosition(Vector2(600.0f, 80.0f));
		myHealth.push_back(hp5);

		HUDMana* mp1 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp1->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 170.0f));
		mp1->AssignAnimation(L"Mana_01");
		myMana.push_back(mp1);
		HUDMana* mp2 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp2->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 160.0f));
		mp2->AssignAnimation(L"Mana_02");
		myMana.push_back(mp2);
		HUDMana* mp3 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp3->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 150.0f));
		mp3->AssignAnimation(L"Mana_03");
		myMana.push_back(mp3);
		HUDMana* mp4 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp4->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 140.0f));
		mp4->AssignAnimation(L"Mana_04");
		myMana.push_back(mp4);
		HUDMana* mp5 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp5->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 130.0f));
		mp5->AssignAnimation(L"Mana_05");
		myMana.push_back(mp5);
		HUDMana* mp6 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp6->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 120.0f));
		mp6->AssignAnimation(L"Mana_06");
		myMana.push_back(mp6);
		HUDMana* mp7 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp7->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 110.0f));
		mp7->AssignAnimation(L"Mana_07");
		myMana.push_back(mp7);
		HUDMana* mp8 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp8->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 100.0f));
		mp8->AssignAnimation(L"Mana_08");
		myMana.push_back(mp8);
		HUDMana* mp9 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp9->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 90.0f));
		mp9->AssignAnimation(L"Mana_09");
		myMana.push_back(mp9);
		HUDMana* mp10 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp10->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 80.0f));
		mp10->AssignAnimation(L"Mana_10");
		myMana.push_back(mp10);
		HUDMana* mp11 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp11->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 70.0f));
		mp11->AssignAnimation(L"Mana_11");
		myMana.push_back(mp11);
		HUDMana* mp12 = InputObject::Instantiate<HUDMana>(myLayerType::UI);
		mp12->GetComponent<Transform>()->SetPosition(Vector2(94.0f, 60.0f));
		mp12->AssignAnimation(L"Mana_12");
		myMana.push_back(mp12);
	}

	void Player::Update()
	{
		GameObject::Update();
		if (attackCooldown < 3.0f)
			attackCooldown += Time::DeltaTime();
		if (attackCooldown > 1.0f)
			altSlashTrigger = false;
		if (damageInvincibleTime < 5.0f)
			damageInvincibleTime += Time::DeltaTime();
		if (playerHealth > playerMaxHealth)
			playerHealth = playerMaxHealth;
		if (playerMana > playerMaxMana)
			playerMana = playerMaxMana;

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
			else
				myHealth[i]->SetActivated(true);
		}

		for (size_t i = 0; i < myMana.size(); i++)
		{
			if (i + 1 > playerMana)
				myMana[i]->SetActivated(false);
			else
				myMana[i]->SetActivated(true);
		}

		if (Input::GetKeyDown(myKeyCode::I))
		{
			// 디버그용 위치 초기화
			GetComponent<Transform>()->SetPosition(Vector2(2300.0f, 4600.0f));
			myCurrentState = myPlayerState::Fall;
		}
		if (Input::GetKeyDown(myKeyCode::U))
		{
			// 디버그용 체력회복
			HealthPlus();
		}
		if (Input::GetKeyDown(myKeyCode::Y))
		{
			// 디버그용 마나 회복
			ManaPlus();
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
		Animator* animator = GetComponent<Animator>();

		isAttacking = false;

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_walk_left", true);
		else
			animator->PlayAnimation(L"Knight_walk_right", true);

		MoveFunc(&position);
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

		isGrounded = false;
		isAttacking = false;

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_jump_left");
		else
			animator->PlayAnimation(L"Knight_jump_right");
		
		MoveFunc(&position);
		JumpFunc(&position);
		transform->SetPosition(position);

		if (Input::GetKeyDown(myKeyCode::S))
			myCurrentState = myPlayerState::JumpAttack;
	}

	void Player::Fall()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();

		jumpPressingTime = 0.0f;
		isAttacking = false;

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_fall_left");
		else
			animator->PlayAnimation(L"Knight_fall_right");

		position.y += 600.0f * Time::DeltaTime();
		MoveFunc(&position);
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

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_falling_left", true);
		else
			animator->PlayAnimation(L"Knight_falling_right", true);

		position.y += 600.0f * Time::DeltaTime();
		MoveFunc(&position);
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
		Animator* animator = GetComponent<Animator>();

		if (isGrounded == false)
			position.y += 600.0f * Time::DeltaTime();
		MoveFunc(&position);
		AttackFunc();
		transform->SetPosition(position);

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = myPlayerState::Idle;
		}

		//if (Input::GetKeyPressing(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Right))
		//	myCurrentState = myPlayerState::Move;
		if (isLookingLeft)
		{
			if (Input::GetKeyDown(myKeyCode::Right))
				myCurrentState = myPlayerState::Move;
		}
		else
		{
			if (Input::GetKeyDown(myKeyCode::Left))
				myCurrentState = myPlayerState::Move;
		}

		if (Input::GetKeyDown(myKeyCode::D))
			myCurrentState = myPlayerState::Jump;
	}

	void Player::JumpAttack()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();

		MoveFunc(&position);
		JumpFunc(&position);
		AttackFunc();
		transform->SetPosition(position);


		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myPlayerState::Fall;

		//if (Input::GetKeyPressing(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Right))
		//	myCurrentState = myPlayerState::Jump;
		if (isLookingLeft)
		{
			if (Input::GetKeyDown(myKeyCode::Right))
				myCurrentState = myPlayerState::Jump;
		}
		else
		{
			if (Input::GetKeyDown(myKeyCode::Left))
				myCurrentState = myPlayerState::Jump;
		}
	}

	void Player::FallAttack()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();

		position.y += 600.0f * Time::DeltaTime();
		MoveFunc(&position);
		AttackFunc();
		transform->SetPosition(position);

		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myPlayerState::Falling;

		//if (Input::GetKeyPressing(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Right))
		//	myCurrentState = myPlayerState::Falling;
		if (isLookingLeft)
		{
			if (Input::GetKeyDown(myKeyCode::Right))
				myCurrentState = myPlayerState::Falling;
		}
		else
		{
			if (Input::GetKeyDown(myKeyCode::Left))
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
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		if (damageStunTime == 0.0f)
		{
			playerHealth--;
			isGrounded = false;
		}
		damageInvincibleTime = 0.0f;

		if (isLookingLeft)
			position.x += 300.0f * Time::DeltaTime();
		else
			position.x -= 300.0f * Time::DeltaTime();
		position.y -= 300.0f * Time::DeltaTime();
		transform->SetPosition(position);

		damageStunTime += Time::DeltaTime();
		if (damageStunTime > 0.25f)
			myCurrentState = Player::myPlayerState::Fall;
	}

	void Player::Death()
	{}

	void Player::MoveFunc(Vector2* pos)
	{
		if (Input::GetKeyPressing(myKeyCode::Left))
		{
			(*pos).x -= 300.0f * Time::DeltaTime();
			isLookingLeft = true;
		}
		else if (Input::GetKeyPressing(myKeyCode::Right))
		{
			(*pos).x += 300.0f * Time::DeltaTime();
			isLookingLeft = false;
		}
	}

	void Player::JumpFunc(Vector2* pos)
	{
		if (Input::GetKeyDown(myKeyCode::D) || Input::GetKeyPressing(myKeyCode::D))
		{
			if (jumpPressingTime < 0.4f)
			{
				(*pos).y -= 600.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else if (0.4f <= jumpPressingTime && jumpPressingTime < 0.5f)
			{
				(*pos).y -= 300.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else if (0.5f <= jumpPressingTime && jumpPressingTime < 0.6f)
			{
				(*pos).y -= 150.0f * Time::DeltaTime();
				jumpPressingTime += Time::DeltaTime();
			}
			else
				myCurrentState = myPlayerState::Fall;
		}
		else
			myCurrentState = myPlayerState::Fall;
	}

	void Player::AttackFunc()
	{
		Animator* animator = GetComponent<Animator>();

		if (isAttacking == false && attackCooldown >= 0.5f)
		{
			isAttacking = true;

			if (isLookingLeft)
			{
				if (altSlashTrigger)
					animator->PlayAnimation(L"Knight_attack_alt_left");
				else
					animator->PlayAnimation(L"Knight_attack_left");
			}
			else
			{
				if (altSlashTrigger)
					animator->PlayAnimation(L"Knight_attack_alt_right");
				else
					animator->PlayAnimation(L"Knight_attack_right");
			}

			attackCooldown = 0.0f;

			PlayerSlash* playerslash = InputObject::Instantiate<PlayerSlash>(myLayerType::PlayerSlash);
			playerslash->SetOwner(this);
			if (isLookingLeft)
			{
				if (altSlashTrigger)
				{
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_left", false);
					altSlashTrigger = false;
				}
				else
				{
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_left", false);
					altSlashTrigger = true;
				}
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 100.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(-100.0f, 0.0f));
			}
			else
			{
				if (altSlashTrigger)
				{
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_right", false);
					altSlashTrigger = false;
				}
				else
				{
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_right", false);
					altSlashTrigger = true;
				}
				playerslash->GetComponent<Collider>()->SetSize(Vector2(160.0f, 100.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(100.0f, 0.0f));
			}
		}
		if (animator->IsActavatedAnimationComplete())
			isAttacking = false;
	}
}