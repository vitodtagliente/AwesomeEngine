// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "base_camera.h"

const meta_t& BaseCamera::getTypeMeta() const { return BaseCameraType::meta(); }
const char* BaseCamera::getTypeName() const { return BaseCameraType::name(); }
const properties_t BaseCamera::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties = Component::getTypeProperties();
    properties.insert(std::make_pair<std::string, Property>("color", Property("color", NativeType::NT_int, "int", sizeof(int), origin + offsetof(BaseCamera, color), {
    })));
    return properties;
}
std::size_t BaseCamera::getTypeSize() const { return sizeof(BaseCamera); }

BaseCameraType::BaseCameraType()
{
    TypeFactoryRegister::load(BaseCameraType::name(), []() -> const meta_t& { return BaseCameraType::meta(); }, []() -> IType* { return BaseCameraType::instantiate(); });
}

BaseCamera* const BaseCameraType::instantiate()
{
    return new BaseCamera();
}

const meta_t& BaseCameraType::meta()
{
    static meta_t s_meta{
    };
    return s_meta;
}

const char* BaseCameraType::name() { return "BaseCamera"; }

BaseCameraType __basecamera_type;

