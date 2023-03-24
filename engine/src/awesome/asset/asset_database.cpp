#include "asset_database.h"

#include "asset.h"

#include <awesome/data/json_file.h>
#include <awesome/encoding/json.h>

bool AssetDatabase::erase(const uuid& id)
{
	const auto& it = std::find_if(
		records.begin(),
		records.end(),
		[&id](const AssetRecord& record) -> bool
		{
			return record.id == id;
		}
	);
	return records.erase(it), true;
}

bool AssetDatabase::exists(const uuid& id) const
{
	const auto& it = std::find_if(
		records.begin(),
		records.end(),
		[&id](const AssetRecord& record) -> bool
		{
			return record.id == id;
		}
	);

	return (it != records.end());
}

bool AssetDatabase::exists(const std::filesystem::path& _path) const
{
	const std::filesystem::path compare = _path.extension().string() == Asset::Extension ? _path.parent_path() / _path.stem() : _path;
	const auto& it = std::find_if(
		records.begin(),
		records.end(),
		[&compare](const AssetRecord& record) -> bool
		{
			return record.path == compare;
		}
	);

	return (it != records.end());
}

const AssetRecord* const AssetDatabase::find(const uuid& id) const
{
	const auto& it = std::find_if(
		records.begin(),
		records.end(),
		[&id](const AssetRecord& record) -> bool
		{
			return record.id == id;
		}
	);

	if (it != records.end())
	{
		return &(*it);
	}
	return nullptr;
}

const AssetRecord* const AssetDatabase::find(const std::filesystem::path& _path) const
{
	const std::filesystem::path compare = _path.extension().string() == Asset::Extension ? _path.parent_path() / _path.stem() : _path;
	const auto& it = std::find_if(
		records.begin(),
		records.end(),
		[&compare](const AssetRecord& record) -> bool
		{
			return record.path == compare;
		}
	);

	if (it != records.end())
	{
		return &(*it);
	}
	return nullptr;
}

bool AssetDatabase::insert(const AssetRecord& record)
{
	return records.push_back(record), true;
}

void AssetDatabase::save() const
{
	json::value data = json::array();
	for (const AssetRecord& record : records)
	{
		data.push_back(json::object({
			{"id", static_cast<std::string>(record.id)},
			{"path", record.path.string()},
			{"type", record.type}
			})
		);
	}
	JsonFile::save(data, path);
}

bool AssetDatabase::load(const std::filesystem::path& _path)
{
	path = _path;
	if (!std::filesystem::exists(_path)) return false;

	json::value data;
	if (!JsonFile::load(path, data)) return false;

	// for (const auto& elem : data.as_array())
	// {
	// 	AssetRecord record;
	// 	// record.id = elem["id"].as_string();
	// 	record.path = elem["path"].as_string();
	// 	record.type = elem["type"].as_number().as_int();
	// 	records.push_back(record);
	// }
	return true;
}

void AssetRecord::save(const std::filesystem::path& _path)
{
	JsonFile::save(json::object({
			{"id", static_cast<std::string>(id)},
			{"type", type}
		}),
		_path
	);
}