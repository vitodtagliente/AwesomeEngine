// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "camera_controller_2d_component.h"

const meta_t& CameraController2dComponent::getTypeMeta() const { return CameraController2dComponentType::type().meta; }
const std::string& CameraController2dComponent::getTypeName() const { return CameraController2dComponentType::type().name; }
const properties_t CameraController2dComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("speed", Property("speed", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(CameraController2dComponent, speed), {
    })));
    properties.insert(std::make_pair<std::string, Property>("zoomSpeed", Property("zoomSpeed", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(CameraController2dComponent, zoomSpeed), {
    })));
    return properties;
}
std::size_t CameraController2dComponent::getTypeSize() const { return CameraController2dComponentType::type().size; }

const TypeDefinition& CameraController2dComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new CameraController2dComponent(); }, "CameraController2dComponent", {
        std::make_pair("Type", "Component"),
    }, sizeof(CameraController2dComponent));
    return s_typeDefinition;
}
