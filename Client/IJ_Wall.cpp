#include "IJ_Wall.h"
#include "IJ_Player.h"
#include "IJ_Transform.h"
#include "IJ_Collider.h"


namespace IJ
{
	Wall::Wall()
	{}
	Wall::~Wall()
	{}

	void Wall::Initialize()
	{}
	void Wall::Update()
	{}
	void Wall::Render(HDC hdc)
	{}

	void Wall::OnCollisionEnter(Collider* other)
	{}
	void Wall::OnCollisionStay(Collider* other)
	{}
	void Wall::OnCollisionExit(Collider* other)
	{}
}