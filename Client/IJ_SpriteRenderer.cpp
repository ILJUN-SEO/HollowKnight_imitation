#include "IJ_SpriteRenderer.h"
#include "IJ_Transform.h"
#include "IJ_GameObject.h"
#include "IJ_Camera.h"


namespace IJ
{
	SpriteRenderer::SpriteRenderer()
		:Component(myComponentType::SpriteRenderer)
		, myTexture(nullptr)
		, myScale(Vector2::One)
		, isDrawOnCamera(false)
		, myAlpha(1.0f)
	{}

	SpriteRenderer::~SpriteRenderer()
	{}

	void SpriteRenderer::Initialize()
	{}

	void SpriteRenderer::Update()
	{}

	void SpriteRenderer::Render(HDC hdc)
	{	
		if (myTexture == nullptr)
			return;

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Math::Vector2 pos = tr->GetPosition();

		if (isDrawOnCamera == false)
			pos = Camera::GetWinPosition(pos);
		
		if (myTexture->GetType() == myTextureType::bmp)
		{
			TransparentBlt(hdc, (int)pos.x, (int)pos.y
				, myTexture->GetWidth() * myScale.x, myTexture->GetHeight() * myScale.y
				, myTexture->GetHDC(), 0, 0, myTexture->GetWidth(), myTexture->GetHeight(), RGB(255, 0, 255));
		}

		else if (myTexture->GetType() == myTextureType::png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(myTexture->GetImage()
				, (int)(pos.x - (myTexture->GetWidth() * myScale.x / 2.0f))
				, (int)(pos.y - (myTexture->GetHeight() * myScale.y / 2.0f))
				, (int)(myTexture->GetWidth() * myScale.x)
				, (int)(myTexture->GetHeight() * myScale.y));
		}
	}
}