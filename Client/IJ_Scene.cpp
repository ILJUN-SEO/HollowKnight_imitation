#include "IJ_Scene.h"


namespace IJ
{
	Scene::Scene()
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
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : myLayers)
		{
			layer.Render(hdc);
		}
	}
}