#pragma once

namespace ECS
{
	class IComponent
	{
	public:

		using Id = size_t;

		IComponent()
			: m_id(id_counter++)
		{

		}
		virtual ~IComponent() = default;

		Id id() const { return m_id; }

	private:

		static Id id_counter;

		// component id
		Id m_id;

	};

	IComponent::Id IComponent::id_counter = 0;
}