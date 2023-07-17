#include "IJ_TitleScene_Background.h"
#include "IJ_SpriteRenderer.h"


namespace IJ
{
	TitleScene_Background::TitleScene_Background()
	{} 

	TitleScene_Background::~TitleScene_Background()
	{}

	void TitleScene_Background::Initialize()
	{}

	void TitleScene_Background::Update()
	{
		GameObject::Update();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
	}

	void TitleScene_Background::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}