#pragma once
#include "IJ_Scene.h"


namespace IJ
{
	class BossScene : public Scene
	{
	public:
		BossScene();
		virtual ~BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
