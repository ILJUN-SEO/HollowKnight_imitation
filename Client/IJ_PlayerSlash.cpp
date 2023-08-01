#include "IJ_PlayerSlash.h"
#include "IJ_GameObject.h"
#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Time.h"


namespace IJ
{
	PlayerSlash::PlayerSlash()
		: myOwner(nullptr)
		, myDeathTime(0.5f)
	{}

	PlayerSlash::~PlayerSlash()
	{}

	void PlayerSlash::Initialize()
	{}

	void PlayerSlash::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(myOwner->GetComponent<Transform>()->GetPosition());

		myDeathTime -= Time::DeltaTime();
		if (myDeathTime < 0.0f)
		{
			Destroy(this);
		}
	}

	void PlayerSlash::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerSlash::OnCollisionEnter(Collider* other)
	{}

	void PlayerSlash::OnCollisionStay(Collider* other)
	{}

	void PlayerSlash::OnCollisionExit(Collider* other)
	{}
}