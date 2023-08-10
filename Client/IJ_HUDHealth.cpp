#include "IJ_HUDHealth.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_Animator.h"

namespace IJ
{
	HUDHealth::HUDHealth()
		: isActivated(true)
	{}

	HUDHealth::~HUDHealth()
	{}

	void HUDHealth::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"HUDhealth"
			, L"..\\Resources\\Extras\\atlas\\Health_atlas.png");
		Animator* at = AddComponent<Animator>();
		at->SetDrawOnCamera(true);
		at->CreateAnimationInAnimator(L"Health_On", image, Vector2(0.0f, 0.0f), Vector2(80.0f, 80.0f), 1);
		at->CreateAnimationInAnimator(L"Health_Off", image, Vector2(80.0f, 0.0f), Vector2(80.0f, 80.0f), 1);
	}

	void HUDHealth::Update()
	{
		GameObject::Update();

		Animator* at = GetComponent<Animator>();
		if (isActivated)
			at->PlayAnimation(L"Health_On");
		else
			at->PlayAnimation(L"Health_Off");
	}

	void HUDHealth::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}