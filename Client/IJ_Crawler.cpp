#include "IJ_Crawler.h"
#include "IJ_Transform.h"
#include "IJ_Time.h"
#include "IJ_Animator.h"


namespace IJ
{
	Crawler::Crawler()
	{}

	Crawler::~Crawler()
	{}

	void Crawler::Initialize()
	{}

	void Crawler::Update()
	{
		GameObject::Update();
	}

	void Crawler::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}