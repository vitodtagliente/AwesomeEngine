// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "engine_settings.h"
#pragma warning(disable: 4100)

const char* const reflect::Enum<EngineMode>::name() { return "EngineMode"; }
const reflect::enum_values_t& reflect::Enum<EngineMode>::values()
{
    static reflect::enum_values_t s_values{
        { "Editor", static_cast<int>(EngineMode::Editor) }, 
        { "Server", static_cast<int>(EngineMode::Server) }, 
        { "Standalone", static_cast<int>(EngineMode::Standalone) }, 
    };
    return s_values;
}

const char* const reflect::Enum<FpsMode>::name() { return "FpsMode"; }
const reflect::enum_values_t& reflect::Enum<FpsMode>::values()
{
    static reflect::enum_values_t s_values{
        { "Fps30", static_cast<int>(FpsMode::Fps30) }, 
        { "Fps60", static_cast<int>(FpsMode::Fps60) }, 
        { "Fps90", static_cast<int>(FpsMode::Fps90) }, 
        { "Unlimited", static_cast<int>(FpsMode::Unlimited) }, 
    };
    return s_values;
}

const reflect::meta_t& reflect::Type<RendererSettings>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<RendererSettings>::name() { return "RendererSettings"; }

const reflect::properties_t& Type<RendererSettings>::properties()
{
    static reflect::properties_t s_properties {
        { "debug", reflect::Property{ offsetof(RendererSettings, debug), reflect::meta_t { }, "debug", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "renderCollisions", reflect::Property{ offsetof(RendererSettings, renderCollisions), reflect::meta_t { }, "renderCollisions", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "collisionWireColor", reflect::Property{ offsetof(RendererSettings, collisionWireColor), reflect::meta_t { }, "collisionWireColor", reflect::PropertyType{ "graphics::Color", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(graphics::Color), reflect::PropertyType::Type::T_native } } },
        { "renderQuadtree", reflect::Property{ offsetof(RendererSettings, renderQuadtree), reflect::meta_t { }, "renderQuadtree", reflect::PropertyType{ "bool", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(bool), reflect::PropertyType::Type::T_bool } } },
        { "quadtreeWireColor", reflect::Property{ offsetof(RendererSettings, quadtreeWireColor), reflect::meta_t { }, "quadtreeWireColor", reflect::PropertyType{ "graphics::Color", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(graphics::Color), reflect::PropertyType::Type::T_native } } },
    };
    return s_properties;
}

std::size_t reflect::Type<RendererSettings>::size()
{
    return sizeof(RendererSettings);
}

void reflect::Type<RendererSettings>::from_string(const std::string& str, RendererSettings& type)
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
    
    stream >> type.debug;
    stream >> type.renderCollisions;
    {
        std::string pack;
        stream >> pack;
        reflect::Type<graphics::Color>::from_string(pack, type.collisionWireColor);
    }
    stream >> type.renderQuadtree;
    {
        std::string pack;
        stream >> pack;
        reflect::Type<graphics::Color>::from_string(pack, type.quadtreeWireColor);
    }
}

std::string reflect::Type<RendererSettings>::to_string(const RendererSettings& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << type.debug;
    stream << type.renderCollisions;
    stream << reflect::Type<graphics::Color>::to_string(type.collisionWireColor);
    stream << type.renderQuadtree;
    stream << reflect::Type<graphics::Color>::to_string(type.quadtreeWireColor);
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<RendererSettings>::from_json(const std::string& json, RendererSettings& type)
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
            if (key == "debug") reflect::encoding::json::Deserializer::parse(value, type.debug);
            if (key == "renderCollisions") reflect::encoding::json::Deserializer::parse(value, type.renderCollisions);
            if (key == "collisionWireColor") reflect::Type<graphics::Color>::from_json(value, type.collisionWireColor);
            if (key == "renderQuadtree") reflect::encoding::json::Deserializer::parse(value, type.renderQuadtree);
            if (key == "quadtreeWireColor") reflect::Type<graphics::Color>::from_json(value, type.quadtreeWireColor);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<RendererSettings>::to_json(const RendererSettings& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"RendererSettings\"" << "," << std::endl;
    stream << offset << "    " << "\"debug\": " << reflect::encoding::json::Serializer::to_string(type.debug) << "," << std::endl;
    stream << offset << "    " << "\"renderCollisions\": " << reflect::encoding::json::Serializer::to_string(type.renderCollisions) << "," << std::endl;
    stream << offset << "    " << "\"collisionWireColor\": " << reflect::Type<graphics::Color>::to_json(type.collisionWireColor, offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"renderQuadtree\": " << reflect::encoding::json::Serializer::to_string(type.renderQuadtree) << "," << std::endl;
    stream << offset << "    " << "\"quadtreeWireColor\": " << reflect::Type<graphics::Color>::to_json(type.quadtreeWireColor, offset + "    ") << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& RendererSettings::type_meta() const { return reflect::Type<RendererSettings>::meta(); }
const char* const RendererSettings::type_name() const { return reflect::Type<RendererSettings>::name(); }
const reflect::properties_t& RendererSettings::type_properties() const { return reflect::Type<RendererSettings>::properties(); }
RendererSettings::operator std::string() const { return reflect::Type<RendererSettings>::to_string(*this); }
void RendererSettings::from_string(const std::string& str)
{
    reflect::Type<RendererSettings>::from_string(str, *this);
    type_initialize();
}
void RendererSettings::from_json(const std::string& json)
{
    reflect::Type<RendererSettings>::from_json(json, *this);
    type_initialize();
}
std::string RendererSettings::to_json(const std::string& offset) const { return reflect::Type<RendererSettings>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<SceneSettings>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<SceneSettings>::name() { return "SceneSettings"; }

const reflect::properties_t& Type<SceneSettings>::properties()
{
    static reflect::properties_t s_properties {
        { "editor", reflect::Property{ offsetof(SceneSettings, editor), reflect::meta_t { }, "editor", reflect::PropertyType{ "SceneAsset", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(SceneAsset), reflect::PropertyType::Type::T_type } } },
        { "server", reflect::Property{ offsetof(SceneSettings, server), reflect::meta_t { }, "server", reflect::PropertyType{ "SceneAsset", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(SceneAsset), reflect::PropertyType::Type::T_type } } },
        { "standalone", reflect::Property{ offsetof(SceneSettings, standalone), reflect::meta_t { }, "standalone", reflect::PropertyType{ "SceneAsset", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(SceneAsset), reflect::PropertyType::Type::T_type } } },
    };
    return s_properties;
}

std::size_t reflect::Type<SceneSettings>::size()
{
    return sizeof(SceneSettings);
}

void reflect::Type<SceneSettings>::from_string(const std::string& str, SceneSettings& type)
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
        type.editor.from_string(pack);
    }
    {
        std::string pack;
        stream >> pack;
        type.server.from_string(pack);
    }
    {
        std::string pack;
        stream >> pack;
        type.standalone.from_string(pack);
    }
}

std::string reflect::Type<SceneSettings>::to_string(const SceneSettings& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << static_cast<std::string>(type.editor);
    stream << static_cast<std::string>(type.server);
    stream << static_cast<std::string>(type.standalone);
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<SceneSettings>::from_json(const std::string& json, SceneSettings& type)
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
            if (key == "editor") type.editor.from_json(value);
            if (key == "server") type.server.from_json(value);
            if (key == "standalone") type.standalone.from_json(value);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<SceneSettings>::to_json(const SceneSettings& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"SceneSettings\"" << "," << std::endl;
    stream << offset << "    " << "\"editor\": " << type.editor.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"server\": " << type.server.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"standalone\": " << type.standalone.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& SceneSettings::type_meta() const { return reflect::Type<SceneSettings>::meta(); }
const char* const SceneSettings::type_name() const { return reflect::Type<SceneSettings>::name(); }
const reflect::properties_t& SceneSettings::type_properties() const { return reflect::Type<SceneSettings>::properties(); }
SceneSettings::operator std::string() const { return reflect::Type<SceneSettings>::to_string(*this); }
void SceneSettings::from_string(const std::string& str)
{
    reflect::Type<SceneSettings>::from_string(str, *this);
    type_initialize();
}
void SceneSettings::from_json(const std::string& json)
{
    reflect::Type<SceneSettings>::from_json(json, *this);
    type_initialize();
}
std::string SceneSettings::to_json(const std::string& offset) const { return reflect::Type<SceneSettings>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<EngineSettings>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<EngineSettings>::name() { return "EngineSettings"; }

const reflect::properties_t& Type<EngineSettings>::properties()
{
    static reflect::properties_t s_properties {
        { "fps", reflect::Property{ offsetof(EngineSettings, fps), reflect::meta_t { }, "fps", reflect::PropertyType{ "FpsMode", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(FpsMode), reflect::PropertyType::Type::T_enum } } },
        { "mode", reflect::Property{ offsetof(EngineSettings, mode), reflect::meta_t { }, "mode", reflect::PropertyType{ "EngineMode", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(EngineMode), reflect::PropertyType::Type::T_enum } } },
        { "renderer", reflect::Property{ offsetof(EngineSettings, renderer), reflect::meta_t { }, "renderer", reflect::PropertyType{ "RendererSettings", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(RendererSettings), reflect::PropertyType::Type::T_type } } },
        { "scene", reflect::Property{ offsetof(EngineSettings, scene), reflect::meta_t { }, "scene", reflect::PropertyType{ "SceneSettings", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(SceneSettings), reflect::PropertyType::Type::T_type } } },
    };
    return s_properties;
}

std::size_t reflect::Type<EngineSettings>::size()
{
    return sizeof(EngineSettings);
}

void reflect::Type<EngineSettings>::from_string(const std::string& str, EngineSettings& type)
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
        int pack;
        stream >> pack;
        type.fps = static_cast<FpsMode>(type.fps);
    }
    {
        int pack;
        stream >> pack;
        type.mode = static_cast<EngineMode>(type.mode);
    }
    {
        std::string pack;
        stream >> pack;
        type.renderer.from_string(pack);
    }
    {
        std::string pack;
        stream >> pack;
        type.scene.from_string(pack);
    }
}

std::string reflect::Type<EngineSettings>::to_string(const EngineSettings& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << static_cast<int>(type.fps);
    stream << static_cast<int>(type.mode);
    stream << static_cast<std::string>(type.renderer);
    stream << static_cast<std::string>(type.scene);
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<EngineSettings>::from_json(const std::string& json, EngineSettings& type)
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
            if (key == "fps")
            {
                std::string temp;
                reflect::encoding::json::Deserializer::parse(value, temp);
                stringToEnum(value, type.fps);
            }
            if (key == "mode")
            {
                std::string temp;
                reflect::encoding::json::Deserializer::parse(value, temp);
                stringToEnum(value, type.mode);
            }
            if (key == "renderer") type.renderer.from_json(value);
            if (key == "scene") type.scene.from_json(value);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<EngineSettings>::to_json(const EngineSettings& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"EngineSettings\"" << "," << std::endl;
    stream << offset << "    " << "\"fps\": " << reflect::encoding::json::Serializer::to_string(enumToString(type.fps)) << "," << std::endl;
    stream << offset << "    " << "\"mode\": " << reflect::encoding::json::Serializer::to_string(enumToString(type.mode)) << "," << std::endl;
    stream << offset << "    " << "\"renderer\": " << type.renderer.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"scene\": " << type.scene.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& EngineSettings::type_meta() const { return reflect::Type<EngineSettings>::meta(); }
const char* const EngineSettings::type_name() const { return reflect::Type<EngineSettings>::name(); }
const reflect::properties_t& EngineSettings::type_properties() const { return reflect::Type<EngineSettings>::properties(); }
EngineSettings::operator std::string() const { return reflect::Type<EngineSettings>::to_string(*this); }
void EngineSettings::from_string(const std::string& str)
{
    reflect::Type<EngineSettings>::from_string(str, *this);
    type_initialize();
}
void EngineSettings::from_json(const std::string& json)
{
    reflect::Type<EngineSettings>::from_json(json, *this);
    type_initialize();
}
std::string EngineSettings::to_json(const std::string& offset) const { return reflect::Type<EngineSettings>::to_json(*this, offset); }