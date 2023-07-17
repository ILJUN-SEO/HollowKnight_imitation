#pragma once
#include "IJ_Resource.h"


namespace IJ
{
	using namespace Math;
	class Texture;
	class Animator;

	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{}
		};

		Animation();
		virtual ~Animation();

		void Update();
		void Render(HDC hdc);

		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; };

		void CreateAnimation(const std::wstring& name
			, class Texture* texture
			, Vector2 lefttop, Vector2 size, Vector2 offset
			, UINT spriteLength, float duration);

		void Reset();

		bool IsComplete() { return isComplete; }
		void SetAnimator(Animator* animator) { myAnimator = animator; }

	private:
		Animator* myAnimator;
		Texture* myTexture;

		std::vector<Sprite> mySpriteSheet;
		int myIndex;
		float myTime;
		bool isComplete;
	};
}
