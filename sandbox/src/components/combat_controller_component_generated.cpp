// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "combat_controller_component.h"

const meta_t& CombatControllerComponent::getTypeMeta() const { return CombatControllerComponentType::type().meta; }
const std::string& CombatControllerComponent::getTypeName() const { return CombatControllerComponentType::type().name; }
const properties_t CombatControllerComponent::getTypeProperties() const {
    properties_t properties = Component::getTypeProperties();
    return properties;
}
std::size_t CombatControllerComponent::getTypeSize() const { return CombatControllerComponentType::type().size; }

const Type& CombatControllerComponentType::type()
{
    static const Type s_type([]() -> IType* { return new CombatControllerComponent(); }, "CombatControllerComponent", {
    }, sizeof(CombatControllerComponent));
    return s_type;
}
