// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "lifetime_component.h"

const meta_t& LifetimeComponent::getTypeMeta() const { return LifetimeComponentType::type().meta; }
const std::string& LifetimeComponent::getTypeName() const { return LifetimeComponentType::type().name; }
const properties_t LifetimeComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("value", Property("value", Property::TypeDescriptor("double", Property::Type::T_double, Property::DecoratorType::D_normalized, {}), sizeof(double), origin + offsetof(LifetimeComponent, value), {
    })));
    return properties;
}
std::size_t LifetimeComponent::getTypeSize() const { return LifetimeComponentType::type().size; }

const TypeDefinition& LifetimeComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new LifetimeComponent(); }, "LifetimeComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(LifetimeComponent));
    return s_typeDefinition;
}
