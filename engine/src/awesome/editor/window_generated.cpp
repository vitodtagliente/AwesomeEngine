// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "window.h"

const meta_t& Window::getTypeMeta() const { return __WindowType::type().meta; }
const std::string& Window::getTypeName() const { return __WindowType::type().name; }
const properties_t Window::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("visible", Property("visible", Property::TypeDescriptor("bool", Property::Type::T_bool, Property::DecoratorType::D_normalized, {}), sizeof(bool), origin + offsetof(Window, visible), {
    })));
    return properties;
}
std::size_t Window::getTypeSize() const { return __WindowType::type().size; }
const meta_t& Window::staticTypeMeta() { return __WindowType::type().meta; }
const std::string& Window::staticTypeName() { return __WindowType::type().name; }

const TypeDefinition& __WindowType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new Window(); }, "Window", {
    }, sizeof(Window));
    return s_typeDefinition;
}
