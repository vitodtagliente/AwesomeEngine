#include "game_settings.h"

#include <fstream>

#include <awesome/asset/asset_library.h>
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
	deserialize(json::Deserializer::parse(content));
}

void GameSettings::save()
{
	Archive archive(AssetLibrary::instance().getDirectory() / GameSettings::filename, Archive::Mode::Write);
	archive << json::Serializer::to_string(serialize());
}

json::value GameSettings::serialize() const
{
	json::value data = json::object();
	json::value weaponsData = json::object();
	for (const auto& pair : weapons)
	{
		const WeaponItem& weapon = pair.second;
		json::value weaponData = ::serialize(pair.second);
		json::value levelsData = json::array();
		for (const WeaponLevel& level : weapon.levels)
		{
			levelsData.push_back(::serialize(level));
		}
		weaponData["levels"] = levelsData;
		weaponsData[pair.first] = weaponData;
	}
	data["weapons"] = weaponsData;
	return data;
}

void GameSettings::deserialize(const json::value& value)
{
	const auto& weaponsData = value.safeAt("weapons").as_object({});
	for (const auto& pair : weaponsData)
	{
		WeaponItem weapon;
		::deserialize(pair.second, weapon);
		for (const auto& levelData : pair.second.safeAt("levels").as_array({}))
		{
			WeaponLevel level;
			::deserialize(levelData, level);
			weapon.levels.push_back(level);
		}
		weapons.insert(std::make_pair(pair.first, weapon));
	}
}
