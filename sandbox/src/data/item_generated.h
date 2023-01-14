// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct EnumType<enum class ItemCategory>
{
    static const char* name();
    static const  enum_values_t& values();
};

struct __ItemCategoryEnum : RegisteredInEnumFactory<enum class ItemCategory>
{
    static bool registered() { return value; };
};

template <>
struct EnumType<enum class EquipmentPositionType>
{
    static const char* name();
    static const  enum_values_t& values();
};

struct __EquipmentPositionTypeEnum : RegisteredInEnumFactory<enum class EquipmentPositionType>
{
    static bool registered() { return value; };
};

template <>
struct EnumType<enum class ConsumableEffectType>
{
    static const char* name();
    static const  enum_values_t& values();
};

struct __ConsumableEffectTypeEnum : RegisteredInEnumFactory<enum class ConsumableEffectType>
{
    static bool registered() { return value; };
};

struct __ConsumableItemDataType : RegisteredInTypeFactory<__ConsumableItemDataType>
{
    __ConsumableItemDataType() = delete;

    static const TypeDefinition& type();
    static bool registered() { return value; };
};

struct __EquipmentItemDataType : RegisteredInTypeFactory<__EquipmentItemDataType>
{
    __EquipmentItemDataType() = delete;

    static const TypeDefinition& type();
    static bool registered() { return value; };
};

struct __ItemType : RegisteredInTypeFactory<__ItemType>
{
    __ItemType() = delete;

    static const TypeDefinition& type();
    static bool registered() { return value; };
};

