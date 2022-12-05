// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "health_component.h"

const meta_t& HealthComponent::getTypeMeta() const { return HealthComponentType::type().meta; }
const std::string& HealthComponent::getTypeName() const { return HealthComponentType::type().name; }
const properties_t HealthComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("min", Property("min", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(HealthComponent, min), {
    })));
    properties.insert(std::make_pair<std::string, Property>("max", Property("max", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(HealthComponent, max), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_colorToRestore", Property("m_colorToRestore", Property::TypeDescriptor("graphics::Color", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(graphics::Color), origin + offsetof(HealthComponent, m_colorToRestore), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_destroyOnDeath", Property("m_destroyOnDeath", Property::TypeDescriptor("bool", Property::Type::T_bool, Property::DecoratorType::D_normalized, {}), sizeof(bool), origin + offsetof(HealthComponent, m_destroyOnDeath), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_hitColor", Property("m_hitColor", Property::TypeDescriptor("graphics::Color", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(graphics::Color), origin + offsetof(HealthComponent, m_hitColor), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_hitDuration", Property("m_hitDuration", Property::TypeDescriptor("double", Property::Type::T_double, Property::DecoratorType::D_normalized, {}), sizeof(double), origin + offsetof(HealthComponent, m_hitDuration), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_value", Property("m_value", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(HealthComponent, m_value), {
    })));
    return properties;
}
std::size_t HealthComponent::getTypeSize() const { return HealthComponentType::type().size; }

const TypeDefinition& HealthComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> IType* { return new HealthComponent(); }, "HealthComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(HealthComponent));
    return s_typeDefinition;
}
