// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "world.h"

const meta_t& SceneSettings::getTypeMeta() const { return __SceneSettingsType::type().meta; }
const std::string& SceneSettings::getTypeName() const { return __SceneSettingsType::type().name; }
const properties_t SceneSettings::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("quadspaceBounds", Property("quadspaceBounds", Property::TypeDescriptor("float", Property::Type::T_float, Property::DecoratorType::D_normalized, {}), sizeof(float), origin + offsetof(SceneSettings, quadspaceBounds), {
    })));
    return properties;
}
std::size_t SceneSettings::getTypeSize() const { return __SceneSettingsType::type().size; }

const TypeDefinition& __SceneSettingsType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new SceneSettings(); }, "SceneSettings", {
        std::make_pair("Type", "Data"),
    }, sizeof(SceneSettings));
    return s_typeDefinition;
}
