// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "network_window.h"

const meta_t& NetworkWindow::getTypeMeta() const { return NetworkWindowType::type().meta; }
const std::string& NetworkWindow::getTypeName() const { return NetworkWindowType::type().name; }
const properties_t NetworkWindow::getTypeProperties() const {
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t NetworkWindow::getTypeSize() const { return NetworkWindowType::type().size; }

const TypeDefinition& NetworkWindowType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> IType* { return new NetworkWindow(); }, "NetworkWindow", {
        std::make_pair("Category", "Window"),
    }, sizeof(NetworkWindow));
    return s_typeDefinition;
}
