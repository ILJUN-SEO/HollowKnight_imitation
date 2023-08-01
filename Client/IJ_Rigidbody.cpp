#include "IJ_Rigidbody.h"
#include "IJ_Time.h"
#include "IJ_GameObject.h"
#include "IJ_Transform.h"


namespace IJ
{
	Rigidbody::Rigidbody()
		: Component(myComponentType::Rigidbody)
		, myMass(1.0f)
		, myFriction(10.0f)
		, isEnableGravity(false)
		, isGrounded(false)
	{
		myMaxVelocity = Vector2(200.0f, 1000.0f);
		myGravity = Vector2(0.0f, 800.0f);
	}

	Rigidbody::~Rigidbody()
	{}

	void Rigidbody::Initialize()
	{}

	void Rigidbody::Update()
	{
		myAccelation = myForce / myMass;

		myVelocity += myAccelation * Time::DeltaTime();

		if (isGrounded)
		{
			Vector2 gravity = myGravity;
			gravity.normalize();

			float dot = Math::Dot(myVelocity, gravity);
			myVelocity -= gravity * dot;
		}
		else
		{
			myVelocity += myGravity * Time::DeltaTime();
		}

		Vector2 gravity = myGravity;
		gravity.normalize();
		float dot = Math::Dot(myVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = myVelocity - gravity;
		if (myMaxVelocity.y < gravity.length())
		{
			gravity.normalize();
			gravity *= myMaxVelocity.y;
		}
		if (myMaxVelocity.x < sideVelocity.length())
		{
			sideVelocity.normalize();
			sideVelocity *= myMaxVelocity.x;
		}
		myVelocity = gravity + sideVelocity;


		//if (!(myVelocity == Vector2::Zero))
		if (myVelocity.x != 0.0f && myVelocity.y != 0.0f)
		{
			Vector2 friction = -myVelocity;
			friction = friction.normalize() * myFriction * myMass * Time::DeltaTime();

			if (myVelocity.length() < friction.length())
				myVelocity = Vector2::Zero;
			else
				myVelocity += friction;
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos = pos + myVelocity * Time::DeltaTime();
		tr->SetPosition(pos);
		myForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{}
}