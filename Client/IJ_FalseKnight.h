#pragma once
#include "IJ_GameObject.h"


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

		void Idle();
		void Jump_Antic();
		void Jump();

		void AdjustDirection();

	private:
		myFKState myCurrentState;
		bool isLookingLeft;
		float myWaitTime;
		int myNextPatternNum;
		Vector2 myTargetPosition;
	};
}
