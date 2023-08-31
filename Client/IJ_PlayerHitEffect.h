#pragma once
//#include "IJ_GameObject.h"
#include "IJ_Player.h"


namespace IJ
{
	class PlayerHitEffect : public GameObject
	{
	public:
		PlayerHitEffect();
		virtual ~PlayerHitEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetOwner(Player* player) { myOwner = player; }

	private:
		Player* myOwner;
	};
}
