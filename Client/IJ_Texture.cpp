#include "IJ_Texture.h"
#include "IJ_Application.h"
#include "IJ_ResourceManager.h"
#include "IJ_GameObject.h"
#include "IJ_Transform.h"
#include "IJ_Camera.h"


extern IJ::Application application;

namespace IJ
{
	Texture::Texture()
		: myWidth(0)
		, myHeight(0)
		, myHDC(NULL)
		, myBitmap(NULL)
		, myType(myTextureType::None)
		, myImage(nullptr)
		, isDrawOnCamera(false)
	{}

	Texture::~Texture()
	{	
		delete myImage;
		myImage = nullptr;

		DeleteObject(myBitmap);
		myBitmap = NULL;
	}

	void Texture::Render(HDC hdc
		, Vector2 pos
		, Vector2 size
		, Vector2 leftTop
		, Vector2 rightBottom
		, Vector2 offset
		, float rotate
		, Vector2 scale
		, bool drawOnCamera
		, float alphainput)
	{
		if (myBitmap == nullptr && myImage == nullptr)
			return;

		if (drawOnCamera == false)
			pos = Camera::GetWinPosition(pos);

		if (myType == myTextureType::bmp)
		{
			TransparentBlt(hdc
				, (int)pos.x - (size.x * scale.x / 2.0f) + offset.x
				, (int)pos.y - (size.y * scale.y / 2.0f) + offset.y
				, size.x * scale.x
				, size.y * scale.y
				, myHDC
				, leftTop.x, leftTop.y, rightBottom.x, rightBottom.y
				, RGB(255, 0, 255));
		}
		else if (myType == myTextureType::Alphabmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			int alpha = (int)(alphainput * 255.0f);
			if (alpha <= 0)
				alpha = 0;
			func.SourceConstantAlpha = alpha;

			AlphaBlend(hdc
				, (int)pos.x - (size.x * scale.x / 2.0f) + offset.x
				, (int)pos.y - (size.y * scale.y / 2.0f) + offset.y
				, size.x * scale.x
				, size.y * scale.y
				, myHDC
				, leftTop.x, leftTop.y
				, rightBottom.x, rightBottom.y
				, func);
		}
		else if (myType == myTextureType::png)
		{
			Gdiplus::ImageAttributes imageAtt = {};
			imageAtt.SetColorKey(Gdiplus::Color(255, 0, 255)
								, Gdiplus::Color(255, 0, 255));

			Gdiplus::Graphics graphics(hdc);

			graphics.TranslateTransform((float)pos.x, (float)pos.y);
			graphics.RotateTransform(rotate);
			graphics.TranslateTransform(-(float)pos.x, -(float)pos.y);

			graphics.DrawImage(myImage
				, Gdiplus::Rect
				(
					(int)(pos.x - (size.x * scale.x / 2.0f) + offset.x)
					, (int)(pos.y - (size.y * scale.y / 2.0f) + offset.y)
					, (int)(size.x * scale.x)
					, (int)(size.y * scale.y)
				)
				, leftTop.x, leftTop.y
				, rightBottom.x, rightBottom.y
				, Gdiplus::UnitPixel
				, nullptr);
		}

		//Rectangle(hdc
		//	, pos.x, pos.y
		//	, pos.x + 10, pos.y + 10);
	}

	Texture* Texture::CreateTexture(const std::wstring& name, UINT width, UINT height)
	{
		Texture* texture = ResourceManager::Find<Texture>(name);
		if (texture != nullptr)
			return texture;

		texture = new Texture();
		texture->SetWidth(width);
		texture->SetHeight(height);
		HDC hdc = application.GetHDC();
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
		texture->SetHBitmap(bitmap);

		HDC bitmapHDC = CreateCompatibleDC(hdc);
		texture->SetHDC(hdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(bitmapHDC, bitmap);
		DeleteObject(defaultBitmap);

		texture->SetName(name);
		texture->SetType(myTextureType::Alphabmp);
		ResourceManager::Insert<Texture>(name, texture);

		return texture;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		if (ext == L"bmp")
		{
			myType = myTextureType::bmp;
			myBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (myBitmap == nullptr)
				return S_FALSE;

			BITMAP info = {};
			GetObject(myBitmap, sizeof(BITMAP), &info);

			if (info.bmBitsPixel == 32)
				myType = myTextureType::Alphabmp;

			myWidth = info.bmWidth;
			myHeight = info.bmHeight;

			HDC mainHDC = application.GetHDC();
			myHDC = CreateCompatibleDC(mainHDC);

			HBITMAP defaultBitmap = (HBITMAP)SelectObject(myHDC, myBitmap);
			DeleteObject(defaultBitmap);
		}

		else if (ext == L"png")
		{
			myType = myTextureType::png;
			myImage = Gdiplus::Image::FromFile(path.c_str());

			myWidth = myImage->GetWidth();
			myHeight = myImage->GetHeight();
		}

		return S_OK;
	}
}