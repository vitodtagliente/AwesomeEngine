// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "particles2d_component.h"

const meta_t& Particles2dComponent::getTypeMeta() const { return Particles2dComponentType::type().meta; }
const std::string& Particles2dComponent::getTypeName() const { return Particles2dComponentType::type().name; }
const properties_t Particles2dComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("autoplay", Property("autoplay", Property::TypeDescriptor("bool", Property::Type::T_bool, Property::DecoratorType::D_normalized, {}), sizeof(bool), origin + offsetof(Particles2dComponent, autoplay), {
    })));
    properties.insert(std::make_pair<std::string, Property>("loop", Property("loop", Property::TypeDescriptor("bool", Property::Type::T_bool, Property::DecoratorType::D_normalized, {}), sizeof(bool), origin + offsetof(Particles2dComponent, loop), {
    })));
    return properties;
}
std::size_t Particles2dComponent::getTypeSize() const { return Particles2dComponentType::type().size; }

const TypeDefinition& Particles2dComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new Particles2dComponent(); }, "Particles2dComponent", {
        std::make_pair("Type", "Component"),
    }, sizeof(Particles2dComponent));
    return s_typeDefinition;
}
