// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "pawn_component.h"

const meta_t& PawnComponent::getTypeMeta() const { return PawnComponentType::type().meta; }
const std::string& PawnComponent::getTypeName() const { return PawnComponentType::type().name; }
const properties_t PawnComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("speed", Property("speed", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(PawnComponent, speed), {
    })));
    properties.insert(std::make_pair<std::string, Property>("dashSpeed", Property("dashSpeed", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(PawnComponent, dashSpeed), {
    })));
    return properties;
}
std::size_t PawnComponent::getTypeSize() const { return PawnComponentType::type().size; }

const TypeDefinition& PawnComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new PawnComponent(); }, "PawnComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(PawnComponent));
    return s_typeDefinition;
}
