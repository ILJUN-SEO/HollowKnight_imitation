#include "IJ_Scene.h"
#include "IJ_Input.h"


namespace IJ
{
	Scene::Scene()
		: isShowCollider(false)
		, myBGM(nullptr)
	{
		myLayers.resize((int)myLayerType::END);
	}
	Scene::~Scene()
	{}

	void Scene::Initialize()
	{}
	void Scene::Update()
	{
		for (Layer& layer : myLayers)
		{
			layer.Update();
		}

		if (Input::GetKeyDown(myKeyCode::P))
			ToggleShowCollider();
	}
	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : myLayers)
		{
			layer.Render(hdc);
		}
	}
}