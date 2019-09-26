#pragma once

namespace ECS
{
	// generic id data type
	using id_t = size_t;

	template<typename T>
	struct type
	{
		constexpr static id_t id()
		{
			return reinterpret_cast<id_t>(&type<T>::id);
		}
	};
}