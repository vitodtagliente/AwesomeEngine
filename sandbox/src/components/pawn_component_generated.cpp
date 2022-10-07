// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "pawn_component.h"

const meta_t& PawnComponent::getTypeMeta() const { return PawnComponentType::type().meta; }
const std::string& PawnComponent::getTypeName() const { return PawnComponentType::type().name; }
const properties_t PawnComponent::getTypeProperties() const {
    properties_t properties = Component::getTypeProperties();
    return properties;
}
std::size_t PawnComponent::getTypeSize() const { return PawnComponentType::type().size; }

const Type& PawnComponentType::type()
{
    static const Type s_type([]() -> IType* { return new PawnComponent(); }, "PawnComponent", {
    }, sizeof(PawnComponent));
    return s_type;
}
