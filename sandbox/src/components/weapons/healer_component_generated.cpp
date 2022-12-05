// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "healer_component.h"

const meta_t& HealerComponent::getTypeMeta() const { return HealerComponentType::type().meta; }
const std::string& HealerComponent::getTypeName() const { return HealerComponentType::type().name; }
const properties_t HealerComponent::getTypeProperties() const {
    properties_t properties = WeaponComponent::getTypeProperties();
    return properties;
}
std::size_t HealerComponent::getTypeSize() const { return HealerComponentType::type().size; }

const TypeDefinition& HealerComponentType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> IType* { return new HealerComponent(); }, "HealerComponent", {
        std::make_pair("Category", "Component"),
    }, sizeof(HealerComponent));
    return s_typeDefinition;
}
