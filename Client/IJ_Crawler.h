#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class Crawler : public GameObject
	{
	public:
		Crawler();
		virtual ~Crawler();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:

	};
}
