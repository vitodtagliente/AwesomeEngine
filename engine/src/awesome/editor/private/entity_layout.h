/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/entity/entity.h>

namespace editor
{
	struct EntityLayout final
	{
		EntityLayout() = delete;

		static void input(Entity& entity);
	};
}