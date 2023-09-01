#pragma once
#include "IJ_GameObject.h"
#include "IJ_FalseKnight.h"


namespace IJ
{
	class FalseKnight_Head : public GameObject
	{
	public:
		enum class myFKHeadState
		{
			Armored,
			Idle,
			Hit,
			Dying,
			Dead,
			END,
		};

		FalseKnight_Head();
		virtual ~FalseKnight_Head();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Armored();
		void Idle();
		void Hit();
		void Dying();
		void Dead();

		void SetOwner(FalseKnight* fk) { myOwner = fk; }
		FalseKnight* GetOwner() { return myOwner; }
		void SetFKHeadState(myFKHeadState state) { myCurrentState = state; }
		myFKHeadState GetFKHeadState() { return myCurrentState; }
		bool GetLookingLeft() { return isLookingLeft; }

	private:
		FalseKnight* myOwner;
		myFKHeadState myCurrentState;
		bool isLookingLeft;
	};
}
