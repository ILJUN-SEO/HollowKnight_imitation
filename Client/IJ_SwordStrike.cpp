#include "IJ_SwordStrike.h"

#include "IJ_ResourceManager.h"
#include "IJ_Resource.h"
#include "IJ_Texture.h"

#include "IJ_Animator.h"

namespace IJ
{
	SwordStrike::SwordStrike()
	{}
	SwordStrike::~SwordStrike()
	{}

	void SwordStrike::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"SwordStrikeEffect"
			, L"..\\Resources\\Extras\\atlas\\swordstrike_atlas.png");

		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimationInAnimator(L"SwordStrikeEffect", image, Vector2(0.0f, 0.0f), Vector2(219.0f, 106.0f), 3);
		animator->PlayAnimation(L"SwordStrikeEffect");
	}
	void SwordStrike::Update()
	{	
		GameObject::Update();

		Animator* animator = GetComponent<Animator>();
		if (animator->IsActavatedAnimationComplete())
			Destroy(this);
	}
	void SwordStrike::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SwordStrike::OnCollisionEnter(Collider* other)
	{}
	void SwordStrike::OnCollisionStay(Collider* other)
	{}
	void SwordStrike::OnCollisionExit(Collider* other)
	{}
}