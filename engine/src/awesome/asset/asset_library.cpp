#include "asset_library.h"

#include <thread>

void AssetLibrary::init(const EngineMode mode, const std::filesystem::path& path)
{
	m_path = path;
	database.path = path / AssetDatabase::Filename;
	if (mode != EngineMode::Editor)
	{
		database.load(database.path);
	}
}