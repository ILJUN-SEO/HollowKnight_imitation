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
		Texture* image = ResourceManager::Load<Texture>(L"Knight"
			, L"..\\Resources\\Extras\\Knight\\Knight.png");

		Player* player = InputObject::Instantiate<Player>(myLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();

		tr->SetPosition(Vector2(400.0f, 400.0f));
		
		image = ResourceManager::Load<Texture>(L"Knight_idle"
			, L"..\\Resources\\Extras\\atlas\\knight_idle_atlas.bmp");
		Animator* at = player->AddComponent<Animator>();
		at->CreateAnimation(L"Knight_idle", image, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 9);
		at->PlayAnimation(L"Knight_idle", true);
		at->MakeFollowCamera(true);

		image = ResourceManager::Load<Texture>(L"Knight_walk"
			, L"..\\Resources\\Extras\\atlas\\knight_walk_atlas.bmp");
		at->CreateAnimation(L"Knight_walk", image, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 7);
		at->MakeFollowCamera(true);

		image = ResourceManager::Load<Texture>(L"PlayBackground"
			, L"..\\Resources\\Extras\\PlayScene\\PlayBackground.png");
		PlayBackground* playbackground = InputObject::Instantiate<PlayBackground>(myLayerType::Background);
		SpriteRenderer* playbackground_sr = playbackground->AddComponent<SpriteRenderer>();
		playbackground_sr->SetTexture(image);
		playbackground_sr->MakeFollowCamera(false);
		playbackground->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 450.0f));

		image = ResourceManager::Load<Texture>(L"Temp_Platform"
			, L"..\\Resources\\Extras\\Terrain\\temp_platform.png");
		Temp_Platform* tempplatform = InputObject::Instantiate<Temp_Platform>(myLayerType::Terrain);
		SpriteRenderer* tempplatform_sr = tempplatform->AddComponent<SpriteRenderer>();
		tempplatform_sr->SetTexture(image);
		tempplatform_sr->SetScale(Vector2::One);
		tempplatform_sr->MakeFollowCamera(true);
		tempplatform->GetComponent<Transform>()->SetPosition(Vector2(0.0f, 150.0f));

		image = ResourceManager::Load<Texture>(L"HUDFrame"
			, L"..\\Resources\\Extras\\HUD\\HUDFrame.png");
		HUDFrame* hudframe = InputObject::Instantiate<HUDFrame>(myLayerType::UI);
		SpriteRenderer* hudframe_sr = hudframe->AddComponent<SpriteRenderer>();
		hudframe_sr->SetTexture(image);
		hudframe_sr->MakeFollowCamera(false);
		hudframe->GetComponent<Transform>()->SetPosition(Vector2(150.0f, 100.0f));

		image = ResourceManager::Load<Texture>(L"HUDHealth"
			, L"..\\Resources\\Extras\\HUD\\Health_idle\\Health_idle.png");
		HUDHealth* hudhealth = InputObject::Instantiate<HUDHealth>(myLayerType::UI);
		SpriteRenderer* hudhealth_sr = hudhealth->AddComponent<SpriteRenderer>();
		hudhealth_sr->SetTexture(image);
		hudhealth_sr->MakeFollowCamera(false);
		hudhealth->GetComponent<Transform>()->SetPosition(Vector2(250.f, 100.0f));

		image = ResourceManager::Load<Texture>(L"Crawler_walk"
			, L"..\\Resources\\Extras\\atlas\\crawler_walk_atlas.bmp");
		Crawler* crawler = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		Animator* crawler_anim = crawler->AddComponent<Animator>();
		crawler_anim->CreateAnimation(L"Crawler_walk", image, Vector2(0.0f, 0.0f), Vector2(128.0f, 80.0f), 4);
		crawler_anim->PlayAnimation(L"Crawler_walk", true);
		crawler_anim->MakeFollowCamera(true);


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