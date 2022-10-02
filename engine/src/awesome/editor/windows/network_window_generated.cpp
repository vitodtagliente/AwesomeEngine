// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "network_window.h"

const meta_t& NetworkWindow::getTypeMeta() const { return NetworkWindowType::meta(); }
const char* NetworkWindow::getTypeName() const { return NetworkWindowType::name(); }
const properties_t NetworkWindow::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t NetworkWindow::getTypeSize() const { return sizeof(NetworkWindow); }

NetworkWindowType::NetworkWindowType()
{
    TypeFactoryRegister::load(NetworkWindowType::name(), []() -> const meta_t& { return NetworkWindowType::meta(); }, []() -> IType* { return NetworkWindowType::instantiate(); });
}

NetworkWindow* const NetworkWindowType::instantiate()
{
    return new NetworkWindow();
}

const meta_t& NetworkWindowType::meta()
{
    static meta_t s_meta{
    };
    return s_meta;
}

const char* NetworkWindowType::name() { return "NetworkWindow"; }

NetworkWindowType __networkwindow_type;

