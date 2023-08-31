#include "IJ_BuzzerTrigger.h"
#include "IJ_Buzzer.h"
#include "IJ_Collider.h"
#include "IJ_Transform.h"

#include "IJ_ResourceManager.h"
#include "IJ_Sound.h"


namespace IJ
{
	BuzzerTrigger::BuzzerTrigger()
		: myBuzzer(nullptr)
	{}
	BuzzerTrigger::~BuzzerTrigger()
	{}	
	
	void BuzzerTrigger::Initialize()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetSize(Vector2(500.0f, 500.0f));
	}
	void BuzzerTrigger::Update()
	{
		GameObject::Update();

		Transform* transform = GetComponent<Transform>();
		transform->SetPosition(myBuzzer->GetComponent<Transform>()->GetPosition());

		if (myBuzzer->GetBuzzerState() == Buzzer::myBuzzerState::Dead)
			Destroy(this);
	}
	void BuzzerTrigger::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BuzzerTrigger::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr && myBuzzer->GetBuzzerState() == Buzzer::myBuzzerState::Idle)
		{
			Sound* sound = ResourceManager::Load<Sound>(L"Buzzer_startle", L"..\\Resources\\Sound\\buzzer\\buzzer_startle_01.wav");
			sound->Play(false);
			myBuzzer->SetBuzzerState(Buzzer::myBuzzerState::Startle);
			myBuzzer->SetTarget(player);
		}
	}
	void BuzzerTrigger::OnCollisionStay(Collider* other)
	{}
	void BuzzerTrigger::OnCollisionExit(Collider* other)
	{}
}
