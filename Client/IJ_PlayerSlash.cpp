#include "IJ_PlayerSlash.h"
#include "IJ_Player.h"
#include "IJ_Time.h"
#include "IJ_SceneManager.h"

#include "IJ_GameObject.h"
#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"

#include "IJ_ObjectManager.h"
#include "IJ_Crawler.h"
#include "IJ_Buzzer.h"
#include "IJ_FalseKnight.h"
#include "IJ_FalseKnight_Head.h"

#include "IJ_SwordStrike.h"


namespace IJ
{
	using namespace Math;

	PlayerSlash::PlayerSlash()
		: myPlayer(nullptr)
		, myDeathTime(0.5f)
		, downSlashTrigger(false)
		, alreadyHit(false)
	{}

	PlayerSlash::~PlayerSlash()
	{}

	void PlayerSlash::Initialize()
	{
		Texture* texture = ResourceManager::Load<Texture>(L"SlashEffect"
			, L"..\\Resources\\Extras\\atlas\\SlashEffect.png");
		Transform* slash_tr = GetComponent<Transform>();
		Animator* slash_at = AddComponent<Animator>();
		slash_at->CreateAnimationInAnimator(L"Slash_left", texture, Vector2(0.0f, 0.0f), Vector2(320.0f, 140.0f), 3, Vector2(-50.0f, -20.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_right", texture, Vector2(0.0f, 140.0f), Vector2(320.0f, 140.0f), 3, Vector2(50.0f, -20.0f));
		//slash_at->CreateAnimationInAnimator(L"Slash_alt_left", texture, Vector2(0.0f, 280.0f), Vector2(320.0f, 140.0f), 3, Vector2(-50.0f, 0.0f));
		//slash_at->CreateAnimationInAnimator(L"Slash_alt_right", texture, Vector2(0.0f, 420.0f), Vector2(320.0f, 140.0f), 3, Vector2(50.0f, 0.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_up_left", texture, Vector2(0.0f, 560.0f), Vector2(169.0f, 192.0f), 3, Vector2(0.0f, -100.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_up_right", texture, Vector2(0.0f, 752.0f), Vector2(169.0f, 192.0f), 3, Vector2(0.0f, -100.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_down_left", texture, Vector2(0.0f, 944.0f), Vector2(182.0f, 209.0f), 3, Vector2(0.0f, 100.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_down_right", texture, Vector2(0.0f, 1153.0f), Vector2(182.0f, 209.0f), 3, Vector2(0.0f, 100.0f));
		Collider* slash_col = AddComponent<Collider>();

		Sound* sound = ResourceManager::Load<Sound>(L"Sword_swing", L"..\\Resources\\Sound\\player\\sword_1.wav");
		sound->SetVolume(20.0f);
		sound->Play(false);
		ResourceManager::Load<Sound>(L"Sword_hit", L"..\\Resources\\Sound\\enemy_damage.wav");
		ResourceManager::Load<Sound>(L"Boss_hit", L"..\\Resources\\Sound\\falseknight\\false_knight_damage_armour.wav");
		ResourceManager::Load<Sound>(L"Boss_stun", L"..\\Resources\\Sound\\falseknight\\boss_stun.wav");
		ResourceManager::Load<Sound>(L"Boss_head_hit", L"..\\Resources\\Sound\\falseknight\\Fknight_hit_01.wav");
		ResourceManager::Load<Sound>(L"Boss_dying", L"..\\Resources\\Sound\\falseknight\\FKnight_death.wav");
	}

	void PlayerSlash::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(myPlayer->GetComponent<Transform>()->GetPosition());

		myDeathTime -= Time::DeltaTime();
		if (myDeathTime < 0.0f || GetComponent<Animator>()->IsActavatedAnimationComplete())
		{
			Destroy(this);
		}
	}

	void PlayerSlash::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerSlash::OnCollisionEnter(Collider* other)
	{
		Sound* sound = ResourceManager::Find<Sound>(L"Sword_hit");

		Crawler* crawler = dynamic_cast<Crawler*>(other->GetOwner());
		if (crawler != nullptr)
		{
			if (crawler->GetCrawlerState() != Crawler::myCrawlerState::Dead && !(alreadyHit))
			{
				alreadyHit = true;

				crawler->Damaged(1);
				if (crawler->GetCrawlerHP() <= 0)
					ResourceManager::Load<Sound>(L"Enemy_death", L"..\\Resources\\Sound\\enemy_death_sword.wav")->Play(false);
				myPlayer->ManaPlus();

				SwordStrike* swordstrike = InputObject::Instantiate<SwordStrike>(myLayerType::Effect);
				swordstrike->GetComponent<Transform>()->SetPosition(crawler->GetComponent<Transform>()->GetPosition());

				sound->Play(false);

				if (downSlashTrigger)
				{
					myPlayer->SetRecoilTime(0.0f);
					Vector2 playerpos = myPlayer->GetComponent<Transform>()->GetPosition();
					myPlayer->RecoilFunc(&playerpos);
					myPlayer->GetComponent<Transform>()->SetPosition(playerpos);
				}
			}
		}
		Buzzer* buzzer = dynamic_cast<Buzzer*>(other->GetOwner());
		if (buzzer != nullptr)
		{
			if (buzzer->GetBuzzerState() != Buzzer::myBuzzerState::Dead && !(alreadyHit))
			{
				alreadyHit = true;

				buzzer->Damaged(1);
				if (buzzer->GetBuzzerHP() <= 0)
					ResourceManager::Load<Sound>(L"Enemy_death", L"..\\Resources\\Sound\\enemy_death_sword.wav")->Play(false);
				myPlayer->ManaPlus();

				SwordStrike* swordstrike = InputObject::Instantiate<SwordStrike>(myLayerType::Effect);
				swordstrike->GetComponent<Transform>()->SetPosition(Vector2(buzzer->GetComponent<Transform>()->GetPosition()));

				sound->Play(false);

				if (downSlashTrigger)
				{
					myPlayer->SetRecoilTime(0.0f);
					Vector2 playerpos = myPlayer->GetComponent<Transform>()->GetPosition();
					myPlayer->RecoilFunc(&playerpos);
				}
			}
		}

		FalseKnight* fk = dynamic_cast<FalseKnight*>(other->GetOwner());
		if (fk != nullptr)
		{
			Animator* fk_animator = fk->GetComponent<Animator>();
			Rigidbody* fk_rigidbody = fk->GetComponent<Rigidbody>();

			if (fk->GetFKState() != FalseKnight::myFKState::Stun_Roll
				&& fk->GetFKState() != FalseKnight::myFKState::Stun_Pop
				&& fk->GetFKState() != FalseKnight::myFKState::Stun_Hit
				&& fk->GetFKState() != FalseKnight::myFKState::Stun_Recover
				&& fk->GetFKState() != FalseKnight::myFKState::Dying
				&& fk->GetFKState() != FalseKnight::myFKState::Dead)
			{
				fk->ArmorDamaged(1);
				ResourceManager::Find<Sound>(L"Boss_hit")->Play(false);

				SwordStrike* swordstrike = InputObject::Instantiate<SwordStrike>(myLayerType::Effect);
				swordstrike->GetComponent<Transform>()->SetPosition(Vector2(fk->GetComponent<Transform>()->GetPosition()));

				if (fk->GetArmor() <= 0)
				{
					fk->SetFKState(FalseKnight::myFKState::Stun_Roll);

					ResourceManager::Find<Sound>(L"Boss_stun")->Play(false);

					if (myPlayer->GetLookingLeft())
						fk->SetLookingLeft(false);
					else
						fk->SetLookingLeft(true);

					if (fk->GetLookingLeft())
					{
						fk_animator->PlayAnimation(L"FK_stun_roll_left");
						fk_rigidbody->SetVelocity(Vector2(300.0f, 0.0f));
					}
					else
					{
						fk_animator->PlayAnimation(L"FK_stun_roll_right");
						fk_rigidbody->SetVelocity(Vector2(-300.0f, 0.0f));
					}
				}
			}
		}

		FalseKnight_Head* fkhead = dynamic_cast<FalseKnight_Head*>(other->GetOwner());
		if (fkhead != nullptr)
		{
			if (fkhead->GetFKHeadState() == FalseKnight_Head::myFKHeadState::Idle)
			{
				myPlayer->ManaPlus();
				fk = fkhead->GetOwner();
				fk->HPDamaged(1);

				SwordStrike* swordstrike = InputObject::Instantiate<SwordStrike>(myLayerType::Effect);
				swordstrike->GetComponent<Transform>()->SetPosition(Vector2(fkhead->GetComponent<Transform>()->GetPosition()));

				if (fk->GetHP() <= 0)
				{
					fk->SetFKState(FalseKnight::myFKState::Dying);
					fk->ResetWaitTime();

					SceneManager::GetActivatedScene()->GetBGM()->Stop(true);
					ResourceManager::Find<Sound>(L"Boss_dying")->Play(false);

					if (fk->GetLookingLeft())
						fk->GetComponent<Animator>()->PlayAnimation(L"FK_stun_hit_left", true);
					else
						fk->GetComponent<Animator>()->PlayAnimation(L"FK_stun_hit_right", true);

					fkhead->SetFKHeadState(FalseKnight_Head::myFKHeadState::Dying);
					if (fkhead->GetLookingLeft())
						fkhead->GetComponent<Animator>()->PlayAnimation(L"FK_head_hit_left", true);
					else
						fkhead->GetComponent<Animator>()->PlayAnimation(L"FK_head_hit_right", true);
				}
				else
				{
					fkhead->SetFKHeadState(FalseKnight_Head::myFKHeadState::Hit);
					ResourceManager::Find<Sound>(L"Boss_head_hit")->Play(false);
					if (fkhead->GetLookingLeft())
						fkhead->GetComponent<Animator>()->PlayAnimation(L"FK_head_hit_left");
					else
						fkhead->GetComponent<Animator>()->PlayAnimation(L"FK_head_hit_right");

					fk->SetFKState(FalseKnight::myFKState::Stun_Hit);
					if (fk->GetLookingLeft())
						fk->GetComponent<Animator>()->PlayAnimation(L"FK_stun_hit_left");
					else
						fk->GetComponent<Animator>()->PlayAnimation(L"FK_stun_hit_right");
				}
			}
		}
	}

	void PlayerSlash::OnCollisionStay(Collider* other)
	{}

	void PlayerSlash::OnCollisionExit(Collider* other)
	{}
}