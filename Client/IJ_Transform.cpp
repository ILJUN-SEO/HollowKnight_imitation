#include "IJ_Transform.h"


namespace IJ
{
	Transform::Transform()
		:Component(myComponentType::Transform)
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