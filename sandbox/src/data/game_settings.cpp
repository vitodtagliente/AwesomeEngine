#include "game_settings.h"

const std::string GameSettings::filename{ "db.json" };

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
}
