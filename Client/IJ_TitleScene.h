#pragma once
#include "IJ_Scene.h"
#include "IJ_TitleScene_Title.h"


namespace IJ
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		std::vector<TitleScene_Title*> myMenu;
	};
}
