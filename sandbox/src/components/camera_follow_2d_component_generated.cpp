// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "camera_follow_2d_component.h"

const meta_t& CameraFollow2dComponent::getTypeMeta() const { return CameraFollow2dComponentType::type().meta; }
const std::string& CameraFollow2dComponent::getTypeName() const { return CameraFollow2dComponentType::type().name; }
const properties_t CameraFollow2dComponent::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("m_speed", Property("m_speed", PropertyType::T_float, "float", true, sizeof(float), origin + offsetof(CameraFollow2dComponent, m_speed), {
    })));
    return properties;
}
std::size_t CameraFollow2dComponent::getTypeSize() const { return CameraFollow2dComponentType::type().size; }

const Type& CameraFollow2dComponentType::type()
{
    static const Type s_type([]() -> IType* { return new CameraFollow2dComponent(); }, "CameraFollow2dComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(CameraFollow2dComponent));
    return s_type;
}
