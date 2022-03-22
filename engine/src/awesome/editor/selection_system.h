/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <variant>
#include <string>

#include <awesome/core/singleton.h>
#include <awesome/data/asset.h>
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
			Selection(std::shared_ptr<Asset> asset);

			Type type;
			std::variant<Entity*, std::shared_ptr<Asset>> data;
		};

		SelectionSystem();

		void select(Entity* entity);
		void select(std::shared_ptr<Asset> asset);
		void unselect();

		const std::optional<Selection>& getSelection() const { return m_selection; }
		inline bool hasSelection() const { return m_selection.has_value(); }

	private:
		std::optional<Selection> m_selection;
	};
}