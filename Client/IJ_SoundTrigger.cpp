#include "IJ_SoundTrigger.h"
#include "IJ_Collider.h"
#include "IJ_Transform.h"

#include "IJ_Player.h"
#include "IJ_Crawler.h"


namespace IJ
{
	SoundTrigger::SoundTrigger()
		: myOwner(nullptr)
	{}
	SoundTrigger::~SoundTrigger()
	{}

	void SoundTrigger::Initialize()
	{
		AddComponent<Collider>()->SetSize(Vector2(1500.0f, 800.0f));
	}
	void SoundTrigger::Update()
	{
		GameObject::Update();

		GetComponent<Transform>()->SetPosition(myOwner->GetComponent<Transform>()->GetPosition());

	}
	void SoundTrigger::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SoundTrigger::OnCollisionEnter(Collider* other)
	{}
	void SoundTrigger::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Crawler* crawler = dynamic_cast<Crawler*>(myOwner);
			if (crawler != nullptr)
			{
				crawler->SetPlayerNearby(true);
			}
		}
	}
	void SoundTrigger::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Crawler* crawler = dynamic_cast<Crawler*>(myOwner);
			if (crawler != nullptr)
			{
				crawler->SetPlayerNearby(false);
			}
		}
	}
}