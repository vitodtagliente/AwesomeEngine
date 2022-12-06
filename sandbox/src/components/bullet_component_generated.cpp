// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "bullet_component.h"

const meta_t& BulletComponent::getTypeMeta() const { return BulletComponentType::type().meta; }
const std::string& BulletComponent::getTypeName() const { return BulletComponentType::type().name; }
const properties_t BulletComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("damage", Property("damage", Property::TypeDescriptor("int", Property::Type::T_int, Property::DecoratorType::D_normalized, {}), sizeof(int), origin + offsetof(BulletComponent, damage), {
    })));
    properties.insert(std::make_pair<std::string, Property>("speed", Property("speed", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(BulletComponent, speed), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_destroyOnCollision", Property("m_destroyOnCollision", Property::TypeDescriptor("bool", Property::Type::T_bool, Property::DecoratorType::D_normalized, {}), sizeof(bool), origin + offsetof(BulletComponent, m_destroyOnCollision), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_targetTag", Property("m_targetTag", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(BulletComponent, m_targetTag), {
    })));
    return properties;
}
std::size_t BulletComponent::getTypeSize() const { return BulletComponentType::type().size; }

const TypeDefinition& BulletComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new BulletComponent(); }, "BulletComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(BulletComponent));
    return s_typeDefinition;
}
