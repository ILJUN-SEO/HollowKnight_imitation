#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class Splat : public GameObject
	{
	public:
		Splat();
		virtual ~Splat();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:

	};
}
