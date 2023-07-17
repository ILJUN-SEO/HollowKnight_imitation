#include "IJ_PlayBackground.h"


namespace IJ
{
	PlayBackground::PlayBackground()
	{}

	PlayBackground::~PlayBackground()
	{}

	void PlayBackground::Initialize()
	{}

	void PlayBackground::Update()
	{
		GameObject::Update();
	}

	void PlayBackground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}