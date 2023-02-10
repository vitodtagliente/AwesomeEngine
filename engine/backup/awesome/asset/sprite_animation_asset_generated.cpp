// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "sprite_animation_asset.h"

const meta_t& SpriteAnimationAsset::getTypeMeta() const { return __SpriteAnimationAssetType::type().meta; }
const std::string& SpriteAnimationAsset::getTypeName() const { return __SpriteAnimationAssetType::type().name; }
const properties_t SpriteAnimationAsset::getTypeProperties() const {
    properties_t properties = Asset::getTypeProperties();
    return properties;
}
std::size_t SpriteAnimationAsset::getTypeSize() const { return __SpriteAnimationAssetType::type().size; }
const meta_t& SpriteAnimationAsset::staticTypeMeta() { return __SpriteAnimationAssetType::type().meta; }
const std::string& SpriteAnimationAsset::staticTypeName() { return __SpriteAnimationAssetType::type().name; }

const TypeDefinition& __SpriteAnimationAssetType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new SpriteAnimationAsset(); }, "SpriteAnimationAsset", {
        std::make_pair("CreateInEditor", "true"),
        std::make_pair("Extension", ".spriteanim"),
        std::make_pair("Type", "Asset"),
    }, sizeof(SpriteAnimationAsset));
    return s_typeDefinition;
}