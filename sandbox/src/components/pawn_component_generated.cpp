// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "pawn_component.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<PawnComponent>::instantiate()
{
    return dynamic_cast<IType*>(new PawnComponent());
}

const reflect::meta_t& reflect::Type<PawnComponent>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Component" },
    };
    return s_meta;
}
const char* const reflect::Type<PawnComponent>::name() { return "PawnComponent"; }

const reflect::properties_t& Type<PawnComponent>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Component properties
        { "enabled", reflect::Property{ offsetof(PawnComponent, enabled), reflect::meta_t { }, "enabled", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "m_id", reflect::Property{ offsetof(PawnComponent, m_id), reflect::meta_t { }, "m_id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        // Properties
        { "speed", reflect::Property{ offsetof(PawnComponent, speed), reflect::meta_t { }, "speed", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
        { "dashSpeed", reflect::Property{ offsetof(PawnComponent, dashSpeed), reflect::meta_t { }, "dashSpeed", reflect::PropertyType{ "float", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(float), reflect::PropertyType::Type::T_float } } },
    };
    return s_properties;
}

std::size_t reflect::Type<PawnComponent>::size()
{
    return sizeof(PawnComponent);
}

void reflect::Type<PawnComponent>::from_string(const std::string& str, PawnComponent& type)
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
    stream >> type.speed;
    stream >> type.dashSpeed;
}

std::string reflect::Type<PawnComponent>::to_string(const PawnComponent& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class Component properties
    stream << type.enabled;
    stream << static_cast<std::string>(type.m_id);
    // Properties
    stream << type.speed;
    stream << type.dashSpeed;
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<PawnComponent>::from_json(const std::string& json, PawnComponent& type)
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
            if (key == "speed") reflect::encoding::json::Deserializer::parse(value, type.speed);
            if (key == "dashSpeed") reflect::encoding::json::Deserializer::parse(value, type.dashSpeed);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<PawnComponent>::to_json(const PawnComponent& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"PawnComponent\"" << "," << std::endl;
    // Parent class Component properties
    stream << offset << "    " << "\"enabled\": " << reflect::encoding::json::Serializer::to_string(type.enabled) << "," << std::endl;
    stream << offset << "    " << "\"m_id\": " << type.m_id.to_json(offset + "    ") << "," << std::endl;
    // Properties
    stream << offset << "    " << "\"speed\": " << reflect::encoding::json::Serializer::to_string(type.speed) << "," << std::endl;
    stream << offset << "    " << "\"dashSpeed\": " << reflect::encoding::json::Serializer::to_string(type.dashSpeed) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& PawnComponent::type_meta() const { return reflect::Type<PawnComponent>::meta(); }
const char* const PawnComponent::type_name() const { return reflect::Type<PawnComponent>::name(); }
const reflect::properties_t& PawnComponent::type_properties() const { return reflect::Type<PawnComponent>::properties(); }
PawnComponent::operator std::string() const { return reflect::Type<PawnComponent>::to_string(*this); }
void PawnComponent::from_string(const std::string& str)
{
    reflect::Type<PawnComponent>::from_string(str, *this);
    type_initialize();
}
void PawnComponent::from_json(const std::string& json)
{
    reflect::Type<PawnComponent>::from_json(json, *this);
    type_initialize();
}
std::string PawnComponent::to_json(const std::string& offset) const { return reflect::Type<PawnComponent>::to_json(*this, offset); }