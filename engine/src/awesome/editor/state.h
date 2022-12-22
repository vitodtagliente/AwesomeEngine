/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>
#include <queue>

#include <awesome/asset/asset.h>
#include <awesome/core/singleton.h>

class State : public Singleton<State>
{
public:
	struct Selection
	{
		Selection() = default;

		void clear();

		AssetPtr asset;
		class Entity* entity{ nullptr };
		std::filesystem::path path;
	};

	State();

	void select();
	void select(class Entity* const entity);
	void select(const AssetPtr& asset);

	bool hasPendingContentRefresh();

	bool isContentChanged;
	std::filesystem::path path;
	Selection selection;
	bool showWindows{ true };

private:
	std::queue<AssetPtr> history;
};