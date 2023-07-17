#pragma once
#include "IJ_Entity.h"
#include "IJ_GameObject.h"


namespace IJ
{
	enum class myLayerType
	{
		Background,
		Terrain,
		Enemy,
		Player,
		Effect,
		UI,
		END,
	};

	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject(GameObject* gameobject) { myGameObjects.push_back(gameobject); }

	private:
		std::vector<GameObject*> myGameObjects;
	};
}
