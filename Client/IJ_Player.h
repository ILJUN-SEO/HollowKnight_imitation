#pragma once
#include "IJ_GameObject.h"


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
			Spell,
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
		void Spell();
		void Death();

	private:
		myPlayerState myCurrentState;
		bool isLookingLeft;
		bool isGrounded;
		float jumpPressingTime;
		bool isAttacking;

		UINT playerHealth;
		UINT playerMana;
	};
}
