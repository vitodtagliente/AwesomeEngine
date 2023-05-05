#include "asset_database.h"

#include <awesome/data/type_file.h>

#include "asset.h"

AssetRecord& AssetRecord::operator= (const AssetRecord& other)
{
	id = other.id;
	path = other.path;
	type = other.type;
	return *this;
}

bool AssetRecord::operator== (const AssetRecord& other) const
{
	return id == other.id;
}

bool AssetRecord::operator!= (const AssetRecord& other) const
{
	return id != other.id;
}

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
	if (it != records.end())
	{
		records.erase(it);
		return true;
	}
	return false;
}

bool AssetDatabase::erase(const std::filesystem::path& _path)
{
	const auto& it = std::find_if(
		records.begin(),
		records.end(),
		[&_path](const AssetRecord& record) -> bool
		{
			return record.path == _path;
		}
	); 
	if (it != records.end())
	{
		records.erase(it);
		return true;
	}
	return false;
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