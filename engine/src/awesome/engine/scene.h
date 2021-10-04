#pragma once

#include <vector>
#include <awesome/core/string_id.h>

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

		string_id name;
		std::vector<Object*> objects;
	};
}