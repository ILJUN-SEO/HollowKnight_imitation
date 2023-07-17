#include "IJ_Texture.h"
#include "IJ_Application.h"
#include "IJ_ResourceManager.h"


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
	{}

	Texture::~Texture()
	{	
		delete myImage;
		myImage = nullptr;

		DeleteObject(myBitmap);
		myBitmap = NULL;
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