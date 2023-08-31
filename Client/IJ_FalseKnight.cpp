#include "IJ_FalseKnight.h"
#include "IJ_Time.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"

#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Rigidbody.h"
#include "IJ_Collider.h"


namespace IJ
{
	FalseKnight::FalseKnight()
		: myCurrentState(myFKState::Idle)
		, isLookingLeft(true)
		, myWaitTime(0.0f)
		, myNextPatternNum(0)
	{}
	FalseKnight::~FalseKnight()
	{}

	void FalseKnight::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"FalseKnight_atlas"
			, L"..\\Resources\\Extras\\atlas\\FalseKnight_atlas.png");

		Animator* animator = AddComponent<Animator>();
		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		Collider* collider = AddComponent<Collider>();

		animator->SetDrawOnCamera(false);
		animator->CreateAnimationInAnimator(L"FK_idle_right", image, Vector2(0.0f, 0.0f), Vector2(750.0f, 450.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_idle_left", image, Vector2(0.0f, 450.0f), Vector2(750.0f, 450.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_jump_antic_right", image, Vector2(0.0f, 900.0f), Vector2(750.0f, 400.0f), 3);
		animator->CreateAnimationInAnimator(L"FK_jump_antic_left", image, Vector2(0.0f, 1300.0f), Vector2(750.0f, 400.0f), 3);
		animator->CreateAnimationInAnimator(L"FK_jump_right", image, Vector2(0.0f, 1700.0f), Vector2(750.0f, 400.0f), 4);
		animator->CreateAnimationInAnimator(L"FK_jump_left", image, Vector2(3600.0f, 1700.0f), Vector2(750.0f, 400.0f), 4);
		animator->CreateAnimationInAnimator(L"FK_land_right", image, Vector2(0.0f, 900.0f), Vector2(750.0f, 400.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_land_left", image, Vector2(0.0f, 1300.0f), Vector2(750.0f, 400.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_jump_attack_right", image, Vector2(0.0f, 2100.0f), Vector2(1080.0f, 500.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_jump_attack_left", image, Vector2(0.0f, 2600.0f), Vector2(1080.0f, 500.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_jump_attack_crash_right", image, Vector2(0.0f, 3100.0f), Vector2(900.0f, 620.0f), 6);
		animator->CreateAnimationInAnimator(L"FK_jump_attack_crash_left", image, Vector2(0.0f, 3720.0f), Vector2(900.0f, 620.0f), 6);
		animator->CreateAnimationInAnimator(L"FK_attack_antic_right", image, Vector2(0.0f, 4340.0f), Vector2(900.0f, 420.0f), 4);
		animator->CreateAnimationInAnimator(L"FK_attack_antic_left", image, Vector2(3600.0f, 4340.0f), Vector2(900.0f, 420.0f), 4);
		animator->CreateAnimationInAnimator(L"FK_attack_right", image, Vector2(0.0f, 4760.0f), Vector2(900.0f, 600.0f), 8);
		animator->CreateAnimationInAnimator(L"FK_attack_left", image, Vector2(0.0f, 5360.0f), Vector2(900.0f, 600.0f), 8);
		animator->CreateAnimationInAnimator(L"FK_rage", image, Vector2(0.0f, 5960.0f), Vector2(900.0f, 600.0f), 8);

		animator->PlayAnimation(L"FK_idle_left", true);

		collider->SetSize(Vector2(250.0f, 300.0f)); // 哭率场240 坷弗率场 1610
		collider->SetOffset(Vector2(0.0f, 55.0f));
	}
	void FalseKnight::Update()
	{
		GameObject::Update();

		switch (myCurrentState)
		{
		case IJ::FalseKnight::myFKState::Idle:
			Idle();
			break;
		case IJ::FalseKnight::myFKState::Jump_Antic:
			Jump_Antic();
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

	}
	void FalseKnight::OnCollisionExit(Collider* other)
	{}

	void FalseKnight::Idle()
	{
		myWaitTime += Time::DeltaTime();

		if (myWaitTime >= 3.0f)
		{
			if (myNextPatternNum == 0)
			{
				myCurrentState = FalseKnight::myFKState::Jump_Antic;
			}
		}
	}

	void FalseKnight::Jump_Antic()
	{

	}
}