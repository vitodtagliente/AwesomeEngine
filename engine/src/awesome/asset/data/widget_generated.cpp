// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "widget.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<Widget>::instantiate()
{
    return dynamic_cast<IType*>(new Widget());
}

const reflect::meta_t& reflect::Type<Widget>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<Widget>::name() { return "Widget"; }

const reflect::properties_t& Type<Widget>::properties()
{
    static reflect::properties_t s_properties {
        { "control", reflect::Property{ offsetof(Widget, control), reflect::meta_t { }, "control", reflect::PropertyType{ "std::unique_ptr<Control>", { 
            reflect::PropertyType{ "Control", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(Control), reflect::PropertyType::Type::T_type },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::unique_ptr<Control>), reflect::PropertyType::Type::T_template } } },
    };
    return s_properties;
}

std::size_t reflect::Type<Widget>::size()
{
    return sizeof(Widget);
}

void reflect::Type<Widget>::from_string(const std::string& str, Widget& type)
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
        bool valid = false;
        stream >> valid;
        if (valid)
        {
            reflect::encoding::InputByteStream temp_stream(buffer, stream.getIndex());
            std::size_t temp_element_size;
            temp_stream >> temp_element_size;
            std::string type_id;
            temp_stream >> type_id;
            if (type_id == Type<Control>::name())
            {
                type.control = std::make_unique<Control>();
            }
            else
            {
                type.control = std::unique_ptr<Control>(TypeFactory::instantiate<Control>(type_id));
            }
            {
                std::string pack;
                stream >> pack;
                type.control->from_string(pack);
            }
        }
    }
}

std::string reflect::Type<Widget>::to_string(const Widget& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << (type.control ? true : false); 
    if(type.control) stream << static_cast<std::string>(*type.control);
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<Widget>::from_json(const std::string& json, Widget& type)
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
            if (key == "control") reflect::encoding::json::Deserializer::parse(value, type.control);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<Widget>::to_json(const Widget& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"Widget\"" << "," << std::endl;
    stream << offset << "    " << "\"control\": " << reflect::encoding::json::Serializer::to_string(type.control) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& Widget::type_meta() const { return reflect::Type<Widget>::meta(); }
const char* const Widget::type_name() const { return reflect::Type<Widget>::name(); }
const reflect::properties_t& Widget::type_properties() const { return reflect::Type<Widget>::properties(); }
Widget::operator std::string() const { return reflect::Type<Widget>::to_string(*this); }
void Widget::from_string(const std::string& str)
{
    reflect::Type<Widget>::from_string(str, *this);
    type_initialize();
}
void Widget::from_json(const std::string& json)
{
    reflect::Type<Widget>::from_json(json, *this);
    type_initialize();
}
std::string Widget::to_json(const std::string& offset) const { return reflect::Type<Widget>::to_json(*this, offset); }