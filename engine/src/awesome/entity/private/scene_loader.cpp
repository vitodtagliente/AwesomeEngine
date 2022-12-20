#include "scene_loader.h"

#include <thread>

void SceneLoader::load(const SceneAssetPtr& asset, const std::function<void(std::vector<std::unique_ptr<Entity>>&)>& callback)
{
	std::thread handler([asset, callback]()
		{
			std::vector<std::unique_ptr<Entity>> entitiesToSpawn;
			const auto& entitiesData = asset->data.value().safeAt("entities").as_array({});
			for (const auto& entityData : entitiesData)
			{
				std::unique_ptr<Entity> entity = std::make_unique<Entity>();
				entity->deserialize(entityData);
				entitiesToSpawn.push_back(std::move(entity));
			}
			callback(entitiesToSpawn);
		}
	);
	handler.detach();
}