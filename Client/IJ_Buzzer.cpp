#include "IJ_Buzzer.h"


namespace IJ
{
	Buzzer::Buzzer()
		: myCurrentState(Buzzer::myBuzzerState::Idle)
		, buzzerHP(2)
		, isLookingLeft(true)
	{}
	Buzzer::~Buzzer()
	{}

	void Buzzer::Initialize()
	{}
	void Buzzer::Update()
	{}
	void Buzzer::Render(HDC hdc)
	{}

	void Buzzer::OnCollisionEnter(Collider* other)
	{}
	void Buzzer::OnCollisionStay(Collider* other)
	{}
	void Buzzer::OnCollisionExit(Collider* other)
	{}
}