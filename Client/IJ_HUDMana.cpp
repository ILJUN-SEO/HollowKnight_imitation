#include "IJ_HUDMana.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_Animator.h"


namespace IJ
{
	HUDMana::HUDMana()
		: isActivated(false)
		, assignedAnimationName(L"")
	{}
	HUDMana::~HUDMana()
	{}

	void HUDMana::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"HUDMana"
			, L"..\\Resources\\Extras\\HUD\\Mana\\ManaOrb_full.png");
		Animator* animator = AddComponent<Animator>();
		animator->SetDrawOnCamera(true);
		animator->CreateAnimationInAnimator(L"Mana_01", image, Vector2(0.0f, 110.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_02", image, Vector2(0.0f, 100.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_03", image, Vector2(0.0f, 90.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_04", image, Vector2(0.0f, 80.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_05", image, Vector2(0.0f, 70.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_06", image, Vector2(0.0f, 60.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_07", image, Vector2(0.0f, 50.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_08", image, Vector2(0.0f, 40.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_09", image, Vector2(0.0f, 30.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_10", image, Vector2(0.0f, 20.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_11", image, Vector2(0.0f, 10.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_12", image, Vector2(0.0f, 0.0f), Vector2(128.0f, 10.0f), 1);
		animator->CreateAnimationInAnimator(L"Mana_Empty", image, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), 1);
	}
	void HUDMana::Update()
	{
		GameObject::Update();

		Animator* animator = GetComponent<Animator>();
		if (isActivated)
			animator->PlayAnimation(assignedAnimationName);
		else
			animator->PlayAnimation(L"Mana_Empty");
	}
	void HUDMana::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}