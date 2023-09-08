#pragma once
#include "IJ_GameObject.h"
#include "IJ_Player.h"


namespace IJ
{
	class FalseKnight : public GameObject
	{
	public:
		enum class myFKState
		{
			Idle,
			Jump_Antic,
			Jump,
			Land,
			Jump_Attack,
			Jump_Attack_Crash,
			Attack_Antic,
			Attack,
			Stun_Roll,
			Stun_Pop,
			Stun_Hit,
			Stun_Recover,
			Dying,
			Dead,
			END,
		};

		FalseKnight();
		virtual ~FalseKnight();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void AdjustDirection();
		void ArmorDamaged(int damage) { myArmor -= damage; }
		int GetArmor() { return myArmor; }
		void HPDamaged(int damage) { myHP -= damage; }
		int GetHP() { return myHP; }

		void Idle();
		void Jump_Antic();
		void Jump();
		void Land();
		void Jump_Attack();
		void Jump_Attack_Crash();
		void Attack_Antic();
		void Attack();
		void Stun_Roll();
		void Stun_Pop();
		void Stun_Hit();
		void Stun_Recover();
		void Dying();
		void Dead();

		void SetFKState(myFKState state) { myCurrentState = state; }
		myFKState GetFKState() { return myCurrentState; }
		void SetLookingLeft(bool value) { isLookingLeft = value; }
		bool GetLookingLeft() { return isLookingLeft; }
		void SetTargetPlayer(Player* player) { myTargetPlayer = player; }
		void ResetWaitTime() { myWaitTime = 0.0f; }

	private:
		myFKState myCurrentState;
		myFKState myNextState;
		bool isLookingLeft;
		float myWaitTime;
		Math::Vector2 myTargetPosition;
		Player* myTargetPlayer;
		int myArmor;
		int myHP;
	};
}
