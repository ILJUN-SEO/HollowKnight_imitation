#pragma once
#include "IJ_Resource.h"


namespace IJ
{
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

		static Texture* CreateTexture(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;

		void SetWidth(UINT width) { myWidth = width; }
		UINT GetWidth() { return myWidth; }
		void SetHeight(UINT height) { myHeight = height; }
		UINT GetHeight() { return myHeight; }

		void SetHDC(HDC hdc) { myHDC = hdc; }
		HDC GetHDC() { return myHDC; }
		void SetHBitmap(HBITMAP bitmap) { myBitmap = bitmap; }
		myTextureType GetType() { return myType; }
		Gdiplus::Image* GetImage() { return myImage; }

	private:
		UINT myWidth;
		UINT myHeight;

		HDC myHDC;
		HBITMAP myBitmap;
		myTextureType myType;
		Gdiplus::Image* myImage;
	};
}
