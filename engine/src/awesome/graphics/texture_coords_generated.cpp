// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "texture_coords.h"

const reflect::meta_t& reflect::Type<graphics::TextureCoords>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<graphics::TextureCoords>::name() { return "graphics::TextureCoords"; }

const reflect::properties_t& Type<graphics::TextureCoords>::properties()
{
    static reflect::properties_t s_properties {
        { "u", reflect::Property{ offsetof(graphics::TextureCoords, u), reflect::meta_t { }, "u", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
        { "v", reflect::Property{ offsetof(graphics::TextureCoords, v), reflect::meta_t { }, "v", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
    };
    return s_properties;
}

std::size_t reflect::Type<graphics::TextureCoords>::size()
{
    return sizeof(graphics::TextureCoords);
}

void reflect::Type<graphics::TextureCoords>::from_string(const std::string& str, graphics::TextureCoords& type)
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
    
    stream >> type.u;
    stream >> type.v;
}

std::string reflect::Type<graphics::TextureCoords>::to_string(const graphics::TextureCoords& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << type.u;
    stream << type.v;
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<graphics::TextureCoords>::from_json(const std::string& json, graphics::TextureCoords& type)
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
            if (key == "u") reflect::encoding::json::Deserializer::parse(value, type.u);
            if (key == "v") reflect::encoding::json::Deserializer::parse(value, type.v);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<graphics::TextureCoords>::to_json(const graphics::TextureCoords& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"graphics::TextureCoords\"" << "," << std::endl;
    stream << offset << "    " << "\"u\": " << reflect::encoding::json::Serializer::to_string(type.u) << "," << std::endl;
    stream << offset << "    " << "\"v\": " << reflect::encoding::json::Serializer::to_string(type.v) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}