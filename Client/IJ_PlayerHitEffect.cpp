#include "IJ_PlayerHitEffect.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"

#include "IJ_Transform.h"
#include "IJ_Animator.h"


namespace IJ
{
	PlayerHitEffect::PlayerHitEffect()
		: myOwner(nullptr)
	{}
	PlayerHitEffect::~PlayerHitEffect()
	{}

	void PlayerHitEffect::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"PlayerHit_atlas"
				, L"..\\Resources\\Extras\\atlas\\PlayerHit_atlas.png");

		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimationInAnimator(L"PlayerHit_effect", image, Vector2(0.0f, 0.0f), Vector2(150.0f, 80.0f), 5);
		animator->SetScale(Vector2(2.5f, 2.5f));
		animator->PlayAnimation(L"PlayerHit_effect");
	}
	void PlayerHitEffect::Update()
	{
		GameObject::Update();

		Transform* transform = GetComponent<Transform>();
		Vector2 position = transform->GetPosition();

		position = myOwner->GetComponent<Transform>()->GetPosition();
		transform->SetPosition(position);

		if (GetComponent<Animator>()->IsActavatedAnimationComplete())
			Destroy(this);
	}
	void PlayerHitEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerHitEffect::OnCollisionEnter(Collider* other)
	{}
	void PlayerHitEffect::OnCollisionStay(Collider* other)
	{}
	void PlayerHitEffect::OnCollisionExit(Collider* other)
	{}
}