#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class PlayBackground : public GameObject
	{
	public:
		PlayBackground();
		virtual ~PlayBackground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
