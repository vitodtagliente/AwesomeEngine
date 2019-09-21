#pragma once

#include "component.h"

namespace ECS
{
	class DataComponent : public Component
	{
	public:
		
		DataComponent()
			: Component()
		{

		}
		virtual ~DataComponent() = default;

		inline virtual bool operator== (const DataComponent& t_other) const 
		{ 
			return id() == t_other.id();
		}
		inline virtual bool operator!= (const DataComponent& t_other) const
		{
			return id() != t_other.id();
		}

	};
}