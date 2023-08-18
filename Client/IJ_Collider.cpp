#include "IJ_Collider.h"
#include "IJ_Transform.h"
#include "IJ_GameObject.h"
#include "IJ_Camera.h"
#include "IJ_Input.h"
#include "IJ_SceneManager.h"
#include "IJ_Scene.h"

namespace IJ
{
	UINT Collider::myCollisionIDCount = 0;

	Collider::Collider()
		: Component(myComponentType::Collider)
		, myCollisionID(-1)
		, isOnCollision(false)
		, myPosition(Vector2::Zero)
		, mySize(Vector2::Zero)
		, myScale(1.0f)
		, myOffset(Vector2::Zero)
		, isDrawOnCamera(false)
	{
		myCollisionID = myCollisionIDCount;
		myCollisionIDCount++;
	}

	Collider::~Collider()
	{}

	void Collider::Initialize()
	{}

	void Collider::Update()
	{
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();

		//myPosition = pos + myOffset;

		//pos.x -= (mySize.x * myScale) / 2.0f;
		//pos.y -= (mySize.y * myScale) / 2.0f;
		//pos.x += myOffset.x;
		//pos.y += myOffset.y;

		//if (isDrawOnCamera == false)
		//	pos = Camera::GetWinPosition(pos);
	}

	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		myPosition = pos + myOffset;

		pos.x -= (mySize.x * myScale) / 2.0f;
		pos.y -= (mySize.y * myScale) / 2.0f;
		pos.x += myOffset.x;
		pos.y += myOffset.y;

		if (isDrawOnCamera == false)
			pos = Camera::GetWinPosition(pos);

		if (SceneManager::GetActivatedScene()->GetShowCollider() == true)
		{
			HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

			HPEN pen = NULL;
			if (isOnCollision)
				pen = CreatePen(PS_SOLID, 2, RGB(255, 50, 50));
			else
				pen = CreatePen(PS_SOLID, 2, RGB(50, 50, 255));
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);

			Rectangle(hdc
				, pos.x, pos.y
				, pos.x + (mySize.x * myScale), pos.y + (mySize.y * myScale));

			SelectObject(hdc, oldPen);
			DeleteObject(pen);
			SelectObject(hdc, oldBrush);
			DeleteObject(transparentBrush);
		}
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		isOnCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		isOnCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}