#include "IJ_Layer.h"


namespace IJ
{
	Layer::Layer()
	{}

	Layer::~Layer()
	{}

	void Layer::Initialize()
	{}

	void Layer::Update()
	{
		for (GameObject* gameobject : myGameObjects)
		{
			gameobject->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* gameobject : myGameObjects)
		{
			gameobject->Render(hdc);
		}
	}
}