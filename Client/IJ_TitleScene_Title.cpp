#include "IJ_TitleScene_Title.h"
#include "IJ_SpriteRenderer.h"
#include "IJ_Transform.h"
#include "IJ_Animator.h"


namespace IJ
{
	TitleScene_Title::TitleScene_Title()
		: isActivated(false)
		, myActiveAnimationName(L"")
		, myNonActiveAnimationName(L"")
	{}
	TitleScene_Title::~TitleScene_Title()
	{}

	void TitleScene_Title::Initialize()
	{}
	void TitleScene_Title::Update()
	{
		GameObject::Update();

		if (GetComponent<Animator>() != nullptr)
		{
			if (isActivated)
			{
				GetComponent<Animator>()->PlayAnimation(myActiveAnimationName);
			}
			else
			{
				GetComponent<Animator>()->PlayAnimation(myNonActiveAnimationName);
			}
		}
	}
	void TitleScene_Title::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}