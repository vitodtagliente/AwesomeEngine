#include "menu_items.h"

namespace editor
{
const TypeDescriptor& NewSceneMenuItem::get_descriptor() const
{
    return NewSceneMenuItemType::descriptor();
}

fields_t NewSceneMenuItem::get_fields() const
{
    return NewSceneMenuItemType::fields(this);
}

void NewSceneMenuItem::autoload()
{
    TypeFactory::load<NewSceneMenuItem>();
}

const TypeDescriptor& NewSceneMenuItem::descriptor()
{
    return NewSceneMenuItemType::descriptor();
}

TypeDescriptor NewSceneMenuItemType::s_typeDescriptor{ NewSceneMenuItemType::registerTypeDescriptor };

const TypeDescriptor& NewSceneMenuItemType::descriptor()
{
    return s_typeDescriptor;
}

fields_t NewSceneMenuItemType::fields(const NewSceneMenuItem* const)
{
    return fields_t();
}

void NewSceneMenuItemType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "NewSceneMenuItem";
    descriptor->size = sizeof(NewSceneMenuItem);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "MenuItem"));

    TypeFactoryRegister::hook("NewSceneMenuItem", []() -> const TypeDescriptor& { return NewSceneMenuItemType::s_typeDescriptor; }, []() -> void* { return new NewSceneMenuItem(); });
}

const TypeDescriptor& SaveSceneAsMenuItem::get_descriptor() const
{
    return SaveSceneAsMenuItemType::descriptor();
}

fields_t SaveSceneAsMenuItem::get_fields() const
{
    return SaveSceneAsMenuItemType::fields(this);
}

void SaveSceneAsMenuItem::autoload()
{
    TypeFactory::load<SaveSceneAsMenuItem>();
}

const TypeDescriptor& SaveSceneAsMenuItem::descriptor()
{
    return SaveSceneAsMenuItemType::descriptor();
}

TypeDescriptor SaveSceneAsMenuItemType::s_typeDescriptor{ SaveSceneAsMenuItemType::registerTypeDescriptor };

const TypeDescriptor& SaveSceneAsMenuItemType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SaveSceneAsMenuItemType::fields(const SaveSceneAsMenuItem* const)
{
    return fields_t();
}

void SaveSceneAsMenuItemType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SaveSceneAsMenuItem";
    descriptor->size = sizeof(SaveSceneAsMenuItem);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "MenuItem"));

    TypeFactoryRegister::hook("SaveSceneAsMenuItem", []() -> const TypeDescriptor& { return SaveSceneAsMenuItemType::s_typeDescriptor; }, []() -> void* { return new SaveSceneAsMenuItem(); });
}

const TypeDescriptor& SaveSceneMenuItem::get_descriptor() const
{
    return SaveSceneMenuItemType::descriptor();
}

fields_t SaveSceneMenuItem::get_fields() const
{
    return SaveSceneMenuItemType::fields(this);
}

void SaveSceneMenuItem::autoload()
{
    TypeFactory::load<SaveSceneMenuItem>();
}

const TypeDescriptor& SaveSceneMenuItem::descriptor()
{
    return SaveSceneMenuItemType::descriptor();
}

TypeDescriptor SaveSceneMenuItemType::s_typeDescriptor{ SaveSceneMenuItemType::registerTypeDescriptor };

const TypeDescriptor& SaveSceneMenuItemType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SaveSceneMenuItemType::fields(const SaveSceneMenuItem* const)
{
    return fields_t();
}

void SaveSceneMenuItemType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SaveSceneMenuItem";
    descriptor->size = sizeof(SaveSceneMenuItem);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "MenuItem"));

    TypeFactoryRegister::hook("SaveSceneMenuItem", []() -> const TypeDescriptor& { return SaveSceneMenuItemType::s_typeDescriptor; }, []() -> void* { return new SaveSceneMenuItem(); });
}

const TypeDescriptor& ShowWindowsMenuItem::get_descriptor() const
{
    return ShowWindowsMenuItemType::descriptor();
}

fields_t ShowWindowsMenuItem::get_fields() const
{
    return ShowWindowsMenuItemType::fields(this);
}

void ShowWindowsMenuItem::autoload()
{
    TypeFactory::load<ShowWindowsMenuItem>();
}

const TypeDescriptor& ShowWindowsMenuItem::descriptor()
{
    return ShowWindowsMenuItemType::descriptor();
}

TypeDescriptor ShowWindowsMenuItemType::s_typeDescriptor{ ShowWindowsMenuItemType::registerTypeDescriptor };

const TypeDescriptor& ShowWindowsMenuItemType::descriptor()
{
    return s_typeDescriptor;
}

fields_t ShowWindowsMenuItemType::fields(const ShowWindowsMenuItem* const)
{
    return fields_t();
}

void ShowWindowsMenuItemType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "ShowWindowsMenuItem";
    descriptor->size = sizeof(ShowWindowsMenuItem);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "MenuItem"));

    TypeFactoryRegister::hook("ShowWindowsMenuItem", []() -> const TypeDescriptor& { return ShowWindowsMenuItemType::s_typeDescriptor; }, []() -> void* { return new ShowWindowsMenuItem(); });
}

const TypeDescriptor& SpriteAnimationMenuItem::get_descriptor() const
{
    return SpriteAnimationMenuItemType::descriptor();
}

fields_t SpriteAnimationMenuItem::get_fields() const
{
    return SpriteAnimationMenuItemType::fields(this);
}

void SpriteAnimationMenuItem::autoload()
{
    TypeFactory::load<SpriteAnimationMenuItem>();
}

const TypeDescriptor& SpriteAnimationMenuItem::descriptor()
{
    return SpriteAnimationMenuItemType::descriptor();
}

TypeDescriptor SpriteAnimationMenuItemType::s_typeDescriptor{ SpriteAnimationMenuItemType::registerTypeDescriptor };

const TypeDescriptor& SpriteAnimationMenuItemType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SpriteAnimationMenuItemType::fields(const SpriteAnimationMenuItem* const)
{
    return fields_t();
}

void SpriteAnimationMenuItemType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SpriteAnimationMenuItem";
    descriptor->size = sizeof(SpriteAnimationMenuItem);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "MenuItem"));

    TypeFactoryRegister::hook("SpriteAnimationMenuItem", []() -> const TypeDescriptor& { return SpriteAnimationMenuItemType::s_typeDescriptor; }, []() -> void* { return new SpriteAnimationMenuItem(); });
}

const TypeDescriptor& SpriteMenuItem::get_descriptor() const
{
    return SpriteMenuItemType::descriptor();
}

fields_t SpriteMenuItem::get_fields() const
{
    return SpriteMenuItemType::fields(this);
}

void SpriteMenuItem::autoload()
{
    TypeFactory::load<SpriteMenuItem>();
}

const TypeDescriptor& SpriteMenuItem::descriptor()
{
    return SpriteMenuItemType::descriptor();
}

TypeDescriptor SpriteMenuItemType::s_typeDescriptor{ SpriteMenuItemType::registerTypeDescriptor };

const TypeDescriptor& SpriteMenuItemType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SpriteMenuItemType::fields(const SpriteMenuItem* const)
{
    return fields_t();
}

void SpriteMenuItemType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SpriteMenuItem";
    descriptor->size = sizeof(SpriteMenuItem);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "MenuItem"));

    TypeFactoryRegister::hook("SpriteMenuItem", []() -> const TypeDescriptor& { return SpriteMenuItemType::s_typeDescriptor; }, []() -> void* { return new SpriteMenuItem(); });
}

} // namespace editor
