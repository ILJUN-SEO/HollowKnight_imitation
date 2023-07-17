#include "IJ_Animation.h"
#include "IJ_Texture.h"
#include "IJ_Animator.h"
#include "IJ_Time.h"
#include "IJ_Transform.h"
#include "IJ_GameObject.h"
#include "IJ_Camera.h"


namespace IJ
{
	Animation::Animation()
		: myAnimator(nullptr)
		, myTexture(nullptr)
		, mySpriteSheet{}
		, myIndex(-1)
		, myTime(0.0f)
		, isComplete(false)
	{}

	Animation::~Animation()
	{}

	void Animation::Update()
	{
		if (isComplete)
			return;

		myTime += Time::DeltaTime();
		if (mySpriteSheet[myIndex].duration < myTime)
		{
			myTime = 0.0f;

			if (myIndex < mySpriteSheet.size() - 1)
				myIndex++;
			else
				isComplete = true;
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (myTexture == nullptr)
			return;

		Transform* tr = myAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (myAnimator->GetFollowingCamera())
			pos = Camera::GetWinPosition(pos);
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;

		int alpha = (int)(myAnimator->GetAlpha() * 255.0f);
		if (alpha <= 0)
			alpha = 0;
		func.SourceConstantAlpha = alpha;

		AlphaBlend(hdc, (int)pos.x - (mySpriteSheet[myIndex].size.x / 2.0f) + mySpriteSheet[myIndex].offset.x
			, (int)pos.y - (mySpriteSheet[myIndex].size.y / 2.0f) + mySpriteSheet[myIndex].offset.y
			, mySpriteSheet[myIndex].size.x
			, mySpriteSheet[myIndex].size.y
			, myTexture->GetHDC()
			, mySpriteSheet[myIndex].leftTop.x
			, mySpriteSheet[myIndex].leftTop.y
			, mySpriteSheet[myIndex].size.x
			, mySpriteSheet[myIndex].size.y
			, func);
	}

	void Animation::CreateAnimation(const std::wstring& name, Texture* texture
		, Vector2 lefttop, Vector2 size, Vector2 offset
		, UINT spriteLength, float duration)
	{
		myTexture = texture;

		for (int i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};

			sprite.leftTop.x = lefttop.x + (size.x * i);
			sprite.leftTop.y = lefttop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mySpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		myTime = 0.0f;
		myIndex = 0;
		isComplete = false;
	}
}