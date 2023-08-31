#pragma once
#include "IJ_GameObject.h"
#include "IJ_Animation.h"


namespace IJ
{
	class TitleScene_Title : public GameObject
	{
	public:
		TitleScene_Title();
		virtual ~TitleScene_Title();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void ToggleActivated()
		{
			if (isActivated)
				isActivated = false;
			else
				isActivated = true;
		}
		void SetActivated(bool value) { isActivated = value; }
		bool GetActivated() { return isActivated; }
		void SetActiveAnim(std::wstring animName) { myActiveAnimationName = animName; }
		std::wstring GetActiveAnim() { return myActiveAnimationName; }
		void SetNonActiveAnim(std::wstring animName) { myNonActiveAnimationName = animName; }
		std::wstring GetNonActiveAnim() { return myNonActiveAnimationName; }

	private:
		bool isActivated;

		std::wstring myActiveAnimationName;
		std::wstring myNonActiveAnimationName;
	};
}
