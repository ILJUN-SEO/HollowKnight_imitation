#include "IJ_PlayerSlash.h"
#include "IJ_GameObject.h"
#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_Time.h"
#include "IJ_Texture.h"
#include "IJ_ResourceManager.h"

#include "IJ_Crawler.h"
#include "IJ_Buzzer.h"


namespace IJ
{
	using namespace Math;

	PlayerSlash::PlayerSlash()
		: myPlayer(nullptr)
		, myDeathTime(0.5f)
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
		slash_at->CreateAnimationInAnimator(L"Slash_up_left", texture, Vector2(0.0f, 444.0f), Vector2(170.0f, 180.0f), 3, Vector2(0.0f, -100.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_up_right", texture, Vector2(0.0f, 624.0f), Vector2(170.0f, 180.0f), 3, Vector2(0.0f, -100.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_down_left", texture, Vector2(0.0f, 804.0f), Vector2(190.0f, 210.0f), 3, Vector2(0.0f, 100.0f));
		slash_at->CreateAnimationInAnimator(L"Slash_down_right", texture, Vector2(0.0f, 1014.0f), Vector2(190.0f, 210.0f), 3, Vector2(0.0f, 100.0f));
		Collider* slash_col = AddComponent<Collider>();
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
		Crawler* crawler = dynamic_cast<Crawler*>(other->GetOwner());
		if (crawler != nullptr)
		{
			crawler->Damaged(1);
			myPlayer->ManaPlus();
		}
		Buzzer* buzzer = dynamic_cast<Buzzer*>(other->GetOwner());
		if (buzzer != nullptr)
		{
			buzzer->SetBuzzerState(Buzzer::myBuzzerState::Dead);
			myPlayer->ManaPlus();
		}
	}

	void PlayerSlash::OnCollisionStay(Collider* other)
	{}

	void PlayerSlash::OnCollisionExit(Collider* other)
	{}
}