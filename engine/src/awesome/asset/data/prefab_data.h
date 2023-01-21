/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

#include "prefab_data_generated.h"

CLASS(Type = Data, AssetType = Prefab)
struct PrefabData : public Type
{
	PROPERTY() json::value entity;
	PROPERTY() std::string note;

	GENERATED_BODY()
};