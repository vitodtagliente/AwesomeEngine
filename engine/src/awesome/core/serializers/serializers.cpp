#include "serializers.h"

const TypeDescriptor& ColorSerializer::get_descriptor() const
{
    return ColorSerializerType::descriptor();
}

fields_t ColorSerializer::get_fields() const
{
    return ColorSerializerType::fields(this);
}

void ColorSerializer::autoload()
{
    TypeFactory::load<ColorSerializer>();
}

const TypeDescriptor& ColorSerializer::descriptor()
{
    return ColorSerializerType::descriptor();
}

TypeDescriptor ColorSerializerType::s_typeDescriptor{ ColorSerializerType::registerTypeDescriptor };

const TypeDescriptor& ColorSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t ColorSerializerType::fields(const ColorSerializer* const pointer)
{
    return fields_t();
}

void ColorSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "ColorSerializer";
    descriptor->size = sizeof(ColorSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("ColorSerializer", []() -> const TypeDescriptor& { return ColorSerializerType::s_typeDescriptor; }, []() -> void* { return new ColorSerializer(); });
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
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Component"));

    TypeFactoryRegister::hook("UuidSerializer", []() -> const TypeDescriptor& { return UuidSerializerType::s_typeDescriptor; }, []() -> void* { return new UuidSerializer(); });
}

