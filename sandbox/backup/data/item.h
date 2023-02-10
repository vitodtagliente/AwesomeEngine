/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/core/reflection.h>

#include "item_generated.h"

ENUM()
enum class ItemCategory : int
{
	Consumable,
	Currency,
	Equipment,
	Resource,
	Valuable
};

ENUM()
enum class EquipmentPositionType : int
{
	Invalid,
	Armor,
	Boots,
	Helmet,
	Weapon
};

ENUM()
enum class ConsumableEffectType : int
{
	Invalid,
	Heal
};

CLASS(Type = Data)
struct ConsumableItemData : public Type
{
	PROPERTY() ConsumableEffectType effectType { ConsumableEffectType::Invalid };

	GENERATED_BODY()
};

CLASS(Type = Data)
struct EquipmentItemData : public Type
{
	PROPERTY() EquipmentPositionType positionType { EquipmentPositionType::Invalid };

	GENERATED_BODY()
};

CLASS(Type = Data)
struct Item : public Type
{
	PROPERTY() uuid id;
	PROPERTY() std::string name;
	PROPERTY() ItemCategory category { ItemCategory::Valuable };
	PROPERTY() std::string description;
	PROPERTY() ImageAssetPtr icon;
	PROPERTY() int quantityLimit{ 999 };
	PROPERTY() bool stackable{ true };
	PROPERTY() std::unique_ptr<ConsumableItemData> consumableData;
	PROPERTY() std::unique_ptr<EquipmentItemData> equipmentData;

	GENERATED_BODY()
};