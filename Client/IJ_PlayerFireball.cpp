#include "IJ_PlayerFireball.h"

#include "IJ_ObjectManager.h"
#include "IJ_Time.h"

#include "IJ_ResourceManager.h"
#include "IJ_Resource.h"
#include "IJ_Texture.h"
#include "IJ_Sound.h"

#include "IJ_Animator.h"
#include "IJ_Transform.h"
#include "IJ_Collider.h"

#include "IJ_Ground.h"
#include "IJ_Wall.h"
#include "IJ_Crawler.h"
#include "IJ_Buzzer.h"

#include "IJ_Splat.h"


namespace IJ
{
	PlayerFireball::PlayerFireball()
		: myDeathTime(1.0f)
		, isLookingLeft(true)
	{}
	PlayerFireball::~PlayerFireball()
	{}

	void PlayerFireball::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"PlayerFireball"
			, L"..\\Resources\\Extras\\atlas\\fireball_atlas.png");
		Animator* fireball_animator = AddComponent<Animator>();
		fireball_animator->CreateAnimationInAnimator(L"Fireball_left", image, Vector2(0.0f, 110.0f), Vector2(270.0f, 110.0f), 3);
		fireball_animator->CreateAnimationInAnimator(L"Fireball_right", image, Vector2(0.0f, 0.0f), Vector2(270.0f, 110.0f), 3);

		Collider* fireball_collider = AddComponent<Collider>();
		fireball_collider->SetSize(Vector2(270.0f, 110.0f));
	}
	void PlayerFireball::Update()
	{
		GameObject::Update();

		Animator* animator = GetComponent<Animator>();
		Transform* fireball_transform = GetComponent<Transform>();
		Vector2 fb_pos = fireball_transform->GetPosition();

		if (isLookingLeft)
		{
			animator->PlayAnimation(L"Fireball_left", true);
			fb_pos.x -= 1000.0f * Time::DeltaTime();
		}
		else
		{
			animator->PlayAnimation(L"Fireball_right", true);
			fb_pos.x += 1000.0f * Time::DeltaTime();
		}
		fireball_transform->SetPosition(fb_pos);

		myDeathTime -= Time::DeltaTime();
		if (myDeathTime < 0.0f)
			Destroy(this);
	}
	void PlayerFireball::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerFireball::OnCollisionEnter(Collider* other)
	{
		Sound* sound = ResourceManager::Load<Sound>(L"Sword_hit", L"..\\Resources\\Sound\\enemy_damage.wav");

		Crawler* crawler = dynamic_cast<Crawler*>(other->GetOwner());
		if (crawler != nullptr)
		{
			if (crawler->GetCrawlerState() != Crawler::myCrawlerState::Dead)
			{
				crawler->Damaged(2);
				if (crawler->GetCrawlerHP() <= 0)
					ResourceManager::Load<Sound>(L"Enemy_death", L"..\\Resources\\Sound\\enemy_death_sword.wav")->Play(false);

				Splat* splat = InputObject::Instantiate<Splat>(myLayerType::Effect);
				splat->GetComponent<Transform>()->SetPosition(crawler->GetComponent<Transform>()->GetPosition());

				sound->Play(false);
			}
		}

		Buzzer* buzzer = dynamic_cast<Buzzer*>(other->GetOwner());
		if (buzzer != nullptr)
		{
			if (buzzer->GetBuzzerState() != Buzzer::myBuzzerState::Dead)
			{
				buzzer->Damaged(2);
				if (buzzer->GetBuzzerHP() <= 0)
					ResourceManager::Load<Sound>(L"Enemy_death", L"..\\Resources\\Sound\\enemy_death_sword.wav")->Play(false);

				Splat* splat = InputObject::Instantiate<Splat>(myLayerType::Effect);
				splat->GetComponent<Transform>()->SetPosition(buzzer->GetComponent<Transform>()->GetPosition());

				sound->Play(false);
			}
		}

		Wall* wall = dynamic_cast<Wall*>(other->GetOwner());
		if (wall != nullptr)
			Destroy(this);
	}
	void PlayerFireball::OnCollisionStay(Collider* other)
	{}
	void PlayerFireball::OnCollisionExit(Collider* other)
	{}
}