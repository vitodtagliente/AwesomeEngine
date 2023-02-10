#include "asset_library.h"

#include <thread>

#include <awesome/data/json_file.h>

void AssetLibrary::init(const std::filesystem::path path)
{
	m_directory = path;
	const std::filesystem::path db_path = path / AssetDatabase::Filename;
	JsonFile::load(db_path, database);
}

void AssetLibrary::flush()
{
	if (database.dirty)
	{
		const std::filesystem::path db_path = m_directory / AssetDatabase::Filename;
		JsonFile::save(database, db_path);
		database.dirty = false;
	}
}

void AssetLibrary::release(const AssetPtr& asset)
{
	if (asset != nullptr)
	{
		release(asset->id);
	}
}

void AssetLibrary::release(const uuid& id)
{
	m_cache.erase(id);
}

std::shared_ptr<Asset> AssetLibrary::find(const uuid& id)
{
	const auto& cacheIt = m_cache.find(id);
	if (cacheIt != m_cache.end() && !cacheIt->second.isExpired())
	{
		return cacheIt->second.asset.lock();
	}

	AssetRecord* const record = database.find(id);
	if (record == nullptr || record->id == uuid::Invalid)
	{
		return nullptr;
	}

	std::shared_ptr<Asset> asset = create(record->path);
	if (asset != nullptr)
	{
		m_cache.insert(std::make_pair(asset->id, Slot(asset)));
	}
	return asset;
}

std::shared_ptr<Asset> AssetLibrary::create(const std::filesystem::path& path)
{
	const std::filesystem::path assetPath = path.string() + Asset::Extension;
	if (!std::filesystem::exists(path)
		|| !std::filesystem::exists(assetPath))
	{
		return nullptr;
	}

	Asset* data = nullptr;
	JsonFile::load(assetPath, (Type**)&data, "Asset");

	if (data != nullptr)
	{
		AssetPtr asset = std::shared_ptr<Asset>(data);
		asset->path = path;
		asset->state = Asset::State::Loading;
		std::thread handler([path, asset]()
			{
				if (asset->load(path))
				{
					asset->state = Asset::State::Ready;
					if (asset->onLoad) asset->onLoad();
				}
				else
				{
					asset->state = Asset::State::Error;
				}
			}
		);
		handler.detach();
		return asset;
	}
	return nullptr;
}

bool AssetDatabase::erase(const uuid& id)
{
	const auto& it = std::find_if(records.begin(), records.end(),
		[&id](const std::unique_ptr<AssetRecord>& record) -> bool
		{
			return record->id == id;
		}
	);
	dirty = it != records.end();
	return records.erase(it), true;
}

bool AssetDatabase::exists(const uuid& id) const
{
	const auto& it = std::find_if(records.begin(), records.end(),
		[&id](const std::unique_ptr<AssetRecord>& record) -> bool
		{
			return record->id == id;
		}
	);

	return (it != records.end());
}

bool AssetDatabase::exists(const std::filesystem::path& path) const
{
	const std::filesystem::path compare = path.extension().string() == Asset::Extension ? path.parent_path() / path.stem() : path;
	const auto& it = std::find_if(records.begin(), records.end(),
		[&compare](const std::unique_ptr<AssetRecord>& record) -> bool
		{
			return record->path == compare;
		}
	);

	return (it != records.end());
}

AssetRecord* const AssetDatabase::find(const uuid& id) const
{
	const auto& it = std::find_if(records.begin(), records.end(),
		[&id](const std::unique_ptr<AssetRecord>& record) -> bool
		{
			return record->id == id;
		}
	);

	if (it != records.end())
	{
		return (*it).get();
	}
	return nullptr;
}

AssetRecord* const AssetDatabase::find(const std::filesystem::path& path) const
{
	const std::filesystem::path compare = path.extension().string() == Asset::Extension ? path.parent_path() / path.stem() : path;
	const auto& it = std::find_if(records.begin(), records.end(),
		[&compare](const std::unique_ptr<AssetRecord>& record) -> bool
		{
			return record->path == compare;
		}
	);

	if (it != records.end())
	{
		return (*it).get();
	}
	return nullptr;
}

bool AssetDatabase::insert(const uuid& id, const std::filesystem::path& path, const std::string& type)
{
	std::unique_ptr<AssetRecord> record = std::make_unique<AssetRecord>();
	record->id = id;
	record->path = path;
	record->type = type;
	dirty = true;
	return records.push_back(std::move(record)), true;
}