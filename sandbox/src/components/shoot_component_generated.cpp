// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "shoot_component.h"

const meta_t& ShootComponent::getTypeMeta() const { return __ShootComponentType::type().meta; }
const std::string& ShootComponent::getTypeName() const { return __ShootComponentType::type().name; }
const properties_t ShootComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("m_bulletPrefab", Property("m_bulletPrefab", Property::TypeDescriptor("PrefabAssetPtr", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(PrefabAssetPtr), origin + offsetof(ShootComponent, m_bulletPrefab), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_damage", Property("m_damage", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(ShootComponent, m_damage), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_frequency", Property("m_frequency", Property::TypeDescriptor("double", Property::Type::T_double, Property::DecoratorType::D_normalized, {}), sizeof(double), origin + offsetof(ShootComponent, m_frequency), {
    })));
    return properties;
}
std::size_t ShootComponent::getTypeSize() const { return __ShootComponentType::type().size; }
const meta_t& ShootComponent::staticTypeMeta() { return __ShootComponentType::type().meta; }
const std::string& ShootComponent::staticTypeName() { return __ShootComponentType::type().name; }

const TypeDefinition& __ShootComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new ShootComponent(); }, "ShootComponent", {
        std::make_pair("Type", "Component"),
    }, sizeof(ShootComponent));
    return s_typeDefinition;
}
