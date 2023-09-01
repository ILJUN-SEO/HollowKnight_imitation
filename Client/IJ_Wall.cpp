#include "IJ_Wall.h"
#include "IJ_Transform.h"
#include "IJ_Collider.h"
#include "IJ_Rigidbody.h"

#include "IJ_Player.h"
#include "IJ_Buzzer.h"
#include "IJ_FalseKnight.h"


namespace IJ
{
	Wall::Wall()
	{}
	Wall::~Wall()
	{}

	void Wall::Initialize()
	{}
	void Wall::Update()
	{
		GameObject::Update();
	}
	void Wall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Wall::OnCollisionEnter(Collider* other)
	{
		FKCollision(other);
	}
	void Wall::OnCollisionStay(Collider* other)
	{
		Transform* walltr = GetComponent<Transform>();
		Vector2 wallpos = walltr->GetPosition();
		Collider* wallcol = GetComponent<Collider>();

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* playertr = player->GetComponent<Transform>();
			Vector2 playerpos = playertr->GetPosition();
			Collider* playercol = other;

			float jupX = fabs((wallcol->GetSize().x / 2.0f) + (playercol->GetSize().x / 2.0f));
			float jupY = fabs((wallcol->GetSize().y / 2.0f) + (playercol->GetSize().y / 2.0f));
			float acdisX = fabs(playerpos.x - wallcol->GetPosition().x);
			float acdisY = fabs(playerpos.y - wallcol->GetPosition().y);

			if (playerpos.y > wallpos.y - (wallcol->GetSize().y / 2.0f) - (playercol->GetSize().y / 2.0f)
				&& playerpos.y < wallpos.y + (wallcol->GetSize().y / 2.0f) + (playercol->GetSize().y / 2.0f))
			{
				if (playerpos.x > wallpos.x)
					playerpos.x = wallpos.x + (wallcol->GetSize().x / 2.0f) + (playercol->GetSize().x / 2.0f) + 1.0f;
				else if (playerpos.x < wallpos.x)
					playerpos.x = wallpos.x - (wallcol->GetSize().x / 2.0f) - (playercol->GetSize().x / 2.0f) - 1.0f;
			}
			playertr->SetPosition(playerpos);
		}

		FKCollision(other);
	}
	void Wall::OnCollisionExit(Collider* other)
	{}

	void Wall::FKCollision(Collider* collider)
	{
		FalseKnight* fk = dynamic_cast<FalseKnight*>(collider->GetOwner());
		if (fk == nullptr)
			return;
		else
		{
			Transform* walltr = GetComponent<Transform>();
			Vector2 wallpos = walltr->GetPosition();
			Collider* wallcol = GetComponent<Collider>();

			Transform* fktr = fk->GetComponent<Transform>();
			Vector2 fkpos = fktr->GetPosition();
			Collider* fkcol = collider;

			if (fkpos.x < wallpos.x)
			{
				fkpos.x = wallpos.x - (wallcol->GetSize().x / 2.0f) - (fkcol->GetSize().x / 2.0f);
			}
			else if (fkpos.x > wallpos.x)
			{
				fkpos.x = wallpos.x + (wallcol->GetSize().x / 2.0f) + (fkcol->GetSize().x / 2.0f);
			}

			fktr->SetPosition(fkpos);
		}
	}
}