// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "minion_controller_component.h"

const meta_t& MinionControllerComponent::getTypeMeta() const { return MinionControllerComponentType::type().meta; }
const std::string& MinionControllerComponent::getTypeName() const { return MinionControllerComponentType::type().name; }
const properties_t MinionControllerComponent::getTypeProperties() const {
    properties_t properties = Component::getTypeProperties();
    return properties;
}
std::size_t MinionControllerComponent::getTypeSize() const { return MinionControllerComponentType::type().size; }

const Type& MinionControllerComponentType::type()
{
    static const Type s_type([]() -> IType* { return new MinionControllerComponent(); }, "MinionControllerComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(MinionControllerComponent));
    return s_type;
}
