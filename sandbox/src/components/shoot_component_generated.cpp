// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "shoot_component.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<ShootComponent>::instantiate()
{
    return dynamic_cast<IType*>(new ShootComponent());
}

const reflect::meta_t& reflect::Type<ShootComponent>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Component" },
    };
    return s_meta;
}
const char* const reflect::Type<ShootComponent>::name() { return "ShootComponent"; }

const reflect::properties_t& Type<ShootComponent>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Component properties
        { "enabled", reflect::Property{ offsetof(ShootComponent, enabled), reflect::meta_t { }, "enabled", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "m_id", reflect::Property{ offsetof(ShootComponent, m_id), reflect::meta_t { }, "m_id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        // Properties
        { "m_bullet", reflect::Property{ offsetof(ShootComponent, m_bullet), reflect::meta_t { }, "m_bullet", reflect::PropertyType{ "PrefabAsset", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(PrefabAsset), reflect::PropertyType::Type::T_type } } },
        { "m_damage", reflect::Property{ offsetof(ShootComponent, m_damage), reflect::meta_t { }, "m_damage", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        { "m_frequency", reflect::Property{ offsetof(ShootComponent, m_frequency), reflect::meta_t { }, "m_frequency", reflect::PropertyType{ "double", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(double), reflect::PropertyType::Type::T_double } } },
    };
    return s_properties;
}

std::size_t reflect::Type<ShootComponent>::size()
{
    return sizeof(ShootComponent);
}

void reflect::Type<ShootComponent>::from_string(const std::string& str, ShootComponent& type)
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
    {
        std::string pack;
        stream >> pack;
        type.m_bullet.from_string(pack);
    }
    stream >> type.m_damage;
    stream >> type.m_frequency;
}

std::string reflect::Type<ShootComponent>::to_string(const ShootComponent& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class Component properties
    stream << type.enabled;
    stream << static_cast<std::string>(type.m_id);
    // Properties
    stream << static_cast<std::string>(type.m_bullet);
    stream << type.m_damage;
    stream << type.m_frequency;
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<ShootComponent>::from_json(const std::string& json, ShootComponent& type)
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
            if (key == "m_bullet") type.m_bullet.from_json(value);
            if (key == "m_damage") reflect::encoding::json::Deserializer::parse(value, type.m_damage);
            if (key == "m_frequency") reflect::encoding::json::Deserializer::parse(value, type.m_frequency);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<ShootComponent>::to_json(const ShootComponent& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"ShootComponent\"" << "," << std::endl;
    // Parent class Component properties
    stream << offset << "    " << "\"enabled\": " << reflect::encoding::json::Serializer::to_string(type.enabled) << "," << std::endl;
    stream << offset << "    " << "\"m_id\": " << type.m_id.to_json(offset + "    ") << "," << std::endl;
    // Properties
    stream << offset << "    " << "\"m_bullet\": " << type.m_bullet.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"m_damage\": " << reflect::encoding::json::Serializer::to_string(type.m_damage) << "," << std::endl;
    stream << offset << "    " << "\"m_frequency\": " << reflect::encoding::json::Serializer::to_string(type.m_frequency) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& ShootComponent::type_meta() const { return reflect::Type<ShootComponent>::meta(); }
const char* const ShootComponent::type_name() const { return reflect::Type<ShootComponent>::name(); }
const reflect::properties_t& ShootComponent::type_properties() const { return reflect::Type<ShootComponent>::properties(); }
ShootComponent::operator std::string() const { return reflect::Type<ShootComponent>::to_string(*this); }
void ShootComponent::from_string(const std::string& str)
{
    reflect::Type<ShootComponent>::from_string(str, *this);
    type_initialize();
}
void ShootComponent::from_json(const std::string& json)
{
    reflect::Type<ShootComponent>::from_json(json, *this);
    type_initialize();
}
std::string ShootComponent::to_json(const std::string& offset) const { return reflect::Type<ShootComponent>::to_json(*this, offset); }