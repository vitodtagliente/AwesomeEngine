#pragma once

#include <functional>

namespace ECS
{
	namespace detail {

		/**
		 * Template class that hold the declaration of the id.
		 *
		 * We use the pointer of this id as type id.
		 */

		template<typename T>
		struct type_id_ptr {
			// Having a static data member will ensure (I hope) that it has only one address for the whole program.
			// Furthermore, the static data member having different types will ensure (I hope) it won't get optimized.
			static constexpr bool existance = true;
		};

	} // namespace detail

	/**
	 * The type of a type id.
	 */

	using id_t = size_t;



	/**
	 * The function that returns the type id.
	 *
	 * It uses the pointer to the static data member of a class template to achieve this.
	 * Altough the value is not predictible, it's stable (I hope).
	 */

	template <typename T>
	constexpr auto type_id() noexcept -> const void* {
		return &detail::type_id_ptr<T>::existance;
	}
}