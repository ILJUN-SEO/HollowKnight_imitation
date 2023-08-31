#pragma once
#include "IJ_Entity.h"
#include "IJ_Layer.h"
#include "IJ_Sound.h"


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

		Layer& GetLayer(myLayerType type) { return myLayers[(UINT)type]; }

		void ToggleShowCollider()
		{
			if (isShowCollider == true)
				isShowCollider = false;
			else
				isShowCollider = true;
		}
		bool GetShowCollider() { return isShowCollider; }

		void SetBGM(Sound* sound) { myBGM = sound; }
		Sound* GetBGM() { return myBGM; }

	private:
		std::vector<Layer> myLayers;

		bool isShowCollider;
		Sound* myBGM;
	};
}
