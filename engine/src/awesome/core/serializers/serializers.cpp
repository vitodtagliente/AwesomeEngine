#include "serializers.h"

const TypeDescriptor& AssetSerializer::get_descriptor() const
{
    return AssetSerializerType::descriptor();
}

fields_t AssetSerializer::get_fields() const
{
    return AssetSerializerType::fields(this);
}

void AssetSerializer::autoload()
{
    TypeFactory::load<AssetSerializer>();
}

const TypeDescriptor& AssetSerializer::descriptor()
{
    return AssetSerializerType::descriptor();
}

TypeDescriptor AssetSerializerType::s_typeDescriptor{ AssetSerializerType::registerTypeDescriptor };

const TypeDescriptor& AssetSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t AssetSerializerType::fields(const AssetSerializer* const pointer)
{
    return fields_t();
}

void AssetSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "AssetSerializer";
    descriptor->size = sizeof(AssetSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("AssetSerializer", []() -> const TypeDescriptor& { return AssetSerializerType::s_typeDescriptor; }, []() -> void* { return new AssetSerializer(); });
}

const TypeDescriptor& GraphicsSerializer::get_descriptor() const
{
    return GraphicsSerializerType::descriptor();
}

fields_t GraphicsSerializer::get_fields() const
{
    return GraphicsSerializerType::fields(this);
}

void GraphicsSerializer::autoload()
{
    TypeFactory::load<GraphicsSerializer>();
}

const TypeDescriptor& GraphicsSerializer::descriptor()
{
    return GraphicsSerializerType::descriptor();
}

TypeDescriptor GraphicsSerializerType::s_typeDescriptor{ GraphicsSerializerType::registerTypeDescriptor };

const TypeDescriptor& GraphicsSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t GraphicsSerializerType::fields(const GraphicsSerializer* const pointer)
{
    return fields_t();
}

void GraphicsSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "GraphicsSerializer";
    descriptor->size = sizeof(GraphicsSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("GraphicsSerializer", []() -> const TypeDescriptor& { return GraphicsSerializerType::s_typeDescriptor; }, []() -> void* { return new GraphicsSerializer(); });
}

const TypeDescriptor& MathSerializer::get_descriptor() const
{
    return MathSerializerType::descriptor();
}

fields_t MathSerializer::get_fields() const
{
    return MathSerializerType::fields(this);
}

void MathSerializer::autoload()
{
    TypeFactory::load<MathSerializer>();
}

const TypeDescriptor& MathSerializer::descriptor()
{
    return MathSerializerType::descriptor();
}

TypeDescriptor MathSerializerType::s_typeDescriptor{ MathSerializerType::registerTypeDescriptor };

const TypeDescriptor& MathSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t MathSerializerType::fields(const MathSerializer* const pointer)
{
    return fields_t();
}

void MathSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "MathSerializer";
    descriptor->size = sizeof(MathSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("MathSerializer", []() -> const TypeDescriptor& { return MathSerializerType::s_typeDescriptor; }, []() -> void* { return new MathSerializer(); });
}

const TypeDescriptor& UuidSerializer::get_descriptor() const
{
    return UuidSerializerType::descriptor();
}

fields_t UuidSerializer::get_fields() const
{
    return UuidSerializerType::fields(this);
}

void UuidSerializer::autoload()
{
    TypeFactory::load<UuidSerializer>();
}

const TypeDescriptor& UuidSerializer::descriptor()
{
    return UuidSerializerType::descriptor();
}

TypeDescriptor UuidSerializerType::s_typeDescriptor{ UuidSerializerType::registerTypeDescriptor };

const TypeDescriptor& UuidSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t UuidSerializerType::fields(const UuidSerializer* const pointer)
{
    return fields_t();
}

void UuidSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "UuidSerializer";
    descriptor->size = sizeof(UuidSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("UuidSerializer", []() -> const TypeDescriptor& { return UuidSerializerType::s_typeDescriptor; }, []() -> void* { return new UuidSerializer(); });
}

