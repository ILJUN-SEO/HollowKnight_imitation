#include "IJ_CollisionManager.h"
#include "IJ_Scene.h"
#include "IJ_SceneManager.h"


namespace IJ
{
	std::map<UINT64, bool> CollisionManager::myCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::myLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{}

	void CollisionManager::Update()
	{
		Scene* activatedScene = SceneManager::GetActivatedScene();
		for (UINT row = 0; row < LAYER_MAX; row++)
		{
			for (UINT col = 0; col < LAYER_MAX; col++)
			{
				if (myLayerMasks[row][col] == true)
					LayerCollision(activatedScene, (myLayerType)row, (myLayerType)col);
			}
		}
	}

	void CollisionManager::Render(HDC hdc)
	{}

	void CollisionManager::Release()
	{}


	void CollisionManager::Clear()
	{
		myLayerMasks->reset();
		myCollisionMap.clear();
	}

	void CollisionManager::CollisionLayerCheck(myLayerType leftLayerType, myLayerType rightLayerType, bool value)
	{
		int row = -1;
		int col = -1;

		if (leftLayerType > rightLayerType)
		{
			row = (UINT)leftLayerType;
			col = (UINT)rightLayerType;
		}
		else
		{
			row = (UINT)rightLayerType;
			col = (UINT)leftLayerType;
		}

		myLayerMasks[row][col] = value;
	}

	void CollisionManager::LayerCollision(Scene* scene, myLayerType leftLayerType, myLayerType rightLayerType)
	{
		Layer& leftLayer = scene->GetLayer(leftLayerType);
		std::vector<GameObject*>& leftLayersGameObjects = leftLayer.GetGameObjects();

		Layer& rightLayer = scene->GetLayer(rightLayerType);
		std::vector<GameObject*>& rightLayersGameObjects = rightLayer.GetGameObjects();

		for (GameObject* left : leftLayersGameObjects)
		{
			Collider* leftCollider = left->GetComponent<Collider>();
			if (leftCollider == nullptr)
				continue;

			for (GameObject* right : rightLayersGameObjects)
			{
				Collider* rightCollider = right->GetComponent<Collider>();
				if (rightCollider == nullptr || leftCollider == rightCollider)
					continue;

				ColliderCollision(leftCollider, rightCollider);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* leftCollider, Collider* rightCollider)
	{
		ColliderID ID;
		ID.left = (UINT)leftCollider->GetCollisionID();
		ID.right = (UINT)rightCollider->GetCollisionID();

		std::map<UINT64, bool>::iterator iter = myCollisionMap.find(ID.id);

		if (iter == myCollisionMap.end())
		{
			myCollisionMap.insert(std::make_pair(ID.id, false));
			iter = myCollisionMap.find(ID.id);
		}

		if (Intersect(leftCollider, rightCollider))
		{
			if (iter->second == false)
			{
				leftCollider->OnCollisionEnter(rightCollider);
				rightCollider->OnCollisionEnter(leftCollider);

				iter->second = true;
			}
			else
			{
				leftCollider->OnCollisionStay(rightCollider);
				rightCollider->OnCollisionStay(leftCollider);
			}
		}
		else
		{
			if (iter->second == true)
			{
				leftCollider->OnCollisionExit(rightCollider);
				rightCollider->OnCollisionExit(leftCollider);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* leftcollider, Collider* rightcollider)
	{
		Vector2 leftPosition = leftcollider->GetPosition();
		Vector2 rightPosition = rightcollider->GetPosition();

		Vector2 leftSize = leftcollider->GetSize();
		Vector2 rightSize = rightcollider->GetSize();

		if (fabs(leftPosition.x - rightPosition.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPosition.y - rightPosition.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
			return true;

		return false;
	}
}