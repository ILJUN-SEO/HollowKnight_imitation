#include "IJ_Collider.h"
#include "IJ_Transform.h"
#include "IJ_GameObject.h"

namespace IJ
{
	Collider::Collider()
		: Component(myComponentType::Collider)
		, mySize(Vector2::Zero)
		, myOffset(Vector2::Zero)
	{}

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
		pos.x -= mySize.x / 2.0f;
		pos.y -= mySize.y / 2.0f;
		pos.x += myOffset.x;
		pos.y += myOffset.y;

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN bluePen = CreatePen(PS_SOLID, 1, RGB(50, 50, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, bluePen);

		Rectangle(hdc
			, pos.x, pos.y
			, pos.x + mySize.x, pos.y + mySize.y);

		SelectObject(hdc, oldPen);
		DeleteObject(bluePen);
	}
}