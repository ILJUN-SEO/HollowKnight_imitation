#include "IJ_Buzzer.h"
#include "IJ_Time.h"
#include "IJ_Transform.h"
#include "IJ_Rigidbody.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_ObjectManager.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"

#include "IJ_BuzzerTrigger.h"
#include "IJ_Player.h"
#include "IJ_PlayerSlash.h"


namespace IJ
{
	Buzzer::Buzzer()
		: myCurrentState(Buzzer::myBuzzerState::Idle)
		, buzzerHP(2)
		, isLookingLeft(true)
		, myTarget(nullptr)
	{}
	Buzzer::~Buzzer()
	{}

	void Buzzer::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"Buzzer"
			, L"..\\Resources\\Extras\\atlas\\buzzer_atlas.png");
		Animator* animator = AddComponent<Animator>();
		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		Collider* collider = AddComponent<Collider>();

		animator->CreateAnimationInAnimator(L"Buzzer_idle_left", image, Vector2(0.0f, 0.0f), Vector2(144.0f, 144.0f), 5);
		animator->CreateAnimationInAnimator(L"Buzzer_idle_right", image, Vector2(0.0f, 144.0f), Vector2(144.0f, 144.0f), 5);
		animator->CreateAnimationInAnimator(L"Buzzer_startle_left", image, Vector2(0.0f, 288.0f), Vector2(160.0f, 144.0f), 4);
		animator->CreateAnimationInAnimator(L"Buzzer_startle_right", image, Vector2(0.0f, 432.0f), Vector2(160.0f, 144.0f), 4);
		animator->CreateAnimationInAnimator(L"Buzzer_chase_left", image, Vector2(0.0f, 576.0f), Vector2(144.0f, 144.0f), 4);
		animator->CreateAnimationInAnimator(L"Buzzer_chase_right", image, Vector2(0.0f, 720.0f), Vector2(144.0f, 144.0f), 4);
		animator->CreateAnimationInAnimator(L"Buzzer_dead", image, Vector2(0.0f, 864.0f), Vector2(144.0f, 144.0f), 3);

		rigidbody->SetMaxVelocity(Vector2(200.0f, 200.0f));

		collider->SetSize(Vector2(80.0f, 80.0f));

		BuzzerTrigger* trigger = InputObject::Instantiate<BuzzerTrigger>(myLayerType::Enemy);
		trigger->SetOwner(this);
	}
	void Buzzer::Update()
	{
		GameObject::Update();

		switch (myCurrentState)
		{
		case IJ::Buzzer::myBuzzerState::Idle:
			Idle();
			break;
		case IJ::Buzzer::myBuzzerState::Startle:
			Startle();
			break;
		case IJ::Buzzer::myBuzzerState::Chase:
			Chase();
			break;
		case IJ::Buzzer::myBuzzerState::Dead:
			Dead();
			break;
		case IJ::Buzzer::myBuzzerState::END:
			break;
		default:
			break;
		}

		if (buzzerHP <= 0)
			myCurrentState = myBuzzerState::Dead;
	}
	void Buzzer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Buzzer::OnCollisionEnter(Collider* other)
	{}
	void Buzzer::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (myCurrentState != myBuzzerState::Dead && player->GetPlayerInvincible() == false)
				player->SetState(Player::myPlayerState::Damaged);
		}
	}
	void Buzzer::OnCollisionExit(Collider* other)
	{}

	void Buzzer::Idle()
	{
		Animator* animator = GetComponent<Animator>();

		if (isLookingLeft)
			animator->PlayAnimation(L"Buzzer_idle_left", true);
		else
			animator->PlayAnimation(L"Buzzer_idle_right", true);
	}
	void Buzzer::Startle()
	{
		Transform* transform = GetComponent<Transform>();
		Animator* animator = GetComponent<Animator>();

		if (myTarget->GetComponent<Transform>()->GetPosition().x < transform->GetPosition().x)
			animator->PlayAnimation(L"Buzzer_startle_left");
		else
			animator->PlayAnimation(L"Buzzer_startle_right");

		if (animator->IsActavatedAnimationComplete())
			myCurrentState = myBuzzerState::Chase;
	}
	void Buzzer::Chase()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Rigidbody* rb = GetComponent<Rigidbody>();
		Animator* at = GetComponent<Animator>();

		Transform* p_tr = myTarget->GetComponent<Transform>();
		Vector2 p_pos = p_tr->GetPosition();

		Vector2 vel = rb->GetVelocity();
		if (vel.x < 0)
			at->PlayAnimation(L"Buzzer_chase_left", true);
		else
			at->PlayAnimation(L"Buzzer_chase_right", true);

		Vector2 myDirection = p_pos - pos;
		myDirection.normalize();

		rb->AddForce(myDirection * 300.0f);
	}
	void Buzzer::Dead()
	{
		Animator* animator = GetComponent<Animator>();
		Rigidbody* rigidbody = GetComponent<Rigidbody>();

		animator->PlayAnimation(L"Buzzer_dead");

		rigidbody->SetEnableGravity(true);
	}
}