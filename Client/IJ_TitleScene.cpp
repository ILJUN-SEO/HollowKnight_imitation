#include "IJ_TitleScene.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Transform.h"
#include "IJ_Application.h"
#include "IJ_ObjectManager.h"
#include "IJ_Camera.h"

#include "IJ_TitleScene_Background.h"
#include "IJ_TitleScene_Title.h"


extern IJ::Application application;

namespace IJ
{
	TitleScene::TitleScene()
	{}

	TitleScene::~TitleScene()
	{}

	void TitleScene::Initialize()
	{

		Texture* texture = ResourceManager::Load<Texture>(L"TitleScene_Background"
						, L"..\\Resources\\Extras\\TitleScene\\TitleScene_Background.png");
		TitleScene_Background* titlescene_background = InputObject::Instantiate<TitleScene_Background>(myLayerType::Background);
		SpriteRenderer* sr = titlescene_background->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetScale(Math::Vector2(1.0f, 1.0f));
		sr->SetDrawOnCamera(true);
		titlescene_background->GetComponent<Transform>()->SetPosition(Math::Vector2(800.0f, 450.0f));

		texture = ResourceManager::Load<Texture>(L"TitleScene_Title"
						, L"..\\Resources\\Extras\\TitleScene\\TitleLogo\\TitleScene_Title.png");
		TitleScene_Title* titlescene_title = InputObject::Instantiate<TitleScene_Title>(myLayerType::UI);
		sr = titlescene_title->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetScale(Math::Vector2(0.5f, 0.5f));
		sr->SetDrawOnCamera(true);
		titlescene_title->GetComponent<Transform>()->SetPosition(Math::Vector2(800.0f, 250.0f));
	}

	void TitleScene::Update()
	{
		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}