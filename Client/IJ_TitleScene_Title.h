#pragma once
#include "IJ_GameObject.h"


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

	private:

	};
}
