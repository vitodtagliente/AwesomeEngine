// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "asset_database.h"
#pragma warning(disable: 4100)

const reflect::meta_t& reflect::Type<AssetRecord>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<AssetRecord>::name() { return "AssetRecord"; }

const reflect::properties_t& Type<AssetRecord>::properties()
{
    static reflect::properties_t s_properties {
        { "id", reflect::Property{ offsetof(AssetRecord, id), reflect::meta_t { }, "id", reflect::PropertyType{ "uuid", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(uuid), reflect::PropertyType::Type::T_type } } },
        { "type", reflect::Property{ offsetof(AssetRecord, type), reflect::meta_t { }, "type", reflect::PropertyType{ "int", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(int), reflect::PropertyType::Type::T_int } } },
    };
    return s_properties;
}

std::size_t reflect::Type<AssetRecord>::size()
{
    return sizeof(AssetRecord);
}

void reflect::Type<AssetRecord>::from_string(const std::string& str, AssetRecord& type)
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
        type.id.from_string(pack);
    }
    stream >> type.type;
}

std::string reflect::Type<AssetRecord>::to_string(const AssetRecord& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    stream << static_cast<std::string>(type.id);
    stream << type.type;
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<AssetRecord>::from_json(const std::string& json, AssetRecord& type)
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
            if (key == "id") type.id.from_json(value);
            if (key == "type") reflect::encoding::json::Deserializer::parse(value, type.type);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<AssetRecord>::to_json(const AssetRecord& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"AssetRecord\"" << "," << std::endl;
    stream << offset << "    " << "\"id\": " << type.id.to_json(offset + "    ") << "," << std::endl;
    stream << offset << "    " << "\"type\": " << reflect::encoding::json::Serializer::to_string(type.type) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& AssetRecord::type_meta() const { return reflect::Type<AssetRecord>::meta(); }
const char* const AssetRecord::type_name() const { return reflect::Type<AssetRecord>::name(); }
const reflect::properties_t& AssetRecord::type_properties() const { return reflect::Type<AssetRecord>::properties(); }
AssetRecord::operator std::string() const { return reflect::Type<AssetRecord>::to_string(*this); }
void AssetRecord::from_string(const std::string& str)
{
    reflect::Type<AssetRecord>::from_string(str, *this);
    type_initialize();
}
void AssetRecord::from_json(const std::string& json)
{
    reflect::Type<AssetRecord>::from_json(json, *this);
    type_initialize();
}
std::string AssetRecord::to_json(const std::string& offset) const { return reflect::Type<AssetRecord>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<AssetDatabase>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<AssetDatabase>::name() { return "AssetDatabase"; }

const reflect::properties_t& Type<AssetDatabase>::properties()
{
    static reflect::properties_t s_properties {
        { "path", reflect::Property{ offsetof(AssetDatabase, path), reflect::meta_t { }, "path", reflect::PropertyType{ "std::filesystem::path", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::filesystem::path), reflect::PropertyType::Type::T_unknown } } },
        { "records", reflect::Property{ offsetof(AssetDatabase, records), reflect::meta_t { }, "records", reflect::PropertyType{ "std::vector<AssetRecord>", { 
            reflect::PropertyType{ "AssetRecord", {  }, reflect::PropertyType::DecoratorType::D_raw, sizeof(AssetRecord), reflect::PropertyType::Type::T_type },
        }, reflect::PropertyType::DecoratorType::D_raw, sizeof(std::vector<AssetRecord>), reflect::PropertyType::Type::T_template } } },
    };
    return s_properties;
}

std::size_t reflect::Type<AssetDatabase>::size()
{
    return sizeof(AssetDatabase);
}

void reflect::Type<AssetDatabase>::from_string(const std::string& str, AssetDatabase& type)
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
        type.records.clear();
        std::size_t size;
        stream >> size;
        for (int i = 0; i < size; ++i)
        {
            AssetRecord element;
            {
                std::string pack;
                stream >> pack;
                element.from_string(pack);
            }
            type.records.push_back(std::move(element));
        }
    }
}

std::string reflect::Type<AssetDatabase>::to_string(const AssetDatabase& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    {
        stream << type.records.size();
        for (const auto& element : type.records)
        {
            stream << static_cast<std::string>(element);
        }
    }
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<AssetDatabase>::from_json(const std::string& json, AssetDatabase& type)
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
            if (key == "records") reflect::encoding::json::Deserializer::parse(value, type.records);
            src = src.substr(index + 1);
        }
        else break;
    };
}

std::string reflect::Type<AssetDatabase>::to_json(const AssetDatabase& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"AssetDatabase\"" << "," << std::endl;
    stream << offset << "    " << "\"records\": " << reflect::encoding::json::Serializer::to_string(type.records) << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& AssetDatabase::type_meta() const { return reflect::Type<AssetDatabase>::meta(); }
const char* const AssetDatabase::type_name() const { return reflect::Type<AssetDatabase>::name(); }
const reflect::properties_t& AssetDatabase::type_properties() const { return reflect::Type<AssetDatabase>::properties(); }
AssetDatabase::operator std::string() const { return reflect::Type<AssetDatabase>::to_string(*this); }
void AssetDatabase::from_string(const std::string& str)
{
    reflect::Type<AssetDatabase>::from_string(str, *this);
    type_initialize();
}
void AssetDatabase::from_json(const std::string& json)
{
    reflect::Type<AssetDatabase>::from_json(json, *this);
    type_initialize();
}
std::string AssetDatabase::to_json(const std::string& offset) const { return reflect::Type<AssetDatabase>::to_json(*this, offset); }

const reflect::meta_t& reflect::Type<AssetLoader>::meta()
{
    static reflect::meta_t s_meta {
    };
    return s_meta;
}
const char* const reflect::Type<AssetLoader>::name() { return "AssetLoader"; }

const reflect::properties_t& Type<AssetLoader>::properties()
{
    static reflect::properties_t s_properties {
    };
    return s_properties;
}

std::size_t reflect::Type<AssetLoader>::size()
{
    return sizeof(AssetLoader);
}

void reflect::Type<AssetLoader>::from_string(const std::string& str, AssetLoader& type)
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

std::string reflect::Type<AssetLoader>::to_string(const AssetLoader& type)
{
    reflect::encoding::ByteBuffer buffer;
    reflect::encoding::OutputByteStream stream(buffer);
    stream << name();
    
    
    return std::string(reinterpret_cast<const char*>(&stream.getBuffer()[0]), stream.getBuffer().size());
}

void reflect::Type<AssetLoader>::from_json(const std::string& json, AssetLoader& type)
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

std::string reflect::Type<AssetLoader>::to_json(const AssetLoader& type, const std::string& offset)
{
    std::stringstream stream;
    stream << "{" << std::endl;
    stream << offset << "    " << "\"type_id\": " << "\"AssetLoader\"" << "," << std::endl;
    stream << offset << "}";
    return stream.str();
}

const reflect::meta_t& AssetLoader::type_meta() const { return reflect::Type<AssetLoader>::meta(); }
const char* const AssetLoader::type_name() const { return reflect::Type<AssetLoader>::name(); }
const reflect::properties_t& AssetLoader::type_properties() const { return reflect::Type<AssetLoader>::properties(); }
AssetLoader::operator std::string() const { return reflect::Type<AssetLoader>::to_string(*this); }
void AssetLoader::from_string(const std::string& str)
{
    reflect::Type<AssetLoader>::from_string(str, *this);
    type_initialize();
}
void AssetLoader::from_json(const std::string& json)
{
    reflect::Type<AssetLoader>::from_json(json, *this);
    type_initialize();
}
std::string AssetLoader::to_json(const std::string& offset) const { return reflect::Type<AssetLoader>::to_json(*this, offset); }