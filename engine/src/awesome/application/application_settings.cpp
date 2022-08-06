#include "application_settings.h"

const TypeDescriptor& ApplicationSettings::get_descriptor() const
{
    return ApplicationSettingsType::descriptor();
}

fields_t ApplicationSettings::get_fields() const
{
    return ApplicationSettingsType::fields(this);
}

void ApplicationSettings::autoload()
{
    TypeFactory::load<ApplicationSettings>();
}

const TypeDescriptor& ApplicationSettings::descriptor()
{
    return ApplicationSettingsType::descriptor();
}

TypeDescriptor ApplicationSettingsType::s_typeDescriptor{ ApplicationSettingsType::registerTypeDescriptor };

const TypeDescriptor& ApplicationSettingsType::descriptor()
{
    return s_typeDescriptor;
}

fields_t ApplicationSettingsType::fields(const ApplicationSettings* const pointer)
{
    member_address_t origin = reinterpret_cast<member_address_t>(pointer);
    fields_t fields;
    fields.insert(std::make_pair<std::string, FieldDescriptor>("fps", FieldDescriptor("fps", FieldDescriptor::Type::T_unknown, "FpsMode", origin + offsetof(ApplicationSettings, fps))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("mode", FieldDescriptor("mode", FieldDescriptor::Type::T_unknown, "ApplicationMode", origin + offsetof(ApplicationSettings, mode))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("workspacePath", FieldDescriptor("workspacePath", FieldDescriptor::Type::T_unknown, "std::filesystem::path", origin + offsetof(ApplicationSettings, workspacePath))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("editorScene", FieldDescriptor("editorScene", FieldDescriptor::Type::T_unknown, "SceneAssetPtr", origin + offsetof(ApplicationSettings, editorScene))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("serverScene", FieldDescriptor("serverScene", FieldDescriptor::Type::T_unknown, "SceneAssetPtr", origin + offsetof(ApplicationSettings, serverScene))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("standaloneScene", FieldDescriptor("standaloneScene", FieldDescriptor::Type::T_unknown, "SceneAssetPtr", origin + offsetof(ApplicationSettings, standaloneScene))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("serverIp", FieldDescriptor("serverIp", FieldDescriptor::Type::T_string, "std::string", origin + offsetof(ApplicationSettings, serverIp))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("serverPort", FieldDescriptor("serverPort", FieldDescriptor::Type::T_int, "int", origin + offsetof(ApplicationSettings, serverPort))));
    fields.insert(std::make_pair<std::string, FieldDescriptor>("maxServerConnections", FieldDescriptor("maxServerConnections", FieldDescriptor::Type::T_int, "int", origin + offsetof(ApplicationSettings, maxServerConnections))));
    return fields;
}

void ApplicationSettingsType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "ApplicationSettings";
    descriptor->size = sizeof(ApplicationSettings);

    TypeFactoryRegister::hook("ApplicationSettings", []() -> const TypeDescriptor& { return ApplicationSettingsType::s_typeDescriptor; }, []() -> void* { return new ApplicationSettings(); });
}

