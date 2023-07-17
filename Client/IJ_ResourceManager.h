#pragma once
#include "IJ_Resource.h"


namespace IJ
{
	class ResourceManager
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& name)
		{
			auto iter = myResources.find(name);

			if (iter == myResources.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* resource = ResourceManager::Find<T>(name);

			if (resource != nullptr)
				return resource;

			resource = new T();

			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;

				return nullptr;
			}

			resource->SetName(name);
			resource->SetPath(path);
			myResources.insert(std::make_pair(name, resource));

			return resource;
		}

		template <typename T>
		static void Insert(const std::wstring& name, T* resource)
		{
			resource->SetName(name);
			myResources.insert(std::make_pair(name, resource));
		}

	private:
		static std::map<std::wstring, Resource*> myResources;
	};
}
