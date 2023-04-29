#include "asset_library.h"

#include "asset.h"

void AssetLibrary::init(const EngineMode mode, const std::filesystem::path& path)
{
	m_path = path;
	database.path = path / AssetDatabase::Filename;
	if (mode != EngineMode::Editor)
	{
		database.load(database.path);
	}

	for (const auto& [name, options] : TypeFactory::list("Type", "AssetLoader"))
	{
		std::unique_ptr<AssetLoader> loader = std::unique_ptr<AssetLoader>(TypeFactory::instantiate<AssetLoader>(name));
		if (loader != nullptr)
		{
			m_loaders.push_back(std::move(loader));
		}
	}
}