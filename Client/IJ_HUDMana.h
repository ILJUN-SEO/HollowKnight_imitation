#pragma once
#include "IJ_GameObject.h"
#include "IJ_Animator.h"
#include "IJ_Animation.h"


namespace IJ
{
	class HUDMana : public GameObject
	{
	public:
		HUDMana();
		virtual ~HUDMana();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetActivated(bool value) { isActivated = value; }
		bool GetActivated() { return isActivated; }
		void AssignAnimation(const std::wstring& name) { assignedAnimationName = name; }

	private:
		bool isActivated;
		std::wstring assignedAnimationName;
	};
}
