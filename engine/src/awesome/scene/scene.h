#pragma once

#include <vector>
#include <awesome/data/string_id.h>

namespace awesome
{
	class Object;

	struct Scene
	{
	public:

		Scene()
			: name()
			, objects()
		{

		}

		StringId name;
		std::vector<Object*> objects;
	};
}