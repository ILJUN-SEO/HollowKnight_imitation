#pragma once
#include "IJ_Component.h"
#include "IJ_Texture.h"


namespace IJ
{
	using namespace Math;
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetTexture(Texture* texture) { myTexture = texture; }
		void SetScale(Math::Vector2 scale) { myScale = scale; }
		void MakeFollowCamera(bool value) { isDrawnOnCamera = value; }
		void SetAlpha(float alpha) { myAlpha = alpha; }
		float GetAlpha() { return myAlpha; }

	private:
		bool isDrawnOnCamera;
		Texture* myTexture;
		Vector2 myScale;
		float myAlpha;
	};
}
