// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "body2d_component.h"

const meta_t& Body2dComponent::getTypeMeta() const { return Body2dComponentType::type().meta; }
const std::string& Body2dComponent::getTypeName() const { return Body2dComponentType::type().name; }
const properties_t Body2dComponent::getTypeProperties() const {
    properties_t properties = Component::getTypeProperties();
    return properties;
}
std::size_t Body2dComponent::getTypeSize() const { return Body2dComponentType::type().size; }

const Type& Body2dComponentType::type()
{
    static const Type s_type([]() -> IType* { return new Body2dComponent(); }, "Body2dComponent", {
    }, sizeof(Body2dComponent));
    return s_type;
}
