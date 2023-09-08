#include "IJ_BossScene.h"
#include "IJ_Camera.h"
#include "IJ_ObjectManager.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_Sound.h"

#include "IJ_Transform.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Animator.h"
#include "IJ_Collider.h"
#include "IJ_CollisionManager.h"
#include "IJ_Rigidbody.h"

#include "IJ_Player.h"
#include "IJ_Ground.h"
#include "IJ_Wall.h"
#include "IJ_PlayBackground.h"
#include "IJ_FalseKnight.h"


namespace IJ
{
	BossScene::BossScene()
	{}
	BossScene::~BossScene()
	{}

	void BossScene::Initialize()
	{
		// 배경 관련
		// 왼쪽벽 90 정중앙 960 오른쪽벽 1760
		PlayBackground* background = InputObject::Instantiate<PlayBackground>(myLayerType::Background);
		Texture* image = ResourceManager::Load<Texture>(L"Boss_background"
				, L"..\\Resources\\Extras\\Stage\\BossStage_light.bmp");
		background->GetComponent<Transform>()->SetPosition(Vector2(960.0f, 540.0f));
		SpriteRenderer* spriterenderer = background->AddComponent<SpriteRenderer>();
		spriterenderer->SetTexture(image);
		spriterenderer->SetDrawOnCamera(false);

		// 지형 관련
		Ground* ground = InputObject::Instantiate<Ground>(myLayerType::Terrain);
		ground->GetComponent<Transform>()->SetPosition(Vector2(960.0f, 990.0f));
		ground->AddComponent<Collider>()->SetSize(Vector2(1920.0f, 200.0f));

		Wall* wallLeft = InputObject::Instantiate<Wall>(myLayerType::Terrain);
		wallLeft->GetComponent<Transform>()->SetPosition(Vector2(-150.0f, 540.0f));
		wallLeft->AddComponent<Collider>()->SetSize(Vector2(500.0f, 1080.0f));

		Wall* wallRight = InputObject::Instantiate<Wall>(myLayerType::Terrain);
		wallRight->GetComponent<Transform>()->SetPosition(Vector2(2050.0f, 540.0f));
		wallRight->AddComponent<Collider>()->SetSize(Vector2(500.0f, 1080.0f));

		// 플레이어 관련
		Player* player = InputObject::Instantiate<Player>(myLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(Vector2(600.0f, 825.0f));
		player->SetLookingLeft(false);

		// 적 관련
		FalseKnight* falseKnight = InputObject::Instantiate<FalseKnight>(myLayerType::Enemy);
		falseKnight->GetComponent<Transform>()->SetPosition(Vector2(1200.0f, 300.0f));
		falseKnight->GetComponent<Rigidbody>()->SetGrounded(false);
		falseKnight->SetTargetPlayer(player);

		// 소리 관련
		Sound* sound = ResourceManager::Load<Sound>(L"Boss_BGM"
			, L"..\\Resources\\Sound\\BGM\\BossBattle.wav");
		sound->SetVolume(30.0f);
		ResourceManager::Load<Sound>(L"Boss_Defeat"
			, L"..\\Resources\\Sound\\BGM\\BossDefeat.wav");
		SetBGM(sound);

		// 충돌 관련
		CollisionManager::CollisionLayerCheck(myLayerType::EnemyAttack, myLayerType::Terrain, true);


		Camera::SetTarget(player);
	}
	void BossScene::Update()
	{
		Scene::Update();
	}
	void BossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}