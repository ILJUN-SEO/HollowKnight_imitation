#pragma once
#include "IJ_Entity.h"
#include "IJ_Component.h"


namespace IJ
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			myComponents.push_back(component);
			component->SetOwner(this);

			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* component = nullptr;
			for (Component* c : myComponents)
			{
				component = dynamic_cast<T*>(c);
				if (component != nullptr)
					return component;
			}

			return component;
		}

	private:
		std::vector<Component*> myComponents;
	};
}
