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

	// register the handlers
	for (const auto& [name, options] : TypeFactory::list("Type", "AssetHandler"))
	{
		std::unique_ptr<AssetHandler> handler = std::unique_ptr<AssetHandler>(TypeFactory::instantiate<AssetHandler>(name));
		if (handler != nullptr)
		{
			m_handlers.push_back(*handler);
		}
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
	if (cacheIt != m_cache.end() && !cacheIt->second.expired())
	{
		return cacheIt->second.asset.lock();
	}

	const AssetRecord* const record = database.find(id);
	if (record == nullptr || record->id == uuid::Invalid)
	{
		return nullptr;
	}

	const AssetHandler* const handler = findHandler(record->path);
	if (handler == nullptr)
	{
		return nullptr;
	}

	AssetPtr asset = create(*handler, *record);
	if (asset != nullptr)
	{
		m_cache.insert(std::make_pair(asset->id, Slot(asset)));
	}
	return asset;
}

const AssetHandler* const AssetLibrary::findHandler(const std::filesystem::path& path) const
{
	const auto& it = std::find_if(
		m_handlers.begin(),
		m_handlers.end(),
		[extension = path.extension().string()](const AssetHandler& handler) -> bool
		{
			return std::find(handler.extensions.begin(), handler.extensions.end(), extension) != handler.extensions.end();
		}
	);

	if (it != m_handlers.end())
	{
		return &(*it);
	}
	return nullptr;
}

std::shared_ptr<Asset> AssetLibrary::create(const AssetHandler& handler, const AssetRecord& record)
{
	const std::filesystem::path assetPath = record.path.string() + Asset::Extension;
	if (!std::filesystem::exists(record.path)
		|| !std::filesystem::exists(assetPath))
	{
		return nullptr;
	}

	AssetPtr asset = handler.create();
	if (asset != nullptr)
	{
		asset->path = record.path;
		asset->state = Asset::State::Loading;
		std::thread thread([path = record.path, asset]()
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
		thread.detach();
		return asset;
	}
	return nullptr;
}