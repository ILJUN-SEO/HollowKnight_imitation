#include "IJ_FalseKnight.h"
#include "IJ_Time.h"
#include "IJ_Input.h"
#include "IJ_SceneManager.h"
#include <cmath>

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_Sound.h"

#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Rigidbody.h"
#include "IJ_Collider.h"

#include "IJ_ObjectManager.h"
#include "IJ_FalseKnight_Head.h"
#include "IJ_FalseKnight_Attack.h"
#include "IJ_PlayerHitEffect.h"


namespace IJ
{
	FalseKnight::FalseKnight()
		: myCurrentState(myFKState::Jump)
		, myNextState(myFKState::Jump)
		, isLookingLeft(true)
		, myWaitTime(0.0f)
		, myTargetPosition(Vector2(0.0f, 0.0f))
		, myTargetPlayer(nullptr)
		, myArmor(2)
		, myHP(2)
	{}
	FalseKnight::~FalseKnight()
	{}

	void FalseKnight::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"FalseKnight_atlas"
			, L"..\\Resources\\Extras\\atlas\\FalseKnight_atlas.png");
		ResourceManager::Load<Sound>(L"FK_jump"
			, L"..\\Resources\\Sound\\falseknight\\false_knight_jump.wav");
		ResourceManager::Load<Sound>(L"FK_land"
			, L"..\\Resources\\Sound\\falseknight\\false_knight_land.wav");
		ResourceManager::Load<Sound>(L"FK_strike_ground"
			, L"..\\Resources\\Sound\\falseknight\\false_knight_strike_ground.wav");

		Animator* animator = AddComponent<Animator>();
		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		Collider* collider = AddComponent<Collider>();

		animator->SetDrawOnCamera(false);
		animator->CreateAnimationInAnimator(L"FK_idle_right", image, Vector2(0.0f, 0.0f), Vector2(750.0f, 450.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_idle_left", image, Vector2(0.0f, 450.0f), Vector2(750.0f, 450.0f), 5);

		animator->CreateAnimationInAnimator(L"FK_jump_antic_right", image, Vector2(0.0f, 900.0f), Vector2(750.0f, 450.0f), 3);
		animator->CreateAnimationInAnimator(L"FK_jump_antic_left", image, Vector2(0.0f, 1350.0f), Vector2(750.0f, 450.0f), 3);
		animator->CreateAnimationInAnimator(L"FK_land_right", image, Vector2(0.0f, 900.0f), Vector2(750.0f, 450.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_land_left", image, Vector2(0.0f, 1350.0f), Vector2(750.0f, 450.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_jump_right", image, Vector2(0.0f, 1800.0f), Vector2(900.0f, 400.0f), 4, Vector2(0.0f, -50.0f));
		animator->CreateAnimationInAnimator(L"FK_jump_left", image, Vector2(3600.0f, 1800.0f), Vector2(900.0f, 400.0f), 4, Vector2(0.0f, -50.0f));

		animator->CreateAnimationInAnimator(L"FK_jump_attack_right", image, Vector2(0.0f, 2200.0f), Vector2(1080.0f, 500.0f), 5, Vector2(0.0f, -50.0f));
		animator->CreateAnimationInAnimator(L"FK_jump_attack_left", image, Vector2(0.0f, 2700.0f), Vector2(1080.0f, 500.0f), 5, Vector2(0.0f, -50.0f));
		animator->CreateAnimationInAnimator(L"FK_jump_attack_crash_right", image, Vector2(900.0f, 3200.0f), Vector2(900.0f, 620.0f), 5, Vector2(0.0f, -85.0f));
		animator->CreateAnimationInAnimator(L"FK_jump_attack_crash_left", image, Vector2(900.0f, 3820.0f), Vector2(900.0f, 620.0f), 5, Vector2(0.0f, -85.0f));
		//animator->CreateAnimationInAnimator(L"FK_jump_attack_crash_right", image, Vector2(0.0f, 3100.0f), Vector2(900.0f, 620.0f), 6);
		//animator->CreateAnimationInAnimator(L"FK_jump_attack_crash_left", image, Vector2(0.0f, 3720.0f), Vector2(900.0f, 620.0f), 6);

		animator->CreateAnimationInAnimator(L"FK_attack_antic_right", image, Vector2(0.0f, 4440.0f), Vector2(900.0f, 420.0f), 4, Vector2::Zero, 0.2f);
		animator->CreateAnimationInAnimator(L"FK_attack_antic_left", image, Vector2(3600.0f, 4440.0f), Vector2(900.0f, 420.0f), 4, Vector2::Zero, 0.2f);
		animator->CreateAnimationInAnimator(L"FK_attack_right", image, Vector2(1800.0f, 4860.0f), Vector2(900.0f, 600.0f), 6, Vector2(0.0f, -75.0f));
		animator->CreateAnimationInAnimator(L"FK_attack_left", image, Vector2(1800.0f, 5460.0f), Vector2(900.0f, 600.0f), 6, Vector2(0.0f, -75.0f));

		animator->CreateAnimationInAnimator(L"FK_rage", image, Vector2(0.0f, 6060.0f), Vector2(900.0f, 600.0f), 8);

		animator->CreateAnimationInAnimator(L"FK_stun_roll_right", image, Vector2(0.0f, 6660.0f), Vector2(800.0f, 520.0f), 9, Vector2(0.0f, -35.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_roll_left", image, Vector2(0.0f, 7180.0f), Vector2(800.0f, 520.0f), 9, Vector2(0.0f, -35.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_pop_right", image, Vector2(0.0f, 7700.0f), Vector2(500.0f, 500.0f), 5, Vector2(0.0f, -25.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_pop_left", image, Vector2(2500.0f, 7700.0f), Vector2(500.0f, 500.0f), 5, Vector2(0.0f, -25.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_idle_right", image, Vector2(5000.0f, 0.0f), Vector2(500.0f, 500.0f), 1, Vector2(0.0f, -25.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_idle_left", image, Vector2(6500.0f, 0.0f), Vector2(500.0f, 500.0f), 1, Vector2(0.0f, -25.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_hit_right", image, Vector2(4000.0f, 0.0f), Vector2(500.0f, 500.0f), 3, Vector2(0.0f, -25.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_hit_left", image, Vector2(5500.0f, 0.0f), Vector2(500.0f, 500.0f), 3, Vector2(0.0f, -25.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_recover_right", image, Vector2(0.0f, 8200.0f), Vector2(800.0f, 500.0f), 6, Vector2(0.0f, -25.0f));
		animator->CreateAnimationInAnimator(L"FK_stun_recover_left", image, Vector2(0.0f, 8700.0f), Vector2(800.0f, 500.0f), 6, Vector2(0.0f, -25.0f));

		animator->PlayAnimation(L"FK_jump_left", true);

		rigidbody->SetEnableGravity(true);
		rigidbody->SetMaxVelocity(Vector2(2000.0f, 1000.0f));

		collider->SetSize(Vector2(250.0f, 250.0f)); // 哭率场240 坷弗率场 1610
		collider->SetOffset(Vector2(0.0f, 50.0f));

		myTargetPosition = GetComponent<Transform>()->GetPosition();
		myNextState = FalseKnight::myFKState::Jump;

		FalseKnight_Head* fkhead = InputObject::Instantiate<FalseKnight_Head>(myLayerType::Enemy);
		fkhead->SetOwner(this);
	}
	void FalseKnight::Update()
	{
		GameObject::Update();

		if (Input::GetKeyDown(myKeyCode::L))
			myNextState = FalseKnight::myFKState::Jump;
		if (Input::GetKeyDown(myKeyCode::K))
			myNextState = FalseKnight::myFKState::Jump_Attack;
		if (Input::GetKeyDown(myKeyCode::J))
			myNextState = FalseKnight::myFKState::Attack;

		switch (myCurrentState)
		{
		case IJ::FalseKnight::myFKState::Idle:
			Idle();
			break;
		case IJ::FalseKnight::myFKState::Jump_Antic:
			Jump_Antic();
			break;
		case IJ::FalseKnight::myFKState::Jump:
			Jump();
			break;
		case IJ::FalseKnight::myFKState::Land:
			Land();
			break;
		case IJ::FalseKnight::myFKState::Jump_Attack:
			Jump_Attack();
			break;
		case IJ::FalseKnight::myFKState::Jump_Attack_Crash:
			Jump_Attack_Crash();
			break;
		case IJ::FalseKnight::myFKState::Attack_Antic:
			Attack_Antic();
			break;
		case IJ::FalseKnight::myFKState::Attack:
			Attack();
			break;
		case IJ::FalseKnight::myFKState::Stun_Roll:
			Stun_Roll();
			break;
		case IJ::FalseKnight::myFKState::Stun_Pop:
			Stun_Pop();
			break;
		case IJ::FalseKnight::myFKState::Stun_Hit:
			Stun_Hit();
			break;
		case IJ::FalseKnight::myFKState::Stun_Recover:
			Stun_Recover();
			break;
		case IJ::FalseKnight::myFKState::Dying:
			Dying();
			break;
		case IJ::FalseKnight::myFKState::Dead:
			Dead();
			break;
		case IJ::FalseKnight::myFKState::END:
			break;
		default:
			break;
		}
	}
	void FalseKnight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseKnight::OnCollisionEnter(Collider* other)
	{}
	void FalseKnight::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (myCurrentState != FalseKnight::myFKState::Stun_Roll
				&& myCurrentState != FalseKnight::myFKState::Stun_Pop
				&& myCurrentState != FalseKnight::myFKState::Stun_Hit
				&& myCurrentState != FalseKnight::myFKState::Stun_Recover
				&& myCurrentState != FalseKnight::myFKState::Dying
				&& myCurrentState != FalseKnight::myFKState::Dead)
			{
				if (player->GetPlayerInvincible() == false)
				{
					player->SetState(Player::myPlayerState::Damaged);
					ResourceManager::Find<Sound>(L"Knight_damaged")->Play(false);

					PlayerHitEffect* playerhit = InputObject::Instantiate<PlayerHitEffect>(myLayerType::Effect);
					playerhit->SetOwner(player);
				}
			}
		}
	}
	void FalseKnight::OnCollisionExit(Collider* other)
	{}

	void FalseKnight::AdjustDirection()
	{
		if (myTargetPlayer->GetComponent<Transform>()->GetPosition().x < GetComponent<Transform>()->GetPosition().x)
			isLookingLeft = true;
		else if (GetComponent<Transform>()->GetPosition().x < myTargetPlayer->GetComponent<Transform>()->GetPosition().x)
			isLookingLeft = false;
	}

	void FalseKnight::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		myWaitTime += Time::DeltaTime();

		if (myWaitTime >= 3.0f)
		{
			AdjustDirection();
			if (myNextState == FalseKnight::myFKState::Jump)
			{
				myCurrentState = FalseKnight::myFKState::Jump_Antic;
				if (isLookingLeft)
					animator->PlayAnimation(L"FK_jump_antic_left");
				else
					animator->PlayAnimation(L"FK_jump_antic_right");
			}
			else if (myNextState == FalseKnight::myFKState::Jump_Attack)
			{
				myCurrentState = FalseKnight::myFKState::Jump_Antic;
				if (isLookingLeft)
					animator->PlayAnimation(L"FK_jump_antic_left");
				else
					animator->PlayAnimation(L"FK_jump_antic_right");
			}
			else if (myNextState == FalseKnight::myFKState::Attack)
			{
				myCurrentState = FalseKnight::myFKState::Attack_Antic;
				if (isLookingLeft)
					animator->PlayAnimation(L"FK_attack_antic_left");
				else
					animator->PlayAnimation(L"FK_attack_antic_right");
			}

			myWaitTime = 0.0f;
		}
	}

	void FalseKnight::Jump_Antic()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rigidbody = GetComponent<Rigidbody>();

		Vector2 playerpos = myTargetPlayer->GetComponent<Transform>()->GetPosition();
		float playerDistance = position.x - playerpos.x;

		if (myNextState == FalseKnight::myFKState::Jump)
		{
			if (animator->IsActavatedAnimationComplete())
			{
				if (playerDistance > 0.0f && fabs(playerDistance) <= 500.0f)
					myTargetPosition.x = position.x + 500.0f;
				else if (playerDistance < 0.0f && fabs(playerDistance) <= 500.0f)
					myTargetPosition.x = position.x - 500.0f;
				else if (fabs(playerDistance) > 500.0f)
					myTargetPosition.x = myTargetPlayer->GetComponent<Transform>()->GetPosition().x;

				myCurrentState = FalseKnight::myFKState::Jump;
				rigidbody->SetGrounded(false);
				rigidbody->SetVelocity(Vector2((myTargetPosition.x - position.x) / 2.5f, -1000.0f));

				if (isLookingLeft)
					animator->PlayAnimation(L"FK_jump_left", true);
				else
					animator->PlayAnimation(L"FK_jump_right", true);

				ResourceManager::Find<Sound>(L"FK_jump")->Play(false);
			}
		}
		else if (myNextState == FalseKnight::myFKState::Jump_Attack)
		{ 
			if (animator->IsActavatedAnimationComplete())
			{
				if (playerpos.x < position.x)
					myTargetPosition.x = playerpos.x + 300.0f;
				else
					myTargetPosition.x = playerpos.x - 300.0f;

				myCurrentState = FalseKnight::myFKState::Jump_Attack;
				rigidbody->SetGrounded(false);
				rigidbody->SetVelocity(Vector2((myTargetPosition.x - position.x) / 2.5f, -1000.0f));

				if (isLookingLeft)
					animator->PlayAnimation(L"FK_jump_attack_left");
				else
					animator->PlayAnimation(L"FK_jump_attack_right");

				ResourceManager::Find<Sound>(L"FK_jump")->Play(false);
			}
		}
	}

	void FalseKnight::Jump()
	{
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rigidbody = GetComponent<Rigidbody>();

		if (rigidbody->GetGrounded())
		{
			myCurrentState = FalseKnight::myFKState::Land;

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_land_left");
			else
				animator->PlayAnimation(L"FK_land_right");

			ResourceManager::Find<Sound>(L"FK_land")->Play(false);
		}
	}

	void FalseKnight::Land()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = FalseKnight::myFKState::Idle;
			AdjustDirection();

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_idle_left", true);
			else
				animator->PlayAnimation(L"FK_idle_right", true);
		}
	}
	void FalseKnight::Jump_Attack()
	{
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rigidbody = GetComponent<Rigidbody>();

		if (rigidbody->GetGrounded())
		{
			myCurrentState = FalseKnight::myFKState::Jump_Attack_Crash;

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_jump_attack_crash_left");
			else
				animator->PlayAnimation(L"FK_jump_attack_crash_right");

			ResourceManager::Find<Sound>(L"FK_strike_ground")->Play(false);

			FalseKnight_Attack* fkAttack = InputObject::Instantiate<FalseKnight_Attack>(myLayerType::EnemyAttack);
			fkAttack->SetOwner(this);
			fkAttack->SetAttackType(FalseKnight_Attack::myFKAttackType::Swing);
			//fkAttack->GetComponent<Collider>()->SetPosiiton(GetComponent<Transform>()->GetPosition());
			fkAttack->GetComponent<Collider>()->SetSize(Vector2(100.0f, 100.0f));
			if (isLookingLeft)
			{
				fkAttack->GetComponent<Collider>()->SetOffset(Vector2(-300.0f, 130.0f));
				fkAttack->GetComponent<Animator>()->PlayAnimation(L"Slam_left");
			}
			else
			{
				fkAttack->GetComponent<Collider>()->SetOffset(Vector2(300.0f, 130.0f));
				fkAttack->GetComponent<Animator>()->PlayAnimation(L"Slam_right");
			}
		}
	}

	void FalseKnight::Jump_Attack_Crash()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = FalseKnight::myFKState::Idle;
			AdjustDirection();

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_idle_left", true);
			else
				animator->PlayAnimation(L"FK_idle_right", true);
		}
	}

	void FalseKnight::Attack_Antic()
	{
		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = FalseKnight::myFKState::Attack;
			if (isLookingLeft)
				animator->PlayAnimation(L"FK_attack_left");
			else
				animator->PlayAnimation(L"FK_attack_right");

			ResourceManager::Find<Sound>(L"FK_strike_ground")->Play(false);

			FalseKnight_Attack* fkAttack = InputObject::Instantiate<FalseKnight_Attack>(myLayerType::EnemyAttack);
			fkAttack->SetOwner(this);
			fkAttack->SetAttackType(FalseKnight_Attack::myFKAttackType::Shockwave);
			fkAttack->GetComponent<Collider>()->SetSize(Vector2(160.0f, 100.0f));
			
			if (isLookingLeft)
			{
				fkAttack->GetComponent<Transform>()->SetPosition(Vector2(position.x - 300.f, position.y + 130.0f));
				fkAttack->SetLookingLeft(true);
				fkAttack->GetComponent<Animator>()->PlayAnimation(L"Shockwave_left");
			}
			else
			{
				fkAttack->GetComponent<Transform>()->SetPosition(Vector2(position.x + 300.f, position.y + 130.0f));
				fkAttack->SetLookingLeft(false);
				fkAttack->GetComponent<Animator>()->PlayAnimation(L"Shockwave_right");
			}
		}
	}
	void FalseKnight::Attack()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = FalseKnight::myFKState::Idle;
			AdjustDirection();

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_idle_left", true);
			else
				animator->PlayAnimation(L"FK_idle_right", true);
		}
	}

	void FalseKnight::Stun_Roll()
	{
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		
		Vector2 velocity = rigidbody->GetVelocity();
		if (velocity.x <= -50.0f)
			velocity.x += 50.0f;
		else if (50.0f <= velocity.x)
			velocity.x -= 50.f;
		else
			velocity.x = 0.0f;
		rigidbody->SetVelocity(velocity);

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = FalseKnight::myFKState::Stun_Pop;

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_stun_pop_left");
			else
				animator->PlayAnimation(L"FK_stun_pop_right");
		}
	}

	void FalseKnight::Stun_Pop()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = FalseKnight::myFKState::Stun_Hit;

			
			if (isLookingLeft)
			{
				animator->PlayAnimation(L"FK_stun_idle_left");
			}
			else
			{
				animator->PlayAnimation(L"FK_stun_idle_right");
			}
		}
	}

	void FalseKnight::Stun_Hit()
	{
		Animator* animator = GetComponent<Animator>();

		myWaitTime += Time::DeltaTime();
		if (myWaitTime > 5.0f)
		{
			myCurrentState = FalseKnight::myFKState::Stun_Recover;

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_stun_recover_left");
			else
				animator->PlayAnimation(L"FK_stun_recover_right");

			myWaitTime = 0.0f;
		}
		else
		{
			if (animator->IsActavatedAnimationComplete())
			{
				if (isLookingLeft)
					animator->PlayAnimation(L"FK_stun_idle_left");
				else
					animator->PlayAnimation(L"FK_stun_idle_right");
			}
		}
	}

	void FalseKnight::Stun_Recover()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = FalseKnight::myFKState::Idle;
			AdjustDirection();
			myArmor = 2;

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_idle_left");
			else
				animator->PlayAnimation(L"FK_idle_right");
		}
	}

	void FalseKnight::Dying()
	{
		Animator* animator = GetComponent<Animator>();

		myWaitTime += Time::DeltaTime();

		if (myWaitTime >= 5.0f)
		{
			myCurrentState = FalseKnight::myFKState::Dead;

			SceneManager::GetActivatedScene()->SetBGM(ResourceManager::Find<Sound>(L"Boss_Defeat"));
			SceneManager::GetActivatedScene()->GetBGM()->Play(false);

			if (isLookingLeft)
				animator->PlayAnimation(L"FK_stun_idle_left");
			else
				animator->PlayAnimation(L"FK_stun_idle_right");

			myWaitTime = 0.0f;
		}
	}
	void FalseKnight::Dead()
	{
	}
}