#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class Temp_Platform : public GameObject
	{
	public:
		Temp_Platform();
		virtual ~Temp_Platform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:

	};
}
