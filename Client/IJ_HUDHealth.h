#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class HUDHealth : public GameObject
	{
	public:
		HUDHealth();
		virtual ~HUDHealth();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
