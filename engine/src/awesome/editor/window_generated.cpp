// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "window.h"

const meta_t& Window::getTypeMeta() const { return WindowType::type().meta; }
const std::string& Window::getTypeName() const { return WindowType::type().name; }
const properties_t Window::getTypeProperties() const {
    properties_t properties;
    return properties;
}
std::size_t Window::getTypeSize() const { return WindowType::type().size; }

const TypeDefinition& WindowType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new Window(); }, "Window", {
    }, sizeof(Window));
    return s_typeDefinition;
}
