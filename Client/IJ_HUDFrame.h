#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class HUDFrame : public GameObject
	{
	public:
		HUDFrame();
		virtual ~HUDFrame();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
