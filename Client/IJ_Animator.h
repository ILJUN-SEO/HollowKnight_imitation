#pragma once
#include "IJ_Component.h"
#include "IJ_Animation.h"


namespace IJ
{
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		Animation* CreateAnimationInAnimator(const std::wstring& name
			, class Texture* texture
			, Vector2 leftTop, Vector2 size, UINT spriteLength
			, Vector2 offset = Vector2::Zero, float duration = 0.05f);

		void CreateAnimationFolder(const std::wstring& name
			, const std::wstring& path
			, Vector2 offset = Vector2::Zero, float duration = 0.05f);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = false);
		bool IsActavatedAnimationComplete() { return myActivatedAnimation->IsComplete(); }

		bool GetDrawOnCamera() { return isDrawOnCamera; }
		void SetDrawOnCamera(bool value) { isDrawOnCamera = value; }
		Vector2 GetScale() { return myScale; }
		void SetScale(Vector2 scale) { myScale = scale; }
		float GetAlpha() { return myAlpha; }
		void SetAlpha(float alpha) { myAlpha = alpha; }

	private:
		std::map<std::wstring, Animation*> myAnimations;

		Animation* myActivatedAnimation;
		Vector2 myScale;
		bool isLoop;
		bool isDrawOnCamera;
		float myAlpha;
	};
}
