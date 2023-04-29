// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "image_asset_handler.h"

const reflect::meta_t& reflect::Type<ImageAssetHandler>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "AssetHandler" },
    };
    return s_meta;
}
const char* const reflect::Type<ImageAssetHandler>::name() { return "ImageAssetHandler"; }

const reflect::properties_t& Type<ImageAssetHandler>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class AssetHandler properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<ImageAssetHandler>::size()
{
    return sizeof(ImageAssetHandler);
}

void reflect::Type<ImageAssetHandler>::from_string(const std::string& str, ImageAssetHandler& type)
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
    
    // Parent class AssetHandler properties
    // Properties
}

std::string reflect::Type<ImageAssetHandler>::to_string(const ImageAssetHandler& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class AssetHandler properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<ImageAssetHandler>::from_json(const std::string& json, ImageAssetHandler& type)
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
            // Parent class AssetHandler properties
            // Properties
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<ImageAssetHandler>::to_json(const ImageAssetHandler& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"ImageAssetHandler\"" << "," << std::endl;
    // Parent class AssetHandler properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& ImageAssetHandler::type_meta() const { return reflect::Type<ImageAssetHandler>::meta(); }
const char* const ImageAssetHandler::type_name() const { return reflect::Type<ImageAssetHandler>::name(); }
const reflect::properties_t& ImageAssetHandler::type_properties() const { return reflect::Type<ImageAssetHandler>::properties(); }
ImageAssetHandler::operator std::string() const { return reflect::Type<ImageAssetHandler>::to_string(*this); }
void ImageAssetHandler::from_string(const std::string& str) { reflect::Type<ImageAssetHandler>::from_string(str, *this); }
void ImageAssetHandler::from_json(const std::string& json) { reflect::Type<ImageAssetHandler>::from_json(json, *this); }
std::string ImageAssetHandler::to_json(const std::string& offset) const { return reflect::Type<ImageAssetHandler>::to_json(*this, offset); }