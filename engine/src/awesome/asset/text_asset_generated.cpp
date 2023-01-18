// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "text_asset.h"

const meta_t& TextAsset::getTypeMeta() const { return __TextAssetType::type().meta; }
const std::string& TextAsset::getTypeName() const { return __TextAssetType::type().name; }
const properties_t TextAsset::getTypeProperties() const {
    properties_t properties = Asset::getTypeProperties();
    return properties;
}
std::size_t TextAsset::getTypeSize() const { return __TextAssetType::type().size; }
const meta_t& TextAsset::staticTypeMeta() { return __TextAssetType::type().meta; }
const std::string& TextAsset::staticTypeName() { return __TextAssetType::type().name; }

const TypeDefinition& __TextAssetType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new TextAsset(); }, "TextAsset", {
        std::make_pair("CreateInEditor", "false"),
        std::make_pair("Extension", ".txt|.md|.shader|.ini|.cfg"),
        std::make_pair("Type", "Asset"),
    }, sizeof(TextAsset));
    return s_typeDefinition;
}
