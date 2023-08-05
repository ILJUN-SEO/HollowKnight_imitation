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
#include "IJ_Rigidbody.h"

#include "IJ_Player.h"
#include "IJ_PlayerSlash.h"
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
			, L"..\\Resources\\Extras\\atlas\\knight_atlas_test.png");
		Player* player = InputObject::Instantiate<Player>(myLayerType::Player);
		Transform* tr = player->GetComponent<Transform>();
		Rigidbody* rb = player->GetComponent<Rigidbody>();
		Collider* col = player->GetComponent<Collider>();
		Animator* at = player->GetComponent<Animator>();

		tr->SetPosition(Vector2(800.0f, 600.0f));

		/*at->CreateAnimationInAnimator(L"Knight_idle_left", image, Vector2(0.0f, 0.0f), Vector2(64.0f, 128.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_idle_right", image, Vector2(0.0f, 128.0f), Vector2(64.0f, 128.0f), 9);
		at->CreateAnimationInAnimator(L"Knight_walk_left", image, Vector2(0.0f, 256.0f), Vector2(64.0f, 128.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_walk_right", image, Vector2(0.0f, 384.0f), Vector2(64.0f, 128.0f), 7);
		at->CreateAnimationInAnimator(L"Knight_jump_left", image, Vector2(0.0f, 512.0f), Vector2(96.0f, 136.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_jump_right", image, Vector2(0.0f, 646.0f), Vector2(96.0f, 136.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_left", image, Vector2(0.0f, 784.0f), Vector2(96.0f, 144.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_fall_right", image, Vector2(0.0f, 928.0f), Vector2(96.0f, 144.0f), 6);
		at->CreateAnimationInAnimator(L"Knight_falling_left", image, Vector2(288.0f, 784.0f), Vector2(96.0f, 144.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_falling_right", image, Vector2(288.0f, 928.0f), Vector2(96.0f, 144.0f), 3);
		at->CreateAnimationInAnimator(L"Knight_attack_left", image, Vector2(0.0f, 1072.0f), Vector2(128.0f, 128.0f), 5);
		at->CreateAnimationInAnimator(L"Knight_attack_right", image, Vector2(0.0f, 1200.0f), Vector2(128.0f, 128.0f), 5);*/

		//col->SetSize(Vector2(64.0f, 128.0f));

		//image = ResourceManager::Load<Texture>(L"SlashEffect"
		//	, L"..\\Resources\\Extras\\atlas\\SlashEffect.png");
		//PlayerSlash* slash = InputObject::Instantiate<PlayerSlash>(myLayerType::Player);
		//at = slash->GetComponent<Animator>();
		//at->CreateAnimationInAnimator(L"Slash_left", image, Vector2(0.0f, 0.0f), Vector2(160.0f, 112.0f), 5, Vector2(-100.0f, 0.0f));
		//at->CreateAnimationInAnimator(L"Slash_right", image, Vector2(0.0f, 112.0f), Vector2(160.0f, 112.0f), 5, Vector2(100.0f, 0.0f));

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
		tempplatform->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 500.0f));
		col = tempplatform->AddComponent<Collider>();
		col->SetSize(Vector2(93.0f, 59.0f));

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
		CollisionManager::CollisionLayerCheck(myLayerType::Enemy, myLayerType::Terrain, true);
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