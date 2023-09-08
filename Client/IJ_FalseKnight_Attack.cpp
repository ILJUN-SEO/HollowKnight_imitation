#include "IJ_FalseKnight_Attack.h"
#include "IJ_FalseKnight.h"
#include "IJ_Time.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_Sound.h"

#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"

#include "IJ_ObjectManager.h"
#include "IJ_Player.h"
#include "IJ_PlayerHitEffect.h"
#include "IJ_Wall.h"


namespace IJ
{
	FalseKnight_Attack::FalseKnight_Attack()
		: myOwner(nullptr)
		, myAttackType(myFKAttackType::Swing)
		, isLookingLeft(true)
		, myDeathTime(5.0f)
	{}
	FalseKnight_Attack::~FalseKnight_Attack()
	{}

	void FalseKnight_Attack::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"FK_effect_atlas"
			, L"..\\Resources\\Extras\\atlas\\FK_Effect.png");

		Animator* animator = AddComponent<Animator>();
		Collider* collider = AddComponent<Collider>();
		Rigidbody* rigidbody = AddComponent<Rigidbody>();

		animator->CreateAnimationInAnimator(L"Slam_left", image, Vector2(0.0f, 0.0f), Vector2(750.0f, 180.0f), 6, Vector2(-300.0f, 100.0f));
		animator->CreateAnimationInAnimator(L"Slam_right", image, Vector2(0.0f, 0.0f), Vector2(750.0f, 180.0f), 6, Vector2(300.0f, 100.0f));
		animator->CreateAnimationInAnimator(L"Shockwave_right", image, Vector2(0.0f, 180.0f), Vector2(160.0f, 100.0f), 1);
		animator->CreateAnimationInAnimator(L"Shockwave_left", image, Vector2(160.0f, 180.0f), Vector2(160.0f, 100.0f), 1);
		animator->CreateAnimationInAnimator(L"Stone", image, Vector2(320.0f, 180.0f), Vector2(160.0f, 100.0f), 1);

		rigidbody->SetEnableGravity(false);
		rigidbody->SetGrounded(false);
		rigidbody->SetMaxVelocity(Vector2(1000.0f, 0.0f));
	}
	void FalseKnight_Attack::Update()
	{
		GameObject::Update();

		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();
		Animator* animator = GetComponent<Animator>();
		Collider* collider = GetComponent<Collider>();
		Rigidbody* rigidbody = GetComponent<Rigidbody>();


		if (myAttackType == myFKAttackType::Swing)
		{
			transform->SetPosition(myOwner->GetComponent<Transform>()->GetPosition());
			if (animator->IsActavatedAnimationComplete())
				Destroy(this);
		}
		else if (myAttackType == myFKAttackType::Shockwave)
		{
			myDeathTime -= Time::DeltaTime();

			if (isLookingLeft)
			{
				Vector2 shockvel = rigidbody->GetVelocity();
				shockvel.x -= 20.0f;
				rigidbody->SetVelocity(shockvel);
				//rigidbody->SetVelocity(Vector2(-500.0f, 0.0f));
			}
			else
			{
				Vector2 shockvel = rigidbody->GetVelocity();
				shockvel.x += 20.0f;
				rigidbody->SetVelocity(shockvel);
				//rigidbody->SetVelocity(Vector2(500.0f, 0.0f));
			}

			if (myDeathTime < 0.0f)
				Destroy(this);
		}
		else if (myAttackType == myFKAttackType::Stone)
		{

		}
	}
	void FalseKnight_Attack::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseKnight_Attack::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (player->GetPlayerInvincible() == false && myOwner->GetFKState() != FalseKnight::myFKState::Dead)
			{
				player->SetState(Player::myPlayerState::Damaged);
				ResourceManager::Find<Sound>(L"Knight_damaged")->Play(false);

				PlayerHitEffect* playerhit = InputObject::Instantiate<PlayerHitEffect>(myLayerType::Effect);
				playerhit->SetOwner(player);
			}
		}

		Wall* wall = dynamic_cast<Wall*>(other->GetOwner());
		if (wall != nullptr)
			Destroy(this);
	}
	void FalseKnight_Attack::OnCollisionStay(Collider* other)
	{
	}
	void FalseKnight_Attack::OnCollisionExit(Collider* other)
	{
	}

	void FalseKnight_Attack::PlayerDamageFunc()
	{
	}
}