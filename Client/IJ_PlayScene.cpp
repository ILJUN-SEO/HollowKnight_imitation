#include "IJ_PlayScene.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Transform.h"
#include "IJ_Application.h"
#include "IJ_ObjectManager.h"
#include "IJ_Camera.h"
#include "IJ_Animator.h"
#include "IJ_CollisionManager.h"

#include "IJ_Player.h"
#include "IJ_Temp_Platform.h"
#include "IJ_Temp_Ground.h"
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
		// 플레이어 관련
		Texture* image = ResourceManager::Load<Texture>(L"Knight_atlas"
			, L"..\\Resources\\Extras\\atlas\\knight_atlas.png");
		Player* player = InputObject::Instantiate<Player>(myLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector2(800.0f, 600.0f));
		Animator* at = player->AddComponent<Animator>();
		at->CreateAnimationInAnimator(L"Knight_idle_left", image, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_idle_right", image, Vector2(0.0f, 128.0f), Vector2(64.0f, 128.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_walk_left", image, Vector2(0.0f, 256.0f), Vector2(64.0f, 128.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_walk_right", image, Vector2(0.0f, 384.0f), Vector2(64.0f, 128.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_jump_left", image, Vector2(0.0f, 512.0f), Vector2(96.0f, 128.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_jump_right", image, Vector2(0.0f, 640.0f), Vector2(96.0f, 128.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_left", image, Vector2(0.0f, 768.0f), Vector2(96.0f, 128.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_right", image, Vector2(0.0f, 896.0f), Vector2(96.0f, 128.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_falling_left", image, Vector2(288.0f, 768.0f), Vector2(96.0f, 128.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_falling_right", image, Vector2(288.0f, 896.0f), Vector2(96.0f, 128.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_attack_left", image, Vector2(0.0f, 1024.0f), Vector2(128.0f, 128.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_right", image, Vector2(0.0f, 1152.0f), Vector2(128.0f, 128.0f), 5);

		//at->PlayAnimation(L"Knight_idle_left", true);
		//image = ResourceManager::Load<Texture>(L"Knight_walk"
		//	, L"..\\Resources\\Extras\\atlas\\knight_walk_atlas.bmp");
		//at->CreateAnimationInAnimator(L"Knight_walk_left", image, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 7);
		//at->SetDrawOnCamera(false);
		Collider* col = player->AddComponent<Collider>();
		col->SetSize(Vector2(64.0f, 128.0f));

		// 배경 관련
		image = ResourceManager::Load<Texture>(L"PlayBackground"
			, L"..\\Resources\\Extras\\PlayScene\\PlayBackground.png");
		PlayBackground* playbackground = InputObject::Instantiate<PlayBackground>(myLayerType::Background);
		SpriteRenderer* sr = playbackground->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);
		sr->SetDrawOnCamera(true);
		playbackground->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 450.0f));

		// 지형 관련
		image = ResourceManager::Load<Texture>(L"Temp_Platform"
			, L"..\\Resources\\Extras\\Terrain\\temp_platform.png");
		Temp_Platform* tempplatform = InputObject::Instantiate<Temp_Platform>(myLayerType::Terrain);
		sr = tempplatform->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);
		sr->SetScale(Vector2::One);
		sr->SetDrawOnCamera(false);
		tempplatform->GetComponent<Transform>()->SetPosition(Vector2(400.0f, 600.0f));

		image = ResourceManager::Load<Texture>(L"Temp_Ground"
			, L"..\\Resources\\Extras\\Terrain\\temp_ground.bmp");
		Temp_Ground* tempground = InputObject::Instantiate<Temp_Ground>(myLayerType::Terrain);
		tempground->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 800.0f));
		sr = tempground->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);
		col = tempground->AddComponent<Collider>();
		col->SetSize(Vector2(2000.0f, 200.0f));

		// UI 관련
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

		// 적 관련
		image = ResourceManager::Load<Texture>(L"Crawler_walk"
			, L"..\\Resources\\Extras\\atlas\\crawler_walk_atlas.bmp");
		Crawler* crawler = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		tr = crawler->GetComponent<Transform>();
		tr->SetPosition(Vector2(200.0f, 600.0f));
		at = crawler->AddComponent<Animator>();
		at->CreateAnimationInAnimator(L"Crawler_walk", image, Vector2(0.0f, 0.0f), Vector2(128.0f, 80.0f), 4);
		at->PlayAnimation(L"Crawler_walk", true);
		at->SetDrawOnCamera(false);
		col = crawler->AddComponent<Collider>();
		col->SetSize(Vector2(128.0f, 80.f));

		CollisionManager::CollisionLayerCheck(myLayerType::Player, myLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(myLayerType::Player, myLayerType::Terrain, true);
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