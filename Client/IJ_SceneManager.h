#pragma once
#include "IJ_Scene.h"


namespace IJ
{
	class SceneManager
	{
	public:
		SceneManager();
		virtual ~SceneManager();

		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		template <typename T>
		static T* CreateScene(const std::wstring& scenename)
		{
			T* scene = new T();
			scene->SetName(scenename);
			myScenes.insert(std::make_pair(scenename, scene));
			myActivatedScene = scene;
			scene->Initialize();

			return scene;
		}

		static Scene* LoadScene(const std::wstring& scenename);
		static Scene* GetActivatedScene() { return myActivatedScene; }

	private:
		static std::map<std::wstring, Scene*> myScenes;
		static Scene* myActivatedScene;
	};
}
