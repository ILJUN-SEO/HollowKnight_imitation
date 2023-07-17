#pragma once
#include "CommonInclude.h"

namespace IJ
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { myName = name; }
		std::wstring& GetName() { return myName; }

	private:
		std::wstring myName;
	};
}
