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
		Vector2 GetSize() { return mySize; }
		void SetOffset(Vector2 offset) { myOffset = offset; }
		Vector2 GetOffset() { return myOffset; }
		void ForceSetOnCollision(bool value) { isOnCollision = value; }

	private:
		static UINT myCollisionIDCount;
		UINT myCollisionID;
		bool isOnCollision;

		Vector2 myPosition;
		Vector2 mySize;
		Vector2 myOffset;
		bool isDrawOnCamera;
	};
}
