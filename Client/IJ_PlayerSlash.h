#pragma once
#include "IJ_Player.h"


namespace IJ
{
	class PlayerSlash : public GameObject
	{
	public:
		PlayerSlash();
		virtual ~PlayerSlash();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetOwner(Player* owner) { myPlayer = owner; }
		void SetDownSlashTrigger(bool value) { downSlashTrigger = value; }
		bool GetDownSlashTrigger() { return downSlashTrigger; }

	private:
		Player* myPlayer;
		float myDeathTime;
		bool downSlashTrigger;
		bool alreadyHit;
	};
}
