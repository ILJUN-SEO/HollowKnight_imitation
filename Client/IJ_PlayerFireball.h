#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class PlayerFireball : public GameObject
	{
	public:
		PlayerFireball();
		virtual ~PlayerFireball();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetLookingLeft(bool value) { isLookingLeft = value; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		float myDeathTime;
		bool isLookingLeft;
	};
}
