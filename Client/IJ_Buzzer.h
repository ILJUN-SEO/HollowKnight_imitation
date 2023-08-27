#pragma once
#include "IJ_GameObject.h"

#include "IJ_Player.h"


namespace IJ
{
	class Buzzer : public GameObject
	{
	public:
		enum class myBuzzerState
		{
			Idle,
			Startle,
			Chase,
			Dead,
			END,
		};

		Buzzer();
		virtual ~Buzzer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Damaged(int damage) { buzzerHP -= damage; }

		void Idle();
		void Startle();
		void Chase();
		void Dead();

		myBuzzerState GetBuzzerState() { return myCurrentState; }
		void SetBuzzerState(myBuzzerState state) { myCurrentState = state; }
		void SetTarget(Player* player) { myTarget = player; }

	private:
		myBuzzerState myCurrentState;
		int buzzerHP;
		bool isLookingLeft;

		Player* myTarget;
	};
}
