// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "game_settings.h"

const meta_t& WeaponLevel::getTypeMeta() const { return __WeaponLevelType::type().meta; }
const std::string& WeaponLevel::getTypeName() const { return __WeaponLevelType::type().name; }
const properties_t WeaponLevel::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("duration", Property("duration", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(WeaponLevel, duration), {
    })));
    properties.insert(std::make_pair<std::string, Property>("efficacy", Property("efficacy", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(WeaponLevel, efficacy), {
    })));
    properties.insert(std::make_pair<std::string, Property>("frequency", Property("frequency", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(WeaponLevel, frequency), {
    })));
    properties.insert(std::make_pair<std::string, Property>("quantity", Property("quantity", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(WeaponLevel, quantity), {
    })));
    properties.insert(std::make_pair<std::string, Property>("range", Property("range", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(WeaponLevel, range), {
    })));
    properties.insert(std::make_pair<std::string, Property>("speed", Property("speed", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(WeaponLevel, speed), {
    })));
    return properties;
}
std::size_t WeaponLevel::getTypeSize() const { return __WeaponLevelType::type().size; }
const meta_t& WeaponLevel::staticTypeMeta() { return __WeaponLevelType::type().meta; }
const std::string& WeaponLevel::staticTypeName() { return __WeaponLevelType::type().name; }

const TypeDefinition& __WeaponLevelType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new WeaponLevel(); }, "WeaponLevel", {
        std::make_pair("Type", "Data"),
    }, sizeof(WeaponLevel));
    return s_typeDefinition;
}
const meta_t& WeaponItem::getTypeMeta() const { return __WeaponItemType::type().meta; }
const std::string& WeaponItem::getTypeName() const { return __WeaponItemType::type().name; }
const properties_t WeaponItem::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("name", Property("name", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(WeaponItem, name), {
    })));
    properties.insert(std::make_pair<std::string, Property>("description", Property("description", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(WeaponItem, description), {
    })));
    properties.insert(std::make_pair<std::string, Property>("component", Property("component", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(WeaponItem, component), {
    })));
    properties.insert(std::make_pair<std::string, Property>("icon", Property("icon", Property::TypeDescriptor("ImageAssetPtr", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(ImageAssetPtr), origin + offsetof(WeaponItem, icon), {
    })));
    properties.insert(std::make_pair<std::string, Property>("levels", Property("levels", Property::TypeDescriptor("std::vector<std::unique_ptr<WeaponLevel>>", Property::Type::T_container_vector, Property::DecoratorType::D_normalized, {Property::TypeDescriptor("WeaponLevel", Property::Type::T_custom_type, Property::DecoratorType::D_unique_ptr, {})}), sizeof(std::vector<std::unique_ptr<WeaponLevel>>), origin + offsetof(WeaponItem, levels), {
    })));
    return properties;
}
std::size_t WeaponItem::getTypeSize() const { return __WeaponItemType::type().size; }
const meta_t& WeaponItem::staticTypeMeta() { return __WeaponItemType::type().meta; }
const std::string& WeaponItem::staticTypeName() { return __WeaponItemType::type().name; }

const TypeDefinition& __WeaponItemType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new WeaponItem(); }, "WeaponItem", {
        std::make_pair("Type", "Data"),
    }, sizeof(WeaponItem));
    return s_typeDefinition;
}
const meta_t& GameSettings::getTypeMeta() const { return __GameSettingsType::type().meta; }
const std::string& GameSettings::getTypeName() const { return __GameSettingsType::type().name; }
const properties_t GameSettings::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("items", Property("items", Property::TypeDescriptor("std::map<std::string, std::unique_ptr<Item>>", Property::Type::T_container_map, Property::DecoratorType::D_normalized, {Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), Property::TypeDescriptor("Item", Property::Type::T_custom_type, Property::DecoratorType::D_unique_ptr, {})}), sizeof(std::map<std::string, std::unique_ptr<Item>>), origin + offsetof(GameSettings, items), {
    })));
    properties.insert(std::make_pair<std::string, Property>("weapons", Property("weapons", Property::TypeDescriptor("std::map<std::string, std::unique_ptr<WeaponItem>>", Property::Type::T_container_map, Property::DecoratorType::D_normalized, {Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), Property::TypeDescriptor("WeaponItem", Property::Type::T_custom_type, Property::DecoratorType::D_unique_ptr, {})}), sizeof(std::map<std::string, std::unique_ptr<WeaponItem>>), origin + offsetof(GameSettings, weapons), {
    })));
    properties.insert(std::make_pair<std::string, Property>("playerProgression", Property("playerProgression", Property::TypeDescriptor("std::vector<int>", Property::Type::T_container_vector, Property::DecoratorType::D_normalized, {Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {})}), sizeof(std::vector<int>), origin + offsetof(GameSettings, playerProgression), {
    })));
    return properties;
}
std::size_t GameSettings::getTypeSize() const { return __GameSettingsType::type().size; }
const meta_t& GameSettings::staticTypeMeta() { return __GameSettingsType::type().meta; }
const std::string& GameSettings::staticTypeName() { return __GameSettingsType::type().name; }

const TypeDefinition& __GameSettingsType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new GameSettings(); }, "GameSettings", {
        std::make_pair("Type", "Data"),
    }, sizeof(GameSettings));
    return s_typeDefinition;
}
