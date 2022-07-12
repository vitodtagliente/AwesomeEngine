/// Copyright (c) Vito Domenico Tagliente
#pragma once

class Entity;

namespace editor
{
	struct EntityLayout final
	{
		EntityLayout() = delete;

		static void input(Entity* const entity);
	};
}