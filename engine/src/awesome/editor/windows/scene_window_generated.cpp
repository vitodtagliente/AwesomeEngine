// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "scene_window.h"

const meta_t& SceneWindow::getTypeMeta() const { return SceneWindowType::meta(); }
const char* SceneWindow::getTypeName() const { return SceneWindowType::name(); }
const properties_t SceneWindow::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t SceneWindow::getTypeSize() const { return sizeof(SceneWindow); }

SceneWindowType::SceneWindowType()
{
    TypeFactoryRegister::load(SceneWindowType::name(), []() -> const meta_t& { return SceneWindowType::meta(); }, []() -> IType* { return SceneWindowType::instantiate(); });
}

SceneWindow* const SceneWindowType::instantiate()
{
    return new SceneWindow();
}

const meta_t& SceneWindowType::meta()
{
    static meta_t s_meta{
    };
    return s_meta;
}

const char* SceneWindowType::name() { return "SceneWindow"; }

SceneWindowType __scenewindow_type;

