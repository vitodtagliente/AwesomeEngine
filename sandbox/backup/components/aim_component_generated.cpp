// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "aim_component.h"

const meta_t& AimComponent::getTypeMeta() const { return __AimComponentType::type().meta; }
const std::string& AimComponent::getTypeName() const { return __AimComponentType::type().name; }
const properties_t AimComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("m_maxRange", Property("m_maxRange", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(AimComponent, m_maxRange), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_maxSize", Property("m_maxSize", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(AimComponent, m_maxSize), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_minRange", Property("m_minRange", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(AimComponent, m_minRange), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_minSize", Property("m_minSize", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(AimComponent, m_minSize), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_resizeSpeed", Property("m_resizeSpeed", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(AimComponent, m_resizeSpeed), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_image", Property("m_image", Property::TypeDescriptor("ImageAssetPtr", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(ImageAssetPtr), origin + offsetof(AimComponent, m_image), {
    })));
    properties.insert(std::make_pair<std::string, Property>("m_rect", Property("m_rect", Property::TypeDescriptor("graphics::TextureRect", Property::Type::T_unknown, Property::DecoratorType::D_normalized, {}), sizeof(graphics::TextureRect), origin + offsetof(AimComponent, m_rect), {
    })));
    return properties;
}
std::size_t AimComponent::getTypeSize() const { return __AimComponentType::type().size; }
const meta_t& AimComponent::staticTypeMeta() { return __AimComponentType::type().meta; }
const std::string& AimComponent::staticTypeName() { return __AimComponentType::type().name; }

const TypeDefinition& __AimComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new AimComponent(); }, "AimComponent", {
        std::make_pair("Type", "Component"),
    }, sizeof(AimComponent));
    return s_typeDefinition;
}