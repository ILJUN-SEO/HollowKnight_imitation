#pragma once
#include "IJ_Entity.h"


namespace IJ
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		std::wstring& GetPath() { return myPath; }
		void SetPath(const std::wstring& path) { myPath = path; }

	private:
		std::wstring myPath;
	};
}
