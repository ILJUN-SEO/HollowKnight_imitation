#pragma once
#include "IJ_Component.h"


namespace IJ
{
	using namespace Math;

	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other);
		void OnCollisionStay(Collider* other);
		void OnCollisionExit(Collider* other);

		UINT GetCollisionID() { return myCollisionID; }

		void SetPosiiton(Vector2 position) { myPosition = position; }
		Vector2 GetPosition() { return myPosition; }
		void SetSize(Vector2 size) { mySize = size; }
		Vector2 GetSize() { return mySize * myScale; }
		void SetScale(float scale) { myScale = scale; }
		float GetScale() { return myScale; }
		void SetOffset(Vector2 offset) { myOffset = offset; }
		Vector2 GetOffset() { return myOffset; }

	private:
		static UINT myCollisionIDCount;
		UINT myCollisionID;
		bool isOnCollision;

		Vector2 myPosition;
		Vector2 mySize;
		float myScale;
		Vector2 myOffset;
		bool isDrawOnCamera;
	};
}
