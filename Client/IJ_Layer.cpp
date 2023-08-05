#include "IJ_Layer.h"


namespace IJ
{
	Layer::Layer()
	{}

	Layer::~Layer()
	{
		for (GameObject* obj : myGameObjects)
		{
			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initialize()
	{}

	void Layer::Update()
	{
		for (GameObject* gameobject : myGameObjects)
		{
			if (gameobject->GetGameObjectState() == GameObject::myGameObjectState::Pause)
				continue;

			gameobject->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameobject : myGameObjects)
		{
			if (gameobject->GetGameObjectState() == GameObject::myGameObjectState::Pause)
				continue;

			gameobject->Render(hdc);
		}

		for (std::vector<GameObject*>::iterator iter = myGameObjects.begin();
			iter != myGameObjects.end();)
		{
			if ((*iter)->GetGameObjectState() == GameObject::myGameObjectState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;

				iter = myGameObjects.erase(iter);
			}
			else
				iter++;
		}
	}
}