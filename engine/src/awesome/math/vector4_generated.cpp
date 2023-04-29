// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "vector4.h"
#pragma warning(disable: 4100)

const reflect::meta_t& reflect::Type<math::vec4>::meta()
{
    static reflect::meta_t s_meta {
        { "forward_declaration", "namespace math { typedef struct vector4_t<float> vec4; }" },
    };
    return s_meta;
}
const char* const reflect::Type<math::vec4>::name() { return "math::vec4"; }

const reflect::properties_t& Type<math::vec4>::properties()
{
    static reflect::properties_t s_properties {
        { "x", reflect::Property{ offsetof(math::vec4, x), reflect::meta_t { }, "x", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
        { "y", reflect::Property{ offsetof(math::vec4, y), reflect::meta_t { }, "y", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
        { "z", reflect::Property{ offsetof(math::vec4, z), reflect::meta_t { }, "z", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
        { "w", reflect::Property{ offsetof(math::vec4, w), reflect::meta_t { }, "w", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
    };
    return s_properties;
}

std::size_t reflect::Type<math::vec4>::size()
{
    return sizeof(math::vec4);
}

void reflect::Type<math::vec4>::from_string(const std::string& str, math::vec4& type)
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
    
    stream >> type.x;
    stream >> type.y;
    stream >> type.z;
    stream >> type.w;
}

std::string reflect::Type<math::vec4>::to_string(const math::vec4& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << type.x;
    stream << type.y;
    stream << type.z;
    stream << type.w;
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<math::vec4>::from_json(const std::string& json, math::vec4& type)
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
            if (key == "x") reflect::encoding::json::Deserializer::parse(value, type.x);
            if (key == "y") reflect::encoding::json::Deserializer::parse(value, type.y);
            if (key == "z") reflect::encoding::json::Deserializer::parse(value, type.z);
            if (key == "w") reflect::encoding::json::Deserializer::parse(value, type.w);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<math::vec4>::to_json(const math::vec4& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"math::vec4\"" << "," << std::endl;
    stream << offset << "    " << "\"x\": " << reflect::encoding::json::Serializer::to_string(type.x) << "," << std::endl;
    stream << offset << "    " << "\"y\": " << reflect::encoding::json::Serializer::to_string(type.y) << "," << std::endl;
    stream << offset << "    " << "\"z\": " << reflect::encoding::json::Serializer::to_string(type.z) << "," << std::endl;
    stream << offset << "    " << "\"w\": " << reflect::encoding::json::Serializer::to_string(type.w) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}