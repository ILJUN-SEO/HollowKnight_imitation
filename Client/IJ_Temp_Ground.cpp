#include "IJ_Temp_Ground.h"


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
}