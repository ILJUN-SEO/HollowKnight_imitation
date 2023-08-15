#pragma once
#include "IJ_GameObject.h"


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

	private:
		myBuzzerState myCurrentState;
		UINT buzzerHP;
		bool isLookingLeft;
	};
}
