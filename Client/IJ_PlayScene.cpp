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
#include "IJ_Buzzer.h"


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
		player->SetLookingLeft(false);
		player->SetState(Player::myPlayerState::Fall);


		// 배경 관련
		image = ResourceManager::Load<Texture>(L"KingsPassStage"
			, L"..\\Resources\\Extras\\Stage\\Kingspass_Edited_big_tblt.bmp");
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

		Ground* gr10 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr10->GetComponent<Transform>()->SetPosition(Vector2(4675.0f, 3170.0f));
		col = gr10->AddComponent<Collider>();
		col->SetSize(Vector2(230.0f, 120.0f));

		Ground* gr11 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr11->GetComponent<Transform>()->SetPosition(Vector2(4470.0f, 3060.0f));
		col = gr11->AddComponent<Collider>();
		col->SetSize(Vector2(160.0f, 120.0f));

		Ground* gr12 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr12->GetComponent<Transform>()->SetPosition(Vector2(4250.0f, 2925.0f));
		col = gr12->AddComponent<Collider>();
		col->SetSize(Vector2(280.0f, 200.0f));

		Ground* gr13 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr13->GetComponent<Transform>()->SetPosition(Vector2(4040.0f, 2700.0f));
		col = gr13->AddComponent<Collider>();
		col->SetSize(Vector2(120.0f, 200.0f));

		Ground* gr14 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr14->GetComponent<Transform>()->SetPosition(Vector2(3830.0f, 2520.0f));
		col = gr14->AddComponent<Collider>();
		col->SetSize(Vector2(300.0f, 200.0f));

		Ground* gr15 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr15->GetComponent<Transform>()->SetPosition(Vector2(4690.0f, 2425.0f));
		col = gr15->AddComponent<Collider>();
		col->SetSize(Vector2(630.0f, 120.0f));

		Ground* gr16 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr16->GetComponent<Transform>()->SetPosition(Vector2(5200.0f, 2310.0f));
		col = gr16->AddComponent<Collider>();
		col->SetSize(Vector2(400.0f, 100.0f));

		Ground* gr17 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		gr17->GetComponent<Transform>()->SetPosition(Vector2(8110.0f, 2225.0f));
		col = gr17->AddComponent<Collider>();
		col->SetSize(Vector2(5400.0f, 50.0f));

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

		Ground* pf7 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf7->GetComponent<Transform>()->SetPosition(Vector2(4555.0f, 4055.0f));
		col = pf7->AddComponent<Collider>();
		col->SetSize(Vector2(160.0f, 50.0f));

		Ground* pf8 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf8->GetComponent<Transform>()->SetPosition(Vector2(4830.0f, 3865.0f));
		col = pf8->AddComponent<Collider>();
		col->SetSize(Vector2(120.0f, 100.0f));

		Ground* pf9 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf9->GetComponent<Transform>()->SetPosition(Vector2(5140.0f, 3740.0f));
		col = pf9->AddComponent<Collider>();
		col->SetSize(Vector2(120.0f, 150.0f));

		Ground* pf10 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf10->GetComponent<Transform>()->SetPosition(Vector2(5395.0f, 3510.0f));
		col = pf10->AddComponent<Collider>();
		col->SetSize(Vector2(150.0f, 50.0f));

		Ground* pf11 = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		pf11->GetComponent<Transform>()->SetPosition(Vector2(4990.0f, 3355.0f));
		col = pf11->AddComponent<Collider>();
		col->SetSize(Vector2(230.0f, 60.0f));

		// UI 관련

		// 적 관련
		Crawler* crawler1 = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		crawler1->GetComponent<Transform>()->SetPosition(Vector2(3600.0f, 5116.0f));
		Crawler* crawler2 = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		crawler2->GetComponent<Transform>()->SetPosition(Vector2(5100.0f, 5116.0f));
		Crawler* crawler3 = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		crawler3->GetComponent<Transform>()->SetPosition(Vector2(7300.0f, 5116.0f));
		Crawler* crawler4 = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		crawler4->GetComponent<Transform>()->SetPosition(Vector2(8650.0f, 5460.0f));
		Crawler* crawler5 = InputObject::Instantiate<Crawler>(myLayerType::Enemy);
		crawler5->GetComponent<Transform>()->SetPosition(Vector2(4820.0f, 2320.0f));

		Buzzer* buzzer1 = InputObject::Instantiate<Buzzer>(myLayerType::Enemy);
		buzzer1->GetComponent<Transform>()->SetPosition(Vector2(5000.0f, 3900.0f));
		Buzzer* buzzer2 = InputObject::Instantiate<Buzzer>(myLayerType::Enemy);
		buzzer2->GetComponent<Transform>()->SetPosition(Vector2(4700.0f, 2900.0f));

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