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
		slash_at->CreateAnimationInAnimator(L"Slash_left", texture, Vector2(0.0f, 0.0f), Vector2(160.0f, 112.0f), 3, Vector2(-100.0f, 0.0f) * slash_at->GetScale());
		slash_at->CreateAnimationInAnimator(L"Slash_right", texture, Vector2(0.0f, 112.0f), Vector2(160.0f, 112.0f), 3, Vector2(100.0f, 0.0f) * slash_at->GetScale());
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
			crawler->Damaged(1);
		Buzzer* buzzer = dynamic_cast<Buzzer*>(other->GetOwner());
		if (buzzer != nullptr)
			buzzer->SetBuzzerState(Buzzer::myBuzzerState::Dead);
	}

	void PlayerSlash::OnCollisionStay(Collider* other)
	{}

	void PlayerSlash::OnCollisionExit(Collider* other)
	{}
}