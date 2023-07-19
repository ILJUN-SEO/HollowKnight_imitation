#pragma once
#include "IJ_GameObject.h"


namespace IJ
{
	class Player : public GameObject
	{
	public:
		enum class myPlayerState
		{
			Idle,
			Move,
			Attack,
			Death,
			END
		};
		
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Idle();
		void Move();
		void Attack();
		void Death();

	private:
		myPlayerState myState;
	};
}
