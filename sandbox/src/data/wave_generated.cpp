// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "wave.h"

const char* EnumType<SpawnType>::name() { return "SpawnType"; }
const std::map<const char*, int>  EnumType<SpawnType>::values()
{
    static std::map<const char*, int> s_values{
        { "AroundPosition", static_cast<int>(SpawnType::AroundPosition) }, 
        { "AtPosition", static_cast<int>(SpawnType::AtPosition) }, 
    };
    return s_values;
}

const meta_t& Wave::getTypeMeta() const { return WaveType::type().meta; }
const std::string& Wave::getTypeName() const { return WaveType::type().name; }
const properties_t Wave::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("name", Property("name", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(Wave, name), {
    })));
    properties.insert(std::make_pair<std::string, Property>("description", Property("description", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(Wave, description), {
    })));
    properties.insert(std::make_pair<std::string, Property>("minionPrefab", Property("minionPrefab", Property::TypeDescriptor("PrefabAssetPtr", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(PrefabAssetPtr), origin + offsetof(Wave, minionPrefab), {
    })));
    properties.insert(std::make_pair<std::string, Property>("quantity", Property("quantity", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(Wave, quantity), {
    })));
    properties.insert(std::make_pair<std::string, Property>("perSpawnDelay", Property("perSpawnDelay", Property::TypeDescriptor("double", Property::Type::T_double, Property::DecoratorType::D_normalized, {}), sizeof(double), origin + offsetof(Wave, perSpawnDelay), {
    })));
    properties.insert(std::make_pair<std::string, Property>("spawnType", Property("spawnType", Property::TypeDescriptor("SpawnType", Property::Type::T_custom_enum, Property::DecoratorType::D_normalized, {}), sizeof(SpawnType), origin + offsetof(Wave, spawnType), {
    })));
    properties.insert(std::make_pair<std::string, Property>("spawnPosition", Property("spawnPosition", Property::TypeDescriptor("math::vec3", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(math::vec3), origin + offsetof(Wave, spawnPosition), {
    })));
    properties.insert(std::make_pair<std::string, Property>("spawnRange", Property("spawnRange", Property::TypeDescriptor("math::vec2", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(math::vec2), origin + offsetof(Wave, spawnRange), {
    })));
    properties.insert(std::make_pair<std::string, Property>("startSpawnDelay", Property("startSpawnDelay", Property::TypeDescriptor("double", Property::Type::T_double, Property::DecoratorType::D_normalized, {}), sizeof(double), origin + offsetof(Wave, startSpawnDelay), {
    })));
    return properties;
}
std::size_t Wave::getTypeSize() const { return WaveType::type().size; }

const Type& WaveType::type()
{
    static const Type s_type([]() -> IType* { return new Wave(); }, "Wave", {
        std::make_pair("Category", "Data"),
    }, sizeof(Wave));
    return s_type;
}