// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "save_scene_as_menu_item.h"

const meta_t& SaveSceneAsMenuItem::getTypeMeta() const { return SaveSceneAsMenuItemType::type().meta; }
const std::string& SaveSceneAsMenuItem::getTypeName() const { return SaveSceneAsMenuItemType::type().name; }
const properties_t SaveSceneAsMenuItem::getTypeProperties() const {
    properties_t properties = MenuItem::getTypeProperties();
    return properties;
}
std::size_t SaveSceneAsMenuItem::getTypeSize() const { return SaveSceneAsMenuItemType::type().size; }

const Type& SaveSceneAsMenuItemType::type()
{
    static const Type s_type([]() -> IType* { return new SaveSceneAsMenuItem(); }, "SaveSceneAsMenuItem", {
        std::make_pair("Category", "MenuItem"),
    }, sizeof(SaveSceneAsMenuItem));
    return s_type;
}
