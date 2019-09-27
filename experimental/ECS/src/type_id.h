#pragma once

#include <functional>

namespace ECS
{
	// generic id data type
	using id_t = size_t;

#define STRINGIFY_TYPE(Type) (#Type)

	template<class T>
	class type
	{
	public:

		static constexpr const char* id = STRINGIFY_TYPE(T);
	};
}