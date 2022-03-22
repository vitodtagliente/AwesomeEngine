/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <optional>
#include <variant>
#include <string>

#include <awesome/core/singleton.h>
#include <awesome/entity/entity.h>

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
			Selection(const std::filesystem::path& file);

			Type type;
			std::variant<Entity*, std::filesystem::path> data;
		};

		SelectionSystem();

		void select(Entity* entity);
		void select(const std::filesystem::path& file);
		void unselect();

		const std::optional<Selection>& getSelection() const { return m_selection; }
		inline bool hasSelection() const { return m_selection.has_value(); }

	private:
		std::optional<Selection> m_selection;
	};
}