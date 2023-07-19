#pragma once
#include "CommonInclude.h"
//#include "IJ_Component.h"
#include "IJ_Layer.h"


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

	private:
		static std::map<UINT64, bool> myCollisionMap;
		static std::bitset<LAYER_MAX> myLayerMasks;
	};
}
