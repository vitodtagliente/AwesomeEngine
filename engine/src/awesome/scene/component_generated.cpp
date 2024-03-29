// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "component.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<Component>::instantiate()
{
    return dynamic_cast<IType*>(new Component());
}

const reflect::meta_t& reflect::Type<Component>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<Component>::name() { return "Component"; }

const reflect::properties_t& Type<Component>::properties()
{
    static reflect::properties_t s_properties {
        { "enabled", reflect::Property{ offsetof(Component, enabled), reflect::meta_t { }, "enabled", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "m_id", reflect::Property{ offsetof(Component, m_id), reflect::meta_t { }, "m_id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
    };
    return s_properties;
}

std::size_t reflect::Type<Component>::size()
{
    return sizeof(Component);
}

void reflect::Type<Component>::from_string(const std::string& str, Component& type)
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
    
    stream >> type.enabled;
    {
        std::string pack;
        stream >> pack;
        type.m_id.from_string(pack);
    }
}

std::string reflect::Type<Component>::to_string(const Component& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << type.enabled;
    stream << static_cast<std::string>(type.m_id);
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<Component>::from_json(const std::string& json, Component& type)
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
            if (key == "enabled") reflect::encoding::json::Deserializer::parse(value, type.enabled);
            if (key == "m_id") type.m_id.from_json(value);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<Component>::to_json(const Component& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"Component\"" << "," << std::endl;
    stream << offset << "    " << "\"enabled\": " << reflect::encoding::json::Serializer::to_string(type.enabled) << "," << std::endl;
    stream << offset << "    " << "\"m_id\": " << type.m_id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& Component::type_meta() const { return reflect::Type<Component>::meta(); }
const char* const Component::type_name() const { return reflect::Type<Component>::name(); }
const reflect::properties_t& Component::type_properties() const { return reflect::Type<Component>::properties(); }
Component::operator std::string() const { return reflect::Type<Component>::to_string(*this); }
void Component::from_string(const std::string& str)
{
    reflect::Type<Component>::from_string(str, *this);
    type_initialize();
}
void Component::from_json(const std::string& json)
{
    reflect::Type<Component>::from_json(json, *this);
    type_initialize();
}
std::string Component::to_json(const std::string& offset) const { return reflect::Type<Component>::to_json(*this, offset); }