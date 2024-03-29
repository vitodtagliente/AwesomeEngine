// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "asset.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<Asset>::instantiate()
{
    return dynamic_cast<IType*>(new Asset());
}

const reflect::meta_t& reflect::Type<Asset>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<Asset>::name() { return "Asset"; }

const reflect::properties_t& Type<Asset>::properties()
{
    static reflect::properties_t s_properties {
        { "id", reflect::Property{ offsetof(Asset, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(Asset, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
    };
    return s_properties;
}

std::size_t reflect::Type<Asset>::size()
{
    return sizeof(Asset);
}

void reflect::Type<Asset>::from_string(const std::string& str, Asset& type)
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
    
    {
        std::string pack;
        stream >> pack;
        type.id.from_string(pack);
    }
    stream >> type.type;
}

std::string reflect::Type<Asset>::to_string(const Asset& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << static_cast<std::string>(type.id);
    stream << type.type;
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<Asset>::from_json(const std::string& json, Asset& type)
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
            if (key == "id") type.id.from_json(value);
            if (key == "type") reflect::encoding::json::Deserializer::parse(value, type.type);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<Asset>::to_json(const Asset& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"Asset\"" << "," << std::endl;
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& Asset::type_meta() const { return reflect::Type<Asset>::meta(); }
const char* const Asset::type_name() const { return reflect::Type<Asset>::name(); }
const reflect::properties_t& Asset::type_properties() const { return reflect::Type<Asset>::properties(); }
Asset::operator std::string() const { return reflect::Type<Asset>::to_string(*this); }
void Asset::from_string(const std::string& str)
{
    reflect::Type<Asset>::from_string(str, *this);
    type_initialize();
}
void Asset::from_json(const std::string& json)
{
    reflect::Type<Asset>::from_json(json, *this);
    type_initialize();
}
std::string Asset::to_json(const std::string& offset) const { return reflect::Type<Asset>::to_json(*this, offset); }