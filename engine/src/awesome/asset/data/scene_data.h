/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

#include "scene_data_generated.h"

CLASS(Type = Data)
struct SceneSettingsData : public Type
{
	PROPERTY() float quandspacebounds{ 100.f };

	GENERATED_BODY()
};

CLASS(Type = Data, AssetType = Scene)
struct SceneData : public Type
{
	PROPERTY() std::vector<json::value> entities;
	PROPERTY() std::string note;
	PROPERTY() std::unique_ptr<SceneSettingsData> settings;

	GENERATED_BODY()
};