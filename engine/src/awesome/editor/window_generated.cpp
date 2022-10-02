// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "window.h"

const meta_t& Window::getTypeMeta() const { return WindowType::meta(); }
const char* Window::getTypeName() const { return WindowType::name(); }
const properties_t Window::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    return properties;
}
std::size_t Window::getTypeSize() const { return sizeof(Window); }

WindowType::WindowType()
{
    TypeFactoryRegister::load(WindowType::name(), []() -> const meta_t& { return WindowType::meta(); }, []() -> IType* { return WindowType::instantiate(); });
}

Window* const WindowType::instantiate()
{
    return new Window();
}

const meta_t& WindowType::meta()
{
    static meta_t s_meta{
    };
    return s_meta;
}

const char* WindowType::name() { return "Window"; }

WindowType __window_type;

