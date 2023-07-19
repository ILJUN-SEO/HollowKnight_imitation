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

		Sprite sprite = mySpriteSheet[myIndex];
		Transform* tr = myAnimator->GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* animator = myAnimator;

		myTexture->Render(hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, sprite.offset
			, tr->GetRotation()
			, animator->GetScale()
			, animator->GetDrawOnCamera()
			, animator->GetAlpha());
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

			if (sprite.leftTop.x >= texture->GetWidth())
			{
				sprite.leftTop.x = sprite.leftTop.x - texture->GetWidth();
				sprite.leftTop.y = lefttop.y + size.y;
			}

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