#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class Temp_Ground : public GameObject
	{
	public:
		Temp_Ground();
		virtual ~Temp_Ground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
