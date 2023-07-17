#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class Temp_Platform : public GameObject
	{
	public:
		Temp_Platform();
		virtual ~Temp_Platform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
