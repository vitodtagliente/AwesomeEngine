// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "log_window.h"

const meta_t& LogWindow::getTypeMeta() const { return LogWindowType::type().meta; }
const std::string& LogWindow::getTypeName() const { return LogWindowType::type().name; }
const properties_t LogWindow::getTypeProperties() const {
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t LogWindow::getTypeSize() const { return LogWindowType::type().size; }

const TypeDefinition& LogWindowType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new LogWindow(); }, "LogWindow", {
        std::make_pair("Type", "Window"),
    }, sizeof(LogWindow));
    return s_typeDefinition;
}
