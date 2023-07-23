#pragma once
#include "IJ_Entity.h"

namespace IJ
{
	enum class myComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		Rigidbody,
		End,
	};

	class Component : public Entity
	{
	public:
		Component(myComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetOwner(class GameObject* owner) { myOwner = owner; }
		class GameObject* GetOwner() { return myOwner; }

	private:
		const myComponentType myType;
		class GameObject* myOwner;
	};
}
