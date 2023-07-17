#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class TitleScene_Background : public GameObject
	{
	public:
		TitleScene_Background();
		virtual ~TitleScene_Background();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
