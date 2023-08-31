#pragma once
#include "IJ_GameObject.h"
#include "IJ_Sound.h"


namespace IJ
{
	class Crawler : public GameObject
	{
	public:
		enum class myCrawlerState
		{
			Walk,
			Turn,
			Dead,
			END,
		};

		Crawler();
		virtual ~Crawler();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Damaged(int damage) { crawlerHP -= damage; }
		myCrawlerState GetCrawlerState() { return myCurrentState; }
		int GetCrawlerHP() { return crawlerHP; }
		void SetCrawlerSound(Sound* sound) { myCrawlerSound = sound; }
		void SetPlayerNearby(bool value) { isPlayerNearby = value; }
		bool GetPlayerNearby() { return isPlayerNearby; }
		void SetSoundStarted(bool value) { isSoundStarted = value; }

		void Walk();
		void Turn();
		void Dead();

	private:
		myCrawlerState myCurrentState;
		int crawlerHP;
		bool isLookingLeft;
		float turnTime;
		Sound* myCrawlerSound;
		bool isSoundStarted;
		bool isPlayerNearby;
	};
}
