#pragma once

namespace ECS
{
	template <class T>
	class Component
	{
	public:

		Component() = default;
		virtual ~Component() = default;

		inline bool operator== (const Component& t_component) const { return false; }
		inline bool operator!= (const Component& t_component) const { return false; }

	};
}