#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class PlayerSlash : public GameObject
	{
	public:
		PlayerSlash();
		~PlayerSlash();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetOwner(GameObject* owner) { myOwner = owner; }

	private:
		GameObject* myOwner;
		float myDeathTime;
	};
}
