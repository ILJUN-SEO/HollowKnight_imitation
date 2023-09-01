#pragma once
#include "IJ_GameObject.h"
#include "IJ_FalseKnight.h"


namespace IJ
{
	class FalseKnight_Attack : public GameObject
	{
	public:
		enum class myFKAttackType
		{
			Swing,
			Shockwave,
			Stone,
			END,
		};

		FalseKnight_Attack();
		virtual ~FalseKnight_Attack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void PlayerDamageFunc();

		void SetOwner(FalseKnight* fk) { myOwner = fk; }
		void SetAttackType(myFKAttackType type) { myAttackType = type; }
		myFKAttackType GetAttackType() { return myAttackType; }
		void SetLookingLeft(bool value) { isLookingLeft = value; }

	private:
		FalseKnight* myOwner;
		myFKAttackType myAttackType;
		bool isLookingLeft;
		float myDeathTime;
	};
}
