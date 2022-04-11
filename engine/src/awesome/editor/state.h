/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <variant>

#include <awesome/core/singleton.h>
#include <awesome/data/asset.h>
#include <awesome/entity/entity.h>

namespace editor
{
	struct State : public Singleton<State>
	{
		struct Selection
		{
			enum class Type
			{
				None,
				Asset,
				Entity
			};

			Selection();
			Selection(Entity* const entity);
			Selection(const std::shared_ptr<Asset>& asset);

			inline Entity* asEntity() const { return std::get<Entity*>(data); }
			inline std::shared_ptr<Asset> asAsset() const { return std::get<std::shared_ptr<Asset>>(data); }

			Type type;
			std::variant<Entity*, std::shared_ptr<Asset>> data;
		};

		State();

		void select();
		void select(Entity* const entity);
		void select(const std::shared_ptr<Asset>& asset);

		std::optional<Selection> selection;
		std::filesystem::path path;
	};
}