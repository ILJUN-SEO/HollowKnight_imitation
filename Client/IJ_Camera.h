#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	using namespace Math;
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static Vector2 GetWinPosition(Vector2 pos) { return pos - myWinPosition; }

		static void SetTarget(GameObject* target) { myTarget = target; }
		static GameObject* GetTarget() { return myTarget; }

	private:
		static Vector2 myResolution;
		static Vector2 myCameraPosition;
		static Vector2 myWinPosition;
		static GameObject* myTarget;
	};
}
