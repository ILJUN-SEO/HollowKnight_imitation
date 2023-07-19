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

		GameObject* gameobj = GetOwner();
		Transform* tr = gameobj->GetComponent<Transform>();

		myTexture->Render(hdc
			, tr->GetPosition()
			, Vector2(myTexture->GetWidth(), myTexture->GetHeight())
			, Vector2::Zero
			, Vector2(myTexture->GetWidth(), myTexture->GetHeight())
			, Vector2::Zero
			, tr->GetRotation()
			, myScale
			, isDrawOnCamera
			, myAlpha);
	}
}