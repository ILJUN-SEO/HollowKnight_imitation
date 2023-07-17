#include "IJ_HUDHealth.h"


namespace IJ
{
	HUDHealth::HUDHealth()
	{}

	HUDHealth::~HUDHealth()
	{}

	void HUDHealth::Initialize()
	{}

	void HUDHealth::Update()
	{
		GameObject::Update();
	}

	void HUDHealth::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}