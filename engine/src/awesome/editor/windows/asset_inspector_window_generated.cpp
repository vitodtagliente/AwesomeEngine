// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "asset_inspector_window.h"

const meta_t& AssetInspectorWindow::getTypeMeta() const { return AssetInspectorWindowType::type().meta; }
const std::string& AssetInspectorWindow::getTypeName() const { return AssetInspectorWindowType::type().name; }
const properties_t AssetInspectorWindow::getTypeProperties() const {
    properties_t properties = Window::getTypeProperties();
    return properties;
}
std::size_t AssetInspectorWindow::getTypeSize() const { return AssetInspectorWindowType::type().size; }

const Type& AssetInspectorWindowType::type()
{
    static const Type s_type([]() -> IType* { return new AssetInspectorWindow(); }, "AssetInspectorWindow", {
        std::make_pair("Category", "Window"),
    }, sizeof(AssetInspectorWindow));
    return s_type;
}
