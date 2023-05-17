// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "widget_asset.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<WidgetAsset>::instantiate()
{
    return dynamic_cast<IType*>(new WidgetAsset());
}

const reflect::meta_t& reflect::Type<WidgetAsset>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Asset" },
    };
    return s_meta;
}
const char* const reflect::Type<WidgetAsset>::name() { return "WidgetAsset"; }

const reflect::properties_t& Type<WidgetAsset>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Asset properties
        { "id", reflect::Property{ offsetof(WidgetAsset, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(WidgetAsset, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<WidgetAsset>::size()
{
    return sizeof(WidgetAsset);
}

void reflect::Type<WidgetAsset>::from_string(const std::string& str, WidgetAsset& type)
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

std::string reflect::Type<WidgetAsset>::to_string(const WidgetAsset& type)
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

void reflect::Type<WidgetAsset>::from_json(const std::string& json, WidgetAsset& type)
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

std::string reflect::Type<WidgetAsset>::to_json(const WidgetAsset& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"WidgetAsset\"" << "," << std::endl;
    // Parent class Asset properties
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& WidgetAsset::type_meta() const { return reflect::Type<WidgetAsset>::meta(); }
const char* const WidgetAsset::type_name() const { return reflect::Type<WidgetAsset>::name(); }
const reflect::properties_t& WidgetAsset::type_properties() const { return reflect::Type<WidgetAsset>::properties(); }
WidgetAsset::operator std::string() const { return reflect::Type<WidgetAsset>::to_string(*this); }
void WidgetAsset::from_string(const std::string& str)
{
    reflect::Type<WidgetAsset>::from_string(str, *this);
    type_initialize();
}
void WidgetAsset::from_json(const std::string& json)
{
    reflect::Type<WidgetAsset>::from_json(json, *this);
    type_initialize();
}
std::string WidgetAsset::to_json(const std::string& offset) const { return reflect::Type<WidgetAsset>::to_json(*this, offset); }

IType* const reflect::Type<WidgetAssetLoader>::instantiate()
{
    return dynamic_cast<IType*>(new WidgetAssetLoader());
}

const reflect::meta_t& reflect::Type<WidgetAssetLoader>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "AssetLoader" },
    };
    return s_meta;
}
const char* const reflect::Type<WidgetAssetLoader>::name() { return "WidgetAssetLoader"; }

const reflect::properties_t& Type<WidgetAssetLoader>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class AssetLoader properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<WidgetAssetLoader>::size()
{
    return sizeof(WidgetAssetLoader);
}

void reflect::Type<WidgetAssetLoader>::from_string(const std::string& str, WidgetAssetLoader& type)
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

std::string reflect::Type<WidgetAssetLoader>::to_string(const WidgetAssetLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class AssetLoader properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<WidgetAssetLoader>::from_json(const std::string& json, WidgetAssetLoader& type)
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

std::string reflect::Type<WidgetAssetLoader>::to_json(const WidgetAssetLoader& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"WidgetAssetLoader\"" << "," << std::endl;
    // Parent class AssetLoader properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& WidgetAssetLoader::type_meta() const { return reflect::Type<WidgetAssetLoader>::meta(); }
const char* const WidgetAssetLoader::type_name() const { return reflect::Type<WidgetAssetLoader>::name(); }
const reflect::properties_t& WidgetAssetLoader::type_properties() const { return reflect::Type<WidgetAssetLoader>::properties(); }
WidgetAssetLoader::operator std::string() const { return reflect::Type<WidgetAssetLoader>::to_string(*this); }
void WidgetAssetLoader::from_string(const std::string& str)
{
    reflect::Type<WidgetAssetLoader>::from_string(str, *this);
    type_initialize();
}
void WidgetAssetLoader::from_json(const std::string& json)
{
    reflect::Type<WidgetAssetLoader>::from_json(json, *this);
    type_initialize();
}
std::string WidgetAssetLoader::to_json(const std::string& offset) const { return reflect::Type<WidgetAssetLoader>::to_json(*this, offset); }