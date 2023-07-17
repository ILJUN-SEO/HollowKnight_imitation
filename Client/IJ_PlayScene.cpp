#include "IJ_PlayScene.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Transform.h"
#include "IJ_Application.h"
#include "IJ_ObjectManager.h"
#include "IJ_Camera.h"
#include "IJ_Animator.h"

#include "IJ_Player.h"
#include "IJ_Temp_Platform.h"
#include "IJ_HUDFrame.h"
#include "IJ_HUDHealth.h"
#include "IJ_PlayBackground.h"
#include "IJ_Crawler.h"


extern IJ::Application application;

namespace IJ
{
	PlayScene::PlayScene()
	{}

	PlayScene::~PlayScene()
	{}

	void PlayScene::Initialize()
	{	
		Texture* image = ResourceManager::Load<Texture>(L"Knight_idle"
			, L"..\\Resources\\Extras\\atlas\\knight_idle_atlas.bmp");
		Player* player = InputObject::Instantiate<Player>(myLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector2(400.0f, 400.0f));
		Animator* at = player->AddComponent<Animator>();
		at->CreateAnimation(L"Knight_idle", image, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 9);
		at->PlayAnimation(L"Knight_idle", true);
		at->SetDrawOnCamera(false);

		image = ResourceManager::Load<Texture>(L"Knight_walk"
			, L"..\\Resources\\Extras\\atlas\\knight_walk_atlas.bmp");
		at->CreateAnimation(L"Knight_walk", image, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 7);
		at->SetDrawOnCamera(false);

		image = ResourceManager::Load<Texture>(L"PlayBackground"
			, L"..\\Resources\\Extras\\PlayScene\\PlayBackground.png");
		PlayBackground* playbackground = InputObject::Instantiate<PlayBackground>(myLayerType::Background);
		SpriteRenderer* sr = playbackground->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);
		sr->SetDrawOnCamera(true);
		playbackground->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 450.0f));

		image = ResourceManager::Load<Texture>(L"Temp_Platform"
			, L"..\\Resources\\Extras\\Terrain\\temp_platform.png");
		Temp_Platform* tempplatform = InputObject::Instantiate<Temp_Platform>(myLayerType::Terrain);
		sr = tempplatform->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);
		sr->SetScale(Vector2::One);
		sr->SetDrawOnCamera(false);
		tempplatform->GetComponent<Transform>()->SetPosition(Vector2(0.0f, 150.0f));

		image = ResourceManager::Load<Texture>(L"HUDFrame"
			, L"..\\Resources\\Extras\\HUD\\HUDFrame.png");
		HUDFrame* hudframe = InputObject::Instantiate<HUDFrame>(myLayerType::UI);
		sr = hudframe->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);
		sr->SetDrawOnCamera(true);
		hudframe->GetComponent<Transform>()->SetPosition(Vector2(150.0f, 100.0f));

		image = ResourceManager::Load<Texture>(L"HUDHealth"
			, L"..\\Resources\\Extras\\HUD\\Health_idle\\Health_idle.png");
		HUDHealth* hudhealth = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		sr = hudhealth->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);
		sr->SetDrawOnCamera(true);
		hudhealth->GetComponent<Transform>()->SetPosition(Vector2(250.f, 100.0f));

		image = ResourceManager::Load<Texture>(L"Crawler_walk"
			, L"..\\Resources\\Extras\\atlas\\crawler_walk_atlas.bmp");
		Crawler* crawler = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		tr = crawler->GetComponent<Transform>();
		tr->SetPosition(Vector2(300.0f, 300.0f));
		at = crawler->AddComponent<Animator>();
		at->CreateAnimation(L"Crawler_walk", image, Vector2(0.0f, 0.0f), Vector2(128.0f, 80.0f), 4);
		at->PlayAnimation(L"Crawler_walk", true);
		at->SetDrawOnCamera(false);


		Camera::SetTarget(player);
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}