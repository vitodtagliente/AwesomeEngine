#pragma once

#include "icomponent.h"

namespace ECS
{
	class DataComponent : public IComponent
	{
	public:
		
		DataComponent()
			: IComponent()
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