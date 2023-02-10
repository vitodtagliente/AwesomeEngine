/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

#include <awesome/asset/scene_asset.h>

class Game final
{
public:

	struct Settings
	{
		static Settings load(const std::filesystem::path& path);
		void save(const std::filesystem::path& path);

		std::string mode;
		SceneAssetPtr scene;
	};

};