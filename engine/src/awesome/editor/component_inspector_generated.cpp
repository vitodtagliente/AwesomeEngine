// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "component_inspector.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<ComponentInspector>::instantiate()
{
    return dynamic_cast<IType*>(new ComponentInspector());
}

const reflect::meta_t& reflect::Type<ComponentInspector>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<ComponentInspector>::name() { return "ComponentInspector"; }

const reflect::properties_t& Type<ComponentInspector>::properties()
{
    static reflect::properties_t s_properties {
    };
    return s_properties;
}

std::size_t reflect::Type<ComponentInspector>::size()
{
    return sizeof(ComponentInspector);
}

void reflect::Type<ComponentInspector>::from_string(const std::string& str, ComponentInspector& type)
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
    
}

std::string reflect::Type<ComponentInspector>::to_string(const ComponentInspector& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<ComponentInspector>::from_json(const std::string& json, ComponentInspector& type)
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
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<ComponentInspector>::to_json(const ComponentInspector& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"ComponentInspector\"" << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& ComponentInspector::type_meta() const { return reflect::Type<ComponentInspector>::meta(); }
const char* const ComponentInspector::type_name() const { return reflect::Type<ComponentInspector>::name(); }
const reflect::properties_t& ComponentInspector::type_properties() const { return reflect::Type<ComponentInspector>::properties(); }
ComponentInspector::operator std::string() const { return reflect::Type<ComponentInspector>::to_string(*this); }
void ComponentInspector::from_string(const std::string& str)
{
    reflect::Type<ComponentInspector>::from_string(str, *this);
    type_initialize();
}
void ComponentInspector::from_json(const std::string& json)
{
    reflect::Type<ComponentInspector>::from_json(json, *this);
    type_initialize();
}
std::string ComponentInspector::to_json(const std::string& offset) const { return reflect::Type<ComponentInspector>::to_json(*this, offset); }