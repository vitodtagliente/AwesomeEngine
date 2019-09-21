#pragma once

#include "component.h"

namespace ECS
{
	class LogicComponent : public Component
	{
	public:

		LogicComponent()
			: Component()
		{

		}
		virtual ~LogicComponent() = default;

	};
}