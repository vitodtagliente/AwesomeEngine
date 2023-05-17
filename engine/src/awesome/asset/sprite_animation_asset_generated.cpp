// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "sprite_animation_asset.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<SpriteAnimationAsset>::instantiate()
{
    return dynamic_cast<IType*>(new SpriteAnimationAsset());
}

const reflect::meta_t& reflect::Type<SpriteAnimationAsset>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Asset" },
    };
    return s_meta;
}
const char* const reflect::Type<SpriteAnimationAsset>::name() { return "SpriteAnimationAsset"; }

const reflect::properties_t& Type<SpriteAnimationAsset>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Asset properties
        { "id", reflect::Property{ offsetof(SpriteAnimationAsset, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(SpriteAnimationAsset, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<SpriteAnimationAsset>::size()
{
    return sizeof(SpriteAnimationAsset);
}

void reflect::Type<SpriteAnimationAsset>::from_string(const std::string& str, SpriteAnimationAsset& type)
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

std::string reflect::Type<SpriteAnimationAsset>::to_string(const SpriteAnimationAsset& type)
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

void reflect::Type<SpriteAnimationAsset>::from_json(const std::string& json, SpriteAnimationAsset& type)
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

std::string reflect::Type<SpriteAnimationAsset>::to_json(const SpriteAnimationAsset& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SpriteAnimationAsset\"" << "," << std::endl;
    // Parent class Asset properties
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SpriteAnimationAsset::type_meta() const { return reflect::Type<SpriteAnimationAsset>::meta(); }
const char* const SpriteAnimationAsset::type_name() const { return reflect::Type<SpriteAnimationAsset>::name(); }
const reflect::properties_t& SpriteAnimationAsset::type_properties() const { return reflect::Type<SpriteAnimationAsset>::properties(); }
SpriteAnimationAsset::operator std::string() const { return reflect::Type<SpriteAnimationAsset>::to_string(*this); }
void SpriteAnimationAsset::from_string(const std::string& str)
{
    reflect::Type<SpriteAnimationAsset>::from_string(str, *this);
    type_initialize();
}
void SpriteAnimationAsset::from_json(const std::string& json)
{
    reflect::Type<SpriteAnimationAsset>::from_json(json, *this);
    type_initialize();
}
std::string SpriteAnimationAsset::to_json(const std::string& offset) const { return reflect::Type<SpriteAnimationAsset>::to_json(*this, offset); }

IType* const reflect::Type<SpriteAnimationLoader>::instantiate()
{
    return dynamic_cast<IType*>(new SpriteAnimationLoader());
}

const reflect::meta_t& reflect::Type<SpriteAnimationLoader>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "AssetLoader" },
    };
    return s_meta;
}
const char* const reflect::Type<SpriteAnimationLoader>::name() { return "SpriteAnimationLoader"; }

const reflect::properties_t& Type<SpriteAnimationLoader>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class AssetLoader properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<SpriteAnimationLoader>::size()
{
    return sizeof(SpriteAnimationLoader);
}

void reflect::Type<SpriteAnimationLoader>::from_string(const std::string& str, SpriteAnimationLoader& type)
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

std::string reflect::Type<SpriteAnimationLoader>::to_string(const SpriteAnimationLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class AssetLoader properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<SpriteAnimationLoader>::from_json(const std::string& json, SpriteAnimationLoader& type)
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

std::string reflect::Type<SpriteAnimationLoader>::to_json(const SpriteAnimationLoader& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SpriteAnimationLoader\"" << "," << std::endl;
    // Parent class AssetLoader properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SpriteAnimationLoader::type_meta() const { return reflect::Type<SpriteAnimationLoader>::meta(); }
const char* const SpriteAnimationLoader::type_name() const { return reflect::Type<SpriteAnimationLoader>::name(); }
const reflect::properties_t& SpriteAnimationLoader::type_properties() const { return reflect::Type<SpriteAnimationLoader>::properties(); }
SpriteAnimationLoader::operator std::string() const { return reflect::Type<SpriteAnimationLoader>::to_string(*this); }
void SpriteAnimationLoader::from_string(const std::string& str)
{
    reflect::Type<SpriteAnimationLoader>::from_string(str, *this);
    type_initialize();
}
void SpriteAnimationLoader::from_json(const std::string& json)
{
    reflect::Type<SpriteAnimationLoader>::from_json(json, *this);
    type_initialize();
}
std::string SpriteAnimationLoader::to_json(const std::string& offset) const { return reflect::Type<SpriteAnimationLoader>::to_json(*this, offset); }