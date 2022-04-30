#include "game.h"

#include <fstream>

#include <awesome/asset/asset_library.h>
#include <awesome/core/serialization.h>
#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>

Game::Settings Game::Settings::load(const std::filesystem::path& path)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	Game::Settings settings;
	json::value data = json::Deserializer::parse(read(path));
	settings.mode = data["mode"].as_string("");
	if (data.contains("scene"))
	{
		const uuid id(data["scene"].as_string());
		settings.scene = AssetLibrary::instance().find<SceneAsset>(id);
	}
	return settings;
}

void Game::Settings::save(const std::filesystem::path& path)
{
	const json::value& data = json::object({
		   {"mode", mode},
		   {"scene", scene ? static_cast<std::string>(scene->descriptor.id) : ""}
		});

	Archive archive(path, Archive::Mode::Write);
	archive << json::Serializer::to_string(data);
}
