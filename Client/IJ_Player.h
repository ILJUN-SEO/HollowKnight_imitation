#pragma once
#include "IJ_GameObject.h"
#include "IJ_HUDHealth.h"
#include "IJ_HUDMana.h"


namespace IJ
{
	class Player : public GameObject
	{
	public:
		enum class myPlayerState
		{
			Idle,
			Move,
			Jump,
			Fall,
			Falling,
			Dash,
			Attack,
			JumpAttack,
			FallAttack,
			Focus,
			FocusGet,
			Spell,
			Damaged,
			Death,
			END
		};
		
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetState(myPlayerState state) { myCurrentState = state; }
		myPlayerState GetState() { return myCurrentState; }
		void SetLookingLeft(bool value) { isLookingLeft = value; }
		bool GetLookingLeft() { return isLookingLeft; }
		void SetPlayerGrounded(bool value) { isGrounded = value; }
		bool GetPlayerGrounded() { return isGrounded; }
		bool GetPlayerInvincible()	{ return damageInvincibleTime <= 2.0f; }

		void Idle();
		void Move();
		void Jump();
		void Fall();
		void Falling();
		void Dash();
		void Attack();
		void JumpAttack();
		void FallAttack();
		void Focus();
		void FocusGet();
		void Spell();
		void Damaged();
		void Death();

		void MoveFunc(Math::Vector2* pos);
		void JumpFunc(Math::Vector2* pos);
		void FallFunc(Math::Vector2* pos);
		bool RecoilFunc(Math::Vector2* pos);
		void AttackFunc();
		void SpellFunc();

		void ManaPlus() { playerMana++; }
		void HealthPlus() { playerHealth++; }
		void SetRecoilTime(float recoil) { recoilTime = recoil; }

	private:
		myPlayerState myCurrentState;
		int playerMaxHealth;
		int playerHealth;
		int playerMaxMana;
		int playerMana;
		std::vector<HUDHealth*> myHealth;
		std::vector<HUDMana*> myMana;

		bool isLookingLeft;
		bool isGrounded;

		float jumpPressingTime;
		float damageStunTime;
		float damageInvincibleTime;
		bool isAttacking;
		float attackCooldown;
		bool altSlashTrigger;
		float focusTime;
		float recoilTime;
	};
}
