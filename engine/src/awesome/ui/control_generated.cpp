// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "control.h"
#pragma warning(disable: 4100)

IType* const reflect::Type<Control>::instantiate()
{
    return dynamic_cast<IType*>(new Control());
}

const reflect::meta_t& reflect::Type<Control>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<Control>::name() { return "Control"; }

const reflect::properties_t& Type<Control>::properties()
{
    static reflect::properties_t s_properties {
        { "isFocusable", reflect::Property{ offsetof(Control, isFocusable), reflect::meta_t { }, "isFocusable", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "isInteractable", reflect::Property{ offsetof(Control, isInteractable), reflect::meta_t { }, "isInteractable", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "name", reflect::Property{ offsetof(Control, name), reflect::meta_t { }, "name", reflect::PropertyType{ "std::string", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::string), reflect::PropertyType::Type::T_string } } },
        { "position", reflect::Property{ offsetof(Control, position), reflect::meta_t { }, "position", reflect::PropertyType{ "math::vec2", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(math::vec2), reflect::PropertyType::Type::T_native } } },
        { "replicate", reflect::Property{ offsetof(Control, replicate), reflect::meta_t { }, "replicate", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "tag", reflect::Property{ offsetof(Control, tag), reflect::meta_t { }, "tag", reflect::PropertyType{ "std::string", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::string), reflect::PropertyType::Type::T_string } } },
        { "m_children", reflect::Property{ offsetof(Control, m_children), reflect::meta_t { }, "m_children", reflect::PropertyType{ "std::vector<std::unique_ptr<Control>>", { 
            reflect::PropertyType{ "std::unique_ptr<Control>", { 
                reflect::PropertyType{ "Control", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(Control), reflect::PropertyType::Type::T_type },
            }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::unique_ptr<Control>), reflect::PropertyType::Type::T_template },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::vector<std::unique_ptr<Control>>), reflect::PropertyType::Type::T_template } } },
        { "m_behaviours", reflect::Property{ offsetof(Control, m_behaviours), reflect::meta_t { }, "m_behaviours", reflect::PropertyType{ "std::vector<std::unique_ptr<ControlBehaviour>>", { 
            reflect::PropertyType{ "std::unique_ptr<ControlBehaviour>", { 
                reflect::PropertyType{ "ControlBehaviour", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(ControlBehaviour), reflect::PropertyType::Type::T_type },
            }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::unique_ptr<ControlBehaviour>), reflect::PropertyType::Type::T_template },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::vector<std::unique_ptr<ControlBehaviour>>), reflect::PropertyType::Type::T_template } } },
    };
    return s_properties;
}

std::size_t reflect::Type<Control>::size()
{
    return sizeof(Control);
}

void reflect::Type<Control>::from_string(const std::string& str, Control& type)
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
    
    stream >> type.isFocusable;
    stream >> type.isInteractable;
    stream >> type.name;
    {
        std::string pack;
        stream >> pack;
        reflect::Type<math::vec2>::from_string(pack, type.position);
    }
    stream >> type.replicate;
    stream >> type.tag;
    {
        type.m_children.clear();
        std::size_t size;
        stream >> size;
        for (int i = 0; i < size; ++i)
        {
            std::unique_ptr<Control> element;
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
                        element = std::make_unique<Control>();
                    }
                    else
                    {
                        element = std::unique_ptr<Control>(TypeFactory::instantiate<Control>(type_id));
                    }
                    {
                        std::string pack;
                        stream >> pack;
                        element->from_string(pack);
                    }
                }
            }
            type.m_children.push_back(std::move(element));
        }
    }
    {
        type.m_behaviours.clear();
        std::size_t size;
        stream >> size;
        for (int i = 0; i < size; ++i)
        {
            std::unique_ptr<ControlBehaviour> element;
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
                    if (type_id == Type<ControlBehaviour>::name())
                    {
                        element = std::make_unique<ControlBehaviour>();
                    }
                    else
                    {
                        element = std::unique_ptr<ControlBehaviour>(TypeFactory::instantiate<ControlBehaviour>(type_id));
                    }
                    {
                        std::string pack;
                        stream >> pack;
                        element->from_string(pack);
                    }
                }
            }
            type.m_behaviours.push_back(std::move(element));
        }
    }
}

std::string reflect::Type<Control>::to_string(const Control& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << type.isFocusable;
    stream << type.isInteractable;
    stream << type.name;
    stream << reflect::Type<math::vec2>::to_string(type.position);
    stream << type.replicate;
    stream << type.tag;
    {
        stream << type.m_children.size();
        for (const auto& element : type.m_children)
        {
            stream << (element ? true : false); 
            if(element) stream << static_cast<std::string>(*element);
        }
    }
    {
        stream << type.m_behaviours.size();
        for (const auto& element : type.m_behaviours)
        {
            stream << (element ? true : false); 
            if(element) stream << static_cast<std::string>(*element);
        }
    }
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<Control>::from_json(const std::string& json, Control& type)
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
            if (key == "isFocusable") reflect::encoding::json::Deserializer::parse(value, type.isFocusable);
            if (key == "isInteractable") reflect::encoding::json::Deserializer::parse(value, type.isInteractable);
            if (key == "name") reflect::encoding::json::Deserializer::parse(value, type.name);
            if (key == "position") reflect::Type<math::vec2>::from_json(value, type.position);
            if (key == "replicate") reflect::encoding::json::Deserializer::parse(value, type.replicate);
            if (key == "tag") reflect::encoding::json::Deserializer::parse(value, type.tag);
            if (key == "m_children") reflect::encoding::json::Deserializer::parse(value, type.m_children);
            if (key == "m_behaviours") reflect::encoding::json::Deserializer::parse(value, type.m_behaviours);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<Control>::to_json(const Control& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"Control\"" << "," << std::endl;
    stream << offset << "    " << "\"isFocusable\": " << reflect::encoding::json::Serializer::to_string(type.isFocusable) << "," << std::endl;
    stream << offset << "    " << "\"isInteractable\": " << reflect::encoding::json::Serializer::to_string(type.isInteractable) << "," << std::endl;
    stream << offset << "    " << "\"name\": " << reflect::encoding::json::Serializer::to_string(type.name) << "," << std::endl;
    stream << offset << "    " << "\"position\": " << reflect::Type<math::vec2>::to_json(type.position, offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"replicate\": " << reflect::encoding::json::Serializer::to_string(type.replicate) << "," << std::endl;
    stream << offset << "    " << "\"tag\": " << reflect::encoding::json::Serializer::to_string(type.tag) << "," << std::endl;
    stream << offset << "    " << "\"m_children\": " << reflect::encoding::json::Serializer::to_string(type.m_children) << "," << std::endl;
    stream << offset << "    " << "\"m_behaviours\": " << reflect::encoding::json::Serializer::to_string(type.m_behaviours) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& Control::type_meta() const { return reflect::Type<Control>::meta(); }
const char* const Control::type_name() const { return reflect::Type<Control>::name(); }
const reflect::properties_t& Control::type_properties() const { return reflect::Type<Control>::properties(); }
Control::operator std::string() const { return reflect::Type<Control>::to_string(*this); }
void Control::from_string(const std::string& str)
{
    reflect::Type<Control>::from_string(str, *this);
    type_initialize();
}
void Control::from_json(const std::string& json)
{
    reflect::Type<Control>::from_json(json, *this);
    type_initialize();
}
std::string Control::to_json(const std::string& offset) const { return reflect::Type<Control>::to_json(*this, offset); }