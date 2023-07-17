#include "IJ_SceneManager.h"
#include "IJ_Input.h"
// 모든 씬의 헤더를 추가해주세요
#include "IJ_TitleScene.h"
#include "IJ_PlayScene.h"


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

		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		if (Input::GetKeyDown(myKeyCode::P))
			LoadScene(L"TitleScene");
		if (Input::GetKeyDown(myKeyCode::O))
			LoadScene(L"PlayScene");

		myActivatedScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		myActivatedScene->Render(hdc);
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