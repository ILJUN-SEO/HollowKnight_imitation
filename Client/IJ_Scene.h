#pragma once
#include "IJ_Entity.h"
#include "IJ_Layer.h"


namespace IJ
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddGameObject(myLayerType type, GameObject* gameobject) 
		{ myLayers[(int)type].AddGameObject(gameobject); }

	private:
		std::vector<Layer> myLayers;
	};
}
