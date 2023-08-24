#include "IJ_HUDFrame.h"
#include "IJ_Transform.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_SpriteRenderer.h"


namespace IJ
{
	HUDFrame::HUDFrame()
	{}
	HUDFrame::~HUDFrame()
	{}

	void HUDFrame::Initialize()
	{
		Transform* transform = GetComponent<Transform>();
		transform->SetPosition(Vector2(150.0f, 100.0f));

		Texture* image = ResourceManager::Load<Texture>(L"HUDFrame"
			, L"..\\Resources\\Extras\\HUD\\HUDFrame.png");
		SpriteRenderer* spriterenderer = AddComponent<SpriteRenderer>();

		spriterenderer->SetTexture(image);
		spriterenderer->SetDrawOnCamera(true);
	}
	void HUDFrame::Update()
	{
		GameObject::Update();
	}

	void HUDFrame::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}