// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "settings_window.h"

const meta_t& SettingsWindow::getTypeMeta() const { return SettingsWindowType::type().meta; }
const std::string& SettingsWindow::getTypeName() const { return SettingsWindowType::type().name; }
const properties_t SettingsWindow::getTypeProperties() const {
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t SettingsWindow::getTypeSize() const { return SettingsWindowType::type().size; }

const Type& SettingsWindowType::type()
{
    static const Type s_type([]() -> IType* { return new SettingsWindow(); }, "SettingsWindow", {
        std::make_pair("Category", "Window"),
    }, sizeof(SettingsWindow));
    return s_type;
}
