// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "image_asset.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<ImageAsset>::instantiate()
{
    return dynamic_cast<IType*>(new ImageAsset());
}

const reflect::meta_t& reflect::Type<ImageAsset>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Asset" },
    };
    return s_meta;
}
const char* const reflect::Type<ImageAsset>::name() { return "ImageAsset"; }

const reflect::properties_t& Type<ImageAsset>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Asset properties
        { "id", reflect::Property{ offsetof(ImageAsset, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(ImageAsset, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<ImageAsset>::size()
{
    return sizeof(ImageAsset);
}

void reflect::Type<ImageAsset>::from_string(const std::string& str, ImageAsset& type)
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

std::string reflect::Type<ImageAsset>::to_string(const ImageAsset& type)
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

void reflect::Type<ImageAsset>::from_json(const std::string& json, ImageAsset& type)
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

std::string reflect::Type<ImageAsset>::to_json(const ImageAsset& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"ImageAsset\"" << "," << std::endl;
    // Parent class Asset properties
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& ImageAsset::type_meta() const { return reflect::Type<ImageAsset>::meta(); }
const char* const ImageAsset::type_name() const { return reflect::Type<ImageAsset>::name(); }
const reflect::properties_t& ImageAsset::type_properties() const { return reflect::Type<ImageAsset>::properties(); }
ImageAsset::operator std::string() const { return reflect::Type<ImageAsset>::to_string(*this); }
void ImageAsset::from_string(const std::string& str)
{
    reflect::Type<ImageAsset>::from_string(str, *this);
    type_initialize();
}
void ImageAsset::from_json(const std::string& json)
{
    reflect::Type<ImageAsset>::from_json(json, *this);
    type_initialize();
}
std::string ImageAsset::to_json(const std::string& offset) const { return reflect::Type<ImageAsset>::to_json(*this, offset); }

IType* const reflect::Type<ImageAssetLoader>::instantiate()
{
    return dynamic_cast<IType*>(new ImageAssetLoader());
}

const reflect::meta_t& reflect::Type<ImageAssetLoader>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "AssetLoader" },
    };
    return s_meta;
}
const char* const reflect::Type<ImageAssetLoader>::name() { return "ImageAssetLoader"; }

const reflect::properties_t& Type<ImageAssetLoader>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class AssetLoader properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<ImageAssetLoader>::size()
{
    return sizeof(ImageAssetLoader);
}

void reflect::Type<ImageAssetLoader>::from_string(const std::string& str, ImageAssetLoader& type)
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

std::string reflect::Type<ImageAssetLoader>::to_string(const ImageAssetLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class AssetLoader properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<ImageAssetLoader>::from_json(const std::string& json, ImageAssetLoader& type)
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

std::string reflect::Type<ImageAssetLoader>::to_json(const ImageAssetLoader& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"ImageAssetLoader\"" << "," << std::endl;
    // Parent class AssetLoader properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& ImageAssetLoader::type_meta() const { return reflect::Type<ImageAssetLoader>::meta(); }
const char* const ImageAssetLoader::type_name() const { return reflect::Type<ImageAssetLoader>::name(); }
const reflect::properties_t& ImageAssetLoader::type_properties() const { return reflect::Type<ImageAssetLoader>::properties(); }
ImageAssetLoader::operator std::string() const { return reflect::Type<ImageAssetLoader>::to_string(*this); }
void ImageAssetLoader::from_string(const std::string& str)
{
    reflect::Type<ImageAssetLoader>::from_string(str, *this);
    type_initialize();
}
void ImageAssetLoader::from_json(const std::string& json)
{
    reflect::Type<ImageAssetLoader>::from_json(json, *this);
    type_initialize();
}
std::string ImageAssetLoader::to_json(const std::string& offset) const { return reflect::Type<ImageAssetLoader>::to_json(*this, offset); }