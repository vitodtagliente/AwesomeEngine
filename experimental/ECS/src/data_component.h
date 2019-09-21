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

	};
}