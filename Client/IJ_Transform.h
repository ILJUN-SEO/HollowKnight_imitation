#pragma once
#include "IJ_Component.h"

namespace IJ
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetPosition(Math::Vector2 position) { myPosition = position; }
		Math::Vector2 GetPosition() { return myPosition; }
		void SetRotation(float rotate) { myRotation = rotate; }
		float GetRotation() { return myRotation; }

	private:
		Math::Vector2 myPosition;
		float myRotation;
	};
}
