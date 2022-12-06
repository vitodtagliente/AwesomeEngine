// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "pawn_controller_component.h"

const meta_t& PawnControllerComponent::getTypeMeta() const { return PawnControllerComponentType::type().meta; }
const std::string& PawnControllerComponent::getTypeName() const { return PawnControllerComponentType::type().name; }
const properties_t PawnControllerComponent::getTypeProperties() const {
    properties_t properties = Component::getTypeProperties();
    return properties;
}
std::size_t PawnControllerComponent::getTypeSize() const { return PawnControllerComponentType::type().size; }

const TypeDefinition& PawnControllerComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new PawnControllerComponent(); }, "PawnControllerComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(PawnControllerComponent));
    return s_typeDefinition;
}
