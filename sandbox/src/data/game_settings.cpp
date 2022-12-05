#include "game_settings.h"

#include <fstream>

#include <awesome/asset/asset_library.h>
#include <awesome/core/serialization.h>
#include <awesome/data/archive.h>

const std::string GameSettings::filename{ "db.json" };

void GameSettings::load()
{
	static const auto read = [](const std::filesystem::path& path) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(path.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	std::string content = read(AssetLibrary::instance().getDirectory() / GameSettings::filename);
	Deserializer::deserialize(json::Deserializer::parse(content), *this);
}

void GameSettings::save()
{
	Archive archive(AssetLibrary::instance().getDirectory() / GameSettings::filename, Archive::Mode::Write);
	archive << json::Serializer::to_string(Serializer::serialize(*this));
}
