#include "IJ_TitleScene.h" 

#include "IJ_Application.h"
#include "IJ_Camera.h"
#include "IJ_Input.h"

#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"
#include "IJ_Sound.h"

#include "IJ_Transform.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Animator.h"

#include "IJ_ObjectManager.h"

#include "IJ_TitleScene_Background.h"
#include "IJ_TitleScene_Title.h"


extern IJ::Application application;

namespace IJ
{
	TitleScene::TitleScene()
		: myMenu({})
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

		texture = ResourceManager::Load<Texture>(L"TitleScene_Start"
			, L"..\\Resources\\Extras\\TitleScene\\TitleScene_Start.png");
		TitleScene_Title* titlescene_start = InputObject::Instantiate<TitleScene_Title>(myLayerType::UI);
		Animator* animator = titlescene_start->AddComponent<Animator>();
		animator->SetDrawOnCamera(true);
		titlescene_start->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 550.0f));
		animator->CreateAnimationInAnimator(L"Title_start_white", texture, Vector2(0.0f, 0.0f), Vector2(400.0f, 200.0f), 1);
		titlescene_start->SetActiveAnim(L"Title_start_white");
		animator->CreateAnimationInAnimator(L"Title_start_grey", texture, Vector2(0.0f, 200.0f), Vector2(400.0f, 200.0f), 1);
		titlescene_start->SetNonActiveAnim(L"Title_start_grey");
		titlescene_start->SetActivated(true);
		myMenu.push_back(titlescene_start);

		texture = ResourceManager::Load<Texture>(L"TitleScene_Exit"
			, L"..\\Resources\\Extras\\TitleScene\\TitleScene_Exit.png");
		TitleScene_Title* titlescene_exit = InputObject::Instantiate<TitleScene_Title>(myLayerType::UI);
		animator = titlescene_exit->AddComponent<Animator>();
		animator->SetDrawOnCamera(true);
		titlescene_exit->GetComponent<Transform>()->SetPosition(Vector2(800.0f, 700.0f));
		animator->CreateAnimationInAnimator(L"Title_exit_white", texture, Vector2(0.0f, 0.0f), Vector2(400.0f, 200.0f), 1);
		titlescene_exit->SetActiveAnim(L"Title_exit_white");
		animator->CreateAnimationInAnimator(L"Title_exit_grey", texture, Vector2(0.0f, 200.0f), Vector2(400.0f, 200.0f), 1);
		titlescene_exit->SetNonActiveAnim(L"Title_exit_grey");
		titlescene_exit->SetActivated(false);
		myMenu.push_back(titlescene_exit);


		Sound* sound = ResourceManager::Load<Sound>(L"Title_BGM"
			, L"..\\Resources\\Sound\\BGM\\Title.wav");
		Scene::SetBGM(sound);
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(myKeyCode::Up) || Input::GetKeyDown(myKeyCode::Down))
		{
			for (GameObject* gameobjects : GetLayer(myLayerType::UI).GetGameObjects())
			{
				TitleScene_Title* title = dynamic_cast<TitleScene_Title*>(gameobjects);
				title->ToggleActivated();
			}
		}

		//if (Input::GetKeyDown(myKeyCode::A))
		//{
		//	if (myMenu[0]->GetActivated() == true)
		//	{
		//		SceneManager::GetActivatedScene()->GetBGM()->Stop(true);
		//		SceneManager::LoadScene(L"PlayScene");
		//		//GetActivatedScene()->GetBGM()->Play(true);
		//	}
		//}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}