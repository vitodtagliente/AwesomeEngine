/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>
#include <variant>
#include <string>

#include <awesome/core/singleton.h>
#include <awesome/entity/entity.h>

#include "file.h"

namespace editor
{
	class SelectionSystem : public Singleton<SelectionSystem>
	{
	public:

		struct Selection
		{
			enum class Type
			{
				None,
				Entity,
				File
			};

			Selection();
			Selection(Entity* entity);
			Selection(const File& file);

			Type type;
			std::variant<Entity*, File> data;
		};

		SelectionSystem();

		void select(Entity* entity);
		void select(const File& file);
		void unselect();

		const std::optional<Selection>& getSelection() const { return m_selection; }

	private:
		std::optional<Selection> m_selection;
	};
}