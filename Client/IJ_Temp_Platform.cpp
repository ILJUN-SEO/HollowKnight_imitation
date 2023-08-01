#include "IJ_Temp_Platform.h"
#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"


namespace IJ
{
	Temp_Platform::Temp_Platform()
	{}

	Temp_Platform::~Temp_Platform()
	{}

	void Temp_Platform::Initialize()
	{}

	void Temp_Platform::Update()
	{
		GameObject::Update();
	}

	void Temp_Platform::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Temp_Platform::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* playerTr = player->GetComponent<Transform>();
		Vector2 playerPos = playerTr->GetPosition();
		Rigidbody* playerRb = player->GetComponent<Rigidbody>();

		Collider* col = GetComponent<Collider>();

		float len = fabs(other->GetPosition().y - col->GetPosition().y);
		float scale = fabs(other->GetSize().y / 2.0f + col->GetSize().y / 2.0f);

		if (other->GetPosition().y < col->GetPosition().y - other->GetSize().y / 2.0f)
		{
			if (len < scale)
			{
				playerPos.y -= (scale - len) - 1.0f;
				playerTr->SetPosition(playerPos);
			}

			playerRb->SetGrounded(true);
			player->SetState(Player::myPlayerState::Idle);
		}
		else if (other->GetPosition().y > col->GetPosition().y + (col->GetSize().y / 2.0f) - (other->GetSize().y / 2.0f))
		{
			player->SetState(Player::myPlayerState::Fall);
		}
		//else if (other->GetPosition().x > col->GetPosition().x - (col->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f))
		//{
		//	playerPos.x = col->GetPosition().x - (col->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f) - 1.0f;
		//	playerTr->SetPosition(playerPos);
		//}
	}
	void Temp_Platform::OnCollisionStay(Collider* other)
	{
		//Player* player = dynamic_cast<Player*>(other->GetOwner());
		//Transform* playerTr = player->GetComponent<Transform>();
		//Vector2 playerPos = playerTr->GetPosition();
		//Rigidbody* playerRb = player->GetComponent<Rigidbody>();

		//Collider* col = GetComponent<Collider>();

		//if (other->GetPosition().y < col->GetPosition().y - other->GetSize().y / 2.0f)
		//{}
		//else if (other->GetPosition().y > col->GetPosition().y + (col->GetSize().y / 2.0f) - (other->GetSize().y / 2.0f))
		//{}
		//else if (other->GetPosition().x > col->GetPosition().x - (col->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f))
		//{
		//	playerPos.x = col->GetPosition().x - (col->GetSize().x / 2.0f) - (other->GetSize().x / 2.0f) - 1.0f;
		//	playerTr->SetPosition(playerPos);
		//}
	}
	void Temp_Platform::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Rigidbody* playerRb = player->GetComponent<Rigidbody>();

		if (player->GetState() != Player::myPlayerState::Jump)
		{
			playerRb->SetGrounded(false);
			player->SetState(Player::myPlayerState::Fall);
		}
	}
}