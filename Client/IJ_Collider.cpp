#include "IJ_Collider.h"
#include "IJ_Transform.h"
#include "IJ_GameObject.h"
#include "IJ_Camera.h"

namespace IJ
{
	UINT Collider::myCollisionIDCount = 0;

	Collider::Collider()
		: Component(myComponentType::Collider)
		, myCollisionID(-1)
		, isOnCollision(false)
		, myPosition(Vector2::Zero)
		, mySize(Vector2::Zero)
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
	{}

	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		myPosition = pos + myOffset;

		pos.x -= mySize.x / 2.0f;
		pos.y -= mySize.y / 2.0f;
		pos.x += myOffset.x;
		pos.y += myOffset.y;

		if (isDrawOnCamera == false)
			pos = Camera::GetWinPosition(pos);


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
			, pos.x + mySize.x, pos.y + mySize.y);

		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		SelectObject(hdc, oldBrush);
		DeleteObject(transparentBrush);
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