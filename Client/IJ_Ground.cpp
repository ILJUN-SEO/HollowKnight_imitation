#include "IJ_Ground.h"
#include "IJ_Transform.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"

#include "IJ_Player.h"
#include "IJ_Buzzer.h"


namespace IJ
{
	Ground::Ground()
	{}
	Ground::~Ground()
	{}

	void Ground::Initialize()
	{}
	void Ground::Update()
	{
		GameObject::Update();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* playertr = player->GetComponent<Transform>();
			Vector2 playerpos = playertr->GetPosition();

			float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetPosition().y / 2.0f);

			if (other->GetPosition().y < this->GetComponent<Collider>()->GetPosition().y)
			{
				if (len < scale)
				{
					playerpos.y = this->GetComponent<Collider>()->GetPosition().y - (this->GetComponent<Collider>()->GetSize().y / 2.0f) - (other->GetSize().y / 2.0f) + 1.0f;
					playertr->SetPosition(playerpos);
					player->SetPlayerGrounded(true);
					player->SetState(Player::myPlayerState::Idle);
				}
			}
		}

		Buzzer* buzzer = dynamic_cast<Buzzer*>(other->GetOwner());
		if (buzzer != nullptr)
		{
			if (buzzer->GetBuzzerState() == Buzzer::myBuzzerState::Dead)
			{
				buzzer->GetComponent<Rigidbody>()->SetGrounded(true);
				buzzer->GetComponent<Rigidbody>()->SetVelocity(Vector2::Zero);
			}
		}
	}
	void Ground::OnCollisionStay(Collider* other)
	{}
	void Ground::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Player::myPlayerState pState = player->GetState();
			if (pState != Player::myPlayerState::Jump && pState != Player::myPlayerState::JumpAttack && pState != Player::myPlayerState::Damaged)
			{
				player->SetPlayerGrounded(false);
				if (pState != Player::myPlayerState::Damaged)
					player->SetState(Player::myPlayerState::Fall);
			}
		}
	}
}