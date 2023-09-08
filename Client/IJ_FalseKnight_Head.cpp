#include "IJ_FalseKnight_Head.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"

#include "IJ_Transform.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"

#include "IJ_ObjectManager.h"
#include "IJ_Splat.h"


namespace IJ
{
	FalseKnight_Head::FalseKnight_Head()
		: myOwner(nullptr)
		, myCurrentState(FalseKnight_Head::myFKHeadState::Armored)
		, isLookingLeft(true)
	{}
	FalseKnight_Head::~FalseKnight_Head()
	{}

	void FalseKnight_Head::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"FK_Head"
			, L"..\\Resources\\Extras\\atlas\\FalseKnight_head_atlas.png");

		Animator* animator = AddComponent<Animator>();
		Collider* collider = AddComponent<Collider>();
		Rigidbody* rigidbody = AddComponent<Rigidbody>();

		animator->CreateAnimationInAnimator(L"FK_head_idle_right", image, Vector2(0.0f, 0.0f), Vector2(150.0f, 150.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_head_idle_left", image, Vector2(0.0f, 150.0f), Vector2(150.0f, 150.0f), 5);
		animator->CreateAnimationInAnimator(L"FK_head_hit_right", image, Vector2(1000.0f, 0.0f), Vector2(150.0f, 150.0f), 3);
		animator->CreateAnimationInAnimator(L"FK_head_hit_left", image, Vector2(1000.0f, 150.0f), Vector2(150.0f, 150.0f), 3);
		animator->CreateAnimationInAnimator(L"FK_head_dead_right", image, Vector2(0.0f, 300.0f), Vector2(350.0f, 300.0f), 14, Vector2(0.0f, -20.0f));
		animator->CreateAnimationInAnimator(L"FK_head_dead_left", image, Vector2(0.0f, 600.0f), Vector2(350.0f, 300.0f), 14, Vector2(0.0f, -20.0f));
		animator->CreateAnimationInAnimator(L"FK_head_armored", image, Vector2(2000.0f, 0.0f), Vector2(0.0f, 0.0f), 1);
		animator->PlayAnimation(L"FK_head_armored");

		collider->SetSize(Vector2(150.0f, 150.0f));

		rigidbody->SetEnableGravity(false);
		rigidbody->SetGrounded(true);
	}
	void FalseKnight_Head::Update()
	{
		GameObject::Update();

		if (myCurrentState != FalseKnight_Head::myFKHeadState::Dead && myCurrentState != FalseKnight_Head::myFKHeadState::Dying)
		{
			Vector2 position = myOwner->GetComponent<Transform>()->GetPosition();
			if (myOwner->GetLookingLeft())
				position.x -= 135.0f;
			else
				position.x += 135.0f;
			position.y += 120.0f;
			GetComponent<Transform>()->SetPosition(position);
		}

		switch (myCurrentState)
		{
		case IJ::FalseKnight_Head::myFKHeadState::Armored:
			Armored();
			break;
		case IJ::FalseKnight_Head::myFKHeadState::Idle:
			Idle();
			break;
		case IJ::FalseKnight_Head::myFKHeadState::Hit:
			Hit();
			break;
		case IJ::FalseKnight_Head::myFKHeadState::Dying:
			Dying();
			break;
		case IJ::FalseKnight_Head::myFKHeadState::Dead:
			Dead();
			break;
		case IJ::FalseKnight_Head::myFKHeadState::END:
			break;
		default:
			break;
		}
	}
	void FalseKnight_Head::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void FalseKnight_Head::OnCollisionEnter(Collider* other)
	{}
	void FalseKnight_Head::OnCollisionStay(Collider* other)
	{}
	void FalseKnight_Head::OnCollisionExit(Collider* other)
	{}

	void FalseKnight_Head::Armored()
	{
		Animator* animator = GetComponent<Animator>();
		Collider* collider = GetComponent<Collider>();

		if (myOwner->GetFKState() == FalseKnight::myFKState::Stun_Hit)
		{
			myCurrentState = myFKHeadState::Idle;

			if (myOwner->GetLookingLeft())
				isLookingLeft = true;
			else
				isLookingLeft = false;

			if (isLookingLeft)
			{
				//collider->SetOffset(Vector2(-130.0f, 130.0f));
				animator->PlayAnimation(L"FK_head_idle_left");
			}
			else
			{
				//collider->SetOffset(Vector2(130.0f, 130.0f));
				animator->PlayAnimation(L"FK_head_idle_right");
			}
		}
	}
	void FalseKnight_Head::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		if (myOwner->GetFKState() == FalseKnight::myFKState::Stun_Recover)
		{
			myCurrentState = myFKHeadState::Armored;
			animator->PlayAnimation(L"FK_head_armored");
		}
	}
	void FalseKnight_Head::Hit()
	{
		Animator* animator = GetComponent<Animator>();

		if (animator->IsActavatedAnimationComplete())
		{
			myCurrentState = myFKHeadState::Idle;
			if (isLookingLeft)
				animator->PlayAnimation(L"FK_head_idle_left");
			else
				animator->PlayAnimation(L"FK_head_idle_right");
		}

		if (myOwner->GetFKState() == FalseKnight::myFKState::Stun_Recover)
		{
			myCurrentState = myFKHeadState::Armored;
			animator->PlayAnimation(L"FK_head_armored");
		}
	}
	void FalseKnight_Head::Dying()
	{
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rigidbody = GetComponent<Rigidbody>();

		if (myOwner->GetFKState() == FalseKnight::myFKState::Dead)
		{
			myCurrentState = myFKHeadState::Dead;
			animator->SetScale(Vector2(0.7f, 0.7f));

			Splat* splat = InputObject::Instantiate<Splat>(myLayerType::Effect);
			splat->GetComponent<Transform>()->SetPosition(GetComponent<Transform>()->GetPosition());

			if (isLookingLeft)
			{
				animator->PlayAnimation(L"FK_head_dead_left");
				rigidbody->SetVelocity(Vector2(-600.0f, 0.0f));
			}
			else
			{
				animator->PlayAnimation(L"FK_head_dead_right");
				rigidbody->SetVelocity(Vector2(600.0f, 0.0f));
			}
		}
	}
	void FalseKnight_Head::Dead()
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();

		Vector2 velocity = rigidbody->GetVelocity();
		if (velocity.x <= -10.0f)
			velocity.x += 10.0f;
		else if (10.0f <= velocity.x)
			velocity.x -= 10.f;
		else
			velocity.x = 0.0f;
		rigidbody->SetVelocity(velocity);
	}
}