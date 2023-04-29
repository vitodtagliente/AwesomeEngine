// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "content_browser_window.h"

const reflect::meta_t& reflect::Type<ContentBrowserWindow>::meta()
{
    static reflect::meta_t s_meta {
        { "Type", "Window" },
    };
    return s_meta;
}
const char* const reflect::Type<ContentBrowserWindow>::name() { return "ContentBrowserWindow"; }

const reflect::properties_t& Type<ContentBrowserWindow>::properties()
{
    static reflect::properties_t s_properties {
        // Parent class Window properties
        // Properties
    };
    return s_properties;
}

std::size_t reflect::Type<ContentBrowserWindow>::size()
{
    return sizeof(ContentBrowserWindow);
}

void reflect::Type<ContentBrowserWindow>::from_string(const std::string& str, ContentBrowserWindow& type)
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

std::string reflect::Type<ContentBrowserWindow>::to_string(const ContentBrowserWindow& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    // Parent class Window properties
    // Properties
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<ContentBrowserWindow>::from_json(const std::string& json, ContentBrowserWindow& type)
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

std::string reflect::Type<ContentBrowserWindow>::to_json(const ContentBrowserWindow& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"ContentBrowserWindow\"" << "," << std::endl;
    // Parent class Window properties
    // Properties
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& ContentBrowserWindow::type_meta() const { return reflect::Type<ContentBrowserWindow>::meta(); }
const char* const ContentBrowserWindow::type_name() const { return reflect::Type<ContentBrowserWindow>::name(); }
const reflect::properties_t& ContentBrowserWindow::type_properties() const { return reflect::Type<ContentBrowserWindow>::properties(); }
ContentBrowserWindow::operator std::string() const { return reflect::Type<ContentBrowserWindow>::to_string(*this); }
void ContentBrowserWindow::from_string(const std::string& str)
{
    reflect::Type<ContentBrowserWindow>::from_string(str, *this);
    type_initialize();
}
void ContentBrowserWindow::from_json(const std::string& json)
{
    reflect::Type<ContentBrowserWindow>::from_json(json, *this);
    type_initialize();
}
std::string ContentBrowserWindow::to_json(const std::string& offset) const { return reflect::Type<ContentBrowserWindow>::to_json(*this, offset); }