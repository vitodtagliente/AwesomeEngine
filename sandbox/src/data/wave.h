/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/prefab_asset.h>
#include <awesome/core/reflection.h>

#include "wave_generated.h"

CLASS(Category = Data)
class Wave : public IType
{
public:
	PROPERTY() std::string name;
	PROPERTY() std::string description;
	PROPERTY() PrefabAssetPtr minionPrefab;
	PROPERTY() int quantity{ 1 };
	PROPERTY() double startSpawnDelay{ 0 };
	PROPERTY() double perSpawnDelay{ 1 };

	GENERATED_BODY()
};