// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "scene_window.h"

const reflect::meta_t& reflect::Type<SceneWindow>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Window" },
    };
    return s_meta;
}
const char* const reflect::Type<SceneWindow>::name() { return "SceneWindow"; }

const reflect::properties_t& Type<SceneWindow>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Window properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<SceneWindow>::size()
{
    return sizeof(SceneWindow);
}

void reflect::Type<SceneWindow>::from_string(const std::string& str, SceneWindow& type)
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
    
    // Parent class Window properties
    // Properties
}

std::string reflect::Type<SceneWindow>::to_string(const SceneWindow& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class Window properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<SceneWindow>::from_json(const std::string& json, SceneWindow& type)
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
            // Parent class Window properties
            // Properties
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<SceneWindow>::to_json(const SceneWindow& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SceneWindow\"" << "," << std::endl;
    // Parent class Window properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SceneWindow::type_meta() const { return reflect::Type<SceneWindow>::meta(); }
const char* const SceneWindow::type_name() const { return reflect::Type<SceneWindow>::name(); }
const reflect::properties_t& SceneWindow::type_properties() const { return reflect::Type<SceneWindow>::properties(); }
SceneWindow::operator std::string() const { return reflect::Type<SceneWindow>::to_string(*this); }
void SceneWindow::from_string(const std::string& str) { reflect::Type<SceneWindow>::from_string(str, *this); }
void SceneWindow::from_json(const std::string& json) { reflect::Type<SceneWindow>::from_json(json, *this); }
std::string SceneWindow::to_json(const std::string& offset) const { return reflect::Type<SceneWindow>::to_json(*this, offset); }