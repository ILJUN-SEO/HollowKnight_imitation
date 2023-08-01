#pragma once
#include "IJ_Resource.h"


namespace IJ
{
	using namespace Math;

	enum class myTextureType
	{
		bmp,
		Alphabmp,
		png,
		None,
	};

	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		void Render(HDC hdc
			, Vector2 pos
			, Vector2 size
			, Vector2 leftTop
			, Vector2 rightBottom
			, Vector2 offset = Vector2::Zero
			, float rotate = 0.0f
			, Vector2 scale = Vector2::One
			, bool drawOnCamera = false
			, float alpha = 1.0f);

		static Texture* CreateTexture(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;

		void SetWidth(UINT width) { myWidth = width; }
		UINT GetWidth() { return myWidth; }
		void SetHeight(UINT height) { myHeight = height; }
		UINT GetHeight() { return myHeight; }

		void SetHDC(HDC hdc) { myHDC = hdc; }
		HDC GetHDC() { return myHDC; }
		void SetHBitmap(HBITMAP bitmap) { myBitmap = bitmap; }
		void SetType(myTextureType type) { myType = type; }
		myTextureType GetType() { return myType; }
		Gdiplus::Image* GetImage() { return myImage; }
		void SetXFlip() { myImage->RotateFlip(Gdiplus::RotateNoneFlipX); }

		void SetDrawOnCamera(bool value) { isDrawOnCamera = value; }
		bool GetDrawOnCamera() { return isDrawOnCamera; }

	private:
		UINT myWidth;
		UINT myHeight;

		HDC myHDC;
		HBITMAP myBitmap;
		myTextureType myType;
		Gdiplus::Image* myImage;
		
		bool isDrawOnCamera;
	};
}
