// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "audio_asset.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<AudioAsset>::instantiate()
{
    return dynamic_cast<IType*>(new AudioAsset());
}

const reflect::meta_t& reflect::Type<AudioAsset>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Asset" },
    };
    return s_meta;
}
const char* const reflect::Type<AudioAsset>::name() { return "AudioAsset"; }

const reflect::properties_t& Type<AudioAsset>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Asset properties
        { "id", reflect::Property{ offsetof(AudioAsset, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(AudioAsset, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<AudioAsset>::size()
{
    return sizeof(AudioAsset);
}

void reflect::Type<AudioAsset>::from_string(const std::string& str, AudioAsset& type)
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

std::string reflect::Type<AudioAsset>::to_string(const AudioAsset& type)
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

void reflect::Type<AudioAsset>::from_json(const std::string& json, AudioAsset& type)
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

std::string reflect::Type<AudioAsset>::to_json(const AudioAsset& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"AudioAsset\"" << "," << std::endl;
    // Parent class Asset properties
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& AudioAsset::type_meta() const { return reflect::Type<AudioAsset>::meta(); }
const char* const AudioAsset::type_name() const { return reflect::Type<AudioAsset>::name(); }
const reflect::properties_t& AudioAsset::type_properties() const { return reflect::Type<AudioAsset>::properties(); }
AudioAsset::operator std::string() const { return reflect::Type<AudioAsset>::to_string(*this); }
void AudioAsset::from_string(const std::string& str)
{
    reflect::Type<AudioAsset>::from_string(str, *this);
    type_initialize();
}
void AudioAsset::from_json(const std::string& json)
{
    reflect::Type<AudioAsset>::from_json(json, *this);
    type_initialize();
}
std::string AudioAsset::to_json(const std::string& offset) const { return reflect::Type<AudioAsset>::to_json(*this, offset); }

IType* const reflect::Type<AudioAssetLoader>::instantiate()
{
    return dynamic_cast<IType*>(new AudioAssetLoader());
}

const reflect::meta_t& reflect::Type<AudioAssetLoader>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "AssetLoader" },
    };
    return s_meta;
}
const char* const reflect::Type<AudioAssetLoader>::name() { return "AudioAssetLoader"; }

const reflect::properties_t& Type<AudioAssetLoader>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class AssetLoader properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<AudioAssetLoader>::size()
{
    return sizeof(AudioAssetLoader);
}

void reflect::Type<AudioAssetLoader>::from_string(const std::string& str, AudioAssetLoader& type)
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

std::string reflect::Type<AudioAssetLoader>::to_string(const AudioAssetLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class AssetLoader properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<AudioAssetLoader>::from_json(const std::string& json, AudioAssetLoader& type)
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

std::string reflect::Type<AudioAssetLoader>::to_json(const AudioAssetLoader& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"AudioAssetLoader\"" << "," << std::endl;
    // Parent class AssetLoader properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& AudioAssetLoader::type_meta() const { return reflect::Type<AudioAssetLoader>::meta(); }
const char* const AudioAssetLoader::type_name() const { return reflect::Type<AudioAssetLoader>::name(); }
const reflect::properties_t& AudioAssetLoader::type_properties() const { return reflect::Type<AudioAssetLoader>::properties(); }
AudioAssetLoader::operator std::string() const { return reflect::Type<AudioAssetLoader>::to_string(*this); }
void AudioAssetLoader::from_string(const std::string& str)
{
    reflect::Type<AudioAssetLoader>::from_string(str, *this);
    type_initialize();
}
void AudioAssetLoader::from_json(const std::string& json)
{
    reflect::Type<AudioAssetLoader>::from_json(json, *this);
    type_initialize();
}
std::string AudioAssetLoader::to_json(const std::string& offset) const { return reflect::Type<AudioAssetLoader>::to_json(*this, offset); }