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
		Transform* groundtr = GetComponent<Transform>();
		Vector2 groundpos = groundtr->GetPosition();
		Collider* groundcol = GetComponent<Collider>();

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* playertr = player->GetComponent<Transform>();
			Vector2 playerpos = playertr->GetPosition();
			Collider* playercol = other;

			//float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			//float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetPosition().y / 2.0f);
			//float len = fabs(playerpos.y - groundcol->GetPosition().y);
			//float scale = fabs(playercol->GetSize().y / 2.0f + groundcol->GetPosition().y / 2.0f);
			float jupX = fabs((groundcol->GetSize().x / 2.0f) + (playercol->GetSize().x / 2.0f));
			float jupY = fabs((groundcol->GetSize().y / 2.0f) + (playercol->GetSize().y / 2.0f));
			float acdisX = fabs(playerpos.x - groundcol->GetPosition().x);
			float acdisY = fabs(playerpos.y - groundcol->GetPosition().y);
			
			//if (playerpos.x > groundpos.x - jupX
			//	&& playerpos.x < groundpos.x + jupX)
			if (acdisX < jupX)
			{
				if (playerpos.y < groundpos.y - (groundcol->GetSize().y / 2.0f))
				{
					playerpos.y = groundcol->GetPosition().y
						- (groundcol->GetSize().y / 2.0f)
						- (playercol->GetSize().y / 2.0f)
						+ 1.0f;

					playertr->SetPosition(playerpos);
					player->SetState(Player::myPlayerState::Idle);
				}
				else if (playerpos.y > groundpos.y + (groundcol->GetSize().y / 2.0f))
				{
					player->SetState(Player::myPlayerState::Fall);
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
			else
			{
				Transform* groundtr = GetComponent<Transform>();
				Vector2 groundpos = groundtr->GetPosition();
				Transform* buzzertr = buzzer->GetComponent<Transform>();
				Vector2 buzzerpos = buzzertr->GetPosition();
				
				buzzerpos.y = groundpos.y - (GetComponent<Collider>()->GetSize().y / 2.0f) - (other->GetSize().y / 2.0f) - 1.0f;
				buzzertr->SetPosition(buzzerpos);
			}
		}
	}
	void Ground::OnCollisionStay(Collider* other)
	{
		Transform* groundtr = GetComponent<Transform>();
		Vector2 groundpos = groundtr->GetPosition();
		Collider* groundcol = GetComponent<Collider>();

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* playertr = player->GetComponent<Transform>();
			Vector2 playerpos = playertr->GetPosition();
			Collider* playercol = other;

			if (player->GetState() == Player::myPlayerState::Fall)
			{
				playerpos.y = groundcol->GetPosition().y
					- (groundcol->GetSize().y / 2.0f)
					- (playercol->GetSize().y / 2.0f)
					+ 1.0f;

				playertr->SetPosition(playerpos);
				player->SetState(Player::myPlayerState::Idle);
			}
		}

		Buzzer* buzzer = dynamic_cast<Buzzer*>(other->GetOwner());
		if (buzzer != nullptr)
		{
			Transform* groundtr = GetComponent<Transform>();
			Vector2 groundpos = groundtr->GetPosition();
			Transform* buzzertr = buzzer->GetComponent<Transform>();
			Vector2 buzzerpos = buzzertr->GetPosition();

			buzzerpos.y = groundpos.y - (GetComponent<Collider>()->GetSize().y / 2.0f) - (other->GetSize().y / 2.0f);
			buzzertr->SetPosition(buzzerpos);
		}
	}
	void Ground::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Player::myPlayerState pState = player->GetState();
			if (pState != Player::myPlayerState::Jump 
				&& pState != Player::myPlayerState::JumpAttack 
				&& pState != Player::myPlayerState::Damaged)
			{
				player->SetPlayerGrounded(false);
				if (pState != Player::myPlayerState::Damaged)
					player->SetState(Player::myPlayerState::Fall);
			}
		}
	}
}