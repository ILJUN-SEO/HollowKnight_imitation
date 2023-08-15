#pragma once
#include "IJ_Component.h"


namespace IJ
{
	using namespace Math;

	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddForce(Vector2 force) { myForce += force; }

		void SetMass(float mass) { myMass = mass; }
		void SetVelocity(Vector2 velocity) { myVelocity = velocity; }
		void SetEnableGravity(bool value) { isEnableGravity = value; }
		void SetGrounded(bool value) { isGrounded = value; }
		Vector2 GetVelocity() { return myVelocity; }
		void SetMaxVelocity(Vector2 maxVelocity) { myMaxVelocity = maxVelocity; }

	private:
		float myMass;

		float myFriction;
		//float myStaticFriction;
		//float myKineticFriction;
		//float myFrictionCoefficient;

		Vector2 myForce;
		Vector2 myAccelation;
		Vector2 myVelocity;
		Vector2 myMaxVelocity;
		Vector2 myGravity;

		bool isEnableGravity;
		bool isGrounded;
	};
}
