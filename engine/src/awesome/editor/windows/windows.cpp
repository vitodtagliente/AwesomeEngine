#include "windows.h"

namespace editor
{
const TypeDescriptor& AssetInspectorWindow::get_descriptor() const
{
    return AssetInspectorWindowType::descriptor();
}

fields_t AssetInspectorWindow::get_fields() const
{
    return AssetInspectorWindowType::fields(this);
}

void AssetInspectorWindow::autoload()
{
    TypeFactory::load<AssetInspectorWindow>();
}

const TypeDescriptor& AssetInspectorWindow::descriptor()
{
    return AssetInspectorWindowType::descriptor();
}

TypeDescriptor AssetInspectorWindowType::s_typeDescriptor{ AssetInspectorWindowType::registerTypeDescriptor };

const TypeDescriptor& AssetInspectorWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t AssetInspectorWindowType::fields(const AssetInspectorWindow* const pointer)
{
    return fields_t();
}

void AssetInspectorWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "AssetInspectorWindow";
    descriptor->size = sizeof(AssetInspectorWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("AssetInspectorWindow", []() -> const TypeDescriptor& { return AssetInspectorWindowType::s_typeDescriptor; }, []() -> void* { return new AssetInspectorWindow(); });
}

const TypeDescriptor& ContentBrowserWindow::get_descriptor() const
{
    return ContentBrowserWindowType::descriptor();
}

fields_t ContentBrowserWindow::get_fields() const
{
    return ContentBrowserWindowType::fields(this);
}

void ContentBrowserWindow::autoload()
{
    TypeFactory::load<ContentBrowserWindow>();
}

const TypeDescriptor& ContentBrowserWindow::descriptor()
{
    return ContentBrowserWindowType::descriptor();
}

TypeDescriptor ContentBrowserWindowType::s_typeDescriptor{ ContentBrowserWindowType::registerTypeDescriptor };

const TypeDescriptor& ContentBrowserWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t ContentBrowserWindowType::fields(const ContentBrowserWindow* const pointer)
{
    return fields_t();
}

void ContentBrowserWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "ContentBrowserWindow";
    descriptor->size = sizeof(ContentBrowserWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("ContentBrowserWindow", []() -> const TypeDescriptor& { return ContentBrowserWindowType::s_typeDescriptor; }, []() -> void* { return new ContentBrowserWindow(); });
}

const TypeDescriptor& EntityInspectorWindow::get_descriptor() const
{
    return EntityInspectorWindowType::descriptor();
}

fields_t EntityInspectorWindow::get_fields() const
{
    return EntityInspectorWindowType::fields(this);
}

void EntityInspectorWindow::autoload()
{
    TypeFactory::load<EntityInspectorWindow>();
}

const TypeDescriptor& EntityInspectorWindow::descriptor()
{
    return EntityInspectorWindowType::descriptor();
}

TypeDescriptor EntityInspectorWindowType::s_typeDescriptor{ EntityInspectorWindowType::registerTypeDescriptor };

const TypeDescriptor& EntityInspectorWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t EntityInspectorWindowType::fields(const EntityInspectorWindow* const pointer)
{
    return fields_t();
}

void EntityInspectorWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "EntityInspectorWindow";
    descriptor->size = sizeof(EntityInspectorWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("EntityInspectorWindow", []() -> const TypeDescriptor& { return EntityInspectorWindowType::s_typeDescriptor; }, []() -> void* { return new EntityInspectorWindow(); });
}

const TypeDescriptor& LogWindow::get_descriptor() const
{
    return LogWindowType::descriptor();
}

fields_t LogWindow::get_fields() const
{
    return LogWindowType::fields(this);
}

void LogWindow::autoload()
{
    TypeFactory::load<LogWindow>();
}

const TypeDescriptor& LogWindow::descriptor()
{
    return LogWindowType::descriptor();
}

TypeDescriptor LogWindowType::s_typeDescriptor{ LogWindowType::registerTypeDescriptor };

const TypeDescriptor& LogWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t LogWindowType::fields(const LogWindow* const pointer)
{
    return fields_t();
}

void LogWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "LogWindow";
    descriptor->size = sizeof(LogWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("LogWindow", []() -> const TypeDescriptor& { return LogWindowType::s_typeDescriptor; }, []() -> void* { return new LogWindow(); });
}

const TypeDescriptor& NetworkWindow::get_descriptor() const
{
    return NetworkWindowType::descriptor();
}

fields_t NetworkWindow::get_fields() const
{
    return NetworkWindowType::fields(this);
}

void NetworkWindow::autoload()
{
    TypeFactory::load<NetworkWindow>();
}

const TypeDescriptor& NetworkWindow::descriptor()
{
    return NetworkWindowType::descriptor();
}

TypeDescriptor NetworkWindowType::s_typeDescriptor{ NetworkWindowType::registerTypeDescriptor };

const TypeDescriptor& NetworkWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t NetworkWindowType::fields(const NetworkWindow* const pointer)
{
    return fields_t();
}

void NetworkWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "NetworkWindow";
    descriptor->size = sizeof(NetworkWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("NetworkWindow", []() -> const TypeDescriptor& { return NetworkWindowType::s_typeDescriptor; }, []() -> void* { return new NetworkWindow(); });
}

const TypeDescriptor& PerformanceWindow::get_descriptor() const
{
    return PerformanceWindowType::descriptor();
}

fields_t PerformanceWindow::get_fields() const
{
    return PerformanceWindowType::fields(this);
}

void PerformanceWindow::autoload()
{
    TypeFactory::load<PerformanceWindow>();
}

const TypeDescriptor& PerformanceWindow::descriptor()
{
    return PerformanceWindowType::descriptor();
}

TypeDescriptor PerformanceWindowType::s_typeDescriptor{ PerformanceWindowType::registerTypeDescriptor };

const TypeDescriptor& PerformanceWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t PerformanceWindowType::fields(const PerformanceWindow* const pointer)
{
    return fields_t();
}

void PerformanceWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "PerformanceWindow";
    descriptor->size = sizeof(PerformanceWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("PerformanceWindow", []() -> const TypeDescriptor& { return PerformanceWindowType::s_typeDescriptor; }, []() -> void* { return new PerformanceWindow(); });
}

const TypeDescriptor& SceneWindow::get_descriptor() const
{
    return SceneWindowType::descriptor();
}

fields_t SceneWindow::get_fields() const
{
    return SceneWindowType::fields(this);
}

void SceneWindow::autoload()
{
    TypeFactory::load<SceneWindow>();
}

const TypeDescriptor& SceneWindow::descriptor()
{
    return SceneWindowType::descriptor();
}

TypeDescriptor SceneWindowType::s_typeDescriptor{ SceneWindowType::registerTypeDescriptor };

const TypeDescriptor& SceneWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SceneWindowType::fields(const SceneWindow* const pointer)
{
    return fields_t();
}

void SceneWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SceneWindow";
    descriptor->size = sizeof(SceneWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("SceneWindow", []() -> const TypeDescriptor& { return SceneWindowType::s_typeDescriptor; }, []() -> void* { return new SceneWindow(); });
}

const TypeDescriptor& SettingsWindow::get_descriptor() const
{
    return SettingsWindowType::descriptor();
}

fields_t SettingsWindow::get_fields() const
{
    return SettingsWindowType::fields(this);
}

void SettingsWindow::autoload()
{
    TypeFactory::load<SettingsWindow>();
}

const TypeDescriptor& SettingsWindow::descriptor()
{
    return SettingsWindowType::descriptor();
}

TypeDescriptor SettingsWindowType::s_typeDescriptor{ SettingsWindowType::registerTypeDescriptor };

const TypeDescriptor& SettingsWindowType::descriptor()
{
    return s_typeDescriptor;
}

fields_t SettingsWindowType::fields(const SettingsWindow* const pointer)
{
    return fields_t();
}

void SettingsWindowType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "SettingsWindow";
    descriptor->size = sizeof(SettingsWindow);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Window"));

    TypeFactoryRegister::hook("SettingsWindow", []() -> const TypeDescriptor& { return SettingsWindowType::s_typeDescriptor; }, []() -> void* { return new SettingsWindow(); });
}

} // namespace editor
