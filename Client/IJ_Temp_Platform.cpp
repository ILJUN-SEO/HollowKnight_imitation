#include "IJ_Temp_Platform.h"


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
}