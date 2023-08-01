#include "IJ_Temp_Ground.h"
#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"


namespace IJ
{
	Temp_Ground::Temp_Ground()
	{}

	Temp_Ground::~Temp_Ground()
	{}

	void Temp_Ground::Initialize()
	{}

	void Temp_Ground::Update()
	{
		GameObject::Update();
	}

	void Temp_Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Temp_Ground::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* playertr = player->GetComponent<Transform>();
		Vector2 playerPos = playertr->GetPosition();
		Rigidbody* playerrb = player->GetComponent<Rigidbody>();

		float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
		float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

		if (other->GetPosition().y < this->GetComponent<Collider>()->GetPosition().y - other->GetSize().y / 2.0f)
		{
			if (len < scale)
			{
				playerPos.y -= (scale - len) - 1.0f;
				playertr->SetPosition(playerPos);
			}

			playerrb->SetGrounded(true);
			player->SetState(Player::myPlayerState::Idle);
		}

		if (other->GetPosition().x < this->GetComponent<Collider>()->GetPosition().x - (this->GetComponent<Collider>()->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f))
		{
			playerPos.x = this->GetComponent<Collider>()->GetPosition().x - (this->GetComponent<Collider>()->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f);
			playertr->SetPosition(playerPos);
		}
	}

	void Temp_Ground::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* playertr = player->GetComponent<Transform>();
		Vector2 playerPos = playertr->GetPosition();
		Rigidbody* playerrb = player->GetComponent<Rigidbody>();

		if (other->GetPosition().x < this->GetComponent<Collider>()->GetPosition().x - (this->GetComponent<Collider>()->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f))
		{
			playerPos.x = this->GetComponent<Collider>()->GetPosition().x - (this->GetComponent<Collider>()->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f);
			playertr->SetPosition(playerPos);
		}
	}

	void Temp_Ground::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Rigidbody* rb = player->GetComponent<Rigidbody>();

		if (player->GetState() != Player::myPlayerState::Jump)
		{
			rb->SetGrounded(false);
			player->SetState(Player::myPlayerState::Fall);
		}
	}
}