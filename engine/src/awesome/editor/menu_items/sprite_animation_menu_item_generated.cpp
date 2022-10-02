// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "sprite_animation_menu_item.h"

const meta_t& SpriteAnimationMenuItem::getTypeMeta() const { return SpriteAnimationMenuItemType::meta(); }
const char* SpriteAnimationMenuItem::getTypeName() const { return SpriteAnimationMenuItemType::name(); }
const properties_t SpriteAnimationMenuItem::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = MenuItem::getTypeProperties();
    return properties;
}
std::size_t SpriteAnimationMenuItem::getTypeSize() const { return sizeof(SpriteAnimationMenuItem); }

SpriteAnimationMenuItemType::SpriteAnimationMenuItemType()
{
    TypeFactoryRegister::load(SpriteAnimationMenuItemType::name(), []() -> const meta_t& { return SpriteAnimationMenuItemType::meta(); }, []() -> IType* { return SpriteAnimationMenuItemType::instantiate(); });
}

SpriteAnimationMenuItem* const SpriteAnimationMenuItemType::instantiate()
{
    return new SpriteAnimationMenuItem();
}

const meta_t& SpriteAnimationMenuItemType::meta()
{
    static meta_t s_meta{
    };
    return s_meta;
}

const char* SpriteAnimationMenuItemType::name() { return "SpriteAnimationMenuItem"; }

SpriteAnimationMenuItemType __spriteanimationmenuitem_type;
