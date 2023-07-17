#include "IJ_TitleScene_Title.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Transform.h"

namespace IJ
{
	TitleScene_Title::TitleScene_Title()
	{}

	TitleScene_Title::~TitleScene_Title()
	{}

	void TitleScene_Title::Initialize()
	{}

	void TitleScene_Title::Update()
	{
		GameObject::Update();
	}

	void TitleScene_Title::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}