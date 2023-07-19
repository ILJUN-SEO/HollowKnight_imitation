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

		void SetSize(Vector2 size) { mySize = size; }
		Vector2 GetSize() { return mySize; }
		void SetOffset(Vector2 offset) { myOffset = offset; }
		Vector2 GetOffset() { return myOffset; }

	private:
		Vector2 mySize;
		Vector2 myOffset;
	};
}
