/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/asset/asset.h>
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
			Selection(const AssetPtr& asset);

			inline Entity* asEntity() const { return std::get<Entity*>(data); }
			inline AssetPtr asAsset() const { return std::get<AssetPtr>(data); }

			Type type;
			std::variant<Entity*, AssetPtr> data;
		};

		State();

		void select();
		void select(Entity* const entity);
		void select(const AssetPtr& asset);

		bool hasPendingContentRefresh();

		bool isContentChanged;
		std::filesystem::path path;
		std::optional<Selection> selection;
		bool showWindows{ true };
		std::vector<AssetPtr> history;
	};
}