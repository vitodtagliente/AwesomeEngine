// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "scene_asset.h"
#pragma warning(disable: 4100)

const reflect::meta_t& reflect::Type<SceneAsset>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Asset" },
    };
    return s_meta;
}
const char* const reflect::Type<SceneAsset>::name() { return "SceneAsset"; }

const reflect::properties_t& Type<SceneAsset>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Asset properties
        { "id", reflect::Property{ offsetof(SceneAsset, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(SceneAsset, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<SceneAsset>::size()
{
    return sizeof(SceneAsset);
}

void reflect::Type<SceneAsset>::from_string(const std::string& str, SceneAsset& type)
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

std::string reflect::Type<SceneAsset>::to_string(const SceneAsset& type)
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

void reflect::Type<SceneAsset>::from_json(const std::string& json, SceneAsset& type)
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

std::string reflect::Type<SceneAsset>::to_json(const SceneAsset& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SceneAsset\"" << "," << std::endl;
    // Parent class Asset properties
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SceneAsset::type_meta() const { return reflect::Type<SceneAsset>::meta(); }
const char* const SceneAsset::type_name() const { return reflect::Type<SceneAsset>::name(); }
const reflect::properties_t& SceneAsset::type_properties() const { return reflect::Type<SceneAsset>::properties(); }
SceneAsset::operator std::string() const { return reflect::Type<SceneAsset>::to_string(*this); }
void SceneAsset::from_string(const std::string& str)
{
    reflect::Type<SceneAsset>::from_string(str, *this);
    type_initialize();
}
void SceneAsset::from_json(const std::string& json)
{
    reflect::Type<SceneAsset>::from_json(json, *this);
    type_initialize();
}
std::string SceneAsset::to_json(const std::string& offset) const { return reflect::Type<SceneAsset>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<SceneAssetLoader>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "AssetLoader" },
    };
    return s_meta;
}
const char* const reflect::Type<SceneAssetLoader>::name() { return "SceneAssetLoader"; }

const reflect::properties_t& Type<SceneAssetLoader>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class AssetLoader properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<SceneAssetLoader>::size()
{
    return sizeof(SceneAssetLoader);
}

void reflect::Type<SceneAssetLoader>::from_string(const std::string& str, SceneAssetLoader& type)
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

std::string reflect::Type<SceneAssetLoader>::to_string(const SceneAssetLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class AssetLoader properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<SceneAssetLoader>::from_json(const std::string& json, SceneAssetLoader& type)
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

std::string reflect::Type<SceneAssetLoader>::to_json(const SceneAssetLoader& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SceneAssetLoader\"" << "," << std::endl;
    // Parent class AssetLoader properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SceneAssetLoader::type_meta() const { return reflect::Type<SceneAssetLoader>::meta(); }
const char* const SceneAssetLoader::type_name() const { return reflect::Type<SceneAssetLoader>::name(); }
const reflect::properties_t& SceneAssetLoader::type_properties() const { return reflect::Type<SceneAssetLoader>::properties(); }
SceneAssetLoader::operator std::string() const { return reflect::Type<SceneAssetLoader>::to_string(*this); }
void SceneAssetLoader::from_string(const std::string& str)
{
    reflect::Type<SceneAssetLoader>::from_string(str, *this);
    type_initialize();
}
void SceneAssetLoader::from_json(const std::string& json)
{
    reflect::Type<SceneAssetLoader>::from_json(json, *this);
    type_initialize();
}
std::string SceneAssetLoader::to_json(const std::string& offset) const { return reflect::Type<SceneAssetLoader>::to_json(*this, offset); }