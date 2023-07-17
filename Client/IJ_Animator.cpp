#include "IJ_Animator.h"
#include "IJ_ResourceManager.h"
#include "IJ_Texture.h"


namespace IJ
{
	Animator::Animator()
		: Component(myComponentType::Animator)
		, myAlpha(1.0f)
	{}

	Animator::~Animator()
	{}

	void Animator::Initialize()
	{}

	void Animator::Update()
	{
		if (myActivatedAnimation)
		{
			myActivatedAnimation->Update();
			if (myActivatedAnimation->IsComplete() && isLoop)
				myActivatedAnimation->Reset();
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (myActivatedAnimation)
			myActivatedAnimation->Render(hdc);
	}

	void Animator::CreateAnimation(const std::wstring& name
		, Texture* texture
		, Vector2 leftTop, Vector2 size
		, UINT spriteLength, Vector2 offset
		, float duration)
	{
		Animation* animation = nullptr;
		animation = ResourceManager::Find<Animation>(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->CreateAnimation(name, texture
			, leftTop, size, offset
			, spriteLength, duration);
		animation->SetAnimator(this);

		myAnimations.insert(std::make_pair(name, animation));
		ResourceManager::Insert<Animation>(name, animation);
	}

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring& path, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCout = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> textures = {};
		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			std::wstring fullName = p.path();

			Texture* texture = ResourceManager::Load<Texture>(fileName, fullName);
			textures.push_back(texture);

			if (width < texture->GetWidth())
				width = texture->GetWidth();

			if (height < texture->GetHeight())
				height = texture->GetHeight();

			fileCout++;
		}

		Texture* spriteSheet = Texture::CreateTexture(name, width * fileCout, height);

		int idx = 0;
		for (Texture* texture : textures)
		{
			BitBlt(spriteSheet->GetHDC(), width * idx, 0
				, texture->GetWidth(), texture->GetHeight()
				, texture->GetHDC(), 0, 0, SRCCOPY);

			idx++;
		}

		CreateAnimation(name
			, spriteSheet, Vector2(0.0f, 0.0f)
			, Vector2(width, height), fileCout
			, offset, duration);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = myAnimations.find(name);
		if (iter == myAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr || myActivatedAnimation == animation)
			return;

		myActivatedAnimation = animation;
		myActivatedAnimation->Reset();
		isLoop = loop;
	}
}