#include "IJ_Component.h"


namespace IJ
{
	Component::Component(myComponentType type)
		: myType(type)
	{}

	Component::~Component()
	{}

	void Component::Initialize()
	{}

	void Component::Update()
	{}

	void Component::Render(HDC hdc)
	{}	
}