#include "IJ_Crawler.h"
#include "IJ_Time.h"
#include "IJ_ObjectManager.h"

#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_Sound.h"

#include "IJ_Player.h"
#include "IJ_PlayerSlash.h"
#include "IJ_SoundTrigger.h"
#include "IJ_PlayerHitEffect.h"


namespace IJ
{
	Crawler::Crawler()
		: myCurrentState(Crawler::myCrawlerState::Walk)
		, crawlerHP(2)
		, isLookingLeft(true)
		, turnTime(0.0f)
		, myCrawlerSound(nullptr)
		, isSoundStarted(false)
		, isPlayerNearby(false)
	{}
	Crawler::~Crawler()
	{}

	void Crawler::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"Crawler"
			, L"..\\Resources\\Extras\\atlas\\crawler_atlas.png");
		Animator* animator = AddComponent<Animator>();
		Collider* collider = AddComponent<Collider>();

		animator->CreateAnimationInAnimator(L"Crawler_walk_left", image, Vector2(0.0f, 0.0f), Vector2(128.0f, 88.0f), 4);
		animator->CreateAnimationInAnimator(L"Crawler_walk_right", image, Vector2(0.0f, 88.0f), Vector2(128.0f, 88.0f), 4);
		animator->CreateAnimationInAnimator(L"Crawler_turn_left", image, Vector2(0.0f, 176.0f), Vector2(128.0f, 88.0f), 2);
		animator->CreateAnimationInAnimator(L"Crawler_turn_right", image, Vector2(0.0f, 264.0f), Vector2(128.0f, 88.0f), 2);
		animator->CreateAnimationInAnimator(L"Crawler_dead", image, Vector2(0.0f, 352.0f), Vector2(128.0f, 88.0f), 1);

		collider->SetSize(Vector2(128.0f, 80.f));

		SoundTrigger* soundtrigger = InputObject::Instantiate<SoundTrigger>(myLayerType::Enemy);
		soundtrigger->SetOwner(this);

		ResourceManager::Load<Sound>(L"Knight_damaged", L"..\\Resources\\Sound\\player\\hero_damage.wav");
	}

	void Crawler::Update()
	{
		GameObject::Update();

		switch (myCurrentState)
		{
		case IJ::Crawler::myCrawlerState::Walk:
			Walk();
			break;
		case IJ::Crawler::myCrawlerState::Turn:
			Turn();
			break;
		case IJ::Crawler::myCrawlerState::Dead:
			Dead();
			break;
		case IJ::Crawler::myCrawlerState::END:
			break;
		default:
			break;
		}

		if (crawlerHP <= 0)
		{
			myCurrentState = myCrawlerState::Dead;
		}
	}

	void Crawler::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Crawler::OnCollisionEnter(Collider* other)
	{}
	void Crawler::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (myCurrentState != Crawler::myCrawlerState::Dead && player->GetPlayerInvincible() == false)
			{
				if (GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x)
					player->SetLookingLeft(true);
				else
					player->SetLookingLeft(false);
				player->SetState(Player::myPlayerState::Damaged);
				ResourceManager::Find<Sound>(L"Knight_damaged")->Play(false);

				PlayerHitEffect* playerhit = InputObject::Instantiate<PlayerHitEffect>(myLayerType::Effect);
				//playerhit->GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());
				playerhit->SetOwner(player);
			}
		}
	}
	void Crawler::OnCollisionExit(Collider* other)
	{}

	void Crawler::Walk()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* at = GetComponent<Animator>();

		if (isLookingLeft)
		{
			at->PlayAnimation(L"Crawler_walk_left", true);
			pos.x -= 100.0f * Time::DeltaTime();
		}
		else
		{
			at->PlayAnimation(L"Crawler_walk_right", true);
			pos.x += 100.0f * Time::DeltaTime();
		}
		tr->SetPosition(pos);
		turnTime += Time::DeltaTime();

		if (turnTime >= 5.0f)
			myCurrentState = myCrawlerState::Turn;

		if (isPlayerNearby && myCurrentState != myCrawlerState::Dead)
		{
			if (isSoundStarted == false)
			{
				myCrawlerSound->Play(true);
				isSoundStarted = true;
			}
		}
		else
		{
			if (isSoundStarted == true)
			{
				myCrawlerSound->Stop(true);
				isSoundStarted = false;
			}
		}
	}

	void Crawler::Turn()
	{
		Animator* at = GetComponent<Animator>();
		turnTime = 0.0f;

		if (isLookingLeft)
			at->PlayAnimation(L"Crawler_turn_left");
		else
			at->PlayAnimation(L"Crawler_turn_right");

		if (at->IsActavatedAnimationComplete())
		{
			if (isLookingLeft)
				isLookingLeft = false;
			else
				isLookingLeft = true;

			myCurrentState = myCrawlerState::Walk;
		}
	}

	void Crawler::Dead()
	{
		Animator* at = GetComponent<Animator>();
		at->PlayAnimation(L"Crawler_dead");

		
		myCrawlerSound->Stop(true);
		isSoundStarted = false;
	}
}