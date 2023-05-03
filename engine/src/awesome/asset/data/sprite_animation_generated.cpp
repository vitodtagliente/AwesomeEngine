// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "sprite_animation.h"
#pragma warning(disable: 4100)

const reflect::meta_t& reflect::Type<SpriteAnimationFrame>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<SpriteAnimationFrame>::name() { return "SpriteAnimationFrame"; }

const reflect::properties_t& Type<SpriteAnimationFrame>::properties()
{
    static reflect::properties_t s_properties {
        { "rect", reflect::Property{ offsetof(SpriteAnimationFrame, rect), reflect::meta_t { }, "rect", reflect::PropertyType{ "graphics::TextureRect", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(graphics::TextureRect), reflect::PropertyType::Type::T_native } } },
        { "duration", reflect::Property{ offsetof(SpriteAnimationFrame, duration), reflect::meta_t { }, "duration", reflect::PropertyType{ "double", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(double), reflect::PropertyType::Type::T_double } } },
    };
    return s_properties;
}

std::size_t reflect::Type<SpriteAnimationFrame>::size()
{
    return sizeof(SpriteAnimationFrame);
}

void reflect::Type<SpriteAnimationFrame>::from_string(const std::string& str, SpriteAnimationFrame& type)
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
        reflect::Type<graphics::TextureRect>::from_string(pack, type.rect);
    }
    stream >> type.duration;
}

std::string reflect::Type<SpriteAnimationFrame>::to_string(const SpriteAnimationFrame& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << reflect::Type<graphics::TextureRect>::to_string(type.rect);
    stream << type.duration;
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<SpriteAnimationFrame>::from_json(const std::string& json, SpriteAnimationFrame& type)
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
            if (key == "rect") reflect::Type<graphics::TextureRect>::from_json(value, type.rect);
            if (key == "duration") reflect::encoding::json::Deserializer::parse(value, type.duration);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<SpriteAnimationFrame>::to_json(const SpriteAnimationFrame& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SpriteAnimationFrame\"" << "," << std::endl;
    stream << offset << "    " << "\"rect\": " << reflect::Type<graphics::TextureRect>::to_json(type.rect, offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"duration\": " << reflect::encoding::json::Serializer::to_string(type.duration) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SpriteAnimationFrame::type_meta() const { return reflect::Type<SpriteAnimationFrame>::meta(); }
const char* const SpriteAnimationFrame::type_name() const { return reflect::Type<SpriteAnimationFrame>::name(); }
const reflect::properties_t& SpriteAnimationFrame::type_properties() const { return reflect::Type<SpriteAnimationFrame>::properties(); }
SpriteAnimationFrame::operator std::string() const { return reflect::Type<SpriteAnimationFrame>::to_string(*this); }
void SpriteAnimationFrame::from_string(const std::string& str)
{
    reflect::Type<SpriteAnimationFrame>::from_string(str, *this);
    type_initialize();
}
void SpriteAnimationFrame::from_json(const std::string& json)
{
    reflect::Type<SpriteAnimationFrame>::from_json(json, *this);
    type_initialize();
}
std::string SpriteAnimationFrame::to_json(const std::string& offset) const { return reflect::Type<SpriteAnimationFrame>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<SpriteAnimation>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<SpriteAnimation>::name() { return "SpriteAnimation"; }

const reflect::properties_t& Type<SpriteAnimation>::properties()
{
    static reflect::properties_t s_properties {
        { "image", reflect::Property{ offsetof(SpriteAnimation, image), reflect::meta_t { }, "image", reflect::PropertyType{ "ImageAsset", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(ImageAsset), reflect::PropertyType::Type::T_type } } },
        { "startingFrame", reflect::Property{ offsetof(SpriteAnimation, startingFrame), reflect::meta_t { }, "startingFrame", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
        { "frames", reflect::Property{ offsetof(SpriteAnimation, frames), reflect::meta_t { }, "frames", reflect::PropertyType{ "std::vector<SpriteAnimationFrame>", { 
            reflect::PropertyType{ "SpriteAnimationFrame", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(SpriteAnimationFrame), reflect::PropertyType::Type::T_type },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::vector<SpriteAnimationFrame>), reflect::PropertyType::Type::T_template } } },
    };
    return s_properties;
}

std::size_t reflect::Type<SpriteAnimation>::size()
{
    return sizeof(SpriteAnimation);
}

void reflect::Type<SpriteAnimation>::from_string(const std::string& str, SpriteAnimation& type)
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
        type.image.from_string(pack);
    }
    stream >> type.startingFrame;
    {
        type.frames.clear();
        std::size_t size;
        stream >> size;
        for (int i = 0; i < size; ++i)
        {
            SpriteAnimationFrame element;
            {
                std::string pack;
                stream >> pack;
                element.from_string(pack);
            }
            type.frames.push_back(std::move(element));
        }
    }
}

std::string reflect::Type<SpriteAnimation>::to_string(const SpriteAnimation& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << static_cast<std::string>(type.image);
    stream << type.startingFrame;
    {
        stream << type.frames.size();
        for (const auto& element : type.frames)
        {
            stream << static_cast<std::string>(element);
        }
    }
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<SpriteAnimation>::from_json(const std::string& json, SpriteAnimation& type)
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
            if (key == "image") type.image.from_json(value);
            if (key == "startingFrame") reflect::encoding::json::Deserializer::parse(value, type.startingFrame);
            if (key == "frames") reflect::encoding::json::Deserializer::parse(value, type.frames);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<SpriteAnimation>::to_json(const SpriteAnimation& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SpriteAnimation\"" << "," << std::endl;
    stream << offset << "    " << "\"image\": " << type.image.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"startingFrame\": " << reflect::encoding::json::Serializer::to_string(type.startingFrame) << "," << std::endl;
    stream << offset << "    " << "\"frames\": " << reflect::encoding::json::Serializer::to_string(type.frames) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SpriteAnimation::type_meta() const { return reflect::Type<SpriteAnimation>::meta(); }
const char* const SpriteAnimation::type_name() const { return reflect::Type<SpriteAnimation>::name(); }
const reflect::properties_t& SpriteAnimation::type_properties() const { return reflect::Type<SpriteAnimation>::properties(); }
SpriteAnimation::operator std::string() const { return reflect::Type<SpriteAnimation>::to_string(*this); }
void SpriteAnimation::from_string(const std::string& str)
{
    reflect::Type<SpriteAnimation>::from_string(str, *this);
    type_initialize();
}
void SpriteAnimation::from_json(const std::string& json)
{
    reflect::Type<SpriteAnimation>::from_json(json, *this);
    type_initialize();
}
std::string SpriteAnimation::to_json(const std::string& offset) const { return reflect::Type<SpriteAnimation>::to_json(*this, offset); }