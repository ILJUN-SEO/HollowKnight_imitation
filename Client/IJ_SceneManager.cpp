#include "IJ_SceneManager.h"
#include "IJ_Scene.h"
#include "IJ_Input.h"
#include "IJ_Camera.h"

#include "IJ_Player.h"
// 모든 씬의 헤더를 추가해주세요
#include "IJ_TitleScene.h"
#include "IJ_PlayScene.h"
#include "IJ_BossScene.h"


namespace IJ
{
	std::map<std::wstring, Scene*> SceneManager::myScenes = {};
	Scene* SceneManager::myActivatedScene = nullptr;

	SceneManager::SceneManager()
	{}

	SceneManager::~SceneManager()
	{}

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<PlayScene>(L"PlayScene");
		CreateScene<BossScene>(L"BossScene");

		LoadScene(L"TitleScene");
		//LoadScene(L"BossScene");
		//GetActivatedScene()->GetBGM()->Play(true);
	}

	void SceneManager::Update()
	{
		if (Input::GetKeyDown(myKeyCode::One))
		{
			GetActivatedScene()->GetBGM()->Stop(true);
			LoadScene(L"TitleScene");
			GetActivatedScene()->GetBGM()->Play(true);
		}
		if (Input::GetKeyDown(myKeyCode::Two))
		{
			GetActivatedScene()->GetBGM()->Stop(true);
			LoadScene(L"PlayScene");
			Player* player = dynamic_cast<Player*>(GetActivatedScene()->GetLayer(myLayerType::Player).GetGameObjects()[0]);
			Camera::SetTarget(player);
			//GetActivatedScene()->GetBGM()->Play(true);
		}
		if (Input::GetKeyDown(myKeyCode::Three))
		{
			GetActivatedScene()->GetBGM()->Stop(true);
			LoadScene(L"BossScene");
			Player* player = dynamic_cast<Player*>(GetActivatedScene()->GetLayer(myLayerType::Player).GetGameObjects()[0]);
			Camera::SetTarget(player);
			//GetActivatedScene()->GetBGM()->Play(true);
		}

		myActivatedScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		myActivatedScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (auto iter : myScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(const std::wstring& scenename)
	{
		std::map<std::wstring, Scene*>::iterator iter = myScenes.find(scenename);

		if (iter == myScenes.end())
			return nullptr;

		myActivatedScene = iter->second;

		return iter->second;
	}
}