// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "settings_window.h"

const meta_t& SettingsWindow::getTypeMeta() const { return SettingsWindowType::meta(); }
const char* SettingsWindow::getTypeName() const { return SettingsWindowType::name(); }
const properties_t SettingsWindow::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t SettingsWindow::getTypeSize() const { return sizeof(SettingsWindow); }

SettingsWindowType::SettingsWindowType()
{
    TypeFactoryRegister::load(SettingsWindowType::name(), []() -> const meta_t& { return SettingsWindowType::meta(); }, []() -> IType* { return SettingsWindowType::instantiate(); });
}

SettingsWindow* const SettingsWindowType::instantiate()
{
    return new SettingsWindow();
}

const meta_t& SettingsWindowType::meta()
{
    static meta_t s_meta{
    };
    return s_meta;
}

const char* SettingsWindowType::name() { return "SettingsWindow"; }

SettingsWindowType __settingswindow_type;
