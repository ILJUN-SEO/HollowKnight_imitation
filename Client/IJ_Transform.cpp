#include "IJ_Transform.h"


namespace IJ
{
	Transform::Transform()
		: Component(myComponentType::Transform)
		, myRotation(0.0f)
	{}

	Transform::~Transform()
	{}

	void Transform::Initialize()
	{}

	void Transform::Update()
	{}

	void Transform::Render(HDC hdc)
	{}
}