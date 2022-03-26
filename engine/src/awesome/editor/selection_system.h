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
				Asset,
				Entity
			};

			Selection();
			Selection(Entity* entity);
			Selection(const std::shared_ptr<Asset>& asset);

			inline Entity* asEntity() const { return std::get<Entity*>(data); }
			inline std::shared_ptr<Asset> asAsset() const { return std::get<std::shared_ptr<Asset>>(data); }

			Type type;
			std::variant<Entity*, std::shared_ptr<Asset>> data;
		};

		SelectionSystem();

		void select(Entity* entity);
		void select(const std::shared_ptr<Asset>& asset);
		void unselect();

		const std::optional<Selection>& getSelection() const { return m_selection; }
		inline bool hasSelection() const { return m_selection.has_value(); }

	private:
		std::optional<Selection> m_selection;
	};
}