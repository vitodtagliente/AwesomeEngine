#pragma once

namespace ECS
{
	template<typename T>
	struct type
	{
		constexpr static size_t id()
		{
			return reinterpret_cast<size_t>(&type<T>::id);
		}
	};
}