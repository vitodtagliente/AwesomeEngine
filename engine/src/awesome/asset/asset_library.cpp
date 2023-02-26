#include "asset_library.h"

#include <thread>

#include "image_asset.h"
#include "prefab_asset.h"

void AssetLibrary::init(const std::filesystem::path& path)
{
	m_path = path;
	const std::filesystem::path db_path = path / AssetDatabase::Filename;
	database.load(db_path);

	// register the handlers
	m_handlers.push_back(AssetHandler{
		[]() ->AssetPtr { return std::make_shared<ImageAsset>(); },
		{ ".png", ".bmp", ".jpg", ".jpeg" },
		"ImageAsset",
		AssetType_Image
	});
	m_handlers.push_back(AssetHandler{
		[]() ->AssetPtr { return std::make_shared<PrefabAsset>(); },
		{ ".prefab" },
		"PrefabAsset",
		AssetType_Prefab
	});
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