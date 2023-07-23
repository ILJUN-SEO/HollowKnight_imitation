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
	{}

	Rigidbody::~Rigidbody()
	{}

	void Rigidbody::Initialize()
	{}

	void Rigidbody::Update()
	{
		myAccelation = myForce / myMass;

		myVelocity += myAccelation * Time::DeltaTime();

		if (!(myVelocity == Vector2::Zero))
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