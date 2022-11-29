/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/sprite_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/serialization.h>
#include <awesome/core/singleton.h>

#include "game_settings_generated.h"

CLASS(Category = Data)
class WeaponLevel : public IType
{
public:
	PROPERTY() float efficacy{ 0.f };
	PROPERTY() float frequency{ 0.f };
	PROPERTY() int power{ 0 };
	PROPERTY() int quantity{ 0 };
	PROPERTY() float range{ 0.f };
	PROPERTY() float speed{ 0.f };

	GENERATED_BODY()
};

CLASS(Category = Data)
class WeaponItem : public IType
{
public:
	PROPERTY() std::string name;
	PROPERTY() std::string description;
	PROPERTY() std::string component;
	PROPERTY() SpriteAssetPtr icon;
	std::vector<WeaponLevel> levels;

	GENERATED_BODY()
};

CLASS(Category = Data)
class GameSettings : public Singleton<GameSettings>, public ISerializable, public IType
{
public:
	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	static const std::string filename;

	std::map<std::string, WeaponItem> weapons;

	GENERATED_BODY()
};