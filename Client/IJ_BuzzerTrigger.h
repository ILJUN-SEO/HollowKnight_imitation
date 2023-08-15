#pragma once
#include "IJ_GameObject.h"

#include "IJ_Buzzer.h"

namespace IJ
{
	class BuzzerTrigger : public GameObject
	{
	public:
		BuzzerTrigger();
		virtual ~BuzzerTrigger();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetOwner(Buzzer* buzzer) { myBuzzer = buzzer; }
	private:
		Buzzer* myBuzzer;
	};
}
