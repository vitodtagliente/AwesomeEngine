// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "button_component.h"

const meta_t& ButtonComponent::getTypeMeta() const { return ButtonComponentType::type().meta; }
const std::string& ButtonComponent::getTypeName() const { return ButtonComponentType::type().name; }
const properties_t ButtonComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("m_clickColor", Property("m_clickColor", Property::TypeDescriptor("graphics::Color", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(graphics::Color), origin + offsetof(ButtonComponent, m_clickColor), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_clickDuration", Property("m_clickDuration", Property::TypeDescriptor("double", Property::Type::T_double, Property::DecoratorType::D_normalized, {}), sizeof(double), origin + offsetof(ButtonComponent, m_clickDuration), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_normalColor", Property("m_normalColor", Property::TypeDescriptor("graphics::Color", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(graphics::Color), origin + offsetof(ButtonComponent, m_normalColor), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_hoveredColor", Property("m_hoveredColor", Property::TypeDescriptor("graphics::Color", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(graphics::Color), origin + offsetof(ButtonComponent, m_hoveredColor), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_sprite", Property("m_sprite", Property::TypeDescriptor("SpriteAssetPtr", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(SpriteAssetPtr), origin + offsetof(ButtonComponent, m_sprite), {
    })));
    return properties;
}
std::size_t ButtonComponent::getTypeSize() const { return ButtonComponentType::type().size; }

const TypeDefinition& ButtonComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new ButtonComponent(); }, "ButtonComponent", {
        std::make_pair("Category", "UI"),
        std::make_pair("Type", "Component"),
    }, sizeof(ButtonComponent));
    return s_typeDefinition;
}
