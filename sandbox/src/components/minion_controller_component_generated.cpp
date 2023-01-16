// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "minion_controller_component.h"

const meta_t& MinionControllerComponent::getTypeMeta() const { return __MinionControllerComponentType::type().meta; }
const std::string& MinionControllerComponent::getTypeName() const { return __MinionControllerComponentType::type().name; }
const properties_t MinionControllerComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("m_targetTag", Property("m_targetTag", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(MinionControllerComponent, m_targetTag), {
    })));
    return properties;
}
std::size_t MinionControllerComponent::getTypeSize() const { return __MinionControllerComponentType::type().size; }
const meta_t& MinionControllerComponent::staticTypeMeta() { return __MinionControllerComponentType::type().meta; }
const std::string& MinionControllerComponent::staticTypeName() { return __MinionControllerComponentType::type().name; }

const TypeDefinition& __MinionControllerComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new MinionControllerComponent(); }, "MinionControllerComponent", {
        std::make_pair("Type", "Component"),
    }, sizeof(MinionControllerComponent));
    return s_typeDefinition;
}
