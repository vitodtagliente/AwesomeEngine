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
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("ColorSerializer", []() -> const TypeDescriptor& { return ColorSerializerType::s_typeDescriptor; }, []() -> void* { return new ColorSerializer(); });
}

const TypeDescriptor& TextureCoordsSerializer::get_descriptor() const
{
    return TextureCoordsSerializerType::descriptor();
}

fields_t TextureCoordsSerializer::get_fields() const
{
    return TextureCoordsSerializerType::fields(this);
}

void TextureCoordsSerializer::autoload()
{
    TypeFactory::load<TextureCoordsSerializer>();
}

const TypeDescriptor& TextureCoordsSerializer::descriptor()
{
    return TextureCoordsSerializerType::descriptor();
}

TypeDescriptor TextureCoordsSerializerType::s_typeDescriptor{ TextureCoordsSerializerType::registerTypeDescriptor };

const TypeDescriptor& TextureCoordsSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t TextureCoordsSerializerType::fields(const TextureCoordsSerializer* const pointer)
{
    return fields_t();
}

void TextureCoordsSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "TextureCoordsSerializer";
    descriptor->size = sizeof(TextureCoordsSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("TextureCoordsSerializer", []() -> const TypeDescriptor& { return TextureCoordsSerializerType::s_typeDescriptor; }, []() -> void* { return new TextureCoordsSerializer(); });
}

const TypeDescriptor& TextureRectSerializer::get_descriptor() const
{
    return TextureRectSerializerType::descriptor();
}

fields_t TextureRectSerializer::get_fields() const
{
    return TextureRectSerializerType::fields(this);
}

void TextureRectSerializer::autoload()
{
    TypeFactory::load<TextureRectSerializer>();
}

const TypeDescriptor& TextureRectSerializer::descriptor()
{
    return TextureRectSerializerType::descriptor();
}

TypeDescriptor TextureRectSerializerType::s_typeDescriptor{ TextureRectSerializerType::registerTypeDescriptor };

const TypeDescriptor& TextureRectSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t TextureRectSerializerType::fields(const TextureRectSerializer* const pointer)
{
    return fields_t();
}

void TextureRectSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "TextureRectSerializer";
    descriptor->size = sizeof(TextureRectSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("TextureRectSerializer", []() -> const TypeDescriptor& { return TextureRectSerializerType::s_typeDescriptor; }, []() -> void* { return new TextureRectSerializer(); });
}

const TypeDescriptor& TransformSerializer::get_descriptor() const
{
    return TransformSerializerType::descriptor();
}

fields_t TransformSerializer::get_fields() const
{
    return TransformSerializerType::fields(this);
}

void TransformSerializer::autoload()
{
    TypeFactory::load<TransformSerializer>();
}

const TypeDescriptor& TransformSerializer::descriptor()
{
    return TransformSerializerType::descriptor();
}

TypeDescriptor TransformSerializerType::s_typeDescriptor{ TransformSerializerType::registerTypeDescriptor };

const TypeDescriptor& TransformSerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t TransformSerializerType::fields(const TransformSerializer* const pointer)
{
    return fields_t();
}

void TransformSerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "TransformSerializer";
    descriptor->size = sizeof(TransformSerializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("TransformSerializer", []() -> const TypeDescriptor& { return TransformSerializerType::s_typeDescriptor; }, []() -> void* { return new TransformSerializer(); });
}

const TypeDescriptor& Vec2Serializer::get_descriptor() const
{
    return Vec2SerializerType::descriptor();
}

fields_t Vec2Serializer::get_fields() const
{
    return Vec2SerializerType::fields(this);
}

void Vec2Serializer::autoload()
{
    TypeFactory::load<Vec2Serializer>();
}

const TypeDescriptor& Vec2Serializer::descriptor()
{
    return Vec2SerializerType::descriptor();
}

TypeDescriptor Vec2SerializerType::s_typeDescriptor{ Vec2SerializerType::registerTypeDescriptor };

const TypeDescriptor& Vec2SerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t Vec2SerializerType::fields(const Vec2Serializer* const pointer)
{
    return fields_t();
}

void Vec2SerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Vec2Serializer";
    descriptor->size = sizeof(Vec2Serializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("Vec2Serializer", []() -> const TypeDescriptor& { return Vec2SerializerType::s_typeDescriptor; }, []() -> void* { return new Vec2Serializer(); });
}

const TypeDescriptor& Vec3Serializer::get_descriptor() const
{
    return Vec3SerializerType::descriptor();
}

fields_t Vec3Serializer::get_fields() const
{
    return Vec3SerializerType::fields(this);
}

void Vec3Serializer::autoload()
{
    TypeFactory::load<Vec3Serializer>();
}

const TypeDescriptor& Vec3Serializer::descriptor()
{
    return Vec3SerializerType::descriptor();
}

TypeDescriptor Vec3SerializerType::s_typeDescriptor{ Vec3SerializerType::registerTypeDescriptor };

const TypeDescriptor& Vec3SerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t Vec3SerializerType::fields(const Vec3Serializer* const pointer)
{
    return fields_t();
}

void Vec3SerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Vec3Serializer";
    descriptor->size = sizeof(Vec3Serializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("Vec3Serializer", []() -> const TypeDescriptor& { return Vec3SerializerType::s_typeDescriptor; }, []() -> void* { return new Vec3Serializer(); });
}

const TypeDescriptor& Vec4Serializer::get_descriptor() const
{
    return Vec4SerializerType::descriptor();
}

fields_t Vec4Serializer::get_fields() const
{
    return Vec4SerializerType::fields(this);
}

void Vec4Serializer::autoload()
{
    TypeFactory::load<Vec4Serializer>();
}

const TypeDescriptor& Vec4Serializer::descriptor()
{
    return Vec4SerializerType::descriptor();
}

TypeDescriptor Vec4SerializerType::s_typeDescriptor{ Vec4SerializerType::registerTypeDescriptor };

const TypeDescriptor& Vec4SerializerType::descriptor()
{
    return s_typeDescriptor;
}

fields_t Vec4SerializerType::fields(const Vec4Serializer* const pointer)
{
    return fields_t();
}

void Vec4SerializerType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "Vec4Serializer";
    descriptor->size = sizeof(Vec4Serializer);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Serializer"));

    TypeFactoryRegister::hook("Vec4Serializer", []() -> const TypeDescriptor& { return Vec4SerializerType::s_typeDescriptor; }, []() -> void* { return new Vec4Serializer(); });
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

