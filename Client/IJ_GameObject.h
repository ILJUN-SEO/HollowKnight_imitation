#pragma once
#include "IJ_Entity.h"
#include "IJ_Component.h"


namespace IJ
{
	class GameObject : public Entity
	{
	public:
		enum class myGameObjectState
		{
			Active,
			Pause,
			Dead,
			END,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		friend static __forceinline void Destroy(GameObject* gameObject);
		void Pause() { myCurrentGOState = myGameObjectState::Pause; }
		myGameObjectState GetGameObjectState() { return myCurrentGOState; }

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
		void Death() { myCurrentGOState = myGameObjectState::Dead; }

		std::vector<Component*> myComponents;
		myGameObjectState myCurrentGOState;
	};

	static __forceinline void Destroy(GameObject* gameObject) { gameObject->Death(); }

}
