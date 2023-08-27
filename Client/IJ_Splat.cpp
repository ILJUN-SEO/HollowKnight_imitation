#include "IJ_Splat.h"

#include "IJ_ResourceManager.h"
#include "IJ_Resource.h"
#include "IJ_Texture.h"

#include "IJ_Animator.h"


namespace IJ
{
	Splat::Splat()
	{}
	Splat::~Splat()
	{}

	void Splat::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"SplatEffect"
			, L"..\\Resources\\Extras\\atlas\\splat_atlas.png");
		
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimationInAnimator(L"SplatEffect", image, Vector2(0.0f, 0.0f), Vector2(309.0f, 116.0f), 6);
		animator->PlayAnimation(L"SplatEffect");
	}
	void Splat::Update()
	{
		GameObject::Update();

		Animator* animator = GetComponent<Animator>();
		if (animator->IsActavatedAnimationComplete())
			Destroy(this);
	}
	void Splat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Splat::OnCollisionEnter(Collider* other)
	{}
	void Splat::OnCollisionStay(Collider* other)
	{}
	void Splat::OnCollisionExit(Collider* other)
	{}
}