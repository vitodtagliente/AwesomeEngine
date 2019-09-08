#pragma once

#include <memory>
#include <awesome/core/string_id.h>
#include <awesome/math/transform.h>

namespace awesome
{
	class Actor
	{
	public:

		enum class State
		{
			Unknown,
			Normal,
			PendingDestroy
		};

		// get the id
		inline const StringId& getId() const { return m_id; }
		// get object state
		inline State getState() const { return m_state; }

	private:

		// actor id
		StringId m_id;
		// actor transform
		transform m_transform;
		// parent actor
		std::weak_ptr<Actor> m_parent;
		// actor state
		State m_state;
	};
}