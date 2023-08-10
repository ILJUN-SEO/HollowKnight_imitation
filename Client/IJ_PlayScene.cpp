#include "IJ_PlayScene.h"
#include "IJ_Camera.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_ObjectManager.h"
#include "IJ_Transform.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_CollisionManager.h"
#include "IJ_Rigidbody.h"
#include "IJ_Application.h"

#include "IJ_Player.h"
#include "IJ_PlayerSlash.h"
#include "IJ_Ground.h"
#include "IJ_Wall.h"
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

		tr->SetPosition(Vector2(2300.0f, 4500.0f));
		player->SetState(Player::myPlayerState::Fall);

		// 배경 관련
		image = ResourceManager::Load<Texture>(L"KingsPassStage"
			, L"..\\Resources\\Extras\\Stage\\Kingspass_Edited_big_tblt3.bmp");
		PlayBackground* kingspass = InputObject::Instantiate<PlayBackground>(myLayerType::Background);
		kingspass->GetComponent<Transform>()->SetPosition(Vector2(6000.0f, 3000.0f));
		SpriteRenderer* sr = kingspass->AddComponent<SpriteRenderer>();
		sr->SetTexture(image);

		// 지형 관련
		Ground* gr1 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr1->GetComponent<Transform>()->SetPosition(Vector2(3435.0f, 5260.0f));
		col = gr1->AddComponent<Collider>();
		col->SetSize(Vector2(5970.0f, 200.0f));

		Ground* gr2 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr2->GetComponent<Transform>()->SetPosition(Vector2(6550.0f, 5380.0f));
		col = gr2->AddComponent<Collider>();
		col->SetSize(Vector2(300.0f, 200.0f));

		Ground* gr3 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr3->GetComponent<Transform>()->SetPosition(Vector2(7190.0f, 5260.0f));
		col = gr3->AddComponent<Collider>();
		col->SetSize(Vector2(1000.0f, 200.0f));

		Ground* gr4 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr4->GetComponent<Transform>()->SetPosition(Vector2(7835.0f, 5490.0f));
		col = gr4->AddComponent<Collider>();
		col->SetSize(Vector2(270.0f, 200.0f));

		Ground* gr5 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr5->GetComponent<Transform>()->SetPosition(Vector2(8445.0f, 5600.0f));
		col = gr5->AddComponent<Collider>();
		col->SetSize(Vector2(950.0f, 200.0f));

		Ground* pf1 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf1->GetComponent<Transform>()->SetPosition(Vector2(8680.0f, 5285.0f));
		col = pf1->AddComponent<Collider>();
		col->SetSize(Vector2(120.0f, 100.0f));

		Ground* pf2 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf2->GetComponent<Transform>()->SetPosition(Vector2(8355.0f, 5030.0f));
		col = pf2->AddComponent<Collider>();
		col->SetSize(Vector2(110.0f, 100.0f));

		Ground* pf3 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf3->GetComponent<Transform>()->SetPosition(Vector2(8015.0f, 5145.0f));
		col = pf3->AddComponent<Collider>();
		col->SetSize(Vector2(230.0f, 50.0f));

		Ground* pf4 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf4->GetComponent<Transform>()->SetPosition(Vector2(8560.0f, 4790.0f));
		col = pf4->AddComponent<Collider>();
		col->SetSize(Vector2(140.0f, 50.0f));

		Ground* pf5 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf5->GetComponent<Transform>()->SetPosition(Vector2(8255.0f, 4535.0f));
		col = pf5->AddComponent<Collider>();
		col->SetSize(Vector2(150.0f, 50.0f));
		
		Ground* pf6 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf6->GetComponent<Transform>()->SetPosition(Vector2(7885.0f, 4615.0f));
		col = pf6->AddComponent<Collider>();
		col->SetSize(Vector2(120.0f, 100.0f));

		Ground* gr6 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr6->GetComponent<Transform>()->SetPosition(Vector2(7485.0f, 4580.0f));
		col = gr6->AddComponent<Collider>();
		col->SetSize(Vector2(260.0f, 200.0f));

		Ground* gr7 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr7->GetComponent<Transform>()->SetPosition(Vector2(7255.0f, 4355.0f));
		col = gr7->AddComponent<Collider>();
		col->SetSize(Vector2(160.0f, 200.0f));

		Ground* gr8 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr8->GetComponent<Transform>()->SetPosition(Vector2(6380.0f, 4140.0f));
		col = gr8->AddComponent<Collider>();
		col->SetSize(Vector2(1580.0f, 200.0f));

		Ground* gr9 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr9->GetComponent<Transform>()->SetPosition(Vector2(4965.0f, 4355.0f));
		col = gr9->AddComponent<Collider>();
		col->SetSize(Vector2(1230, 200.0f));

		// UI 관련
		//image = ResourceManager::Load<Texture>(L"HUDFrame"
		//	, L"..\\Resources\\Extras\\HUD\\HUDFrame.png");
		//HUDFrame* hudframe = InputObject::Instantiate<HUDFrame>(myLayerType::UI);
		//sr = hudframe->AddComponent<SpriteRenderer>();
		//sr->SetTexture(image);
		//sr->SetDrawOnCamera(true);
		//hudframe->GetComponent<Transform>()->SetPosition(Vector2(150.0f, 100.0f));

		

		// 적 관련
		Crawler* crawler1 = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		crawler1->GetComponent<Transform>()->SetPosition(Vector2(3600.0f, 5116.0f));

		Crawler* crawler2 = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		crawler2->GetComponent<Transform>()->SetPosition(Vector2(4600.0f, 5116.0f));
		

		// 충돌 관련
		CollisionManager::CollisionLayerCheck(myLayerType::Player, myLayerType::Enemy, true);
		CollisionManager::CollisionLayerCheck(myLayerType::Player, myLayerType::Terrain, true);
		CollisionManager::CollisionLayerCheck(myLayerType::PlayerSlash, myLayerType::Enemy, true);
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