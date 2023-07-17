#include "IJ_HUDFrame.h"


namespace IJ
{
	HUDFrame::HUDFrame()
	{}

	HUDFrame::~HUDFrame()
	{}

	void HUDFrame::Initialize()
	{}

	void HUDFrame::Update()
	{
		GameObject::Update();
	}

	void HUDFrame::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}