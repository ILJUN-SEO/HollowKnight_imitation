#include "IJ_GameObject.h"
#include "IJ_Transform.h"
#include "IJ_SpriteRenderer.h"


namespace IJ
{
	GameObject::GameObject()
		: myCurrentGOState(myGameObjectState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{}

	void GameObject::Initialize()
	{}

	void GameObject::Update()
	{
		for (Component* component : myComponents)
		{
			component->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* component : myComponents)
		{
			component->Render(hdc);
		}
	}

	void GameObject::OnCollisionEnter(Collider* other)
	{}

	void GameObject::OnCollisionStay(Collider* other)
	{}

	void GameObject::OnCollisionExit(Collider* other)
	{}
}