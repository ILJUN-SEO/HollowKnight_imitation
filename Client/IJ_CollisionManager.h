#pragma once
#include "CommonInclude.h"
#include "IJ_Collider.h"
#include "IJ_Layer.h"
//#include "IJ_Component.h"


namespace IJ
{
#define LAYER_MAX (UINT)myLayerType::END

	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};

		UINT64 id;
	};

	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static void Release();

		static void Clear();
		static void CollisionLayerCheck(myLayerType leftLayer, myLayerType rightLayer, bool value);
		static void LayerCollision(class Scene* scene, myLayerType leftLayer, myLayerType rightLayer);
		static void ColliderCollision(Collider* leftCollider, Collider* rightCollider);
		static bool Intersect(Collider* leftCollider, Collider* rightCollider);

	private:
		static std::map<UINT64, bool> myCollisionMap;
		static std::bitset<LAYER_MAX> myLayerMasks[LAYER_MAX];
	};
}
