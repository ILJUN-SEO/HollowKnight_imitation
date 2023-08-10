#include "IJ_Crawler.h"
#include "IJ_Time.h"
#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"

#include "IJ_Player.h"
#include "IJ_PlayerSlash.h"


namespace IJ
{
	Crawler::Crawler()
		: myCurrentState(Crawler::myCrawlerState::Walk)
		, turnTime(0.0f)
		, isLookingLeft(true)
		, crawlerHP(3)
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
			myCurrentState = myCrawlerState::Dead;
	}

	void Crawler::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Crawler::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		PlayerSlash* slash = dynamic_cast<PlayerSlash*>(other->GetOwner());
		if (myCurrentState != Crawler::myCrawlerState::Dead)
		{
			//if (GetComponent<Transform>()->GetPosition().x < player->GetComponent<Transform>()->GetPosition().x)
			//	player->SetLookingLeft(true);
			//else
			//	player->SetLookingLeft(false);
			player->SetState(Player::myPlayerState::Damaged);
		}
	}
	void Crawler::OnCollisionStay(Collider* other)
	{}
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
	}
}