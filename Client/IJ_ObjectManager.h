#pragma once
#include "IJ_Scene.h"
#include "IJ_GameObject.h"
#include "IJ_SceneManager.h"


namespace IJ::InputObject
{
	template <typename T>
	static __forceinline T* Instantiate(myLayerType type)
	{
		T* gameobject = new T();
		Scene* scene = SceneManager::GetActivatedScene();
		scene->AddGameObject(type, gameobject);
		gameobject->Initialize();

		return gameobject;
	}
}