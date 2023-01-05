/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/singleton.h>

#include "game_settings_generated.h"
#include "item.h"

CLASS(Type = Data)
struct WeaponLevel : public Type
{
	PROPERTY() float duration{ 0.f };
	PROPERTY() float efficacy{ 0.f };
	PROPERTY() float frequency{ 0.f };
	PROPERTY() int quantity{ 0 };
	PROPERTY() float range{ 0.f };
	PROPERTY() float speed{ 0.f };

	GENERATED_BODY()
};

CLASS(Type = Data)
struct WeaponItem : public Type
{
	PROPERTY() std::string name;
	PROPERTY() std::string description;
	PROPERTY() std::string component;
	PROPERTY() ImageAssetPtr icon;
	PROPERTY() std::vector<std::unique_ptr<WeaponLevel>> levels;

	GENERATED_BODY()
};

CLASS(Type = Data)
struct GameSettings : public Singleton<GameSettings>, public Type
{
	void load();
	void save();

	static const std::string filename;

	PROPERTY() std::map<std::string, std::unique_ptr<Item>> items;
	PROPERTY() std::map<std::string, std::unique_ptr<WeaponItem>> weapons;
	PROPERTY() std::vector<int> playerProgression;

	GENERATED_BODY()
};