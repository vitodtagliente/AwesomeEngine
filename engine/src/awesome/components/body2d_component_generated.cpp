// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "body2d_component.h"
#pragma warning(disable: 4100)

const reflect::meta_t& reflect::Type<Body2dComponent>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Component" },
    };
    return s_meta;
}
const char* const reflect::Type<Body2dComponent>::name() { return "Body2dComponent"; }

const reflect::properties_t& Type<Body2dComponent>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Component properties
        { "enabled", reflect::Property{ offsetof(Body2dComponent, enabled), reflect::meta_t { }, "enabled", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "m_id", reflect::Property{ offsetof(Body2dComponent, m_id), reflect::meta_t { }, "m_id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<Body2dComponent>::size()
{
    return sizeof(Body2dComponent);
}

void reflect::Type<Body2dComponent>::from_string(const std::string& str, Body2dComponent& type)
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
    
    // Parent class Component properties
    stream >> type.enabled;
    {
        std::string pack;
        stream >> pack;
        type.m_id.from_string(pack);
    }
    // Properties
}

std::string reflect::Type<Body2dComponent>::to_string(const Body2dComponent& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class Component properties
    stream << type.enabled;
    stream << static_cast<std::string>(type.m_id);
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<Body2dComponent>::from_json(const std::string& json, Body2dComponent& type)
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
            // Parent class Component properties
            if (key == "enabled") reflect::encoding::json::Deserializer::parse(value, type.enabled);
            if (key == "m_id") type.m_id.from_json(value);
            // Properties
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<Body2dComponent>::to_json(const Body2dComponent& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"Body2dComponent\"" << "," << std::endl;
    // Parent class Component properties
    stream << offset << "    " << "\"enabled\": " << reflect::encoding::json::Serializer::to_string(type.enabled) << "," << std::endl;
    stream << offset << "    " << "\"m_id\": " << type.m_id.to_json(offset + "    ") << "," << std::endl;
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& Body2dComponent::type_meta() const { return reflect::Type<Body2dComponent>::meta(); }
const char* const Body2dComponent::type_name() const { return reflect::Type<Body2dComponent>::name(); }
const reflect::properties_t& Body2dComponent::type_properties() const { return reflect::Type<Body2dComponent>::properties(); }
Body2dComponent::operator std::string() const { return reflect::Type<Body2dComponent>::to_string(*this); }
void Body2dComponent::from_string(const std::string& str)
{
    reflect::Type<Body2dComponent>::from_string(str, *this);
    type_initialize();
}
void Body2dComponent::from_json(const std::string& json)
{
    reflect::Type<Body2dComponent>::from_json(json, *this);
    type_initialize();
}
std::string Body2dComponent::to_json(const std::string& offset) const { return reflect::Type<Body2dComponent>::to_json(*this, offset); }