/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

#include "wave_generated.h"

ENUM()
enum class SpawnType
{
	AroundPosition,
	AtPosition
};

CLASS(Category = Data)
class Wave : public IType
{
public:
	PROPERTY() std::string name;
	PROPERTY() std::string description;
	PROPERTY() PrefabAssetPtr minionPrefab;
	PROPERTY() int quantity{ 1 };
	PROPERTY() double perSpawnDelay{ 1 };
	PROPERTY() SpawnType spawnType{ SpawnType::AroundPosition };
	PROPERTY() math::vec3 spawnPosition{ math::vec3::zero };
	PROPERTY() math::vec2 spawnRange{ math::vec2::zero };
	PROPERTY() double startSpawnDelay{ 0 };

	GENERATED_BODY()
};