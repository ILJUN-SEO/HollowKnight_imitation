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

		TitleScene_Background* ts_bg = InputObject::Instantiate<TitleScene_Background>(myLayerType::Background);
		SpriteRenderer* ts_bg_sr = ts_bg->AddComponent<SpriteRenderer>();
		ts_bg_sr->SetTexture(texture);
		ts_bg_sr->SetScale(Math::Vector2(1.0f, 1.0f));
		ts_bg_sr->MakeFollowCamera(false);
		ts_bg->GetComponent<Transform>()->SetPosition(Math::Vector2(800.0f, 450.0f));

		texture = ResourceManager::Load<Texture>(L"TitleScene_Title"
						, L"..\\Resources\\Extras\\TitleScene\\TitleLogo\\TitleScene_Title.png");
		
		TitleScene_Title* ts_t = InputObject::Instantiate<TitleScene_Title>(myLayerType::UI);
		SpriteRenderer* ts_t_sr = ts_t->AddComponent<SpriteRenderer>();
		ts_t_sr->SetTexture(texture);
		ts_t_sr->SetScale(Math::Vector2(0.5f, 0.5f));
		ts_t_sr->MakeFollowCamera(false);
		ts_t->GetComponent<Transform>()->SetPosition(Math::Vector2(800.0f, 250.0f));

		//Camera::SetTarget(ts_bg);
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