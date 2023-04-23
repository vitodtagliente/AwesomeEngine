#include "asset_database.h"

#include <awesome/data/type_file.h>

#include "asset.h"

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
	TypeFile::save(*this, path);
}

bool AssetDatabase::load(const std::filesystem::path& _path)
{
	path = _path;
	if (!std::filesystem::exists(_path)) return false;

	return TypeFile::load(_path, *this);
}

void AssetRecord::save(const std::filesystem::path& _path)
{
	TypeFile::save(*this, _path);
}