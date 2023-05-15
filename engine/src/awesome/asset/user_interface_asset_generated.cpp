// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "user_interface_asset.h"
#pragma warning(disable: 4100)

const reflect::meta_t& reflect::Type<UserInterfaceAsset>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Asset" },
    };
    return s_meta;
}
const char* const reflect::Type<UserInterfaceAsset>::name() { return "UserInterfaceAsset"; }

const reflect::properties_t& Type<UserInterfaceAsset>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Asset properties
        { "id", reflect::Property{ offsetof(UserInterfaceAsset, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(UserInterfaceAsset, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<UserInterfaceAsset>::size()
{
    return sizeof(UserInterfaceAsset);
}

void reflect::Type<UserInterfaceAsset>::from_string(const std::string& str, UserInterfaceAsset& type)
{
    reflect::encoding::ByteBuffer buffer;
    std::transform(
        std::begin(str),
        std::end(str),
        std::back_inserter(buffer),
        [](const char c)
        {
            return std::byte(c);
        }
    );
    
    reflect::encoding::InputByteStream stream(buffer);
    std::string _name;
    stream >> _name;
    if (_name != name()) return;
    
    // Parent class Asset properties
    {
        std::string pack;
        stream >> pack;
        type.id.from_string(pack);
    }
    stream >> type.type;
    // Properties
}

std::string reflect::Type<UserInterfaceAsset>::to_string(const UserInterfaceAsset& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class Asset properties
    stream << static_cast<std::string>(type.id);
    stream << type.type;
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<UserInterfaceAsset>::from_json(const std::string& json, UserInterfaceAsset& type)
{
    std::string src{ reflect::encoding::json::Deserializer::trim(json, reflect::encoding::json::Deserializer::space) };
    
    size_t index = 0;
    std::string key;
    while ((index = reflect::encoding::json::Deserializer::next_key(src, key)) != std::string::npos)
    {
        src = src.substr(index + 2);
        src = reflect::encoding::json::Deserializer::ltrim(src, reflect::encoding::json::Deserializer::space);
        std::string value;
        index = reflect::encoding::json::Deserializer::next_value(src, value);
        if (index != std::string::npos)
        {
            // Parent class Asset properties
            if (key == "id") type.id.from_json(value);
            if (key == "type") reflect::encoding::json::Deserializer::parse(value, type.type);
            // Properties
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<UserInterfaceAsset>::to_json(const UserInterfaceAsset& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"UserInterfaceAsset\"" << "," << std::endl;
    // Parent class Asset properties
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& UserInterfaceAsset::type_meta() const { return reflect::Type<UserInterfaceAsset>::meta(); }
const char* const UserInterfaceAsset::type_name() const { return reflect::Type<UserInterfaceAsset>::name(); }
const reflect::properties_t& UserInterfaceAsset::type_properties() const { return reflect::Type<UserInterfaceAsset>::properties(); }
UserInterfaceAsset::operator std::string() const { return reflect::Type<UserInterfaceAsset>::to_string(*this); }
void UserInterfaceAsset::from_string(const std::string& str)
{
    reflect::Type<UserInterfaceAsset>::from_string(str, *this);
    type_initialize();
}
void UserInterfaceAsset::from_json(const std::string& json)
{
    reflect::Type<UserInterfaceAsset>::from_json(json, *this);
    type_initialize();
}
std::string UserInterfaceAsset::to_json(const std::string& offset) const { return reflect::Type<UserInterfaceAsset>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<UserInterfaceAssetLoader>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "AssetLoader" },
    };
    return s_meta;
}
const char* const reflect::Type<UserInterfaceAssetLoader>::name() { return "UserInterfaceAssetLoader"; }

const reflect::properties_t& Type<UserInterfaceAssetLoader>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class AssetLoader properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<UserInterfaceAssetLoader>::size()
{
    return sizeof(UserInterfaceAssetLoader);
}

void reflect::Type<UserInterfaceAssetLoader>::from_string(const std::string& str, UserInterfaceAssetLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    std::transform(
        std::begin(str),
        std::end(str),
        std::back_inserter(buffer),
        [](const char c)
        {
            return std::byte(c);
        }
    );
    
    reflect::encoding::InputByteStream stream(buffer);
    std::string _name;
    stream >> _name;
    if (_name != name()) return;
    
    // Parent class AssetLoader properties
    // Properties
}

std::string reflect::Type<UserInterfaceAssetLoader>::to_string(const UserInterfaceAssetLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class AssetLoader properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<UserInterfaceAssetLoader>::from_json(const std::string& json, UserInterfaceAssetLoader& type)
{
    std::string src{ reflect::encoding::json::Deserializer::trim(json, reflect::encoding::json::Deserializer::space) };
    
    size_t index = 0;
    std::string key;
    while ((index = reflect::encoding::json::Deserializer::next_key(src, key)) != std::string::npos)
    {
        src = src.substr(index + 2);
        src = reflect::encoding::json::Deserializer::ltrim(src, reflect::encoding::json::Deserializer::space);
        std::string value;
        index = reflect::encoding::json::Deserializer::next_value(src, value);
        if (index != std::string::npos)
        {
            // Parent class AssetLoader properties
            // Properties
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<UserInterfaceAssetLoader>::to_json(const UserInterfaceAssetLoader& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"UserInterfaceAssetLoader\"" << "," << std::endl;
    // Parent class AssetLoader properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& UserInterfaceAssetLoader::type_meta() const { return reflect::Type<UserInterfaceAssetLoader>::meta(); }
const char* const UserInterfaceAssetLoader::type_name() const { return reflect::Type<UserInterfaceAssetLoader>::name(); }
const reflect::properties_t& UserInterfaceAssetLoader::type_properties() const { return reflect::Type<UserInterfaceAssetLoader>::properties(); }
UserInterfaceAssetLoader::operator std::string() const { return reflect::Type<UserInterfaceAssetLoader>::to_string(*this); }
void UserInterfaceAssetLoader::from_string(const std::string& str)
{
    reflect::Type<UserInterfaceAssetLoader>::from_string(str, *this);
    type_initialize();
}
void UserInterfaceAssetLoader::from_json(const std::string& json)
{
    reflect::Type<UserInterfaceAssetLoader>::from_json(json, *this);
    type_initialize();
}
std::string UserInterfaceAssetLoader::to_json(const std::string& offset) const { return reflect::Type<UserInterfaceAssetLoader>::to_json(*this, offset); }