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
		EnemyAttack,
		Player,
		PlayerSlash,
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
		std::vector<GameObject*>& GetGameObjects() { return myGameObjects; }

	private:
		std::vector<GameObject*> myGameObjects;
	};
}
