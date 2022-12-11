// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "item.h"

const char* EnumType<ItemCategory>::name() { return "ItemCategory"; }
const enum_values_t& EnumType<ItemCategory>::values()
{
    static enum_values_t s_values{
        { "Consumable", static_cast<int>(ItemCategory::Consumable) }, 
        { "Currency", static_cast<int>(ItemCategory::Currency) }, 
        { "Equipment", static_cast<int>(ItemCategory::Equipment) }, 
        { "Resource", static_cast<int>(ItemCategory::Resource) }, 
        { "Valuable", static_cast<int>(ItemCategory::Valuable) }, 
    };
    return s_values;
}

const char* EnumType<EquipmentPositionType>::name() { return "EquipmentPositionType"; }
const enum_values_t& EnumType<EquipmentPositionType>::values()
{
    static enum_values_t s_values{
        { "Invalid", static_cast<int>(EquipmentPositionType::Invalid) }, 
        { "Armor", static_cast<int>(EquipmentPositionType::Armor) }, 
        { "Boots", static_cast<int>(EquipmentPositionType::Boots) }, 
        { "Helmet", static_cast<int>(EquipmentPositionType::Helmet) }, 
        { "Weapon", static_cast<int>(EquipmentPositionType::Weapon) }, 
    };
    return s_values;
}

const char* EnumType<ConsumableEffectType>::name() { return "ConsumableEffectType"; }
const enum_values_t& EnumType<ConsumableEffectType>::values()
{
    static enum_values_t s_values{
        { "Invalid", static_cast<int>(ConsumableEffectType::Invalid) }, 
        { "Heal", static_cast<int>(ConsumableEffectType::Heal) }, 
    };
    return s_values;
}

const meta_t& ConsumableItemData::getTypeMeta() const { return ConsumableItemDataType::type().meta; }
const std::string& ConsumableItemData::getTypeName() const { return ConsumableItemDataType::type().name; }
const properties_t ConsumableItemData::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("effectType", Property("effectType", Property::TypeDescriptor("ConsumableEffectType", Property::Type::T_custom_enum, Property::DecoratorType::D_normalized, {}), sizeof(ConsumableEffectType), origin + offsetof(ConsumableItemData, effectType), {
    })));
    return properties;
}
std::size_t ConsumableItemData::getTypeSize() const { return ConsumableItemDataType::type().size; }

const TypeDefinition& ConsumableItemDataType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new ConsumableItemData(); }, "ConsumableItemData", {
        std::make_pair("Category", "Data"),
    }, sizeof(ConsumableItemData));
    return s_typeDefinition;
}
const meta_t& EquipmentItemData::getTypeMeta() const { return EquipmentItemDataType::type().meta; }
const std::string& EquipmentItemData::getTypeName() const { return EquipmentItemDataType::type().name; }
const properties_t EquipmentItemData::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("positionType", Property("positionType", Property::TypeDescriptor("EquipmentPositionType", Property::Type::T_custom_enum, Property::DecoratorType::D_normalized, {}), sizeof(EquipmentPositionType), origin + offsetof(EquipmentItemData, positionType), {
    })));
    return properties;
}
std::size_t EquipmentItemData::getTypeSize() const { return EquipmentItemDataType::type().size; }

const TypeDefinition& EquipmentItemDataType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new EquipmentItemData(); }, "EquipmentItemData", {
        std::make_pair("Category", "Data"),
    }, sizeof(EquipmentItemData));
    return s_typeDefinition;
}
const meta_t& Item::getTypeMeta() const { return ItemType::type().meta; }
const std::string& Item::getTypeName() const { return ItemType::type().name; }
const properties_t Item::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("id", Property("id", Property::TypeDescriptor("uuid", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(uuid), origin + offsetof(Item, id), {
    })));
    properties.insert(std::make_pair<std::string, Property>("name", Property("name", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(Item, name), {
    })));
    properties.insert(std::make_pair<std::string, Property>("category", Property("category", Property::TypeDescriptor("ItemCategory", Property::Type::T_custom_enum, Property::DecoratorType::D_normalized, {}), sizeof(ItemCategory), origin + offsetof(Item, category), {
    })));
    properties.insert(std::make_pair<std::string, Property>("description", Property("description", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(Item, description), {
    })));
    properties.insert(std::make_pair<std::string, Property>("icon", Property("icon", Property::TypeDescriptor("SpriteAssetPtr", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(SpriteAssetPtr), origin + offsetof(Item, icon), {
    })));
    properties.insert(std::make_pair<std::string, Property>("quantityLimit", Property("quantityLimit", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(Item, quantityLimit), {
    })));
    properties.insert(std::make_pair<std::string, Property>("stackable", Property("stackable", Property::TypeDescriptor("bool", Property::Type::T_bool, Property::DecoratorType::D_normalized, {}), sizeof(bool), origin + offsetof(Item, stackable), {
    })));
    properties.insert(std::make_pair<std::string, Property>("consumableData", Property("consumableData", Property::TypeDescriptor("ConsumableItemData", Property::Type::T_custom_type, Property::DecoratorType::D_unique_ptr, {}), sizeof(std::unique_ptr<ConsumableItemData>), origin + offsetof(Item, consumableData), {
    })));
    properties.insert(std::make_pair<std::string, Property>("equipmentData", Property("equipmentData", Property::TypeDescriptor("EquipmentItemData", Property::Type::T_custom_type, Property::DecoratorType::D_unique_ptr, {}), sizeof(std::unique_ptr<EquipmentItemData>), origin + offsetof(Item, equipmentData), {
    })));
    return properties;
}
std::size_t Item::getTypeSize() const { return ItemType::type().size; }

const TypeDefinition& ItemType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new Item(); }, "Item", {
        std::make_pair("Category", "Data"),
    }, sizeof(Item));
    return s_typeDefinition;
}
