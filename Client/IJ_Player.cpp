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
#include "IJ_Sound.h"

#include "IJ_HUDFrame.h"
#include "IJ_HUDHealth.h"
#include "IJ_HUDMana.h"

#include "IJ_PlayerSlash.h"
#include "IJ_PlayerFireball.h"


namespace IJ
{
	Player::Player()
		: myCurrentState(myPlayerState::Idle)
		, playerMaxHealth(5)
		, playerHealth(5)
		, playerMaxMana(12)
		, playerMana(0)
		, myHealth({})
		, myMana({})
		, isLookingLeft(true)
		, isGrounded(false)
		, jumpPressingTime(0.0f)
		, damageStunTime(0.0f)
		, damageInvincibleTime(0.0f)
		, isAttacking(false)
		, attackCooldown(0.5f)
		, altSlashTrigger(false)
		, focusTime(0.0f)
		, recoilTime(3.0f)
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
		at->CreateAnimationInAnimator(L"Knight_attack_up_left", img, Vector2(0.0f, 1720.0f), Vector2(120.0f, 130.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_up_right", img, Vector2(0.0f, 1850.0f), Vector2(120.0f, 130.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_down_left", img, Vector2(0.0f, 1980.0f), Vector2(130.0f, 130.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_down_right", img, Vector2(0.0f, 2110.0f), Vector2(130.0f, 130.0f), 5);
		//at->CreateAnimationInAnimator(L"Knight_focus_left", img, Vector2(0.0f, 2240.0f), Vector2(80.0f, 130.0f), 7);
		//at->CreateAnimationInAnimator(L"Knight_focus_right", img, Vector2(0.0f, 2370.0f), Vector2(80.0f, 130.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_focus_left", img, Vector2(160.0f, 2240.0f), Vector2(80.0f, 130.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_focus_right", img, Vector2(160.0f, 2370.0f), Vector2(80.0f, 130.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_focus_get_left", img, Vector2(0.0f, 2500.0f), Vector2(110.0f, 130.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_focus_get_right", img, Vector2(0.0f, 2630.0f), Vector2(110.0f, 130.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_fireball_left", img, Vector2(0.0f, 2760.0f), Vector2(140.0f, 150.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fireball_right", img, Vector2(0.0f, 2910.0f), Vector2(140.0f, 150.0f), 6);

		at->CreateAnimationInAnimator(L"Knight_stun_left", img, Vector2(600.0f, 300.0f), Vector2(120.0f, 140.0f), 1);
		at->CreateAnimationInAnimator(L"Knight_stun_right", img, Vector2(600.0f, 440.0f), Vector2(120.0f, 140.0f), 1);

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

		ResourceManager::Load<Sound>(L"Knight_walk", L"..\\Resources\\Sound\\player\\hero_walk_footsteps_stone.wav");
		ResourceManager::Load<Sound>(L"Knight_jump", L"..\\Resources\\Sound\\player\\hero_jump.wav");
		ResourceManager::Load<Sound>(L"Knight_focus", L"..\\Resources\\Sound\\player\\focus_health_charging.wav");
		ResourceManager::Load<Sound>(L"Knight_focus_get", L"..\\Resources\\Sound\\player\\focus_health_heal.wav");
		ResourceManager::Load<Sound>(L"Knight_fireball", L"..\\Resources\\Sound\\player\\hero_fireball.wav")->SetVolume(30.0f);
		ResourceManager::Load<Sound>(L"Knight_damaged", L"..\\Resources\\Sound\\player\\hero_damage.wav");
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
		if (recoilTime < 1.0f)
			recoilTime += Time::DeltaTime();

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
		case IJ::Player::myPlayerState::FocusGet:
			FocusGet();
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
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();

		isGrounded = true;
		jumpPressingTime = 0.0f;
		damageStunTime = 0.0f;
		isAttacking = false;
		focusTime = 0.0f;

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_idle_left", true);
		else
			animator->PlayAnimation(L"Knight_idle_right", true);

		if (Input::GetKeyDown(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Left))
		{
			isLookingLeft = true;
			myCurrentState = myPlayerState::Move;
			Move();
			ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
		}
		else if (Input::GetKeyDown(myKeyCode::Right) || Input::GetKeyPressing(myKeyCode::Right))
		{
			isLookingLeft = false;
			myCurrentState = myPlayerState::Move;
			Move();
			ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
		}

		if (Input::GetKeyDown(myKeyCode::D))
		{
			myCurrentState = myPlayerState::Jump;
			JumpFunc(&position);
			ResourceManager::Find<Sound>(L"Knight_jump")->Play(false);
		}

		if (Input::GetKeyDown(myKeyCode::S))
			myCurrentState = myPlayerState::Attack;

		if (Input::GetKeyDown(myKeyCode::A) && playerMana >= 4)
		{
			myCurrentState = myPlayerState::Focus;
			ResourceManager::Find<Sound>(L"Knight_focus")->Play(true);
		}
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
		{
			ResourceManager::Find<Sound>(L"Knight_walk")->Stop(true);
			myCurrentState = myPlayerState::Jump;
			ResourceManager::Find<Sound>(L"Knight_jump")->Play(false);
		}

		if (Input::GetKeyDown(myKeyCode::S))
		{
			ResourceManager::Find<Sound>(L"Knight_walk")->Stop(true);
			myCurrentState = myPlayerState::Attack;
		}

		if (Input::GetKeyDown(myKeyCode::A) && playerMana >= 4)
		{
			ResourceManager::Find<Sound>(L"Knight_walk")->Stop(true);
			myCurrentState = myPlayerState::Focus;
			ResourceManager::Find<Sound>(L"Knight_focus")->Play(true);
		}

		if (Input::GetKeyUp(myKeyCode::Left))
		{
			ResourceManager::Find<Sound>(L"Knight_walk")->Stop(true);
			myCurrentState = myPlayerState::Idle;
		}
		else if (Input::GetKeyUp(myKeyCode::Right))
		{
			ResourceManager::Find<Sound>(L"Knight_walk")->Stop(true);
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

		MoveFunc(&position);
		FallFunc(&position);
		transform->SetPosition(position);

		if (isGrounded)
		{
			if (Input::GetKeyPressing(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Right))
			{
				myCurrentState = myPlayerState::Move;
				Move();
				ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
			}
			else
				myCurrentState = myPlayerState::Idle;
		}
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

		MoveFunc(&position);
		FallFunc(&position);
		transform->SetPosition(position);

		if (isGrounded)
		{
			if (Input::GetKeyPressing(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Right))
			{
				myCurrentState = myPlayerState::Move;
				Move();
				ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
			}
			else
				myCurrentState = myPlayerState::Idle;
		}

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
			FallFunc(&position);
		MoveFunc(&position);
		AttackFunc();
		transform->SetPosition(position);

		if (animator->IsActavatedAnimationComplete())
		{
			if (Input::GetKeyPressing(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Right))
			{
				myCurrentState = myPlayerState::Move;
				Move();
				ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
			}
			else
				myCurrentState = myPlayerState::Idle;
		}

		if (isLookingLeft)
		{
			if (Input::GetKeyDown(myKeyCode::Right))
			{
				myCurrentState = myPlayerState::Move;
				Move();
				ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
			}
		}
		else
		{
			if (Input::GetKeyDown(myKeyCode::Left))
			{
				myCurrentState = myPlayerState::Move;
				Move();
				ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
			}
		}

		if (Input::GetKeyDown(myKeyCode::D))
		{
			myCurrentState = myPlayerState::Jump;
			ResourceManager::Find<Sound>(L"Knight_jump")->Play(false);
		}
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
		{
			if (jumpPressingTime < 0.6f)
				myCurrentState = myPlayerState::Jump;
			else
				myCurrentState = myPlayerState::Fall;
		}

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

		MoveFunc(&position);
		FallFunc(&position);
		AttackFunc();
		transform->SetPosition(position);

		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myPlayerState::Falling;

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
		{
			if (Input::GetKeyPressing(myKeyCode::Left) || Input::GetKeyPressing(myKeyCode::Right))
			{
				myCurrentState = myPlayerState::Move;
				Move();
				ResourceManager::Find<Sound>(L"Knight_walk")->Play(true);
			}
			else
				myCurrentState = myPlayerState::Idle;
		}
	}

	void Player::Focus()
	{
		Animator* animator = GetComponent<Animator>();

		focusTime += Time::DeltaTime();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_focus_left", true);
		else
			animator->PlayAnimation(L"Knight_focus_right", true);

		if (focusTime >= 1.5f)
		{
			HealthPlus();
			playerMana -= 4;

			ResourceManager::Find<Sound>(L"Knight_focus")->Stop(false);
			myCurrentState = Player::myPlayerState::FocusGet;
			ResourceManager::Find<Sound>(L"Knight_focus_get")->Play(false);
		}

		if (Input::GetKeyUp(myKeyCode::A))
		{
			if (focusTime < 0.3f)
			{
				ResourceManager::Find<Sound>(L"Knight_focus")->Stop(false);
				myCurrentState = Player::myPlayerState::Spell;
				SpellFunc();
				ResourceManager::Find<Sound>(L"Knight_fireball")->Play(false);
			}
			else
			{
				ResourceManager::Find<Sound>(L"Knight_focus")->Stop(true);
				myCurrentState = Player::myPlayerState::Idle;
			}
		}
	}

	void Player::FocusGet()
	{
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_focus_get_left");
		else
			animator->PlayAnimation(L"Knight_focus_get_right");

		if(animator->IsActavatedAnimationComplete())
			myCurrentState = Player::myPlayerState::Idle;
	}

	void Player::Spell()
	{
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_fireball_left");
		else
			animator->PlayAnimation(L"Knight_fireball_right");

		if (animator->IsActavatedAnimationComplete())
		{
			if (isGrounded)
				myCurrentState = Player::myPlayerState::Idle;
			else
				myCurrentState = Player::myPlayerState::Fall;
		}
	}

	void Player::Damaged()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		ResourceManager::Find<Sound>(L"Knight_walk")->Stop(true);
		ResourceManager::Find<Sound>(L"Knight_focus")->Stop(true);

		if (isLookingLeft)
			animator->PlayAnimation(L"Knight_stun_left");
		else
			animator->PlayAnimation(L"Knight_stun_right");

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
		if (damageStunTime > 0.4f)
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
		if (RecoilFunc(pos))
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
	}

	void Player::FallFunc(Vector2* pos)
	{
		if (RecoilFunc(pos))
			(*pos).y += 600.0f * Time::DeltaTime();
	}

	bool Player::RecoilFunc(Math::Vector2* pos)
	{
		if (recoilTime < 0.3f)
			(*pos).y -= 600.0f * Time::DeltaTime();

		return recoilTime >= 0.3f;
	}

	void Player::AttackFunc()
	{
		Animator* animator = GetComponent<Animator>();

		if (isAttacking == false && attackCooldown >= 0.6f)
		{
			isAttacking = true;

			if (Input::GetKeyPressing(myKeyCode::Down) && !(isGrounded))
			{
				if (isLookingLeft)
					animator->PlayAnimation(L"Knight_attack_down_left");
				else
					animator->PlayAnimation(L"Knight_attack_down_right");
			}
			else if (Input::GetKeyPressing(myKeyCode::Up))
			{
				if (isLookingLeft)
					animator->PlayAnimation(L"Knight_attack_up_left");
				else
					animator->PlayAnimation(L"Knight_attack_up_right");
			}
			else
			{
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
			}
			

			attackCooldown = 0.0f;

			PlayerSlash* playerslash = InputObject::Instantiate<PlayerSlash>(myLayerType::PlayerSlash);
			playerslash->SetOwner(this);

			if (Input::GetKeyPressing(myKeyCode::Down) && !(isGrounded))
			{
				if (isLookingLeft)
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_down_left", false);
				else
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_down_right", false);

				playerslash->GetComponent<Collider>()->SetSize(Vector2(190.0f, 210.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(0.0f, 100.0f));
				playerslash->SetDownSlashTrigger(true);
			}
			else if (Input::GetKeyPressing(myKeyCode::Up))
			{
				if (isLookingLeft)
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_up_left", false);
				else
					playerslash->GetComponent<Animator>()->PlayAnimation(L"Slash_up_right", false);

				playerslash->GetComponent<Collider>()->SetSize(Vector2(170.0f, 180.0f));
				playerslash->GetComponent<Collider>()->SetOffset(Vector2(0.0f, -100.0f));
			}
			else
			{
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

			
		}
		if (animator->IsActavatedAnimationComplete())
			isAttacking = false;
	}

	void Player::SpellFunc()
	{
		playerMana -= 4;
		PlayerFireball* fireball = InputObject::Instantiate<PlayerFireball>(myLayerType::PlayerSlash);
		fireball->GetComponent<Transform>()->SetPosition(this->GetComponent<Transform>()->GetPosition());
		fireball->SetLookingLeft(this->GetLookingLeft());
	}
}